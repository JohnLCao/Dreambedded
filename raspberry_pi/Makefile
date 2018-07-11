PUBDIR	 = $(HOME)/cmpt433/public/myApps

CCPREFIX = arm-linux-gnueabihf-
CC		 = g++
SRC		 = src
SRCTYPE	 = cpp
HEADER	 = header
BUILD	 = build
INC		 = -I $(HEADER)
CFLAGS	 = -g -Wall -std=c++17 -Werror

MAKE_BUILD_FOLDER = mkdir -p $(BUILD)
BUILD_PREFIX = $(CCPREFIX)$(CC) $(INC) $(CFLAGS)$(LIB) -c $(SRC)/
BUILD_SUFFIX = /$@.$(SRCTYPE) -o $(BUILD)/$@

MAIN = $(BUILD)/main
APP = $(BUILD)/udp_server $(BUILD)/relay $(MAIN)

all: main udp_server relay
	$(CCPREFIX)$(CC) -o dreambed $(APP)
	cp dreambed $(PUBDIR)

relay:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)actuators$(BUILD_SUFFIX)

udp_server:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)networking$(BUILD_SUFFIX)

main:
	$(MAKE_BUILD_FOLDER)
	$(BUILD_PREFIX)main$(BUILD_SUFFIX)

clean:
	rm -r $(BUILD)
