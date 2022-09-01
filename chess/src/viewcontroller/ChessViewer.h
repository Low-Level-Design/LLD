#ifndef _CHESS_VIEWER_H
#define _CHESS_VIEWER_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      24 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/TttContext.h
*  @brief     Implements the TttContext class.
*  
*/

#include "game/Chess.h"
#include <memory>

class ChessViewer 
{
public:
    virtual void displayBoard(const ChessBoard &b) const = 0;

};

class ChessScreenViewer : public ChessViewer
{
public:
    explicit ChessScreenViewer() {}
    void displayBoard(const ChessBoard &b) const override;

};

class ChessGUIViewer : public ChessViewer
{
public:
    explicit ChessGUIViewer() {}
    void displayBoard(const ChessBoard &b) const override;

};

class ChessViewerFactory
{
public:
    static shared_ptr<ChessViewer> makeChessViewer(const string &param);

private:
    static shared_ptr<ChessScreenViewer> makeChessScreenViewer()
    {
        return make_shared<ChessScreenViewer>();
    }

    static shared_ptr<ChessGUIViewer> makeChessGUIViewer()
    {
        return make_shared<ChessGUIViewer>();
    }

};

#endif