#ifndef _CHESS_VIEWER_CPP
#define _CHESS_VIEWER_CPP

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      24 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/TttContext.h
*  @brief     Implements the TttContext class.
*  
*/

#include "ChessViewer.h"
#include <iostream>

using namespace std;

void ChessScreenViewer::displayBoard(const ChessBoard &b) const
{
    //display the board on screen
    //Piece : R , B , KI , Q, KN , P
    //White Piece : WR , WB , WKI , WQ, WKN , WP
    //Black Piece : BR , BB , BKI , BQ, BKN , BP

    int boardSize = b.getBoardSize();
    for (int i = 0 ; i < boardSize ; i++) {
        for (int j = 0 ; j < boardSize ; j++) {
            b.getCell(i,j).print();
            cout << "\t";
        }
        cout <<endl;
    }

}

void ChessGUIViewer::displayBoard(const ChessBoard &b) const
{
    cout << "No Implementation" << endl;
}

shared_ptr<ChessViewer> ChessViewerFactory::makeChessViewer(
                                const string &str)
{
    if (str == "screen") {
        return makeChessScreenViewer();
    } else if (str == "gui") {
        return makeChessGUIViewer();

    } else {
        //handle exception
    }

    return nullptr;

}

#endif