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

using namespace std;
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
  e_BLACK

};

/*************************CLASSES*******************/

class CellPosition 
{

public:
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
private:
  string m_username;
  string m_password;
  string m_name;
  string m_email;
  string m_phone;

};

class Player
{

public:
private:
  Account m_account;
  Color m_color;
  vector<Piece> m_pieces;

};

/***************
 * ChessBoard related classes
 * *************/

class ChessBoard 
{

public:
private:
  int m_boardSize;
  vector<vector<Cell>> m_board;

};

class Cell 
{

public:
private:
  CellPosition m_pos;
  Piece        m_piece;

};



/***************
 * Piece related classes
 * *************/
class Piece 
{

public:
  bool isValidMove() const;
private:

Color m_color;

};

class King : public Piece 
{

public:
  bool isValidMove() const;
private:

};

class Queen : public Piece 
{

public:
  bool isValidMove() const;
private:

};

class Pawn : public Piece 
{

public:
  bool isValidMove() const;
private:

};

class Rook : public Piece 
{

public:
  bool isValidMove() const;
private:

};

class Bishop : public Piece 
{

public:
  bool isValidMove() const;
private:

};

class Knight : public Piece 
{

public:
  bool isValidMove() const;
private:

};

/***************
 * ChessGame related classes
 * *************/

class Move 
{

public:
private:
  Player m_turn;
  Piece m_piece;
  CellPosition m_start;
  CellPosition m_end;
  Piece m_killedPiece;

};

class ChessGame 
{

public:
private:
  ChessBoard m_chessBoard;
  queue<Player> m_players;
  vector<Move> m_moves;
  GameStatus m_status;
  int m_challengeScore;

};

/***************
 * Statistics related classes
 * *************/

class Statistics 
{

public:
private:
  unordered_map<string, int> m_playerStats;
  vector<string, int> m_rankedPlayers;
  bool m_isStatsChanges;

};

#endif
