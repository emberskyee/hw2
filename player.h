#ifndef PLAYER_H
#define PLAYER_H

#include "wheels.h"
#include <iostream>

// Class DECLARATIONS here

class Player {
private:
	double money{};
	Wheel wheel;
	bool gameOver;
public:
	int spinWheel();
	// Getters (accessors)
	double getMoney();
	// Setters (mutators)
	void setMoney(double value);
	void setRange(int min, int max);
	void setGameStatus(bool TorF);

	// Constructor to set money to 0 by default, and destructor
	Player(double startingMoney = 0.0, bool gameOver = false);
	~Player();
};

#endif
