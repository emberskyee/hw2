#include "wheels.h"
#include <cstdlib>
#include <ctime>
using namespace std;

// Class DEFINITIONS here

// Regular wheel class
// Default constructor, with default range being 1 to 10, and desctructor
Wheel::Wheel(int minValue, int maxValue, int winsInARow, bool firstAttempt) :
    minValue(minValue), maxValue(maxValue), winsInARow(winsInARow), firstAttemptDbl(firstAttempt), firstAttemptHalf(firstAttempt) {}
Wheel::~Wheel() {}

// Member function definitions
int Wheel::spin(int playerSpin) {
    return minValue + (rand() % ((maxValue - minValue) + 1)); // This line calculates a random number between the min and max;
}

int Wheel::getMax() {
    return maxValue;
}

int Wheel::getMin() {
    return minValue;
}

int Wheel::getWins() {
    return winsInARow;
}

void Wheel::setRange(int min, int max) {
    minValue = min;
    maxValue = max;
}

void Wheel::setAttemptDbl(bool TorF) {
    firstAttemptDbl = TorF;
}

void Wheel::setAttemptHalf(bool TorF) {
    firstAttemptHalf = TorF;
}

// Hard mode wheel derived class
// Constructor and destructor
hardWheel::hardWheel(int minValue, int maxValue, int winsInARow) : Wheel(minValue, maxValue, winsInARow) {}
hardWheel::~hardWheel() {}

int hardWheel::spin(int playerSpin) {
	int spinValue = minValue + (rand() % ((maxValue - minValue) + 1));
	if (((playerSpin < spinValue) || (playerSpin == spinValue)) && (!(firstAttemptHalf))) {
		winsInARow++;
		if (((winsInARow % 2) == 0) && (winsInARow != 0) && (((maxValue - minValue) + 1) >= 6) && (((maxValue - minValue) + 1) <= 20)) {
			maxValue--;
			cout << "\nHouse won twice in a row! Decreasing values on house's wheel..." << endl;
		}
	}
	else if ((playerSpin > spinValue) && (((maxValue - minValue) + 1) >= 6) && (((maxValue - minValue) + 1) <= 20) && !(firstAttemptDbl)) {
		maxValue++;
		winsInARow = 0;
		cout << "\nHouse lost! Increasing number of slots on house's wheel...\n";
	}
	return spinValue;
}
