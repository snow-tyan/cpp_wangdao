SRCS:=$(wildcard *.cc)
ELFS:=$(SRCS:%.cc=%)
IOLIB:= -lpthread
CXX:=g++
CXXFLAGS:= -Wall -g -O1
RM:=rm -rf
all:$(ELFS)

%:%.cc
	$(CXX) $< -o $@ $(IOLIB)

.PHONY:clean
clean:
	$(RM) $(ELFS)
