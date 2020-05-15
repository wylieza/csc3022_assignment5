driver: driver.cpp
	g++ driver.cpp -o driver -std=c++11 -I ./Eigen

clean:
	rm -rf driver

run: driver
	./driver
