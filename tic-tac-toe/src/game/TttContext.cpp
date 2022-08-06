#ifndef _TTT_CONTEXT_CPP
#define _TTT_CONTEXT_CPP

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      24 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/TttContext.cpp
*  @brief     Implements the classes in TttContext.h.
*  
*/

#include "TttContext.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
using namespace std;

/**
 * @brief Construct a new Ttt Context:: Ttt Context object.
 * 
 */
TttContext::TttContext()
{
  tttGame = nullptr;
}

TttContext::~TttContext() = default;

/**
 * @brief Implements the register_player functionality.
 * 
 * @details For this implementation of tic-tac-toe, only 2 players are allowed.
 *          This function takes details of 2 players as input and then creates
 *          the 2 Player objects and adds them to the Game object.
 * 
 * @return true 
 * @return false 
 */

bool TttContext::registerPlayer()
{
  // initialize the game if its not initialized
  if (tttGame == nullptr)
  {
    tttGame = shared_ptr<TttGame>(new TttGame());
  }
  else
  {
    // Handle already registered case
    int noOfPlayers = tttGame->getNumberOfPlayers();
    if (noOfPlayers > 0)
    {
      throw Player::PlayerException("Players are already registered.");
    }
  }

  // Register all players for the game

  int allowedPlayers = tttGame->getPlayersAllowed();
  for (int i = 0; i < allowedPlayers; i++)
  {
    cout << endl;
    cout << "Register Player " << i + 1 << endl;
    cout << "-----------------" << endl;
    string playerName = "";
    string playerSymbol = "";

    cout << "\nEnter name > ";
    getline(cin, playerName);

    cout << "\nEnter symbol > ";
    getline(cin, playerSymbol);

    // initialize the player
    Player player(playerName, playerSymbol[0]);
    tttGame->addPlayer(player);

    // print display message
    cout << "\nPlayer " << player.getName() << " added |  Symbol : "
         << player.getPSymbol() << endl;
    cout << endl;
  }
  return true;
}

/**
 * @brief Processes an input string and extracts the x and y co-ordinate values
 *        . This function also tests for the different error cases while
 *        extracting the values from the string.
 * 
 * @param str Co-ordinate string containing the x and y values.
 * @param x   Reference to hold the extracted x value.
 * @param y   Reference to hold the extracted y value.
 * @param maxXy Max allowed value of x and y.
 * @return true 
 * @return false 
 */

bool TttContext::processInputString(const string &str, int &x, int &y
                                    , int maxXy)
{
  stringstream ss(str);
  string iStr = "";

  vector<int> coords;
  while (ss >> iStr)
  {
    try
    {
      int val = stoi(iStr);
      if (val < 0 || val >= maxXy)
      {
        return false;
      }
      coords.emplace_back(val);
    }
    catch (...)
    {
      return false;
    }
  }

  if (coords.size() > 2)
  {
    return false;
  }

  x = coords[0];
  y = coords[1];
  return true;
}

/**
 * @brief Implements the start_game functionality.
 * 
 * @details This function implements the game loop for one game
 *          One game loop contains:
 *            while the game is on:
 *              - prompt the user.
 *              - display board.
 *              - take x & y.
 *              - place Input & check game status.
 *              - display board.
 *              - If game ends:
 *                - display game result.
 *                - exit.
 * 
 * @return true 
 * @return false 
 */
bool TttContext::startGame()
{
  // handle the check for player regitration .tttGame should be
  // initialized before coming here
  // play one game

  if (tttGame == nullptr) {
    //Game not initialized. raise exception
    
    throw TttGame::GameException(
        "Game not initialized yet. Please register the players and try again!");
  }
  bool isGameOn = true;
  int playerTurn = 0;
  int playerSize = tttGame->getNumberOfPlayers();
  tttGame->printValidCommands();
  while (isGameOn)
  {
    tttGame->promptUser();
    tttGame->displayBoard();
    tttGame->displayTurn(playerTurn);
    string placeInStr;
    getline(cin, placeInStr);
    if (placeInStr == "quit")
    {
      break;
    }
    int x = -1, y = -1;
    int boardSize = tttGame->getBoardSize();
    bool status = processInputString(placeInStr, x, y, boardSize);
    if (!status)
    {
      cout << endl;
      cout << "[Error] Incorrect values provided. Enter again." << endl;
      continue;
    }
    try
    {
      isGameOn = tttGame->placeInput(x, y, playerTurn);
    }
    catch (GameBoard::BoardException &ce)
    {
      cout << endl;
      cout << "[Error] " << ce.what() << endl;
      continue;
    }
    if (!isGameOn)
    {
      tttGame->displayBoard();
      tttGame->showResult();
      tttGame->resetGame();
    }
    playerTurn = (playerTurn + 1) % playerSize;
  }
  return true;
}

/**
 * @brief This function implements the functionality of the command
 *        print_stats.
 * 
 * @details It goes through each player of the game and prints their stats.
 * 
 * @return true 
 * @return false 
 */

bool TttContext::printStats() const
{
  if (tttGame == nullptr)
  {
    cout << "[Info] No game stats available." << endl;
    cout << endl;
  }
  else
  {
    cout << endl;
    cout << "Game Stats" << endl;
    cout << "----------" << endl;

    int nPlayers = tttGame->getNumberOfPlayers();
    for (int i = 0; i < nPlayers; i++)
    {
      Player pl = tttGame->getIthPlayer(i);
      cout << pl.getName() << "'s stats:" << endl;
      pl.printStats();
    }
  }
  return true;
}

#endif
