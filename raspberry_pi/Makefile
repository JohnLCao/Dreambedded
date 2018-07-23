PUBDIR	 = $(HOME)/cmpt433/public/myApps/rpi

CCPREFIX = arm-linux-gnueabihf-
CC		 = g++
SRC		 = src
SRCTYPE	 = cpp
COMMON	 = ../common
HEADER	 = header
BUILD	 = build
INC		 = -I $(HEADER) -I $(COMMON)
CFLAGS	 = -g -Wall -std=c++17 -Werror

MAKE_BUILD_FOLDER = mkdir -p $(BUILD)
BUILD_PREFIX = $(CCPREFIX)$(CC) $(INC) $(CFLAGS)$(LIB) -c $(SRC)/
BUILD_SUFFIX = /$@.$(SRCTYPE) -o $(BUILD)/$@

COMMON_PREFIX = $(CCPREFIX)$(CC) $(INC) $(CFLAGS)$(LIB) -c $(COMMON)/$(SRC)/

MAIN = $(BUILD)/main
APP = $(BUILD)/udp_server $(BUILD)/relay $(BUILD)/network $(MAIN)

all: main udp_server relay network
	$(CCPREFIX)$(CC) -o dreambed $(APP) -lpthread
	cp dreambed $(PUBDIR)

relay:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)actuators$(BUILD_SUFFIX)

udp_server:
	$(MAKE_BUILD_FOLDER)
	$(COMMON_PREFIX)network$(BUILD_SUFFIX)

network:
	$(MAKE_BUILD_FOLDER)
	$(COMMON_PREFIX)network$(BUILD_SUFFIX)

main:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)main$(BUILD_SUFFIX)

clean:
	rm -r $(BUILD)
