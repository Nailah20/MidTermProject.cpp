#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class WeekData {
public:
	int weekNumber;
	double milesWalked;
	WeekData(int week = 0, double miles = 0.0) : weekNumber(week), milesWalked(miles) {}
};
// Class to manage weekly reports
class WeeklyTracker {
private:
	WeekData* WeeklyData;
	int NumberOfWeeks;
	string fileName;

public:
	WeeklyTracker(int weeks, const string& file) : NumberOfWeeks(weeks), fileName(file) {
		WeeklyData = new WeekData[NumberOfWeeks];
	}
	~WeeklyTracker() {
		delete[] WeeklyData;
	}
	void loadData() {
		ifstream inFile(fileName);
		if (inFile.is_open()) {
			for (int i = 0; i < NumberOfWeeks; ++i) 
				inFile >> WeeklyData[i].weekNumber >> WeeklyData[i].milesWalked;
			inFile.close();
			cout << "Data loaded from " << fileName << endl;
		}
		else {
			cout << "No Data. Enter Miles for  " << NumberOfWeeks << "Weeks." << endl;
			for (int i = 0; i < NumberOfWeeks; ++i) {
				WeeklyData[i].weekNumber = i + 1;
				cout << "Enter Miles Walked for Week " << (i + 1) << ": ";
				while (!(cin >> WeeklyData[i].milesWalked)) {
					cout << "Invalid input. Please enter a number: " << (i + 1) << ": ";
					cin.clear(); // clear the error flag
					cin.ignore(10000, '\n'); // discard invalid input
				}
			}
			saveData();
		}
	}
	void saveData() {
		ofstream outFile(fileName);
		for (int i = 0; i < NumberOfWeeks; ++i) outFile << WeeklyData[i].weekNumber << " " << WeeklyData[i].milesWalked << endl;
		outFile.close();
		cout << "Data saved to " << fileName << endl;
	}

	WeekData* findWeek(int goalWeek) {
		for (int i = 0; i < NumberOfWeeks; ++i) {
			if (WeeklyData[i].weekNumber == goalWeek) 
				return &WeeklyData[i];
			
		}
		return nullptr;
	}
	void displayData() {
		cout << "Weekly Data:" << endl;
		for (int i = 0; i < NumberOfWeeks; ++i) {
			cout << "Week " << WeeklyData[i].weekNumber << ": " << WeeklyData[i].milesWalked << " miles" << endl;
		}
	}
};
	
int main() {
WeeklyTracker tracker(4, "weekly_data.txt");
	tracker.loadData();
	tracker.displayData();

	int SearchWeek = 1;
	WeekData* found = tracker.findWeek(SearchWeek);
	if (found) {
		cout << "Found Week " << found->weekNumber << ": " << found->milesWalked << " miles" << endl;
	} else {
		cout << "Week " << SearchWeek << " not found." << endl;
	}
	return 0;
}
