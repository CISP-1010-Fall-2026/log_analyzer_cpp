/**
* @file log_analyzer.cpp
* @author Henry Meadows
* @brief Analyze a security log file and generate a report
* showing success, failures, and locks plus a failure rate.
* @date November 17, 2026
*/

#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string; 

int main() {
	ifstream inFile("access_log.txt");

	if (!inFile) {
		cout << "Error: Could not open access_log.txt" << endl;
		return 1;
	}

	string timestamp;
	string username;
	string ipAddress;
	string status;

	int totalAttempts = 0;
	int failedCount = 0;
	int lockedCount = 0;

	cout << " -- Processing Server Access Log -- " << endl;

	while (inFile >> timestamp >> username >> ipAddress >> status) {
		/* cout << "Parsed record: " << timestamp << " | "
			<< username << " | " << ipAddress << " | "
			<< status << endl; 
			*/
		totalAttempts++;

		if (status == "FAILED") {
			failedCount++;
			cout << "[WARNING] Failed attempt for user " << username
				<< " from " << ipAddress << endl; 
		}
		else if (status == "LOCKED") {
			lockedCount++;
			cout << "[CRITICAL] Account locked for user " << username
				<< " from " << ipAddress << endl;
		}
	}

	inFile.close();

	cout << "\nTotal Attempts: " << totalAttempts << endl; 
	cout << "Failed Attempts: " << failedCount << endl;
	cout << "Locked Accounts: " << lockedCount << endl; 

	return 0;
}
