#include "support/adc.h"

//constructors and destructors
ADC::ADC(){}
ADC::~ADC(){}

ADC::ADC(int AINNumber)
{
	string fslots = "/sys/devices/platform/bone_capemgr/slots";
	string ADC_PREFIX = "/sys/bus/iio/devices/iio:device0/in_voltage";
	string ADC_SUFFIX = "_raw";

	//TODO: refactor file IO code
	ofstream fs(fslots.c_str());
	if (fs.is_open())
		{
		  fs << "BB-ADC";
		} else {
			cout << "ERROR: cannot open file " << fslots << endl;
		}
	fs.close();

	number = AINNumber;
	path   = ADC_PREFIX + (char)('0' + number) + ADC_SUFFIX;
}

int ADC::readValue()
{
	int readValue;
	ifstream fs(path.c_str());
	if (fs.is_open())
	{
	  // cout << "Reading from a file:" << endl;
	  fs >> readValue;
	} else {
		cout << "ERROR: cannot open file " << path << endl;
	}
	fs.close();
	return readValue;
}

