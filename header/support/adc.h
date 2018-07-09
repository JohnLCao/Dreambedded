#include <iostream>
#include <fstream>

using namespace std;

class ADC {
private:
  int number;
  string path;

public:
  ADC();
  ~ADC();
  ADC (int AINNumber);
  int readValue();
};
