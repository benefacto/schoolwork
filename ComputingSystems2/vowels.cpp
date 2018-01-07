// vowels.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <thread>

using namespace std;

int cumulativeVowelCount = 0;
string filePaths[20] = {};
string directoryPath = "";

void InputDirectoryFromUser()
{
	//cout << "Please provide complete folder path where files 1-20 are contained\n" 
	//<< "(with no ending '\'): ";
	//cin >> directoryPath;
}

void FilePathSet()
{
	string name1;
	string name2;
	for (int i = 1; i <= 20; i++)
	{
		name1 = "file";
		name2 = ".txt";
		filePaths[i] = directoryPath + name1
			+ to_string(i) + name2;
		cout << filePaths[i] << "\n";
	}
}

void ThreadIncrementVowelCount()
{
	// single thread increments count
	// implement locking/semaphores
}

void ThreadReadFile(int threadNumber)
{
	// single thread reads single file
	ThreadIncrementVowelCount();
	// print error if could not find file
}

void StartThread(int threadNumber)
{
	// create a single thread here
	thread thisThread(ThreadReadFile, threadNumber);
	cout << "Thread " << threadNumber << " created";
	thisThread.join();
}

int main()
{
	cout << "Hello world";
	/*
	// take in directory
	//InputDirectoryFromUser();
	// set file names 1-20
	FilePathSet();
	// create 20 threads (for each file)
	for (int i = 1; i <= 20; i++)
	{
		//StartThread(i);
	}
	// join the threads
	// print output of cumulativeVowelCount
	*/
	return 0;
}


