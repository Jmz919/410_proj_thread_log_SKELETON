/*
 * Logger.cpp
 *
 *  Created on: Apr 1, 2021
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
	if (lt == LOG_FILE) {
		fs.close();
	}
}
