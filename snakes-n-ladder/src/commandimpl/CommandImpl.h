#ifndef _COMMAND_IMPL_H
#define _COMMAND_IMPL_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      13 Aug 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/command/CommandImpl.h
*  @brief     Contains the command hierarchy for all the allowed commands.
*  
*/

#include <string>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include "game/SNLContext.h"

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

  explicit CommandImpl(SNLContext &snlContext);
  virtual ~CommandImpl() = 0;
  virtual bool execute() = 0;
  void printValidCommands();

protected:
  SNLContext &m_snlContext; /**< game context reference */
};

/**
 * @brief Implements the 'quit' command of snakes-n-ladder.
 * 
 */

class QuitCommand : public CommandImpl
{
public:
  explicit QuitCommand(SNLContext &snlContext);
  ~QuitCommand();
  bool execute() override;
};

/**
 * @brief Implements the 'register_players' command of snakes-n-ladder.
 * 
 */

class RegisterPlayersCommand : public CommandImpl
{

public:
  explicit RegisterPlayersCommand(SNLContext &snlContext);
  ~RegisterPlayersCommand();
  bool execute() override;

};

/**
 * @brief Implements the 'start_game' command of snakes-n-ladder.
 * 
 */
class StartGameCommand : public CommandImpl
{

public:
  explicit StartGameCommand(SNLContext &snlContext); 
  ~StartGameCommand();
  bool execute() override;
};

/**
 * @brief Implements the 'print_stats' command of snakes-n-ladder.
 * 
 */
class PrintStatsCommand : public CommandImpl
{

public:
  explicit PrintStatsCommand(SNLContext &snlContext);
  ~PrintStatsCommand();
  bool execute() override;
};

/**
 * @brief Implements the 'game_settings' command of snakes-n-ladder.
 * 
 */
class GameSettingsCommand : public CommandImpl
{

public:
  explicit GameSettingsCommand(SNLContext &snlContext);
  ~GameSettingsCommand();
  bool execute() override;
};

/**
 * @brief Implements the 'roll_dice' command of a snakes-n-ladder game.
 * 
 */

class RollDiceCommand : public CommandImpl
{

public:
  explicit RollDiceCommand(SNLContext &snlContext);
  ~RollDiceCommand();
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
  explicit CommandFactory(SNLContext &gc);
  virtual ~CommandFactory();

  shared_ptr<CommandImpl> makeQuitCommand(const string &param);
  shared_ptr<CommandImpl> makeRegisterPlayersCommand(const string &param);
  shared_ptr<CommandImpl> makeStartGameCommand(const string &param);
  shared_ptr<CommandImpl> makePrintStatsCommand(const string &param);
  shared_ptr<CommandImpl> makeGameSettingsCommand(const string &param);
  shared_ptr<CommandImpl> makeRollDiceCommand(const string &param);

private:
  typedef shared_ptr<CommandImpl> (CommandFactory::*FACTORY_PTMF)(
                                              const string &param);
  typedef unordered_map<string, FACTORY_PTMF> COMMAND_MAP;

  
  COMMAND_MAP m_commandMap; /**< Map of string and command creation function */

  SNLContext &m_snlContext; /**< Game context */
};

#endif
