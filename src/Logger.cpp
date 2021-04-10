/*
 * Logger.cpp
 *
 *  Created on: Apr 10, 2021
 *      Author: Josh Zutell
 */
#include <iostream>
#include "../includes/Logger.h"
using namespace std;

/***
 * creates a logger object, if lt=FILE then log to the file given by fn
 * if lt=LOG_CONSOLE the send log info to console via cout
 * @param lt either LOG_FILE or LOG_CONSOLE
 * @param fn if above is LOG_FILE then this is where info logged to
 *           otherwise it is not used
 */
Logger::Logger(LOG_TYPE lt, std::string fn) {
	Logger::lt = lt;
	// if lt is of type LOG_FILE then intiailize filename and filestream
	// otherwise the fn and fs are not needed
	if (lt == LOG_FILE) {
		Logger::fn = fn;
		Logger::fs.open(fn);
	}
}

/***
 * Information to log, either to a file or to console
 * @param info to log
 */
void Logger::Log(std::string info) {
	// determines whether to log to file or console based on log type
	// once determining where to log uses a lock guard to prevent threads interleaving logs
	if (lt == LOG_FILE) {
		lock_guard<mutex> lock(mtx);
		fs << info << endl;
	}
	else {
		lock_guard<mutex> lock(mtx);
		cout << info << endl;
	}
}

/***
 * close any open streams
 */
Logger::~Logger() {
	// if the log type is log file need to close the file stream that was opened
	if (lt == LOG_FILE) {
		fs.close();
	}
}
