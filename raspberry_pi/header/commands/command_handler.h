#pragma once

#include <string>
#include <map>

using namespace std;

class CommandHandler {
  public:
    CommandHandler();

    ~CommandHandler();

    virtual void handle(string msg);

  protected:
    void tokenize(string msg, string tokens[]);
};
