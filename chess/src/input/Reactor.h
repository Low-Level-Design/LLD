#ifndef _REACTOR_H
#define _REACTOR_H

/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      23 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      src/input/Reactor.h
*  @brief     Contains the implementation for Reactor class.
*  
*/

#include "EventHandler.h"
#include<vector>
#include<memory>

class EventHandler;
using namespace std;
/**
 * @class Reactor
 *
 * @brief This class represents a reactor which implements an eventloop . This
 *        continuously waits for an event and then dispatches to an 
 *        event handler.
 */

class Reactor {
public:
  Reactor();
  ~Reactor();

  //start the event loop
  void runEventLoop();

  //end the event loop
  void endEventLoop();

  void registerInputHandler(unique_ptr<EventHandler> &eh);
  void removeEventHandler(unique_ptr<EventHandler> &eh);

   
private:
  //
  bool m_runEventLoop; /**< keeps track of the event loop whether it is 
                            being run or not. */

  vector<unique_ptr<EventHandler>> m_dispatchtable;/** < Vector of unique 
              pointers of event handler objects. used to dispatch callbacks. */

};
#endif
