#ifndef _COMMAND_IMPL_H
#define _COMMAND_IMPL_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      23 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/command/CommandImpl.h
*  @brief     Contains the command hierarchy for all the allowed commands.
*  
*/

#include <string>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include "game/TttContext.h"

using namespace std;

/**
 * @brief Base class of command hierarchy.
 * 
 * @details Implements the funtions abstract functions to execute each 
 *          command.
 */

class CommandImpl
{
  friend class CommandFactory;

public:
  class InvalidCommandException : public std::domain_error
  {
  public:
    explicit InvalidCommandException(const string &message) : 
                                      std::domain_error(message) {}
  };

  explicit CommandImpl(TttContext &tttContext);
  virtual ~CommandImpl() = 0;
  virtual bool execute() = 0;
  void printValidCommands();

protected:
  TttContext &m_tttContext; /**< game context reference */
};

/**
 * @brief Implements the 'quit' command of tic-tac-toe.
 * 
 */

class QuitCommand : public CommandImpl
{
public:
  explicit QuitCommand(TttContext &tttContext);
  ~QuitCommand();
  bool execute() override;
};

/**
 * @brief Implements the 'register_players' command of tic-tac-toe.
 * 
 */

class RegisterPlayerCommand : public CommandImpl
{

public:
  explicit RegisterPlayerCommand(TttContext &tttContext);
  ~RegisterPlayerCommand();
  bool execute() override;

};

/**
 * @brief Implements the 'start_game' command of tic-tac-toe.
 * 
 */
class StartGameCommand : public CommandImpl
{

public:
  explicit StartGameCommand(TttContext &tttContext); 
  ~StartGameCommand();
  bool execute() override;
};

/**
 * @brief Implements the 'print_stats' command of tic-tac-toe.
 * 
 */
class PrintStatsCommand : public CommandImpl
{

public:
  explicit PrintStatsCommand(TttContext &tttContext);
  ~PrintStatsCommand();
  bool execute() override;
};

/**
 * @brief Implements the factory method class for the command hierarchy.
 * 
 * @details Takes the parsed commandline input and then creates the right
 *          command based on the input string. This implementation uses 
 *          'Factory Method Pattern'.
 * 
 */

class CommandFactory
{

public:
  shared_ptr<CommandImpl> makeCommand(const string &commandStr);
  explicit CommandFactory(TttContext &gc);
  virtual ~CommandFactory();

  shared_ptr<CommandImpl> makeQuitCommand(const string &param);
  shared_ptr<CommandImpl> makeRegisterPlayerCommand(const string &param);
  shared_ptr<CommandImpl> makeStartGameCommand(const string &param);
  shared_ptr<CommandImpl> makePrintStatsCommand(const string &param);

private:
  typedef shared_ptr<CommandImpl> (CommandFactory::*FACTORY_PTMF)(
                                              const string &param);
  typedef unordered_map<string, FACTORY_PTMF> COMMAND_MAP;

  
  COMMAND_MAP m_commandMap; /**< Map of string and command creation function */

  TttContext &m_tttContext; /**< Game context */
};

#endif
