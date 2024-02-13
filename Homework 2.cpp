// Homework #2: Ember Roberts, Nyla Spencer, Tahreem Khan
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Wheel {
private:
	int minValue;
	int maxValue;
public:
	int spin() {
		return minValue + rand() % ((maxValue - minValue) + 1); //tahreem changed the 
	}
	// Getters (accessors)
	void setRange(int minValue, int maxValue){
		minValue = minValue;
		maxValue = maxValue;
	}
	int getMax() {
		return maxValue;
	}
	int getMin() {
		return minValue;
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
	int getWheel() {
		int slots = (wheel.getMax() - wheel.getMin()) + 1;
		return slots;
	}

	// Setters (mutators)
	void setMoney(int value) { // For loss of points, main function will have code that enters a negative value into the function
		money += value;
	}
	void setRange(int min, int max) {
		wheel.setRange(min, max);
	}

	// Constructors
	Player(int startMoney = 100, int min = 1, int max = 10) : money(startMoney), wheel(min, max) {}

	char chooseAction() {
		char choice;
		cout << "Choose your action: (d)ouble, (h)alve, (k)eep: ";
		cin >> choice;
		return choice;
	}
};

int main() {
	int min;
	int max;
	Wheel house;
	Player player;
	bool hardMode;

	cout << "********************************* GAME START *********************************" << endl;
	cout << "Starting amount : $" << player.getMoney() << endl;
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

	//int range = (max - min) + 1; // Add one to range to obtain the actual amount of slots on the wheel.
	while (min > max || max - min + 1 < 6 || max - min + 1 > 20) {
		cout << "Range of numbers is too small or too large. Please pick a range that is at least 6 and at most 20: " << endl;
		cout << "Minimum value: " << endl;
		cin >> min;
		cout << "Maximum value: " << endl;
		cin >> max;

	//	range = (max - min) + 1; // Recalculate range each time to avoid infinite loop
	}

	player.setRange(min, max);
	//cout << player.getWheel() << endl; this line is just for testing

	char continuePlaying;
	bool lost = false;
	do {
		int playerSpin = 0;
		int houseSpin = 0;
		// Ask for bet
		double playerBet = 0.0;

		int choice = 0;

		cout << "What would you like to do?\n" << "1. See money\n2. Make a bet\n" << endl;
		cin >> choice;

		while (choice == 1) {
			cout << "Player balance: $" << player.getMoney() << endl;
			cout << "What would you like to do?\n" << "1. See money\n2. Make a bet\n" << endl;
			cin >> choice;
		}

		cout << "How much would you like to bet? " << endl;
		cin >> playerBet;

		while (playerBet < 0 | cin.fail() | playerBet > player.getMoney()) {
			cout << "Please enter a positive integer that is less than your current balance: " << endl;
			cin >> playerBet;
		}

		playerSpin = player.spinWheel();
		houseSpin = house.spin();

		int changeBet = 0;
		cout << "Your wheel landed on: " << playerSpin << endl;
		cout << "Would you like to change your bet?\n " << "1. Don't change\n2. Double bet\n3. Cut bet in half" << endl;
		cin >> changeBet;

		if (changeBet == 2) {
			playerBet *= 2;
		}
		else if (changeBet == 3) {
			playerBet /= 2;
		}

		if (playerSpin > houseSpin) {
			cout << "House wheel landed on: " << houseSpin << endl;
			cout << "You won this round! +$" << playerBet << endl;
		}
		else {
			cout << "House wins the round!\n" << "House spin: " << houseSpin << "\nYour spin: " << playerSpin << endl;
			cout << "-$" << playerBet << endl;
		}

		if (player.getMoney() <= 0) {
			lost = true;
			cout << "You lost all of your money! Better luck next time. " << endl;
			cout << "********************************* GAME OVER *********************************" << endl;
		}
		else {
			cout << "Would you like to continue playing? (y/n)" << endl;
			cin >> continuePlaying;
		}
		continuePlaying = tolower(continuePlaying);
	} while (continuePlaying == 'y' & (!lost));

	return 0;
}
