#ifndef WHEEL_H
#define WHEEL_H

#include <iostream>

// Class DECLARATIONS here

class Wheel {
protected:
	int minValue;
	int maxValue;
	int winsInARow; // For tracking how many wins the house has in a row, necessary for hard mode
	bool firstAttemptDbl{ false }; // Line 13 is for when the player chooses to double, line 14 is for when they choose to halve bet
	bool firstAttemptHalf{ false }; // These are here to track whether or not the player has changed their bet for the functionality of hard mode and 2 in a row tries
	// Without the above code the two tries would be counted separately
public:
	virtual int spin(int playerSpin);
	// Getters (accessors)
	int getMax();
	int getMin();
	int getWins();
	// Setters (mutators)
	void setRange(int min, int max);
	void setAttemptDbl(bool TorF);
	void setAttemptHalf(bool TorF);
	// Declaring constructor and desctructor
	Wheel(int minValue = 1, int maxValue = 10, int winsInARow = 0, bool firstAttempt = false);
	~Wheel();
};

class hardWheel : public Wheel {
public:
	int spin(int playerSpin);

	// Constructors and destructor
	hardWheel(int minValue = 1, int maxValue = 10, int winsInARow = 0);
	~hardWheel();
};

#endif
