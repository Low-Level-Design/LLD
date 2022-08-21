#ifndef _SNL_CONTEXT_CPP
#define _SNL_CONTEXT_CPP

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      13 Aug 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/SNLContext.cpp
*  @brief     Implements the classes in SNLContext.h.
*  
*/

#include "SNLContext.h"
#include "SnakesNLadder.h"
#include "../commandimpl/CommandImpl.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
using namespace std;


  // bool startGame();
  // bool printStats() const;
  // bool storeGameSettings();

/**
 * @brief Construct a new SNL Context:: SNL Context object.
 * 
 */
SNLContext::SNLContext() : m_snlGame(nullptr)
{
  
}

SNLContext::~SNLContext() = default;

/**
 * @brief Implements the register_player functionality.
 * 
 * @details 
 * 
 * @return true 
 * @return false 
 */

bool SNLContext::registerPlayers()
{

  //make sure that GameSettings is initialized before coming here
  //handle errors
  GameSettings *settings = GameSettings::getInstance();
  int diceSize = settings->getDiceSize();
  int boardSize = settings->getBoardSize();
  int noOfSnakes = settings->getNoOfSnakes();
  int noOfLadders = settings->getNoOfLadders();


  if (m_snlGame == nullptr) {
    //Game exception
  
  } else {

    // Handle already registered case
    int noOfPlayers = m_snlGame->getNoOfRegisteredPlayers();
    if (noOfPlayers > 0)
    {
      //throw Player::PlayerException("Players are already registered.");
    }

  }


  int noOfAllowedPlayers = settings->getNoOfPlayers();
  // Make sure that the settings are initialized before this
  // TODO : handle error to ensure settings are initiliazed first 
  
  for (int i = 0 ; i < noOfAllowedPlayers ; i++) {
    cout << endl;
    cout << "Register Player " << i+1 << ":" << endl;
    cout << "------------------" << endl;
    string playerName = "";
    string playerSymbol = "";

    cout << "\nEnter name > ";
    getline(cin, playerName);

    Player pl(playerName);
    m_snlGame->addPlayer(pl);

    //TODO : add Players to the cell
    
    cout << endl <<"Player registered successfully:" <<endl;
    pl.display();
    cout <<endl;

  }

  return true;
}

bool SNLContext::rollDice()
{
  m_snlGame->rollDice();
  return true;
  
}

/**
 * @brief Implements the start_game functionality.
 * 
 * @details 
 * 
 * @return true 
 * @return false 
 */
bool SNLContext::startGame()
{
  bool isGameOver = false;
  CommandFactory cmdFactory(*this);
  while (!isGameOver) {
    m_snlGame->promptUser(); // game# >
    
    //show the board /player's position
    m_snlGame->printPlayersPosition(); // Shabnam : 7,4
    
    //Ninad's Turn : Please roll the dice
    //currPlayer was removed from the front of the queue
    Player currPlayer = m_snlGame->displayPlayerTurn(); 
     
    m_snlGame->promptUser(); // game# > roll_dice
    
    //take the input

    string inputStr;
    getline(cin, inputStr);

    shared_ptr<CommandImpl> cmd = cmdFactory.makeCommand(inputStr);
    
    //roll the dice
    cmd->execute();

    //move after the dice has been rolled

    bool willSamePlayerPlay = false;
    isGameOver = m_snlGame->moveAndCheck(willSamePlayerPlay, currPlayer);

    if (willSamePlayerPlay && !isGameOver) {
      m_snlGame->addPlayerAtFront(currPlayer);
      continue;
    }

    if (isGameOver) {
      //display the results
      //Break and display this game stats. It also updates the global 
      //rank order to make it visible in print_stats. 
      cout << "Game is over" << endl;
      break;
    } else {
      m_snlGame->addPlayer(currPlayer);
    }

  }

  return true;
  
}

/**
 * @brief Implements the game_settings functionality.
 * 
 * @details 
 * 
 * @return true 
 * @return false 
 */
bool SNLContext::storeGameSettings()
{
  GameSettings *settings = GameSettings::getInstance();

  //Game settings header

  cout << endl;
  cout << "GAME SETTINGS"<<endl;
  cout << "-------------"<<endl;

  string noOfPlayers;
  cout << "Enter number of players >";
  getline(cin, noOfPlayers);

  string boardSize;
  cout << "Enter board size >";
  getline(cin, boardSize);

  string diceSize;
  cout << "Enter dice size >";
  getline(cin, diceSize);

  //TODO :  make sure that the no of snakes and ladders are
  // less than or equal the (board size) /2 

  string noOfSnakes;
  cout << "Enter number of snakes >";
  getline(cin, noOfSnakes);

  string noOfLadders;
  cout << "Enter number of ladders >";
  getline(cin, noOfLadders);

  cout << endl;

  
  //register the settings
  settings->setNoOfPlayers(stoi(noOfPlayers));
  settings->setBoardSize(stoi(boardSize));
  settings->setDiceSize(stoi(diceSize));
  settings->setNoOfLadders(stoi(noOfLadders));
  settings->setNoOfSnakes(stoi(noOfSnakes));

  cout << "Game settings registered successfully" << endl;

  if (m_snlGame == nullptr) {
    m_snlGame = std::make_shared<SNLGame>(stoi(boardSize), stoi(diceSize), 
                      stoi(noOfSnakes), stoi(noOfLadders));
  }

  cout << "Game initialization done!" << endl;

  return true;
}


/**
 * @brief This function implements the functionality of the command
 *        print_stats.
 * 
 * @details 
 * 
 * @return true 
 * @return false 
 */

bool SNLContext::printStats() const
{
  cout << "Print Stats" << endl;
  return true;
}

#endif
