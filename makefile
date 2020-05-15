driver: driver.cpp
	g++ driver.cpp -o driver -std=c++11

clean:
	rm -rf driver

run: driver
	./driver