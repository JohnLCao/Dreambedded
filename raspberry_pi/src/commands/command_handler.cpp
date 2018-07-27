#include "commands/command_handler.h"

#include <iostream>
#include <string>

CommandHandler::CommandHandler() {

}

CommandHandler::~CommandHandler() {

}

void CommandHandler::handle(string msg) {
  cout << msg << endl;
}
