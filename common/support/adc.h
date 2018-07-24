#pragma once

#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

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
