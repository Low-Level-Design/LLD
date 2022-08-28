/**
*  @copyright Licensed under GNU GENERAL PUBLIC LICENSE
*  @date      23 Jul 2022
*  @author    Shabnam Banu & Ninad Thakare
*  @file      gameexe/main.cpp
*  @brief     Main function for tic-tac-toe.
*  
*/

#include <iostream>
#include <input/Reactor.h>
#include <input/EventHandler.h>

#include <iostream>
using namespace std;

/**
 * @brief Creates a reactor loop to handle the different commands from the user.
 * 
 * @details Implements the command processing loop using the reactor pattern 
 *          along with EventHandler.
 * 
 * @return int 
 */

int main()
{

  //print game header
  cout << endl;
  cout << endl;
  
  cout << "\t\t\tCHESS GAME"<<endl;
  cout << "\t\t\t----------------"<<endl;

  cout << endl;
  cout << endl;

  Reactor reactor;

  unique_ptr<EventHandler> eh = make_unique<EventHandler>();
  reactor.registerInputHandler(eh);
  reactor.runEventLoop();
  
  return 0;
}
