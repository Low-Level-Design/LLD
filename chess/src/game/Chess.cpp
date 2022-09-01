#ifndef _CHESS_CPP
#define _CHESS_CPP

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      24 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/Tictactoe.cpp
*  @brief     Implements the classes in Tictactoe.h.
*  
*/

#include "Chess.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

Player::Player(const string &name, Color color) : m_account(name)
{
    m_color = color;
    
}

void Player::print() const 
{
    m_account.print();
    if (m_color == e_WHITE) {
        cout << "Color : WHITE" << endl;
    } else if (m_color == e_BLACK) {
        cout << "Color : BLACK" << endl;
    } else if (m_color == e_NOCOLOR) {
        cout << "Color : NOCOLOR" << endl;
    }
}

Account::Account(const string &name)
{
    m_name = name;
    m_email = "";
    m_password = "";
    m_id = m_idGenerator++;
    m_phone = "";

}

void Account::print() const
{
    cout << "Id :" << m_id << endl;
    cout << "Name :" << m_name <<endl;
    
}

int Account::m_idGenerator = 0;


void ChessGame::updateGlobalStats(const Player &winPlayer, 
                                        const Player &losePlayer)
{
  m_stats.updateStats(winPlayer.getName(), m_challengeScore);
  m_stats.updateStats(losePlayer.getName(), -m_challengeScore);

}

ChessGame::ChessGame() : m_chessBoard()
{
    m_status = e_ACTIVE;
    m_challengeScore = 0;
}

void ChessGame::addPlayer(const Player &pl)
{
    m_players.push_back(pl);
}

Move::Move (const Player &turnPlayer, const shared_ptr<Piece> &movedPiece,
                 const CellPosition &start, const CellPosition &end, 
                 const shared_ptr<Piece> &killedPiece)
{
    m_turnPlayer = turnPlayer;
    m_piece = movedPiece;
    m_killedPiece = killedPiece;
    m_start  = start;
    m_end    = end;


}



bool ChessGame::move(const Player &pl, CellPosition start, CellPosition end)
{
    bool isValidMove =  m_chessBoard.isValidMove(pl, start, end);

    shared_ptr<Piece> killedPiece = nullptr;
    shared_ptr<Piece> startPiece = nullptr;
    if (isValidMove) {
        //do the actual move 
        startPiece = m_chessBoard.getCell(start.getX(), 
                                         start.getY()).getPiece();
        m_chessBoard.setPiece(start, nullptr);

        //contain the piece if possible
        killedPiece = m_chessBoard.getCell(end.getX(), end.getY()).getPiece();
        m_chessBoard.setPiece(end, startPiece);
    }

    //create the move object
    Move move(pl, startPiece, start, end, killedPiece);
    addMove(move);
    return true;
}

bool ChessBoard::isValidMove(const Player &pl, const CellPosition &start, 
                                    const CellPosition&end)
{
    //The start and end position should not be same
    if ((start.getX() == end.getX()) && (start.getY() == end.getY())) {
        return false;
    }

    //The start position must have a piece
    if (m_board[start.getX()][start.getY()].isEmpty()) {
        return false;

    }
    //check at source : source piece color should be same as the player color
    if (pl.getColor() != m_board[start.getX()][start.getY()].getPieceColor()) {
        return false;
    }

    //The target cell should be empty or have opposite color piece
    if (!m_board[end.getX()][end.getY()].isEmpty() && (pl.getColor() == 
             m_board[end.getX()][end.getY()].getPieceColor())) {


        return false;
    }

    //see the piece at th start position
    shared_ptr<Piece> piece = m_board[start.getX()][start.getY()].getPiece();


    //call the respective piece valid move
    return piece->isValidMove(pl, start, end, 
               m_board[end.getX()][end.getY()].getPiece(), *this);


}

void ChessBoard::setPiece(const CellPosition &at, const shared_ptr<Piece> &pi)
{
    m_board[at.getX()][at.getY()].setPiece(nullptr);
}

ChessBoard::ChessBoard()
{
    m_boardSize = 8;
    m_board = vector<vector<Cell>>(m_boardSize, vector<Cell>(m_boardSize));

    /* add position to the Cells of the chessboard */
    for (int i = 0 ; i < m_boardSize ; i++) {
        for (int j = 0 ; j < m_boardSize ; j++) {
            CellPosition cp(i, j);
            m_board[i][j].setPos(cp);

        }
    }

    // Add the pieces of the white player . That is 
    // row 0 and 1
    // 0,0 & 0, 7 -> rook
    // 0,1 & 0, 6 -> knight
    // 0,2 & 0, 5 -> bishop
    // 0,3        -> queen
    // 0,4        -> king

    shared_ptr<Rook> rook1 = make_shared<Rook>(e_WHITE);
    m_board[0][0].setPiece(rook1);
    
    shared_ptr<Rook> rook2 = make_shared<Rook>(e_WHITE);
    m_board[0][7].setPiece(rook2);
     
    shared_ptr<Knight> kn1 = make_shared<Knight>(e_WHITE);
    m_board[0][1].setPiece(kn1);
    shared_ptr<Knight> kn2 = make_shared<Knight>(e_WHITE);
    m_board[0][6].setPiece(kn2);
    
    shared_ptr<Bishop> b1 = make_shared<Bishop>(e_WHITE);
    m_board[0][2].setPiece(b1);
    shared_ptr<Bishop> b2 = make_shared<Bishop>(e_WHITE);
    m_board[0][5].setPiece(b2);
    shared_ptr<King> king = make_shared<King>(e_WHITE);
    m_board[0][4].setPiece(king);
    shared_ptr<Queen> queen = make_shared<Queen>(e_WHITE);
    m_board[0][3].setPiece(queen);

    //row 1 for white player - all pawn
    for (int j = 0 ; j < m_boardSize ; j++) {
        shared_ptr<Pawn> p1 = make_shared<Pawn>(e_WHITE);
        m_board[1][j].setPiece(p1);
    }

    //black player row 6 - all pawn
    for (int j = 0 ; j < m_boardSize ; j++) {
        shared_ptr<Pawn> p1 = make_shared<Pawn>(e_WHITE);
        m_board[6][j].setPiece(p1);
    }

    //black player row - 7
    shared_ptr<Rook> rookb1 = make_shared<Rook>(e_BLACK);
    m_board[7][0].setPiece(rookb1);
    shared_ptr<Rook> rookb2 = make_shared<Rook>(e_BLACK);
    m_board[7][7].setPiece(rookb2);

    shared_ptr<Knight> knb1 = make_shared<Knight>(e_BLACK);
    m_board[7][1].setPiece(knb1);
    shared_ptr<Knight> knb2 = make_shared<Knight>(e_BLACK);
    m_board[7][6].setPiece(knb2);
    
    shared_ptr<Bishop> bb1 = make_shared<Bishop>(e_BLACK);
    m_board[7][2].setPiece(bb1);
    shared_ptr<Bishop> bb2 = make_shared<Bishop>(e_BLACK);
    m_board[7][5].setPiece(bb2);
    shared_ptr<King> bKing = make_shared<King>(e_BLACK);
    m_board[7][4].setPiece(bKing);
    shared_ptr<King> bQueen = make_shared<King>(e_BLACK);
    m_board[7][3].setPiece(bQueen);
    

}

Cell::Cell() : m_pos(-1, -1)
{
    m_piece = nullptr;

}

CellPosition::CellPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

Piece::Piece()
{
    m_color = e_NOCOLOR;
}

Piece::Piece(Color color)
{
    m_color = color;
}

void Knight::print() const
{
    if (m_color == e_BLACK) {
        cout << "BKN";
    } else if (m_color == e_WHITE) {
        cout << "WKN";
    } else {
        cout << "";
    }

}

void Bishop::print() const
{
    if (m_color == e_BLACK) {
        cout << "BB";
    } else if (m_color == e_WHITE) {
        cout << "WB";
    } else {
        cout << "";
    }


}

void Rook::print() const
{
    if (m_color == e_BLACK) {
        cout << "BR";
    } else if (m_color == e_WHITE) {
        cout << "WR";
    } else {
        cout << "";
    }


}

void King::print() const
{
    if (m_color == e_BLACK) {
        cout << "BKI";
    } else if (m_color == e_WHITE) {
        cout << "WKI";
    } else {
        cout << "";
    }

}

void Queen::print() const
{
    if (m_color == e_BLACK) {
        cout << "BQ";
    } else if (m_color == e_WHITE) {
        cout << "WQ";
    } else {
        cout << "";
    }


}

void Pawn::print() const
{
    if (m_color == e_BLACK) {
        cout << "BP";
    } else if (m_color == e_WHITE) {
        cout << "WP";
    } else {
        cout << "";
    }

}

bool Piece::checkForHorizontalMovement(const CellPosition &start, 
            const CellPosition &end, const ChessBoard &chessBoard) const
{
    int xAdd = 0;
    if (start.getY() == end.getY()) {
        xAdd = (end.getX() - start.getX()) / abs (start.getY() - end.getY());
        for (int i = start.getX(); i != end.getX() ; i = i + xAdd) {
            if (!(chessBoard.getCell(i, start.getY()).isEmpty())) {
                return false;
            }   
        }
    } else {
        return false;
    }

    return true;

}
                  
bool Piece::checkForVerticalMovement(const CellPosition &start, 
            const CellPosition &end, const ChessBoard &chessBoard) const
{
    
    int yAdd = 0;

    if (start.getX() == end.getX()) {
        yAdd = (end.getY() - start.getY()) / abs(start.getY() - end.getY());
        for (int j = start.getY() ; j != end.getY() ; j = j + yAdd) {
            if (!(chessBoard.getCell(start.getX(), j).isEmpty())) {
                return false;
            }
        }
    } else {
        return false;
    }

    return true;

}

bool Piece::checkForDiagonalMovement(const CellPosition &start, 
                const CellPosition &end, const ChessBoard &chessBoard) const
{
    //There should not be any piece in between
    int xAdd = (end.getX() - start.getX())/abs(start.getX() - end.getX());
    int yAdd = (end.getY() - start.getY())/abs(start.getY() - end.getY());

    for (int i = start.getX() ; i != end.getX() ; i = i + xAdd) {
        for (int j = start.getY() ; j != end.getY() ; i = i + yAdd) {
            if (!chessBoard.getCell(i, j).isEmpty()) {
                return false;
            }
        }
    }

    return true;

}

bool Queen::isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const
{
    //check for vertical
    bool isVerticalMovement = false;

    if ((start.getX() == end.getX()) && (start.getY() != end.getY())) {
        isVerticalMovement = true;
    }

    bool isHorizontalMovement = false;

    if ((start.getY() == end.getY()) && (start.getX() != end.getX())) {
        isHorizontalMovement = true;
    }

    bool isDiagonalMovement = false;

    int xAbsDiff = abs(start.getX() - end.getX());
    int yAbsDiff = abs(start.getY() - end.getY());

    if (xAbsDiff == yAbsDiff) {
        isDiagonalMovement = true;
    }

    if (!isHorizontalMovement && !isHorizontalMovement && !isDiagonalMovement) {
        return false;
    }

    if (isHorizontalMovement) {
        bool checkResult = checkForHorizontalMovement(start, end, chessBoard);
        if (!checkResult) {
            return false;
        }
    }

    if (isVerticalMovement) {
        bool checkResult = checkForVerticalMovement(start, end, chessBoard);
        if (!checkResult) {
            return false;
        }
    }

    
    return checkForDiagonalMovement(start, end, chessBoard);


    
}

bool King::isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const
{
    int xDiff = abs(start.getX()-end.getX());
    int yDiff = abs(start.getY()-end.getY());

    if (xDiff + yDiff == 1 || (xDiff == 1 && yDiff == 1)) {
        return true;
    }

    return false;
    
}

bool Pawn::isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const
{
    //Pawn movement
    //Pawn can move forward to an empty position . If this is that 
    //pawn's first move then it can move forward by 2 positions else 
    // by one position

    if (m_numMoves == 0) {
        if ((end.getX() - start.getX() == 2) && (end.getY() == start.getY())) {
            return true;
        }

    }

    if ((end.getX() - start.getX() == 1) && (end.getY() == start.getY())) {
        return true;
    }


    //Pawn Capturing
    ////Please note EnPassant capturing is ignored to avoid complexity
    //A pawn can capture diagonally to capture
    if (endPiece == nullptr) {
        return false;
    }
    if (pl.getColor() != endPiece->getColor()) {
        if ((end.getX() - start.getX() == 1) && (
                    end.getY() - start.getY() == 1)) {
            return true;
        }

        if ((end.getX() - start.getX() == 1) && (
                    start.getY() - end.getY() == 1)) {
            return true;
        }
    }

    return false;
    
}

bool Rook::isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const
{
    //Rook can only mov ein the horizontal and vertical position

    // x1 != x2  && y1 != y2
    if ((start.getX() != end.getX()) && (start.getY() != end.getY())) {
        return false;

    }

    bool checkVRes = checkForVerticalMovement(start, end, chessBoard);
    if (!checkVRes) {
        return false;
    }

    return checkForHorizontalMovement(start, end, chessBoard);
    

}

bool Bishop::isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const
{
    // The final position should be diagonal to the start position
    int xDiff = abs(start.getX()-end.getX());
    int yDiff = abs(start.getY()-end.getY());

    if (xDiff != yDiff) {
        return false;
    }


    //Check for presence of piece for diagonal movement
    return checkForDiagonalMovement(start, end, chessBoard);
    
    
}

bool Knight::isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const
{
    int xDiff = abs(start.getX()-end.getX());
    int yDiff = abs(start.getY()-end.getY());

    if (xDiff*yDiff == 3) {
        return true;
    }

    return false;
    
}

void Statistics::printStats() const
{
    
    for (auto it = m_playerStats.begin(); it != m_playerStats.end() ; ++it) {
        cout << it->first << "'s score:" << it->second<<endl;
    }

    
}


#endif
