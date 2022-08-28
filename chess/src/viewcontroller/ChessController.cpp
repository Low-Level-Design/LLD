#ifndef _CHESS_CONTROLLER_CPP
#define _CHESS_CONTROLLER_CPP

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      24 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/TttContext.cpp
*  @brief     Implements the classes in TttContext.h.
*  
*/

#include "ChessController.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
using namespace std;

/**
 * @brief Construct a new Ttt Context:: Ttt Context object.
 * 
 */
ChessController::ChessController()
{
  
  //tttGame = nullptr;
}

ChessController::~ChessController() = default;

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

bool ChessController::registerPlayer()
{
  cout << "Player registration done" << endl;
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
bool ChessController::startGame()
{
  cout << "Game started" << endl;
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

bool ChessController::printStats() const
{
  cout << "Stats Printed" << endl;
  return true;
}

#endif
