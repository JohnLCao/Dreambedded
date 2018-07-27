#include "commands/command_handler_bb.h"
#include <string>
#include <iostream>

CommandHandlerBb::CommandHandlerBb() {

}

CommandHandlerBb::~CommandHandlerBb() {

}

void CommandHandlerBb::handle(string msg) {
  cout << "BB " << msg << endl;
}
