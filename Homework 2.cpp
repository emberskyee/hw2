// Homework #2: Ember Roberts, Nyla Spencer, Tahreem Khan
#include <iostream>
#include <string>
#include <random>
using namespace std;

class Wheel {
private:
	int minValue;
	int maxValue;
public:
	int spin() {
		int range = maxValue - minValue;
		return minValue + (rand() % range + 1);
	}
	// Getters (accessors)
	int getMin() {
		return minValue;
	}
	int getMax() {
		return maxValue;
	}
	// Setters (mutators)
	void setRange(int min, int max) {
		minValue = min;
		maxValue = max;
	}
	
	// Default constructor, with default range being 1 to 10
	Wheel(int minValue = 1, int maxValue = 10) : minValue(minValue), maxValue(maxValue) {}
};

class Player {
private:
	int money{};
	int bet{};
	Wheel wheel;

public:
	int spinWheel() {
		int result = wheel.spin();
		return result;
	}
	// Getters (accessors)
	int getMoney() {
		return money;
	}
	int getBet() {
		return bet;
	}
	int getWheel() {
		int slots = (wheel.getMax() - wheel.getMin()) + 1;
		return slots;
	}

	// Setters (mutators)
	void setMoney(int value) { // For loss of points, main function will have code that enters a negative value into the function
		money += value;
	}
	void setBet(int value) {

	}
	void setRange(int min, int max) {
		wheel.setRange(min, max);
	}

	// Constructors
	Player(int money = 0) : money(money) {}
};

int main() {
	int min;
	int max;
	Wheel house;
	Player player;
	bool hardMode;

	cout << "********************************* GAME START *********************************" << endl;
	cout << "Would you like to play on HARD mode?" << endl << "1. Yes\n0. No\n";
	cin >> hardMode;

	if (hardMode) {
		cout << "You have selected HARD mode. Good luck!\n" << endl;
	}
	else {
		cout << "You have selected NORMAL mode. Good luck!\n" << endl;
	}

	cout << "Please enter the range of values you would like your wheel to include: " << endl;
	cout << "Minimum value: " << endl;
	cin >> min;
	cout << "Maximum value: " << endl;
	cin >> max;

	int range = (max - min) + 1; // Add one to range to obtain the actual amount of slots on the wheel.
	while (range < 6 || range > 20) {
		cout << "Range of numbers is too small or too large. Please pick a range that is at least 6 and at most 20: " << endl;
		cout << "Minimum value: " << endl;
		cin >> min;
		cout << "Maximum value: " << endl;
		cin >> max;

		range = (max - min) + 1; // Recalculate range each time to avoid infinite loop
	}

	player.setRange(min, max);
	//cout << player.getWheel() << endl; this line is just for testing

	return 0;
}
