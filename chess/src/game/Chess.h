#ifndef _CHESS_H
#define _CHESS_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      24 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/Tictactoe.h
*  @brief     Implements the classes associated with the tic-tac-toe game.
*  
*/

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <memory>

using namespace std;

class Piece;
class Cell;
class ChessBoard;
class Statistics;

/*************************ENUMS*********************/
enum GameStatus 
{
  e_BLACK_WON, 
  e_WHITE_WON, 
  e_ACTIVE,
  e_DRAW,
  e_PAUSED,
  e_FORFEITED,
  e_REGISGNED

};

enum Color 
{
  e_WHITE,
  e_BLACK,
  e_NOCOLOR

};

/*************************CLASSES*******************/

class CellPosition 
{

public:
  explicit CellPosition(int x, int y);
  explicit CellPosition() {}

  void setX(int x) 
  {
    m_x = x;
  }

  void setY(int y) 
  {
    m_y = y;
  }

  //getters

  const int getX() const
  {
    return m_x;

  }

  const int getY() const
  {
    return m_x;

  }
  

private:
  int m_x;
  int m_y;

};


/***************
 * Player related classes
 * *************/

class Account 
{

public:
  explicit Account(const string &name);
  explicit Account() 
  {
    m_username = "";
    m_password = "";
    m_name = "";
    m_email = "";
    m_phone = "";
  }
  void print() const;

  void printTurn() const
  {
    cout << m_name << "'s turn. Please move" << endl;
  }

  const string &getName() const
  {
    return m_name;
  }
private:
  string m_username;
  string m_password;
  string m_name;
  string m_email;
  string m_phone;
  int    m_id;
  static int m_idGenerator;

};

class Player
{

public:
  void print() const;
  explicit Player(const string &name, Color color);
  explicit Player(): m_account()
  {
    m_color = e_NOCOLOR;

  }
  void printTurn() const
  {
    m_account.printTurn();
  }

  const Color getColor() const
  {
    return m_color;
  }

  const string &getName() const
  {
    return m_account.getName();
  }
  

private:
  Account m_account;
  Color m_color;
  vector<Piece> m_pieces;

};

/***************
 * Piece related classes
 * *************/
class Piece 
{

public:
  explicit Piece();
  explicit Piece(Color color);
  bool isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const
  {
    return false;
  }
  virtual void print() const
  {
    cout << "";
  }

  Color getColor() const
  {
    return m_color;
  }

protected:
  bool checkForHorizontalMovement(const CellPosition &start, 
            const CellPosition &end, const ChessBoard &chessBoard) const;
                  
  bool checkForVerticalMovement(const CellPosition &start, 
            const CellPosition &end, const ChessBoard &chessBoard) const;

  bool checkForDiagonalMovement(const CellPosition &start, 
            const CellPosition &end, const ChessBoard &chessBoard) const;
  
protected:

  Color m_color;

};

class King : public Piece 
{

public:
  void print() const override;
  explicit King(Color color) : Piece(color)
  {}
  bool isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const;


};

class Queen : public Piece 
{

public:
  void print() const override;
  explicit Queen(Color color) : Piece(color)
  {}
  bool isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const;


};

class Pawn : public Piece 
{

public:
  void print() const override;
  explicit Pawn(Color color) : Piece(color)
  {
    m_numMoves = 0;
  }
  bool isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end , const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const;
private:
  int m_numMoves;

};

class Rook : public Piece 
{

public:
  void print() const override;
  explicit Rook(Color color) : Piece(color)
  {}
  bool isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const;
private:

};

class Bishop : public Piece 
{

public:
  void print() const override;
  explicit Bishop(Color color) : Piece(color)
  {}
  bool isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const;
private:

};

class Knight : public Piece 
{

public:
  void print() const override;
  explicit Knight(Color color) : Piece(color)
  {}
  bool isValidMove(const Player &pl, const CellPosition &start, 
            const CellPosition &end, const shared_ptr<Piece> &endPiece,
            const ChessBoard &chessBoard) const;
private:

};

/***************
 * ChessBoard related classes
 * *************/

class ChessBoard 
{

public:


  explicit ChessBoard();
  const int getBoardSize() const
  {
      return m_boardSize;
  }

  const Cell &getCell(int i, int j) const
  {
    return m_board[i][j];
  }

  bool isValidMove(const Player &pl, const CellPosition &start, 
                            const CellPosition&end);

  void setPiece(const CellPosition &at, const shared_ptr<Piece> &piece);

private:
  int m_boardSize;
  vector<vector<Cell>> m_board;

};

class Cell 
{

public:
  explicit Cell();

  //setter

  void setPos(const CellPosition &pos) 
  {
    m_pos = pos;
  }

  void setPiece(const shared_ptr<Piece> &pi) 
  {
    m_piece = pi;
  }

  Color getPieceColor() const
  {
    if (m_piece == nullptr) {
      return e_NOCOLOR;
    }

    return m_piece->getColor();

  }
  void print() const
  {
    if (m_piece == nullptr) {
      cout << "";
      return;
    }
    m_piece->print();
  }

  bool isEmpty() const
  {
    return (m_piece == nullptr);
  }

  const shared_ptr<Piece> &getPiece() const
  {
    return m_piece;
  } 

private:
  CellPosition m_pos;
  shared_ptr<Piece>   m_piece;

};

/***************
 * Statistics related classes
 * *************/

class Statistics 
{

public:

  explicit Statistics() {}
  void updateStats(const string &name, int score)
  {
    m_playerStats[name] += score;
  }

  void printStats() const;


private:
  unordered_map<string, int> m_playerStats;
 
};

/***************
 * ChessGame related classes
 * *************/

class Move 
{

public:
  explicit Move (const Player &turnPlayer, const shared_ptr<Piece> &movedPiece,
                 const CellPosition &start, const CellPosition &end, 
                 const shared_ptr<Piece> &killedPiece);
private:
  Player m_turnPlayer;
  shared_ptr<Piece> m_piece;
  CellPosition m_start;
  CellPosition m_end;
  shared_ptr<Piece> m_killedPiece;

};


class ChessGame 
{

public:
  explicit ChessGame();
  void addPlayer(const Player &pl);

  const ChessBoard &getChessBoard() const
  {
    return m_chessBoard;
  }

  const Player getCurrentPlayer()
  {
    Player pl = m_players.front();
    m_players.pop_front();
    return pl;

  }

  void addPlayerAtFront(const Player &pl) 
  {
    m_players.push_front(pl);

  }

  void promptGame() const
  {
    cout << "game # > ";
  }

  void addMove(const Move &move) 
  {
    m_moves.emplace_back(move);
  }

  void setStatus(GameStatus gStatus) 
  {
    m_status = gStatus;
  }

  void setChallengeScore(int challengeScore)
  {
    m_challengeScore = challengeScore;
  }

  void printStats() const
  {
    m_stats.printStats();
  }

  bool move(const Player &pl, CellPosition start, CellPosition end);
  void updateGlobalStats(const Player &winPlayer, 
                                        const Player &losePlayer);
                    


private:
  ChessBoard m_chessBoard;
  deque<Player> m_players;
  vector<Move> m_moves;
  GameStatus m_status;
  int m_challengeScore;
  Statistics m_stats;

};



#endif
