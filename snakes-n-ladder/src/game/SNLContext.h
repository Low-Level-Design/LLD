#ifndef _SNL_CONTEXT_H
#define _SNL_CONTEXT_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      13 Aug 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/SNLContext.h
*  @brief     Implements the SNLContext class.
*  
*/

#include "SnakesNLadder.h"
#include <memory>

using namespace std;

/**
 * @brief This class acts as a wrapper to call everything required to 
 *        execute a particular command. It also holds the SNLViewer reference
 *        to display Snakes and ladder board.  
 * 
 */

class SNLContext
{
public:
  SNLContext();
  ~SNLContext();
  bool registerPlayers();
  bool startGame();
  bool printStats() const;
  bool storeGameSettings();

private:
  shared_ptr<SNLGame> m_snlGame; /**< Reference to snlGame object. */
  //have an instance of the viewer
};

#endif
