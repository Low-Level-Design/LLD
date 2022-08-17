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

PlayerStat::~PlayerStat() = default;

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

PlayerStat::PlayerStat() {}
Player::Player(const string &name) : m_playerStat(){
    m_id = m_idGenerator++;
    m_name = name;
    m_position = {0, 0};
    
}

Player::~Player() = default;

Dice::Dice(int diceSize) 
{
    
    
    m_maxValue = diceSize;
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

GameBoard::GameBoard(int boardSize, int noOfSnakes, int noOfLadders)
{
    m_boardSize = boardSize;
    m_board     = vector<vector<Cell>>(boardSize);
    ///snakes and ladders initialization with no loops

}

GameBoard::~GameBoard() = default;

SNLGame::SNLGame(int boardSize, int diceSize, int noOfSnakes, int noOfLadders) : 
                            m_gameBoard(boardSize, noOfSnakes, noOfLadders), 
                            m_dice(diceSize), m_stats()
{
    

}

SNLGame::~SNLGame() = default;


#endif