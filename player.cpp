#include "player.h"
#include "wheels.h"
#include <iostream>
using namespace std;

// Class DEFINITIONS here

int Player::spinWheel() {
	return wheel.Wheel::spin(0);
}
// Getters (accessors)
double Player::getMoney() {
	return money;
}
// Setters (mutators)
void Player::setMoney(double value) { // For loss of points, main function will have code that enters a negative value into the function
	money += value;
}
void Player::setRange(int min, int max) {
	wheel.setRange(min, max);
}
void Player::setGameStatus(bool TorF) {
	gameOver = TorF;
}

// Constructor to set money to 0 by default, and destructor for outputting cash out amount at the end
Player::Player(double startingMoney, bool gameOver) : money(startingMoney), gameOver(gameOver) {}
Player::~Player() {
	if (gameOver) {
		cout << "\nThanks for playing!\n" << "Final cash out: $" << money << endl;
	}
}
