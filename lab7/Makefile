CXX = g++
CXXFLAGS = -Wall -Wextra 
TARGET = lab7_main

all: $(TARGET)

# Main executable (using SevenSegment)
$(TARGET): DE1.o SevenSegment.o main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) DE1.o SevenSegment.o main.o

# Object file rules
DE1.o: DE1.cpp DE1.h
	$(CXX) $(CXXFLAGS) -c DE1.cpp

LEDControl.o: LEDControl.cpp LEDControl.h DE1.h
	$(CXX) $(CXXFLAGS) -c LEDControl.cpp

SevenSegment.o: SevenSegment.cpp SevenSegment.h DE1.h
	$(CXX) $(CXXFLAGS) -c SevenSegment.cpp

main.o: main.cpp SevenSegment.h DE1.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
