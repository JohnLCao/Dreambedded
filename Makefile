# Consult https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
# for effective Makefile with this project structure

# may need to install g++ for cross compilation with: 
# sudo apt-get install g++-arm-linux-gnueabihf

CCPREFIX = #arm-linux-gnueabihf-
CC		 = g++
SRC		 = src
SRCTYPE	 = cpp
HEADER	 = header
BUILD	 = build
INC		 = -I $(HEADER)
CFLAGS	 = -g -Wall #adjust as needed
LIB		 = #-pthread

all: monitor sensor actuator

monitor: 
	mkdir -p $(BUILD)
	$(CCPREFIX)$(CC) $(INC) $(CFLAGS) $(LIB) $(SRC)/$@/$@.$(SRCTYPE) -o $(BUILD)/$@

sensor: 

actuator: 

clean: #remove executables
	rm -r $(BUILD)
	