# Consult https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
# for effective Makefile with this project structure

# may need to install g++ for cross compilation with:
# sudo apt-get install g++-arm-linux-gnueabihf

PUBDIR	 = $(HOME)/cmpt433/public/myApps

CCPREFIX = arm-linux-gnueabihf-
CC		 = g++
SRC		 = src
SRCTYPE	 = cpp
HEADER	 = header
BUILD	 = build
INC		 = -I $(HEADER)
CFLAGS	 = -g -Wall -std=c++98 #adjust as needed

LIB		 = #-pthread
SLOTS    = /sys/devices/platform/bone_capemgr/slots
BBC		 = BB-ADC
SENSORS	 = $(BUILD)/ir_distance_sensor #audio_sensor.o power_sensor.o 
SUPPORT	 = $(BUILD)/adc #$(BUILD)/gpio
MONITOR  = $(BUILD)/monitor

MAKE_BUILD_FOLDER = mkdir -p $(BUILD)
BUILD_PREFIX = $(CCPREFIX)$(CC) $(INC) $(CFLAGS)$(LIB) -c $(SRC)/
BUILD_SUFFIX = /$@.$(SRCTYPE) -o $(BUILD)/$@ 
BUILD_TARGET = $(BUILD_PREFIX)$@$(BUILD_SUFFIX)
BUILD_SENSOR = $(BUILD_PREFIX)sensors$(BUILD_SUFFIX)
BUILD_SUPPORT = $(BUILD_PREFIX)support$(BUILD_SUFFIX)

all: monitor sensor actuator support
	#echo $(BBC) > $(SLOTS)
	$(CCPREFIX)$(CC) -o dreambed $(SENSORS) $(SUPPORT) $(MONITOR) libstdc++.so.6
	cp dreambed $(PUBDIR)
	
#-------
#MONITOR
#-------
monitor: 
	$(MAKE_BUILD_FOLDER)
	$(BUILD_TARGET)

#-------
#SENSORS
#-------
sensor: ir_distance_sensor #audio_sensor power_sensor

ir_distance_sensor: 
	$(MAKE_BUILD_FOLDER)
	$(BUILD_SENSOR)
	
#---------
#ACTUATORS
#---------
actuator: 

#-------
#SUPPORT
#-------
support: adc gpio

adc: 
	$(MAKE_BUILD_FOLDER)
	$(BUILD_SUPPORT)
	
gpio: 

######################################
clean: #remove executables
	rm -r $(BUILD)
