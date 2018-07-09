#include <string>
#include <fstream>

using namespace std;

class ADC {
    private:
        int number;
        string path;

    public:
        ADC (int AINNumber);
        virtual int readValue();
};
