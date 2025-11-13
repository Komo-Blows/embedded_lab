CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET1 = lab7_main
TARGET2 = lab6

all: $(TARGET1) $(TARGET2)

# Main executable (using SevenSegment)
$(TARGET1): DE1.o SevenSegment.o main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET1) DE1.o SevenSegment.o main.o

# Lab6 executable (using LEDControl)
$(TARGET2): DE1.o LEDControl.o lab6.o
	$(CXX) $(CXXFLAGS) -o $(TARGET2) DE1.o LEDControl.o lab6.o

# Object file rules
DE1.o: DE1.cpp DE1.h
	$(CXX) $(CXXFLAGS) -c DE1.cpp

LEDControl.o: LEDControl.cpp LEDControl.h DE1.h
	$(CXX) $(CXXFLAGS) -c LEDControl.cpp

SevenSegment.o: SevenSegment.cpp SevenSegment.h DE1.h
	$(CXX) $(CXXFLAGS) -c SevenSegment.cpp

main.o: main.cpp SevenSegment.h DE1.h
	$(CXX) $(CXXFLAGS) -c main.cpp

lab6.o: lab6.cpp LEDControl.h DE1.h
	$(CXX) $(CXXFLAGS) -c lab6.cpp

clean:
	rm -f *.o $(TARGET1) $(TARGET2)

.PHONY: all clean
