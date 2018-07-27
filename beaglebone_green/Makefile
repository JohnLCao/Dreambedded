# Consult https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
# for effective Makefile with this project structure

# may need to install g++ for cross compilation with:
# sudo apt-get install g++-arm-linux-gnueabihf

CC_VER	 = #-5 #change this as needed
PUBDIR	 = $(HOME)/cmpt433/public/myApps

CCPREFIX = arm-linux-gnueabihf-
CC		 = g++$(CC_VER)
SRC		 = src
SRCTYPE	 = cpp
HEADER	 = header
COMMON	 = ../common
BUILD	 = build
INC		 = -I $(HEADER) -I $(COMMON)
CFLAGS	 = -g -Wall -std=c++11 #adjust as needed

LIB		 = -pthread
SLOTS    = /sys/devices/platform/bone_capemgr/slots
BBC		 = BB-ADC
SENSORS	 = $(BUILD)/ir_distance_sensor $(BUILD)/sound_sensor #power_sensor.o
SUPPORT	 = $(BUILD)/adc $(BUILD)/gpio $(BUILD)/udp_server
MONITOR  = $(BUILD)/monitor
MAKE_BUILD_FOLDER = mkdir -p $(BUILD)
# BUILD_PREFIX = $(CCPREFIX)$(CC) $(INC) $(CFLAGS)$(LIB) -c -D_GLIBCXX_USE_CXX11_ABI=0 $(SRC)/
BUILD_PREFIX = $(CCPREFIX)$(CC) $(INC) $(CFLAGS) $(LIB) -c $(SRC)/
BUILD_SUFFIX = /$@.$(SRCTYPE) -o $(BUILD)/$@
BUILD_TARGET = $(BUILD_PREFIX)$@$(BUILD_SUFFIX)
BUILD_SENSOR = $(BUILD_PREFIX)sensors$(BUILD_SUFFIX)

# COMMON_PREFIX = $(CCPREFIX)$(CC) $(INC) $(CFLAGS)$(LIB) -c -D_GLIBCXX_USE_CXX11_ABI=0 $(COMMON)/$(SRC)/
COMMON_PREFIX = $(CCPREFIX)$(CC) $(INC) $(CFLAGS)$(LIB) -c $(COMMON)/$(SRC)/
#COMMON_SUFFIX = /$@.$(SRCTYPE) -o $(BUILD)/$@ ###may change later
BUILD_SUPPORT = $(COMMON_PREFIX)$@.$(SRCTYPE) -o $(BUILD)/$@

all: support sensor actuator monitor
	#echo $(BBC) > $(SLOTS)
	$(CCPREFIX)$(CC) -o dreambed $(SENSORS) $(SUPPORT) $(MONITOR) $(LIB) #libstdc++.so.6
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
sensor: ir_distance_sensor sound_sensor #power_sensor

ir_distance_sensor:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_SENSOR)

sound_sensor:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_SENSOR)
#---------
#ACTUATORS
#---------
actuator:

#-------
#SUPPORT
#-------
support: adc gpio udp_server

adc:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_SUPPORT)

gpio:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_SUPPORT)

udp_server:
	$(MAKE_BUILD_FOLDER)
	$(COMMON_PREFIX)network/$@.$(SRCTYPE) -o $(BUILD)/$@

######################################
clean: #remove executables
	rm -r $(BUILD)
