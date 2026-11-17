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
#include <iomanip>


using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string; 
using std::fixed; 
using std::setprecision; 


/** 
* @brief Reads log file entries and counts activity records.
* @param inFile Open input file stream reference.
* @param total Output reference for total login attempts
* @param failed Output reference for failed login attempts
* @param locked Output reference for locked out accounts
*/
void analyzeLogs(ifstream& inFile, int& total, int& failed, int& locked);

/** 
* @brief Calculate the Failure Rate as a percentage
* @param failed Total failures
* @param total Total entries
* @returns Failed divided by total as a double
*/
double calculateFailureRate(int failed, int total);

/**
* @brief Writes a formatted security report to an open output stream
* @param outFile Open output file stream
* @param total Total login attempts
* @param failed Failed login attempts
* @param locked Total locked out accounts
*/
void writeReport(ofstream& outFile, int total, int failed, int locked);

int main() {
	ifstream inFile("access_log.txt");

	if (!inFile) {
		cout << "Error: Could not open access_log.txt" << endl;
		return 1;
	}

	ofstream outFile("security_report.txt");

	int totalAttempts = 0;
	int failedCount = 0;
	int lockedCount = 0;


	cout << " -- Processing Server Access Log -- " << endl;

	analyzeLogs(inFile, totalAttempts, failedCount, lockedCount);
	writeReport(outFile, totalAttempts, failedCount, lockedCount);
	inFile.close();
	outFile.close();



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

void writeReport(ofstream& outFile, int total, int failed, int locked) {
	double failureRate = calculateFailureRate(failed, total);
	outFile << "======================================" << endl; 
	outFile << "       SECURITY LOG REPORT " << endl; 
	outFile << "======================================" << endl;
	outFile << "\nTotal Attempts: " << total << endl;
	outFile << "Failed Attempts: " << failed << endl;
	outFile << "Locked Accounts: " << locked << endl;
	outFile << fixed << setprecision(2);
	outFile << "Failure Rate: " << failureRate << "%" << endl;

}
