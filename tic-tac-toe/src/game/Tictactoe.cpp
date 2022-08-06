#ifndef _TIC_TAC_TOE_CPP
#define _TIC_TAC_TOE_CPP

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      24 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/Tictactoe.cpp
*  @brief     Implements the classes in Tictactoe.h.
*  
*/

#include "Tictactoe.h"
#include <string>
#include <vector>
#include <iostream>

/**
 * @brief Construct a new Player:: Player object.
 * 
 * @param pName Name of the player.
 * @param symbol Player symbol while playing.
 */
Player::Player(const string &pName, char symbol) 
              : m_name(pName), m_pSymbol(symbol)
{
  m_stats["win"] = 0;
  m_stats["loss"] = 0;
  m_stats["draw"] = 0;
  m_stats["played"] = 0;
}

/**
 * @brief Prints the stats of the player.
 * 
 */

void Player::printStats()
{
  cout << endl;
  cout << "Played :" << m_stats["played"] << endl;
  cout << "Wins   :" << m_stats["win"] << endl;
  cout << "Losses :" << m_stats["loss"] << endl;
  cout << "Draws  :" << m_stats["draw"] << endl;
  cout << endl;
}

/**
 * @brief Increments a particular stats of the player.
 * 
 * @param incrStr String containing the category of the stats. It can be 
 *                "Played", "Wins" , "Losses" , "Draws"
 */

void Player::incrementStats(const string &incrStr)
{
  m_stats[incrStr]++;
}

Player::~Player() = default;

/**
 * @brief Constructs a new Game Board:: Game Board object.
 * 
 * @param bSize Size of the game board.
 */

GameBoard::GameBoard(int bSize) : m_boardSize(bSize)
{
  m_board = vector<vector<char>>(m_boardSize, vector<char>(m_boardSize, '#'));
}

GameBoard::~GameBoard() = default;

/**
 * @brief Resets the gameboard. This function sets all the values of the 
 *        gameboard cell to '#' . '#' represents an empty cell.
 * 
 */

void GameBoard::reset()
{
  for (int i = 0; i < m_boardSize; i++)
  {
    for (int j = 0; j < m_boardSize; j++)
    {
      m_board[i][j] = '#';
    }
  }
}

/**
 * @brief Displays a game board.
 * 
 */

void GameBoard::displayBoard() const
{
  cout << endl;
  for (int i = 0; i < m_boardSize; i++)
  {
    for (int j = 0; j < m_boardSize; j++)
    {
      if (m_board[i][j] == '#')
      {
        cout << "_";
      }
      else
      {
        cout << m_board[i][j];
      }

      cout << " ";
    }
    cout << "\n";
  }
}

/**
 * @brief Places symbol at a particular cell on the game board.
 * 
 * @param x x co-ordinate of the cell.
 * @param y y co-ordinate of the cell.
 * @param symbol symbol to be placed at the particular cell.
 */

void GameBoard::placeInputAt(int x, int y, char symbol)
{
  if (m_board[x][y] != '#')
  {
    throw GameBoard::BoardException("Cell not empty.");
  }
  m_board[x][y] = symbol;
}

/**
 * @brief Returns the size of the board.
 * 
 * @return const int 
 */

const int GameBoard::getBoardSize() const
{
  return m_boardSize;
}

/**
 * @brief Checks whether the board has any ampty cell.
 * 
 * @return true 
 * @return false 
 */

const bool GameBoard::hasEmptyCell() const
{
  for (int i = 0; i < m_boardSize; i++)
  {
    for (int j = 0; j < m_boardSize; j++)
    {
      if (m_board[i][j] == '#')
      {
        return true;
      }
    }
  }
  return false;
}

/**
 * @brief Checks if the player with symbol sym is a winner.
 * 
 * @details Checking whether the current player is a winner involves the 
 *          following steps:
 *            - Checking for consecutive symbols == sym in a row.
 *            - Checking for consecutive symbols == sym in a col.
 *            - Checking for consecutive symbols == sym in a l-r diagonal.
 *            - Checking for consecutive symbols == sym in a r-l diagonal.
 * 
 * @param sym Symbol which is being placed now.
 * @return true 
 * @return false 
 */

const bool GameBoard::checkIsWinner(char sym) const
{
  // check the rows
  for (int i = 0; i < m_boardSize; i++)
  {
    int countSymb = 0;
    for (int j = 0; j < m_boardSize; j++)
    {
      if (m_board[i][j] == sym)
      {
        countSymb++;
      }
    }
    if (countSymb == 3)
    {
      return true;
    }
  }

  // check the cols
  for (int j = 0; j < m_boardSize; j++)
  {
    int countSymb = 0;
    for (int i = 0; i < m_boardSize; i++)
    {
      if (m_board[i][j] == sym)
      {
        countSymb++;
      }
    }
    if (countSymb == 3)
    {
      return true;
    }
  }

  // check the l-r diagonal
  int countSymb = 0;
  for (int i = 0; i < m_boardSize; i++)
  {
    if (m_board[i][i] == sym)
    {
      countSymb++;
    }
  }
  if (countSymb == 3)
  {
    return true;
  }

  countSymb = 0;
  // check the r-l diagonal
  for (int i = 0; i < m_boardSize; i++)
  {
    if (m_board[i][m_boardSize - i - 1] == sym)
    {
      countSymb++;
    }
  }
  if (countSymb == 3)
  {
    return true;
  }
  return false;
}

/**
 * @brief Construct a new Ttt Game:: Ttt Game object.
 * 
 */

TttGame::TttGame() : m_board(3), m_winner(""), m_gameStr("")
{
  m_playersAllowed = 2;
}

TttGame::~TttGame() = default;

/**
 * @brief Add a player to the tic-tac-tie game.
 * 
 * @param player Player to be added.
 */

void TttGame::addPlayer(const Player &player)
{
  // handle more than 2 player exception . Can't happen in this case
  m_players.emplace_back(player);
}

/**
 * @brief Wrapper function to display a board.
 * 
 */

void TttGame::displayBoard() const
{
  m_board.displayBoard();
}

/**
 * @brief Displays the turn of the ith Player.
 * 
 * @param i Player index 
 */

void TttGame::displayTurn(int i) const
{
  Player pl = m_players[i];
  cout << endl;
  cout << pl.getName() << "' turn |"
       << " symbol : " << pl.getPSymbol() << endl;
  cout << "Enter x y [ 0 - 2 ] : Example 2 0" << endl;
  promptUser();
}

/**
 * @brief Returns the board size.
 * 
 * @return const int 
 */

const int TttGame::getBoardSize() const
{
  return m_board.getBoardSize();
}

/**
 * @brief Checks the current game status after the ith player has played
 *        its turn. 
 * 
 * @param playerInd Player Index.
 * @return true 
 * @return false 
 */

bool TttGame::checkGameStatus(int playerInd)
{
  // is Any cell empty ? draw case. store the result
  bool bHasEmptyCell = m_board.hasEmptyCell();
  if (!bHasEmptyCell)
  {
    for (int i = 0; i < m_players.size(); i++)
    {
      m_players[i].incrementStats("draw");
      m_players[i].incrementStats("played");
    }
    m_gameStr = "Draw";
    return false;
  }
  // get the player and player symbol
  char pSymbol = m_players[playerInd].getPSymbol();

  bool isThisPlayerAWinner = m_board.checkIsWinner(pSymbol);
  if (isThisPlayerAWinner)
  {
    m_gameStr = "Wins";
    m_winner = m_players[playerInd].getName();
    m_players[playerInd].incrementStats("win");
    for (int i = 0; i < m_players.size(); i++)
    {
      m_players[i].incrementStats("played");
    }

    // increment Losses for other players
    for (int i = 0; i < m_players.size(); i++)
    {
      if (i == playerInd)
      {
        continue;
      }
      m_players[i].incrementStats("loss");
    }
    return false;
  }
  return true;
}

/**
 * @brief Prints the supported commands of the game.
 * 
 */

void TttGame::printValidCommands() const
{
  cout << "quit : to exit the game" << endl;
}

/**
 * @brief Wrapper function to place input on the Game Board.
 * 
 * @param x x co-ordinate of the cell, where the input will be placed.
 * @param y y co-ordinate of the cell, where the input will be placed.
 * @param playerInd Index of the player playing now.
 * @return true 
 * @return false 
 */

bool TttGame::placeInput(int x, int y, int playerInd)
{
  Player pl = m_players[playerInd];
  m_board.placeInputAt(x, y, pl.getPSymbol());
  return checkGameStatus(playerInd);
}

/**
 * @brief Shows the result of a game.
 * 
 */

void TttGame::showResult() const
{
  cout << endl;
  cout << "Game Result:" << endl;
  if (m_gameStr == "Draw")
  {
    cout << "The game was a DRAW. No winner" << endl;
  }
  else
  {
    cout << m_winner << "  won the game" << endl;
  }
  cout << endl;
}

/**
 * @brief Resets a game to its initial state, to make it ready to start a 
 *        new game.
 * 
 */

void TttGame::resetGame()
{
  m_board.reset();
  m_gameStr = "";
  m_winner = "";
}

/**
 * @brief Prints a game prompt to the user.
 * 
 */

void TttGame::promptUser() const
{
  cout << endl;
  cout << "game #> ";
}

/**
 * @brief Returns the number of players in the current game.
 * 
 * @return const int 
 */

const int TttGame::getNumberOfPlayers() const
{
  return m_players.size();
}

/**
 * @brief Returns the number of players allowed in any game.
 * 
 * @return const int 
 */

const int TttGame::getPlayersAllowed() const
{
  return m_playersAllowed;
}

/**
 * @brief Returns the ith player of the game.
 * 
 * @param i Player index
 * @return const Player 
 */

const Player TttGame::getIthPlayer(int i) const
{
  // if i not in range raise exception. This case cannot rise as we are
  // registering player first
  return m_players[i];
}

#endif
