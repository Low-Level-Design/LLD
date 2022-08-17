#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      13 Aug 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/EventHandler.h
*  @brief     Implements the EventHandler class.
*  
*/

#include<memory>
#include<string>
#include "Reactor.h"
#include "game/SNLContext.h"
#include "commandimpl/CommandImpl.h"

class Reactor;
using namespace std;

/**
 * @brief Implements the EventHandler class.
 * 
 * @details This class is responsible for:
 *          - Taking input from user.
 *          - create the necessary objects to handle and execute the user
 *            command.  
 * 
 */

class EventHandler {

public:
  EventHandler();
  ~EventHandler();

  void handleInput(Reactor *reactor);

private:
  void promptUser();
  bool getInput(string &inputStr);

private :

  SNLContext m_snlContext; /**< Game context reference. */
  CommandFactory m_commandFactory; /**< Command factory object. */ 
  bool m_isUserPrompted; /**< holds the state whether the user has already been 
                             prompted with the supported commands. */
  
};


#endif
