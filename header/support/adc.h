#include <string>
#include <fstream>

// #define ADC_PATH "/sys/devices/platform/bone_capemgr/slots"

using namespace std;

class ADC {
private:
  int number;
  string path;

public:
  ADC (int AINNumber);
  virtual int readValue();
  virtual ~ADC ();
};
