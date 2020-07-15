CC=gcc
CXX=g++
RM=rm -f

TARGET=../sumArray


INCLUDES=-I../include -I. -I./include
LDFLAGS=
LDLIBS=-lpthread

CXXFLAGS=-std=c++14 -Wall -O2 

DIR_OBJ=objs

SRCS=$(wildcard *.cc)

OBJS=$(patsubst %.cc,$(DIR_OBJ)/%.o,$(SRCS))


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDLIBS) $(LDFLAGS) 

$(DIR_OBJ)/%.o: %.cc
	@mkdir -p $(DIR_OBJ)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCLUDES)

clean:
	@$(RM) $(OBJS)
	@$(RM) *~ core

distclean: clean
	@$(RM) $(TARGET)

.PHONY: all clean distclean
	