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

void analyzeLogs(ifstream& inFile, int& total, int& failed, int& locked);
double calculateFailureRate(int failed, int total);


int main() {
	ifstream inFile("access_log.txt");

	if (!inFile) {
		cout << "Error: Could not open access_log.txt" << endl;
		return 1;
	}


	int totalAttempts = 0;
	int failedCount = 0;
	int lockedCount = 0;
	double failureRate = 0.0;

	cout << " -- Processing Server Access Log -- " << endl;

	analyzeLogs(inFile, totalAttempts, failedCount, lockedCount);
	
	inFile.close();

	failureRate = calculateFailureRate(failedCount, totalAttempts);

	cout << "\nTotal Attempts: " << totalAttempts << endl; 
	cout << "Failed Attempts: " << failedCount << endl;
	cout << "Locked Accounts: " << lockedCount << endl; 
	cout << "Failure Rate: " << failureRate << "%" << endl;

	return 0;
}

void analyzeLogs(ifstream& inFile, int& total, int& failed, int& locked) {

	string timestamp;
	string username;
	string ipAddress;
	string status;

	while (inFile >> timestamp >> username >> ipAddress >> status) {
		/* cout << "Parsed record: " << timestamp << " | "
			<< username << " | " << ipAddress << " | "
			<< status << endl;
			*/
		total++;

		if (status == "FAILED") {
			failed++;
			cout << "[WARNING] Failed attempt for user " << username
				<< " from " << ipAddress << endl;
		}
		else if (status == "LOCKED") {
			locked++;
			cout << "[CRITICAL] Account locked for user " << username
				<< " from " << ipAddress << endl;
		}
	}
}

double calculateFailureRate(int failed, int total) {
	if (total == 0.0) {
		return 0.0;
	}
	return static_cast<double>(failed) / total * 100.0; 
}
