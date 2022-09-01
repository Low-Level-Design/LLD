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
#include "commandimpl/CommandImpl.h"
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
  
  m_chessGame = nullptr;
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
  if (m_chessGame == nullptr) {
    m_chessGame = make_shared<ChessGame>();
    m_gameViewer = ChessViewerFactory::makeChessViewer("screen");
  }

  
  cout << endl;
  cout << "PLAYER'S REGISTRATION" <<endl;
  cout << "---------------------" <<endl;

  string playerName = "";
  cout << endl <<"Enter first player name  > " ;
  getline(cin, playerName);
  Player pl(playerName, e_WHITE);
  m_chessGame->addPlayer(pl);

  cout << endl <<"Player registered successfully:" << endl << endl;
  pl.print();
  cout << endl;

  cout << endl <<"Enter second player name  > " ;
  getline(cin, playerName);
  Player pl2(playerName, e_BLACK);
  m_chessGame->addPlayer(pl2);

  cout << endl <<"Player registered successfully:" << endl << endl;
  pl.print();
  cout << endl;


  cout << "Game initialization and player registration done successfully!" 
       << endl;
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
  bool isGameOver = false;

  m_chessGame->promptGame();
  string gameChScore = "";
  cout <<"Enter the challenge score for the game"<< endl;
  getline(cin, gameChScore);

  m_chessGame->setChallengeScore(stoi(gameChScore));
  
  while (!isGameOver) {
    m_chessGame->promptGame();
    cout << endl;
    m_gameViewer->displayBoard(m_chessGame->getChessBoard());
    Player currPlayer = m_chessGame->getCurrentPlayer();
    currPlayer.printTurn();

    //take user input
    //input can be move or quit
    string commandStr = "";
    getline(cin, commandStr);
    
    if (commandStr == "quit") {
      /* 
       * As we have not implemented the complete game here so,
       * we will treat quit as the end of the game
       * The player who quits the game looses the challenge score
       * an other player adds the challenge score.
       */

      cout << "Game Over" << endl;
      if (currPlayer.getColor() == e_WHITE) {
        cout << "BLACK WON" << endl;
        m_chessGame->setStatus(e_BLACK_WON);
      } else if (currPlayer.getColor() == e_BLACK){
        cout << "WHITE WON" << endl;
        m_chessGame->setStatus(e_WHITE_WON);

      }
      //pass the winning and losing player
      m_chessGame->updateGlobalStats(m_chessGame->getCurrentPlayer(), currPlayer);

      break;
    } else if (commandStr.find("move") != string::npos) {
      //create move command and execute
      CommandFactory commFactory(*this);
      shared_ptr<CommandImpl> comm = commFactory.makeCommand(commandStr);
      shared_ptr<MoveCommand> mc = dynamic_pointer_cast<MoveCommand >(comm);
      mc->addPlayer(currPlayer);
      bool isValidMove = mc->execute(); 
      if (!isValidMove) {
        m_chessGame->addPlayerAtFront(currPlayer);
        continue;
      } else {
        //handle command exception and print the supported commands
      } 
    }

  }
  return true;
}

void ChessController::extractMoveCoordinates(const string &paramStr, 
                    CellPosition &start, CellPosition &end)
{
  //extract the coordinates from the string
  stringstream ss(paramStr);

  vector<string> strParts;
  string interStr = "";
  while (getline(ss, interStr, ',')) {
    strParts.emplace_back(interStr);
  }
  //handle move command error exception if the size of strParts is less than 4
  start.setX(stoi(strParts[0]));
  start.setY(stoi(strParts[1]));
  end.setX(stoi(strParts[2]));
  end.setY(stoi(strParts[3]));
  
}

bool ChessController::move(const string &paramStr, const Player &pl)
{
  CellPosition start;
  CellPosition end;

  extractMoveCoordinates(paramStr, start, end);
  return m_chessGame->move(pl, start, end);
  
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
  m_chessGame->printStats();
  return true;
  
}

#endif
