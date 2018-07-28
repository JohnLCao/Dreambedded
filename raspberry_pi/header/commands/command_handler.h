#pragma once

#include <string>

using namespace std;

class CommandHandler {
  public:
    CommandHandler();

    ~CommandHandler();

    virtual void handle(string msg);

};
