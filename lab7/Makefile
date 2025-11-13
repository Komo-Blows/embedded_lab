CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++12
TARGET = de1_program

all: DE1.o LEDControl.o DE1_class.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) DE1.o LEDControl.o DE1_class.o

DE1.o: DE1.cpp DE1.h
	$(CXX) $(CXXFLAGS) -c DE1.cpp

LEDControl.o: LEDControl.cpp LEDControl.h DE1.h
	$(CXX) $(CXXFLAGS) -c LEDControl.cpp

DE1_class.o: DE1_class.cpp DE1.h LEDControl.h
	$(CXX) $(CXXFLAGS) -c DE1_class.cpp

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
