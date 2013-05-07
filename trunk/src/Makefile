CC=g++
CFLAGS = -Wall -pg 


CLASSES_O = sim.o Event.o Scenario.o BaseScenario.o	Location.o Battery.o Distance.o Car.o Revenue.o PassengerRequestEvent.o PassengerServicedEventNoRecharge.o CarBatteryRechargeEvent.o
			

all: sim

$(CLASSES_O): %.o : %.cpp %.hpp sim.hpp
	$(CC) -c $(CFLAGS) $< -o $@

main.o: main.cpp sim.hpp
	$(CC) -c $(CFLAGS) $< -o $@

config.yy.c : config.l config.h
	lex -o config.yy.c config.l

config.tab.c : config.y
	yacc -o config.tab.c --defines=config.tab.h config.y

config.tab.o: config.tab.c
	gcc -c -w $(CFLAGS) $< -o $@

config.yy.o: config.yy.c
	gcc -c -w $(CFLAGS) $< -o $@

MODULES = $(CLASSES_O) main.o config.tab.o config.yy.o

sim: $(MODULES) 
	$(CC)  $(CFLAGS) $(MODULES) -o $@

.PHONY:clean
clean:
	rm -f sim
	rm -f ./*~ 
	rm -f *.o
	rm -f config.*.*
	rm -f gmon.out 
	rm -f ../simdumps/*
	rm -f ../scripts/*~
	rm -f temp_*.cfg

# Other Dependencies


