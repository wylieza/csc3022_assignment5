>>> Assignment 5 - PCA Application <<<


--- Instructions for use ---
This application is design purely to perform an analysis on a particular dataset.
The dataset file "2018-AvgRainfall_mm_.csv" must be present for the application
to function.

The application is executed by typeing "make run"

-- Program Arguments --

 > This program take no arguments <


--- MAKEFILE ---
The makefile allows for compilation, execution and removel of binaries.

Command -> Action
_________________________________________________________________________________________________
>> Standard Commands <<
make                            -> Compile source code
make clean                      -> Remove binaries
make Runs                       -> Runs PCA analysis on the dataset
_________________________________________________________________________________________________

Note: The application can also be executed in the terminal using the usual ./driver


--- Source Code Description ---
>> driver.cpp <<
This is the 'driver' and contains the main() method. This source code reads in the data from
the csv file. Following this (using a 3rd party libary 'Eigen') it performs a PCA analysis,
computing the eigenvectors and eigen values as well as the covariance matrix.


--- Student Details ---
Work of Justin Wylie
Student number: WYLJUS002