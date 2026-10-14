CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY : all
all : deliveryOutput

deliveryOutput : main.cpp deliverySystem.cpp deliveryRiders.cpp
	$(CXX) $(CXXFLAGS) -o deliveryOutput $^

.PHONY : clean

clean :
	rm deliveryOutput
	rm tests

.PHONY : check
check : tests

tests : tests.cpp deliveryRiders.cpp DeliverySystem.cpp
	$(CXX) $(CXXFLAGS) -o test $^
