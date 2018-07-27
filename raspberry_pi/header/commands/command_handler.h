#pragma once

#include <string>

using namespace std;

class CommandHandler {
  public:
    CommandHandler();

    ~CommandHandler();

    void handle(string msg);

};
