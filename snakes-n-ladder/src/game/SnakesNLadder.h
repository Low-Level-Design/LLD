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
#include <memory>
#include <unordered_set>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

class PlayerStats;
class Statistics;

/************************************************************
 *  Game Statistics
 *************************************************************/

class PlayerStats
{

public:
    explicit PlayerStats();
    ~PlayerStats();

    void updateScore(int score) 
    {
        m_score += score;
    }

    void addScore(int score)
    {
        m_score = score;
    }

    const int getScore() const 
    {
        return m_score;
    }

    void reset()
    {
        m_score = 0;
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

    void addScore(int score) 
    {
        m_PlayerStats.addScore(score);
    }

    const int getScore() const
    {
        return m_PlayerStats.getScore();
    }

    void display() const 
    {
        cout << "Player Id: " << m_id << endl;
        cout << "Player Name: " <<m_name << endl;
        cout << "Player Piece: " <<m_id << endl;
    }

    void printPosition() const;

    void reset() 
    {
        m_PlayerStats.reset();
        m_position.first = 0;
        m_position.second = 0;
    }

private:
    int m_id; 
    string m_name;
    pair<int, int> m_position;
    PlayerStats m_PlayerStats;
    static int  m_idGenerator; 

};

/************************************************************
 *  Game Board
 *************************************************************/

class Jumper
{
    
public:
    explicit Jumper(const pair<int, int> &start, const pair<int, int> &end);
    ~Jumper();
    //getters
    const pair<int, int> getStart() const 
    {
        return m_start;
    }

    const pair<int, int> getEnd() const 
    {
        return m_end;
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

    virtual string getJumperType() const
    {
        return "Void";
    }
private:
    pair<int, int> m_start;
    pair<int, int> m_end;
};

class Snake: public Jumper
{

public:
    explicit Snake(const pair<int, int> &start, const pair<int, int> &end)
    :Jumper(start, end) {}

    
    string getJumperType() const override
    {
        return "Snake";
    }
};

class Ladder: public Jumper
{
public:
    explicit Ladder(const pair<int, int> &start, const pair<int, int> &end)
    :Jumper(start, end) {}

    string getJumperType() const override
    {
        return "Ladder";
    }
};


class Cell 
{

public:
    //constructor and destructor
    explicit Cell();
    ~Cell();

    //getters
    const shared_ptr<Snake> getSnake() const 
    {
        return m_snake;
    }

    const shared_ptr<Ladder> getLadder() const 
    {
        return m_ladder;
    }

    const vector<int> getPlayerIds() const 
    {
        return m_playerIds;
    }

    bool hasJumper(const pair<int, int> &pos) const
    {
        return (m_ladder || m_snake);

    }
    
    shared_ptr<Jumper> getJumper() const
    {
        if (m_snake) {
            return m_snake;
        }

        if (m_ladder) {
            return m_ladder;
        }
        return nullptr;
    }
    //setters
    void addSnake(shared_ptr<Snake> &snake) 
    {
        m_snake =  snake;
    }

    void addLadder(shared_ptr<Ladder> &ladder) 
    {
        m_ladder =  ladder;
    } 

    void addPlayerId(int pId) 
    {
        m_playerIds.emplace_back(pId);
    } 

private:
    shared_ptr<Snake> m_snake; 
    shared_ptr<Ladder> m_ladder;

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

    bool hasJumperAt(const pair<int, int> &pos)
    {
        return m_board[pos.first][pos.second].hasJumper(pos);
    }

    shared_ptr<Jumper> getJumperAt(const pair<int, int> &pos)
    {
        return m_board[pos.first][pos.second].getJumper();
    }

    

private:
    void generateSnakes(int noOfSnakes, 
                vector <shared_ptr<Snake>> &snakes, 
                unordered_set<string> &snakeStarts,
                unordered_set<string> &snakeTails);
    void generateLadders(int noOfLadders, 
                unordered_set<string> &snakeStarts,
                unordered_set<string> &snakeTails,
                vector <shared_ptr<Ladder>> &ladders, 
                unordered_set<string> &ladderStarts);
                
};

/************************************************************
 *  Dice
 *************************************************************/

class Dice
{

private:
    int m_maxValue;
    int m_currRollValue;

public:
    explicit Dice(int diceSize);
    const int getMaxValue() const
    {
        return m_maxValue;
    }

    void rollDice();
    

    void setMaxValue(int m_maxValue)
    {
        m_maxValue = m_maxValue;
    };

    const int getCurrRollValue() const 
    {
        return m_currRollValue;
    }

    bool getIsRollMaxValue() const
    {
        return (m_currRollValue == m_maxValue);
    }

    void reset() 
    {
        
        m_currRollValue = 0;

    }
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

    deque<Player> getPlayers() const
    {
        return m_players;
    }

    Player getCurrentPlayer()
    {
        Player frontPlayer = m_players.front();
        m_players.pop_front();
        return frontPlayer;
    }

    Dice getDice() const
    {
        return m_dice;
    }

    const int getNoOfRegisteredPlayers() const {
        return m_players.size();

    }

    void printStats() const;

    //setters

    void addPlayer(const Player& pl) 
    {
        m_players.push_back(pl);

    }

    void addPlayerForStats(const Player &pl);
    
    void addPlayerAtFront(const Player &pl) 
    {
        m_players.push_front(pl);
    }

    void addDice(const Dice &dice)
    {
        m_dice = dice;
    }

    void updateStats(const Player &pl);

    void printPlayersPosition() const;
    Player displayPlayerTurn();
    void promptUser() const;

    void rollDice();
    bool moveAndCheck( bool &willSamePlayerPlayAgain, Player &currPlayer);
    bool move(Player &currPlayer, int rollValue);
    bool checkGameStatus(Player &player);
    void updateResultAndPrint(Player &player);
    void resetGame();


private:

    deque<Player>  m_players;
    GameBoard      m_gameBoard;
    Dice           m_dice;
    shared_ptr<Statistics>  m_stats;
   
};




class Statistics
{

public:

       
    explicit Statistics();
    void registerPlayer(const Player &pl); 
   
    void setHasChanged() 
    {
        m_hasChanged = true;
    }

    void updateScore(const Player &pl)
    {
        string name = pl.getName();
        int score = pl.getScore();
        m_playersRank[name] += score;
    }

    void reset()
    {
        
        m_hasChanged = true;
    }

    void printStats() 
    {
        //print the sorted ranked players

        cout << "Players' Score" <<endl;
        cout << "--------------" <<endl;
        if (!m_hasChanged) {
            for (pair<int, string> plScore : m_rankedPlayerList) {
                cout << plScore.second << " : " << plScore.first <<endl;
            }
        } else {
            // //clear the vector m_rankedPlayerList
            m_rankedPlayerList.clear();

            // //create the vector from the unordered_map
            for (auto it = m_playersRank.begin(); it != m_playersRank.end();
                            ++it) {
                pair<int, string> pl = make_pair(it->second, it->first);
                m_rankedPlayerList.emplace_back(pl);

            }

            sort(m_rankedPlayerList.begin(), m_rankedPlayerList.end()); 
                                   

            for (pair<int, string> plScore : m_rankedPlayerList) {
                cout << plScore.second << " : " << plScore.first <<endl;
            }
            m_hasChanged = false;
          
        }
    
    }


private:
    unordered_map <string, int> m_playersRank;
    vector < pair<int, string> >  m_rankedPlayerList;
    bool m_hasChanged;
 
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