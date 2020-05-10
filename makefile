driver: driver.cpp
	g++ driver.cpp -o driver -std=c++11

run: driver
	./driver