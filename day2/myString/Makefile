SRCS:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc,%.o,$(SRCS))
ELF:=main
CXX:=g++
CXXFLAGS:=-g -Wall
RM:=rm -rf
$(ELF):$(OBJS)
	$(CXX) -o $@ $^
.PHONY:clean
clean:
	$(RM) $(OBJS) $(ELF)
