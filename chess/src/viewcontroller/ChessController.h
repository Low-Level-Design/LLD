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

//#include "src/Tictactoe.h"
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



private:
  //shared_ptr<TttGame> tttGame; /**< Reference to tttGame object. */
};

#endif
