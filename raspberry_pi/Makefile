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
BUILD_SUFFIX = $@.$(SRCTYPE) -o $(BUILD)/$@

COMMON_PREFIX = $(CCPREFIX)$(CC) $(INC) $(CFLAGS)$(LIB) -c $(COMMON)/$(SRC)/

MAIN = $(BUILD)/main
APP = $(BUILD)/command_handler $(BUILD)/command_handler_ui $(BUILD)/command_handler_bb $(BUILD)/udp_server $(BUILD)/relay $(BUILD)/network $(BUILD)/monitor $(BUILD)/gpio $(MAIN)

all: main gpio monitor udp_server relay network command_handler command_handler_ui command_handler_bb deploy_server
	$(CCPREFIX)$(CC) -o dreambed $(APP) -lpthread
	cp dreambed $(PUBDIR)

relay:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)actuators/$(BUILD_SUFFIX)

udp_server:
	$(MAKE_BUILD_FOLDER)
	$(COMMON_PREFIX)network/$(BUILD_SUFFIX)

gpio:
	$(MAKE_BUILD_FOLDER)
	$(COMMON_PREFIX)$(BUILD_SUFFIX)

network:
	$(MAKE_BUILD_FOLDER)
	$(COMMON_PREFIX)network/$(BUILD_SUFFIX)

monitor:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)monitor/$(BUILD_SUFFIX)

command_handler:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)commands/$(BUILD_SUFFIX)

command_handler_ui:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)commands/$(BUILD_SUFFIX)

command_handler_bb:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)commands/$(BUILD_SUFFIX)

main:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)main/$(BUILD_SUFFIX)

deploy_server:
	rsync -av --progress server ~/cmpt433/public/myApps/rpi/

clean:
	rm -r $(BUILD)
