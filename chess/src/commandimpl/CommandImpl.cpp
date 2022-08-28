#ifndef _COMMAND_IMPL_CPP
#define _COMMAND_IMPL_CPP

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      23 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/command/CommandImpl.cpp
*  @brief     Contains the implementation for classes in CommandImpl.h.
*  
*/

#include <iostream>
#include <string>
#include "CommandImpl.h"
using namespace std;

/**
 * Command Factory Implementation.
 */

/**
 * @brief Created the correct CommandImpl class(or its subclasses) based on
 *        the value of commandStr.
 * @details Uses Factory method pattern to make the CommandImpl classes.
 * 
 * @param commandStr  Contains the input command string entered by the user.
 * 
 * @return shared_ptr<CommandImpl> Returns shared pointer of created 
 *         CommandImpl or its derived classes.
 */

shared_ptr<CommandImpl> CommandFactory::makeCommand(const string &commandStr)
{
  //split command str into createStr and param
  //check if createStr & param str are valid else raise 
  //exception
  string createStr = "";
  string param = "";

  if (commandStr == "quit") {
    createStr = commandStr;
  } else if (commandStr == "register_players") {
    createStr = commandStr;
  } else if (commandStr == "start_game") {
    createStr = commandStr;
  } else if (commandStr == "print_stats") {
    createStr = commandStr;
  } else {
    throw CommandImpl::InvalidCommandException(commandStr);
  }

  //populate param string
  if (createStr == "register_players") {
      param =  "";
  } else if (createStr == "quit") {
      param =  "";
  } else if (createStr == "start_game") {
      param =  "";
  } else if (createStr == "print_stats") {
      param =  "";
  } else {
    //raise exception
    throw CommandImpl::InvalidCommandException(commandStr);
  }


  auto findPtr = m_commandMap.find(createStr);
  if (findPtr != m_commandMap.end()) {
    auto fnPtr = m_commandMap[createStr];
    return (this->*fnPtr)(param);
  } else {
    //invalid command exception;
    throw CommandImpl::InvalidCommandException(commandStr);
  }
  return nullptr;
}

/**
 * @brief Construct a new Command Factory:: Command Factory object.
 * 
 * @param gc Empty game context object.
 */

CommandFactory::CommandFactory(ChessController &gc) : 
                m_commandMap(), m_chessControl(gc)
{
  m_commandMap["quit"] = &CommandFactory::makeQuitCommand;
  m_commandMap["register_players"] = &CommandFactory::makeRegisterPlayerCommand;
  m_commandMap["start_game"] = &CommandFactory::makeStartGameCommand;
  m_commandMap["print_stats"] = &CommandFactory::makePrintStatsCommand;
}

CommandFactory::~CommandFactory() = default;

/**
 * @brief Helper function to create QuitCommand.
 * 
 * @param str Param string for the command. Can be empty.
 * @return shared_ptr<CommandImpl> Returns the created QuitCommand shared
 *                                 pointer.
 */

shared_ptr<CommandImpl> CommandFactory::makeQuitCommand(const string &str)
{
  return shared_ptr<CommandImpl>(new QuitCommand(m_chessControl));
}

/**
 * @brief Helper function to create RegisterPlayerCommand.
 * 
 * @param str Param string for the command. Can be empty.
 * @return shared_ptr<CommandImpl> Returns the created RegisterPlayerCommand 
 *                                 shared pointer.
 *                                 
 */

shared_ptr<CommandImpl> CommandFactory::makeRegisterPlayerCommand(
                                        const string &param)
{
  return shared_ptr<CommandImpl>(new RegisterPlayerCommand(
                                      m_chessControl));
}

/**
 * @brief Helper function to create StartGameCommand.
 * 
 * @param str Param string for the command. Can be empty.
 * @return shared_ptr<CommandImpl> Returns the created StartGameCommand 
 *                                 shared pointer.
 *                                 
 */

shared_ptr<CommandImpl> CommandFactory::makeStartGameCommand(
                                           const string &param)
{
  return shared_ptr<CommandImpl>(new StartGameCommand(m_chessControl));
}

/**
 * @brief Helper function to create PrintStatsCommand.
 * 
 * @param str Param string for the command. Can be empty.
 * @return shared_ptr<CommandImpl> Returns the created PrintStatsCommand 
 *                                 shared pointer.
 *                                 
 */

shared_ptr<CommandImpl> CommandFactory::makePrintStatsCommand(
                                           const string &param)
{
  return shared_ptr<CommandImpl>(new PrintStatsCommand(m_chessControl));
}

/**
 * Command Implementation.
 */

/**
 * @brief Construct a new Command Impl:: Command Impl object.
 * 
 * @param tttContext : Empty game context.
 */
CommandImpl::CommandImpl(ChessController &chessControl)
                :m_chessControl(chessControl)
{
}


CommandImpl::~CommandImpl() = default;

/**
 * @brief Prints all the supported commands of tic tac toe.
 * 
 */

void CommandImpl::printValidCommands() 
{
  cout << "Supported Commands:" <<endl; 
  cout << endl;
  cout << "register_players : to register all players." << endl;
  cout << "start_game       : to start a new game." << endl;  
  cout << "quit             : to quit this session." << endl;  
  cout << "print_stats      : to print game stats." << endl;  
  cout << endl;
}

/**
 * @brief Construct a new Quit Command:: Quit Command object.
 * 
 * @param tttContext Empty game context object.
 */
QuitCommand::QuitCommand(ChessController &chessControl)
    :CommandImpl(chessControl)
{
}

QuitCommand::~QuitCommand() = default;

/**
 * @brief  Implements how quit command should be executed.
 * 
 * @return true 
 * @return false 
 */

bool QuitCommand::execute()
{
  return false;
}

/**
 * @brief Construct a new Register Player Command:: Register Player
 *        Command object.
 * 
 * @param tttContext Empty game context object.
 *  
 */

RegisterPlayerCommand::RegisterPlayerCommand(ChessController &chessControl)
    :CommandImpl(chessControl)
{
}

RegisterPlayerCommand::~RegisterPlayerCommand() = default;

/**
 * @brief Implements how to execute register_player command. Logic of 
 *        implementation lies with TttContext class.
 * 
 * @return true 
 * @return false 
 */

bool RegisterPlayerCommand::execute()
{
  //call handleRegister Player on the gamecontext
  return m_chessControl.registerPlayer();
}

/**
 * @brief Construct a new Start Game Command:: Start Game Command object.
 * 
 * @param tttContext Empty game context object.
 */

StartGameCommand::StartGameCommand(ChessController &chessControl)
    :CommandImpl(chessControl)
{
}


StartGameCommand::~StartGameCommand() = default;

/**
 * @brief Implements how to execute start_game command. Logic of
 *        lmplementation lies with TttContext class.
 * 
 * @return true 
 * @return false 
 */

bool StartGameCommand::execute()
{
  //call handleRegister Player on the gamecontext
  return m_chessControl.startGame();
}

/**
 * @brief Construct a new Print Stats Command:: Print Stats Command object.
 * 
 * @param tttContext Empty game context object.
 */
PrintStatsCommand::PrintStatsCommand(ChessController &chessControl)
    :CommandImpl(chessControl)
{
}


PrintStatsCommand::~PrintStatsCommand() = default;

/**
 * @brief Implements how to execute print_stats command. Logic of
 *        lmplementation lies with TttContext class.
 * 
 * @return true 
 * @return false 
 */
bool PrintStatsCommand::execute()
{
  //call handleRegister Player on the gamecontext
  return m_chessControl.printStats();
}

#endif
