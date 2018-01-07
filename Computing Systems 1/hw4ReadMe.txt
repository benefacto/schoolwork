hw4.cpp ReadMe
----------------------------------------------------------------
- The purpose of this program is to simulate input into a cache
- To compile the program, run the linux terminal command:
g++ hw4.cpp -o hw4Exec
- To run the program, provide a config and trace file and run the command:
./hw4Exec config.txt trace.txt
- The program will take config file, create a cache based off its parameters
and take the trace file as input, printing the hits and misses

NOTE: This program is nonfunctional in its current state.
It is based off of an older version that I was able to recover after I accidentally deleted the up-to-date one.
The DirectMappedCache function returns a fatal runtime error: floating point exception.
I have not been able to correct this error in the time allotted, despite my best efforts.
The other associativity functions FullyAssociativeCache, TwoWayCache, FourWayCache are also nonfunctional.
I was counting on building on a functional DirectMappedCache to implement these other functions.