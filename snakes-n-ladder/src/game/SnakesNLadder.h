#ifndef _SNAKES_N_LADDER_H
#define _SNAKES_N_LADDER_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      13 Aug 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/Tictactoe.h
*  @brief     Implements the classes associated with the snakes-n-ladder game.
*  
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
class PlayerStat;
class Statistics;

/************************************************************
 *  Game Statistics
 *************************************************************/

class PlayerStat
{

public:
    explicit PlayerStat();
    ~PlayerStat();

    void updateScore(int score) 
    {
        m_score += score;
    }

private:
    
    int m_score;

};



/************************************************************
 *  Player
 *************************************************************/
/**
 * @brief 
 * 
 */

class Player 
{

public:
    explicit Player(const string &name);
    ~Player();
    //getters
    const int getId() const {return m_id;}
    const string getName() const {return m_name;}
    const pair<int, int> getPosition() const {return m_position;}

    //setters
    void setId(int id) 
    {
        m_id = id;
    }

    void setName(const string &name) 
    {
        m_name = name;
    }

    void setPosition(const pair<int, int> &position) 
    {
        m_position = position;
    }

    void display() const 
    {
        cout << "Player Id: " << m_id << endl;
        cout << "Player Name: " <<m_name << endl;
        cout << "Player Piece: " <<m_id << endl;
    }

private:
    int m_id; 
    string m_name;
    pair<int, int> m_position;
    PlayerStat m_playerStat;
    static int  m_idGenerator; 

};

/************************************************************
 *  Game Board
 *************************************************************/

class Jumper
{
    
    explicit Jumper();
    ~Jumper();
    //getters
    const pair<int, int> getStart() const 
    {
        return m_start;
    }

    const pair<int, int> getEnd() const 
    {
        return m_start;
    }

    //setters

    void setStart(const pair<int, int> &start) 
    {
        m_start = start;
    }

    void setEnd(const pair<int, int> &end) 
    {
        m_end = end;
    }
private:
    pair<int, int> m_start;
    pair<int, int> m_end;
};

class Snake: public Jumper
{
};

class Ladder: public Jumper
{
};


class Cell 
{

public:
    //constructor and destructor
    explicit Cell();
    ~Cell();

    //getters
    const Snake *getSnake() const 
    {
        return m_snake;
    }

    const Ladder *getLadder() const 
    {
        return m_ladder;
    }

    const vector<int> getPlayerIds() const 
    {
        return m_playerIds;
    }

    //setters
    void addSnake(Snake *snake) 
    {
        m_snake =  snake;
    }

    void addLadder(Ladder *ladder) 
    {
        m_ladder =  ladder;
    } 

    void addPlayerId(int pId) 
    {
        m_playerIds.emplace_back(pId);
    } 

private:
    Snake *m_snake;
    Ladder *m_ladder;

    vector<int>  m_playerIds;

};

class GameBoard
{

public:
    explicit GameBoard(int boardSize, int noOfSnakes, int noOfLadders);
    ~GameBoard();

private:
    int m_boardSize;
    vector<vector<Cell>> m_board;

public:

    const int getBoardSize() const
    {
        return m_boardSize;
    }

    void setM_boardSize(int m_boardSize)
    {
        m_boardSize = m_boardSize;
    }
};

/************************************************************
 *  Dice
 *************************************************************/

class Dice
{

private:
    int m_maxValue;

public:
    explicit Dice(int diceSize);
    const int getMaxValue() const
    {
        return m_maxValue;
    }


    void setMaxValue(int m_maxValue)
    {
        m_maxValue = m_maxValue;
    };
};

/************************************************************
 *  Snakes and Ladder Game
 *************************************************************/

class SNLGame
{

public:

    explicit SNLGame(int boardSize, int diceSize, int noOfSnakes, 
                     int noOfLadders);
    ~SNLGame();

    //getters

    queue<Player> getPlayers() const
    {
        return m_players;
    }

    Player getPlayer()
    {
        Player frontPlayer = m_players.front();
        m_players.pop();
        return frontPlayer;
    }

    Dice getDice() const
    {
        return m_dice;
    }

    const int getNoOfRegisteredPlayers() const {
        return m_players.size();

    }

    //setters

    void addPlayer(const Player& pl) 
    {
        m_players.push(pl);

    }

    void addDice(const Dice &dice)
    {
        m_dice = dice;
    }


private:

    queue<Player>  m_players;
    GameBoard      m_gameBoard;
    Dice           m_dice;
    Statistics     *m_stats;
    

    //sorted result of game
    vector<pair<int, Player>>  m_result; 

};

class Statistics
{
public:
    explicit Statistics();
private:
    vector<Player> m_playersRank;
    bool m_hasChanged;
    //update
    

};

/************************************************************
 *  Game Settings Singleton
 *************************************************************/

class GameSettings
{
public:
    static GameSettings* getInstance();
  
    //getters
    const int getNoOfPlayers() const 
    {
        return m_noOfPlayers;
    }

    const int getBoardSize() const 
    {
        return m_boardSize;
    }
    const int getDiceSize() const 
    {
        return m_diceSize;
    }
    const int getNoOfSnakes() const 
    {
        return m_noOfSnakes;
    }
    const int getNoOfLadders() const 
    {
        return m_noOfLadders;
    }
    //setters

    void setNoOfPlayers(int noOfPlayers)
    {
        m_noOfPlayers = noOfPlayers;
    }

    void setBoardSize(int boardSize)
    {
        m_boardSize = boardSize;
    }
    void setDiceSize(int diceSize)
    {
        m_diceSize = diceSize;
    }

    void setNoOfSnakes(int noOfSnakes)
    {
        m_noOfSnakes = noOfSnakes;
    }
    void setNoOfLadders(int noOfLadders)
    {
        m_noOfLadders = noOfLadders;
    }

private:
    explicit GameSettings();
    int m_noOfPlayers;
    int m_boardSize;
    int m_diceSize;
    int m_noOfSnakes;
    int m_noOfLadders;
    static GameSettings* m_instance;
 
};

#endif