#pragma once

#include <string>
#include <map>
#include "support/network/network.h"

using namespace std;

class CommandHandler {
  public:
    CommandHandler();

    ~CommandHandler();

    virtual void handle(string msg, Network *net);

    virtual bool debounce();

  protected:
    void tokenize(string msg, string tokens[]);
};
