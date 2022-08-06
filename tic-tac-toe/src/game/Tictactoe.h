#ifndef _TIC_TAC_TOE_H
#define _TIC_TAC_TOE_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      24 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/Tictactoe.h
*  @brief     Implements the classes associated with the tic-tac-toe game.
*  
*/

#include <string>
#include <vector>
#include <unordered_map>

/**
 * @brief Implements the player class of tic-tac-toe.
 * 
 */

using namespace std;
class Player
{

public:
  class PlayerException : public std::domain_error
  {
  public:
    PlayerException(const string &errorMssg) : std::domain_error(errorMssg)
    {
    }
  };

  explicit Player(const string &Name, char symbol);
  ~Player();

  const char getPSymbol() const
  {
    return m_pSymbol;
  }

  const string getName() const
  {
    return m_name;
  }

  void printStats();

  void incrementStats(const string &incrStr);

private:
  string m_name; /**< Player name.*/
  char m_pSymbol; /**< Player play symbol. */
  unordered_map<string, int> m_stats; /**< Players stats map. */
};

/**
 * @brief Implements the GameBoard of the tic-tac-toe game. 
 * 
 */

class GameBoard
{

public:
  class BoardException : public std::domain_error
  {
  public:
    BoardException(const string &errM) : std::domain_error(errM) {}
  };

public:
  explicit GameBoard(int bSize);
  ~GameBoard();
  void displayBoard() const;
  void placeInputAt(int x, int y, char symbol);
  const int getBoardSize() const;
  const bool hasEmptyCell() const;
  const bool checkIsWinner(char sym) const;
  void reset();

private:
  int m_boardSize; /** < Game board size. */
  vector<vector<char>> m_board; /**< 2-D game board. */
};

/**
 * @brief Implements the tic-tac-toe game. 
 * 
 */

class TttGame
{
public:
  class GameException : public std::domain_error
  {
    public:
    GameException(const string &message) : std::domain_error(message) {}
  };

public:
  explicit TttGame();
  void addPlayer(const Player &pl);
  void displayBoard() const;
  void displayTurn(int i) const;
  const int getBoardSize() const;
  bool checkGameStatus(int playerId);
  void showResult() const;
  void resetGame();
  const int getNumberOfPlayers() const;
  bool placeInput(int x, int y, int playerInd);
  void promptUser() const;
  void printValidCommands() const;
  const int getPlayersAllowed() const;
  const Player getIthPlayer(int i) const;

  ~TttGame();

private:
  int m_playersAllowed; /**< No. of players allowed in the game. */
  vector<Player> m_players; /**< Array of players in a tic-tac-toe game. */
  GameBoard m_board; /**< game board. */
  string m_winner; /**< Winner name. */
  string m_gameStr; /**< Holds the one word game result. */
};

#endif
