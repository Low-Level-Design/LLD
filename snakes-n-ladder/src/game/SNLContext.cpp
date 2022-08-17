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
    m_snlGame = std::make_shared<SNLGame>(diceSize, boardSize, noOfSnakes,
                                  noOfLadders);
  
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
    
    cout << endl <<"Player registered successfully:" <<endl;
    pl.display();
    cout <<endl;

  }

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
  cout << "Game started" << endl;  
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
