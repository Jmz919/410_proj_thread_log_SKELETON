//============================================================================
// Name        : 410_proj_thread_log.cpp
// Author      : Josh Zutell
// Version     : 4-10-21
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <thread>
#include <iostream>
#include <vector>
#include "../includes/constants.h"
#include "../includes/Logger.h"

using namespace std;

/***
 * 
 * log info to both file and console
 * this function runs until main (or another thread) asks it to quit
 * @param info  to log
 * returns void
 */

// create global Logger objects to log info and boolean to stop threads running
Logger logFile(LOG_FILE);
Logger logConsole(LOG_CONSOLE);
bool bDoWork = true;

/***
 * runs threads while bDoWork is true
 * takes a string info and logs it to console and a file
 */
void fun(string info){
	while (bDoWork) {
		logFile.Log(info);
		logConsole.Log(info);

		// temporary causes a thread to sleep to allow the main thread to modify bDoWork
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

int main() {
	
	// start as many threads as you have cores (see std::thread::hardware_concurrency())
	// save these threads in a vector
	vector<thread> thread_vec;
	int num_of_cores = std::thread::hardware_concurrency()/2;
	for (int i = 0; i < num_of_cores; i++) {
		// log the indexes of when the thread was created
		// this is to help differentiate which thread is logging
		string info(to_string(i) + to_string(i) + to_string(i) + to_string(i));
		thread_vec.push_back(thread(fun, info));
	}

	// let threads run a bit (5 seconds)
	this_thread::sleep_for(chrono::milliseconds(5000));

	// ask them all to stop
	bDoWork = false;
	
	// wait for all threads to finish
	for(auto& t : thread_vec) {
		t.join();
	}
	
	return 0;
}
