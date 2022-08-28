#ifndef _EVENT_HANDLER_CPP
#define _EVENT_HANDLER_CPP

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      23 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/EventHandler.cpp
*  @brief     Contains the implementation for classes in EventHandler.h.
*  
*/

#include <iostream>
#include "EventHandler.h"
#include <memory>
using namespace std;

class Reactor;

/**
 * @brief Construct a new Event Handler:: Event Handler object.
 * 
 */
EventHandler::EventHandler() : m_chessControl(), m_commandFactory(m_chessControl)
{
  m_isUserPrompted = false;
}

EventHandler::~EventHandler()
{
}

/**
 * @brief Handles the command inputs from the user.
 * 
 * @details Takes command input, creates the right CommandImpl class from the 
 *          command input and then executes the command. Also, does the error
 *          handling for various errors while executing the commands. 
 * 
 * @param reactor Pointer to the reactor loop object.
 */

void EventHandler::handleInput(Reactor *reactor)
{
  promptUser();
  string input;
  if (!getInput(input)) {
    reactor->endEventLoop();
    return;    
  }
  
  shared_ptr<CommandImpl> command = nullptr;
  try {

    //create a command
    command = m_commandFactory.makeCommand(input);
    bool execRes = command->execute();
    if (!execRes) {
      //quit command case    
      reactor->endEventLoop();
    } 
  // } catch (CommandImpl::InvalidCommandException  &ic) {
  //   cout << "\n[Error] Invalid command '" << ic.what() <<"'"<< endl;
  //   cout << endl;
  //   command->printValidCommands();
  // } catch (Player::PlayerException &pe) {
  //   cout << "\n[Error] "<< pe.what() << endl;
  //   cout << endl;
  //   command->printValidCommands();
  // } catch(TttGame::GameException &ge) {
  //   cout << "\n[Error] "<< ge.what() << endl;
  //   cout << endl;
  //   command->printValidCommands();
  // 
  } catch(...)  {
    cout << "\n[Error] Something went wrong. Please try again!" <<endl;
    cout << endl;
  }

}

/**
 * @brief Prompts the supported command prompt & tic-tac-toe prompt 
 *        to the user.
 * 
 */

void EventHandler::promptUser()
{
  if (!m_isUserPrompted) {
    cout << "Commands:" <<endl; 
    cout << endl;
    cout << "register_players : to register all players." << endl;
    cout << "start_game       : to start a new game." << endl;  
    cout << "quit             : to quit this session." << endl;  
    cout << "print_stats      : to print game stats." << endl;  
    cout << endl;
    m_isUserPrompted = true;
  }
  cout << "chess > "; 
  
}

/**
 * @brief Takes command input from the user.
 * 
 * @param inputStr String to hold the received input command.
 * @return true 
 * @return false 
 */

bool EventHandler::getInput(string &inputStr)
{
  getline(cin, inputStr);
  return !(cin.eof());
}

#endif
