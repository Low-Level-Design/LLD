#ifndef _SNAKES_N_LADDER_CPP
#define _SNAKES_N_LADDER_CPP

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      13 Aug 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/SnakesNLadder.cpp
*  @brief     Implements the classes in SnakesNLadder.h.
*  
*/

#include "SnakesNLadder.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>


using namespace std;
PlayerStats::~PlayerStats() = default;

GameSettings* GameSettings::m_instance = nullptr;
GameSettings* GameSettings::getInstance()
{
    //deleted at the end of the program
    if (m_instance == nullptr) {
        m_instance = new GameSettings();

    }
    return m_instance;

}

GameSettings::GameSettings()
{
    m_noOfPlayers = 0;
    m_boardSize = 0;
    m_diceSize = 0;
    m_noOfSnakes = 0;
    m_noOfLadders = 0;
}

int Player::m_idGenerator = 0;

PlayerStats::PlayerStats() {}
Player::Player(const string &name) : m_PlayerStats(){
    m_id = m_idGenerator++;
    m_name = name;
    m_position = {0, 0};
    
}

void Player::printPosition() const
{
    cout << endl<< m_name << ":" << m_position.first << ", " << m_position.second;
 
}

Player::~Player() = default;

Dice::Dice(int diceSize) 
{
    
    m_currRollValue = -1;
    m_maxValue = diceSize;
}

void Dice::rollDice()
{
    // Providing a seed value
	srand((unsigned) time(NULL));

    m_currRollValue = 1 + rand() % m_maxValue;
    cout << "Roll dice value: " << m_currRollValue << endl;

}

Cell::Cell()
{
    m_snake = nullptr;
    m_ladder = nullptr;

}

Cell::~Cell() = default;

Statistics::Statistics() 
{
    m_hasChanged = true;
    
}

void Statistics::registerPlayer(const Player &pl)
{
    string name = pl.getName();
    m_playersRank[name] = 0;

}

Jumper::Jumper(const pair<int, int> &start, const pair<int, int> &end)
{
    m_start = start;
    m_end = end;
}

Jumper::~Jumper() = default;


void GameBoard::generateSnakes(int noOfSnakes, 
                vector <shared_ptr<Snake>> &snakes, 
                unordered_set<string> &snakeStarts,
                unordered_set<string> &snakeTails)
{
    while (noOfSnakes > 0) {

        int startX =  (rand() % m_boardSize);
        int startY =  (rand() % m_boardSize);

        //snakes cannot be at (0, *)

        if (startX == 0) {
            continue;
        }

        int endX =  (rand() % startX);
        int endY =  (rand() % m_boardSize);

        //check whether it is a valid snake . 
        //startX > endX

        // if (startX <= endX) {   // 4,4 -> 0,2
        //     continue;
        // }
        //This property is ensured by doing a mod of startX


        //check whether other snake has same start point
        string snakeStartStr = std::to_string(startX) + ":" + std::to_string(
                                startY);
        auto findSnk = snakeStarts.find(snakeStartStr);

        if (findSnk != snakeStarts.end()) {
            continue;
        }

        //snakes cannot start at  (boardSize-1, boardSize - 1) and (0, 0)
        if (((startX == m_boardSize-1) && (startY == m_boardSize-1)) ||
             (startX == 0 && startY == 0))  {
            continue;
        }

        

        //add the snake head in the hash set
        snakeStarts.insert(snakeStartStr);

        //add the snake tail
        string snakeTailStr = std::to_string(endX) + ":" + std::to_string(
                                endY);
        snakeTails.insert(snakeTailStr);


        //add the snake in the snakes array
        
        auto ss = make_shared<Snake>(pair<int, int> (startX, startY), 
                                    pair<int, int> (endX, endY));

        snakes.emplace_back(ss);
        //reduce snakes count
        noOfSnakes--;

    }

    cout << snakes.size() << " snakes generated :" << endl;

    for (shared_ptr<Snake> &snake : snakes) {
        cout << "Start :" << snake->getStart().first << ", " << 
             snake->getStart().second <<endl;

        cout << "End :" << snake->getEnd().first << ", " << 
             snake->getEnd().second <<endl;
    }

}

void GameBoard::generateLadders(int noOfLadders, 
                unordered_set<string> &snakeStarts,
                unordered_set<string> &snakeTails,
                vector <shared_ptr<Ladder>> &ladders, 
                unordered_set<string> &ladderStarts)
                
{
    while (noOfLadders > 0) {

        int endX =  (rand() % m_boardSize);
        int endY =  (rand() % m_boardSize);

        //A ladder cannot end at 0
        if (endX == 0) {
            continue;
        }

        int startX =  (rand() % endX);
        int startY =  (rand() % m_boardSize);

        //check whether it is a valid Ladder . 
        //startX < endX    // 0,2 -> 4,4

        // if (startX >= endX) {
        //     continue;
        // }
        //This condition is fulfilled using %endX


        //check whether other ladder has same start point.
        //make sure that 2 ladders doesn't have same start point

        string ladderStartStr = std::to_string(startX) + ":" + std::to_string(
                                startY);
        auto findLdr = ladderStarts.find(ladderStartStr);

        if (findLdr != ladderStarts.end()) {
            continue;
        }

        //make sure : snake and ladder do not start from same cell
        auto findSnk = snakeStarts.find(ladderStartStr);
        if (findSnk != snakeStarts.end()) {
            continue;
        }

        //make sure : head of ladder and tail of snake cannot be in 
        //the same cell(2)
        auto headLadderInTail = snakeTails.find(ladderStartStr);
        if (headLadderInTail != snakeTails.end()) {
            continue;
        }

        //make sure : tail of ladder and head of snake cannot be in the 
        //same cell

        string tailLadderStr = std::to_string(endX) + ":" + std::to_string(
                                endY);
        auto tailLadderInHead = snakeStarts.find(tailLadderStr);
        if (tailLadderInHead != snakeStarts.end()) {
            continue;
        }

        //ladders cannot start at  (boardSize-1, boardSize - 1) and (0, 0)
        if (((startX == m_boardSize-1) && (startY == m_boardSize-1)) ||
             (startX == 0 && startY == 0))  {
            continue;
        }

        //ladders cannot be at (boardSize -1 , *)

        if (startX == m_boardSize - 1) {
            continue;
        }

        //add the ladder in the hash set
        ladderStarts.insert(ladderStartStr);


        //add the ladder in the ladders array
        //ladders.emplace_back(make_shared<Ladder>({startX, startY}, {endX, endY}));
        
        auto ld = make_shared<Ladder>(pair<int, int>(startX, startY), 
                                pair<int, int>(endX, endY));
        
        ladders.emplace_back(ld);
        //reduce ladder count
        noOfLadders--;

    }
    cout << ladders.size() << " ladders generated!" << endl;

    for (shared_ptr<Ladder> &ladder : ladders) {
        cout << "Start :" << ladder->getStart().first << ", " << 
             ladder->getStart().second <<endl;

        cout << "End :" << ladder->getEnd().first << ", " << 
             ladder->getEnd().second <<endl;
    }

}

GameBoard::GameBoard(int boardSize, int noOfSnakes, int noOfLadders)
{
    m_boardSize = boardSize;
    m_board     = vector<vector<Cell>>(m_boardSize, vector<Cell> (m_boardSize));
    
    //Two snakes cannot start from the same cell(1)
    //Two ladders cannot start from the same cell(2)
    //snake and ladder cannot start from same cell(2)
    //snake and ladder can end in the same place
    //head of ladder and tail of snake cannot be in the same cell(2)
    //tail of ladder and head of snake cannot be in the same cell(2)
    //(boardSize-1, boardSize - 1) and (0, 0) cannot have  have snakes and
    //ladders(1)
    //first row cannot have snakes, last row cannot have ladders (1)


    // Providing a seed value
	srand((unsigned) time(NULL));

    //populate the snakes

    unordered_set<string> snakeStarts;
    unordered_set<string> snakeTails;
    vector <shared_ptr<Snake>> snakes; 
    generateSnakes(noOfSnakes, snakes, snakeStarts, snakeTails);
    
    unordered_set<string> ladderStarts;
    vector <shared_ptr<Ladder>> ladders;
    generateLadders(noOfLadders, snakeStarts, snakeTails,
                    ladders, ladderStarts);

    
    //Add snakes to the board
    for (shared_ptr<Snake> &snake : snakes) {
        pair<int, int> start = snake->getStart();
        m_board[start.first][start.second].addSnake(snake);
    }

    cout << "Added the snakes to the game-board" <<endl;

    //Add ladders to the board
    for (shared_ptr<Ladder> &ladder : ladders) {
        pair<int, int> start = ladder->getStart();
        m_board[start.first][start.second].addLadder(ladder);
    }

    cout << "Added the ladders to the game-board" <<endl;

}

GameBoard::~GameBoard() = default;

SNLGame::SNLGame(int boardSize, int diceSize, int noOfSnakes, int noOfLadders) : 
                            m_gameBoard(boardSize, noOfSnakes, noOfLadders), 
                            m_dice(diceSize), m_stats(new Statistics())
{
    

}

void SNLGame::resetGame()
{
    for (auto it = m_players.begin(); it != m_players.end() ; ++it) 
    {
        Player &pl = *it;
        pl.reset();
    }
     
    m_stats->reset();
    m_dice.reset();
}

SNLGame::~SNLGame() = default;

void SNLGame::printPlayersPosition() const
{
    cout << endl;
    cout << endl;
    cout << "Players' Postition:" << endl;
    cout << "-------------------" <<endl;
    for (auto it = m_players.begin(); it != m_players.end() ; ++it) {
        it->printPosition();
    }
    cout << endl;
}

void SNLGame::promptUser() const
{
    cout << endl << "game#>";
}

void SNLGame::rollDice()
{
    m_dice.rollDice();
}

Player SNLGame::displayPlayerTurn()
{
    Player currPlayer = getCurrentPlayer();
    cout << endl << currPlayer.getName() 
         << " 's Turn | Please roll the dice." <<endl; 
    return currPlayer;
}

bool SNLGame::move(Player &currPlayer, int rollValue)
{
    pair<int, int> currPos = currPlayer.getPosition();

    int boardSize = m_gameBoard.getBoardSize();

    int yDelta = currPos.second + rollValue;

    int finalX = currPos.first + (yDelta/boardSize);
    int finalY = (yDelta%boardSize);

    pair<int, int> finalPos = {finalX, finalY};

    if (finalPos.first > boardSize - 1|| finalPos.second > boardSize - 1) {
        cout << "Moves not possible for " <<currPlayer.getName() << endl;
        return false;
    }

    //check if the final position has jumper
    while (m_gameBoard.hasJumperAt(finalPos)) {
        
        shared_ptr<Jumper> Jumper = m_gameBoard.getJumperAt(finalPos);

        cout << "Encountered " << Jumper->getJumperType() << " at "
             << "( " << finalPos.first << ", " << finalPos.second << " )"
             << endl;

        pair<int, int> endOfJumper = Jumper->getEnd();
        
        int newFinalX = endOfJumper.first;
        int newFinalY = endOfJumper.second;
        
        if (newFinalX > boardSize || newFinalY > boardSize) {
            
            break;
        } 
        
        finalPos = {newFinalX, newFinalY};

    }
    
    // if (finalPos.first > boardSize || finalPos.second > boardSize) {
    //     return false;
    // }

    currPlayer.setPosition(finalPos);
    return true;
}

bool SNLGame::checkGameStatus(Player &player) 
{
    int boardSize = m_gameBoard.getBoardSize();
    if ((player.getPosition().first == boardSize - 1) && 
            (player.getPosition().second == boardSize - 1)) 
    {
        return true;
    }
    return false;
}

bool SNLGame::moveAndCheck( bool &willSamePlayerPlayAgain, Player &currPlayer)
{
    int rollValue = m_dice.getCurrRollValue();
    willSamePlayerPlayAgain = m_dice.getIsRollMaxValue();

    bool isMovePossible = move(currPlayer, rollValue); 
    if (!isMovePossible) {
        //game continues with the next player
        return false; 
    } 

    return checkGameStatus(currPlayer);

}

static bool playerComparator(const Player &pl1, const Player &pl2)
{
    return (pl1.getScore() <= pl2.getScore());
}

void SNLGame::updateResultAndPrint(Player &pl)
{
    /* For this demo, The registered players don't change in each game.
     * So, queue of m_players in this game and the list of players in statistics
     * are same. But in real world the list of players in the statistics class
     * would be a superset of the players in this game
     * */

    //do calculation for the local set of players of this game

    for (auto it = m_players.begin(); it != m_players.end() ; it++) 
    {
        Player &pl = *it;
        pair<int, int> posOfPlayer = pl.getPosition();
        int score = (posOfPlayer.first) * m_gameBoard.getBoardSize() + 
                    (posOfPlayer.second + 1);
        pl.addScore(score);
        updateStats(pl);
    }

    //sort local Result
    sort(m_players.begin(), m_players.end(), playerComparator);

    //print local result

    cout << endl;
    cout << "Game is over." << pl.getName() << " is the winner." << endl << endl; 
    cout << "GAME SCORES" <<endl;
    cout << "-----------" <<endl;

    for (auto it = m_players.begin(); it != m_players.end(); ++it) {
        cout << it->getName() << " : " << it->getScore() << endl;
    }
    
    //update Statistics
    m_stats->setHasChanged();

}

void SNLGame::updateStats(const Player &pl)
{
    m_stats->updateScore(pl);
}

void SNLGame::printStats() const
{
    m_stats->printStats();
}

void SNLGame::addPlayerForStats(const Player &pl)
{
    m_stats->registerPlayer(pl);
}


#endif