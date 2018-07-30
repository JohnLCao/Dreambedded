#include <iostream>

#include "monitor/monitor.h"
#include "commands/command_handler_bb.h"
#include "commands/command_handler_ui.h"

using namespace std;

#define UI_MONITOR_PORT 22221
#define BB_MONITOR_PORT 22222
#define HOST "0.0.0.0"

int main(int argc, char const *argv[]) {
  CommandHandlerUi handlerUi;
  Monitor uiMonitor(UI_MONITOR_PORT, HOST);
  uiMonitor.setCmdHandler(&handlerUi);

  CommandHandlerBb handlerBb;
  Monitor bbMonitor(BB_MONITOR_PORT, HOST);
  bbMonitor.setCmdHandler(&handlerBb);

  uiMonitor.listen();
  bbMonitor.listen();
  return 0;
}
