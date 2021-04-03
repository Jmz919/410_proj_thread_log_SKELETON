//============================================================================
// Name        : 410_proj_thread_log.cpp
// Author      : Josh Zutell
// Version     : 4-1-21
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <thread>
#include <iostream>
#include <vector>
#include "../includes/constants.h"
#include "../includes/Logger.h"

using namespace std;

//TODO linker errors?  Did you include the pthread library?   And set the proper dialect?
//TODO declare globals

/***
 * 
 * TODO log info to both file and console (you can do this with 2 Logger objects)
 * TODO this function should run until main (or another thread) asks it to quit
 * @param info  to log
 * returns void
 */

Logger logFile(LOG_FILE);
Logger logConsole(LOG_CONSOLE);
bool bDoWork = true;

void fun(string info){
	while (bDoWork) {
		logFile.Log(info);
		logConsole.Log(info);
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

int main() {
	
	//TODO start as many threads as you have cores (see std::thread::hardware_concurrency())
	//TODO save these threads in a vector

	vector<thread> thread_vec;
	int num_of_cores = std::thread::hardware_concurrency()/2;
	for (int i = 0; i < num_of_cores; i++) {
		string info(to_string(i) + to_string(i) + to_string(i) + to_string(i));
		thread_vec.push_back(thread(fun, info));
	}

	//TODO let threads run a bit (5 seconds)
	this_thread::sleep_for(chrono::milliseconds(5000));

	//TODO ask them all to stop
	bDoWork = false;
	
	//TODO wait for all threads to finish
	for(auto& t : thread_vec) {
		t.join();
	}
	
	return 0;
}
