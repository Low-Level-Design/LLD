#ifndef _TTT_CONTEXT_H
#define _TTT_CONTEXT_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      24 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/TttContext.h
*  @brief     Implements the TttContext class.
*  
*/

#include "Tictactoe.h"
#include <memory>

using namespace std;

/**
 * @brief This class acts as a wrapper to call everything required to 
 *        execute a particular command.
 * 
 */

class TttContext
{
public:
  TttContext();
  ~TttContext();
  bool registerPlayer();
  bool startGame();
  bool printStats() const;

private:
  bool processInputString(const string &str, int &x, int &y, int maxXy);

private:
  shared_ptr<TttGame> tttGame; /**< Reference to tttGame object. */
};

#endif
