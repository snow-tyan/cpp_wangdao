SRCS:=$(wildcard *.cc)
ELFS:=$(SRCS:%.cc=%)
CXX:=g++
CXXFLAGS:= -Wall -g -O1
RM:=rm -rf
all:$(ELFS)
%:%.cc
	$(CXX) $< -o $@ 
.PHONY:clean
clean:
	$(RM) $(ELFS)
