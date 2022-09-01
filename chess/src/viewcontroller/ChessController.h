#ifndef _CHESS_CONTROLLER_H
#define _CHESS_CONTROLLER_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      24 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/TttContext.h
*  @brief     Implements the TttContext class.
*  
*/

#include "game/Chess.h"
#include "ChessViewer.h"
#include <memory>

using namespace std;

/**
 * @brief This class acts as a wrapper to call everything required to 
 *        execute a particular command.
 * 
 */

class ChessController
{

public:
  ChessController();
  ~ChessController();
  bool registerPlayer();
  bool startGame();
  bool printStats() const;
  bool move(const string &param, const Player &pl);

private:

  void extractMoveCoordinates(const string &paramStr, CellPosition &start, 
                               CellPosition &end);


  shared_ptr<ChessGame> m_chessGame; /**< Reference to ChessGame object. */
  shared_ptr<ChessViewer> m_gameViewer;
};

#endif
