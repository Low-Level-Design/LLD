#ifndef _REACTOR_CPP
#define _REACTOR_CPP

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      13 Aug 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/Reactor.cpp
*  @brief     Contains the implementation for classes in Recator.h.
*  
*/

#include <iostream>
#include <algorithm>
#include <memory>

#include "Reactor.h"


using namespace std;

/**
 * @brief Construct a new Reactor:: Reactor object.
 *        Default value of m_runEventLoop is true as for the first 
 *        the loop should start.
 * 
 */

Reactor::Reactor(): m_runEventLoop(true) 
{
}

Reactor::~Reactor() 
{
}

/**
 * @brief Implements the outer event loop for the Reactor.
 * 
 */

void Reactor::runEventLoop()
{
  while(m_runEventLoop) {
    for (unique_ptr<EventHandler> &eh : m_dispatchtable) {
      eh->handleInput(this);
    }
  }

}

/**
 * @brief Breaks the user out of the event loop.
 * 
 */

void Reactor::endEventLoop()
{
  m_runEventLoop = false;
}

/**
 * @brief Removes a registered event handler. 
 * 
 * @param eh 
 */

void Reactor::removeEventHandler(unique_ptr<EventHandler> &eh)
{
  auto newEnd = std::remove(m_dispatchtable.begin(), m_dispatchtable.end(), eh);
  m_dispatchtable.erase(newEnd,m_dispatchtable.end()); 
}

/**
 * @brief Registers an eventHandler.
 * 
 * @param eh EventHnadler to be registered.
 */

void Reactor::registerInputHandler(unique_ptr<EventHandler> &eh)
{
  m_dispatchtable.emplace_back(eh.release());
}
 
#endif
