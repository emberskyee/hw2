// Homework #2: Ember Roberts, Nyla Spencer, Tahreem Khan
#include <iostream>
#include <cstdlib> // Lines 3 and 4 are for seeding the random number generator
#include <ctime>
#include <windows.h> // included for the Sleep() function
using namespace std;

class Wheel {
protected:
	int minValue;
	int maxValue;
	int winsInARow; // For tracking how many wins the house has in a row, necessary for hard mode
	bool firstAttemptDbl{ false }; // Line 13 is for when the player chooses to double, line 14 is for when they choose to halve bet
	bool firstAttemptHalf{ false }; // These are here to track whether or not the player has changed their bet for the functionality of hard mode and 2 in a row tries
	// Without the above code the two tries would be counted separately
public:
	virtual int spin(int playerSpin) {
		return minValue + (rand() % ((maxValue - minValue) + 1)); // This line calculates a random number between the min and max;
	}
	// Getters (accessors)
	int getMax() {
		return maxValue;
	}
	int getMin() {
		return minValue;
	}
	int getWins() {
		return winsInARow;
	}
	// Setters (mutators)
	void setRange(int min, int max) {
		minValue = min;
		maxValue = max;
	}
	void setWins(int value) {
		winsInARow += value;
	}
	void setAttemptDbl(bool TorF) {
		firstAttemptDbl = TorF;
	}
	void setAttemptHalf(bool TorF) {
		firstAttemptHalf = TorF;
	}
	// Default constructor, with default range being 1 to 10, and desctructor
	Wheel(int minValue = 1, int maxValue = 10, int winsInARow = 0, bool firstAttempt = false) : 
		minValue(minValue), maxValue(maxValue), winsInARow(winsInARow), firstAttemptDbl(firstAttempt), firstAttemptHalf(firstAttempt) {}
	~Wheel() {}
};

class hardWheel : public Wheel {
public:
	int spin(int playerSpin) {
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
	// Constructors and destructor
	hardWheel(int minValue = 1, int maxValue = 10, int winsInARow = 0) : Wheel(minValue, maxValue, winsInARow) {}
	~hardWheel() {}
};

class Player {
private:
	double money{};
	Wheel wheel;

public:
	int spinWheel() {
		return wheel.Wheel::spin(0);
	}
	// Getters (accessors)
	int getMoney() {
		return money;
	}
	// Setters (mutators)
	void setMoney(double value) { // For loss of points, main function will have code that enters a negative value into the function
		money += value;
	}
	void setRange(int min, int max) {
		wheel.setRange(min, max);
	}
	// Constructor to set money to 0 by default, and destructor for outputting cash out amount at the end
	Player(double startingMoney = 0.0) : money(startingMoney) {}
	~Player() {
		cout << "\nThanks for playing!\n" << "Final cash out: $" << money << endl;
	}
};

int main() {
	int min;
	int max;
	double deposit;
	Wheel* house;
	Player player;
	bool hardMode;

	cout << "********************************* GAME START *********************************" << endl;
	cout << "How much money would you like to deposit to start with?\n";
	cin >> deposit;
	player.setMoney(deposit);

	while (deposit <= 0) {
		cout << "Please enter an amount that is positive and nonzero: " << endl;
		cin >> deposit;
	}

	cout << "\nStarting balance: $" << player.getMoney() << endl;
	cout << "\nWould you like to play on HARD mode?" << endl << "1. Yes\n0. No\n";
	cin >> hardMode;

	if (hardMode) {
		cout << "You have selected HARD mode. Good luck!\n" << endl;
		house = new hardWheel;
	}
	else {
		cout << "You have selected NORMAL mode. Good luck!\n" << endl;
		house = new Wheel;
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

	srand(time(0)); // Used to seed random number generator each time code is ran to ensure completely random results

	player.setRange(min, max);
	house->setRange(min, max); // In normal mode house will have same values as player throughout, in hard it will have the same at the beginning

	char continuePlaying{};
	do {
		int playerSpin = 0;
		int houseSpin = 0;
		double playerBet = 0.0;
		int choice = 0;

		cout << "\nWhat would you like to do?\n" << "1. See balance\n2. Make a bet" << endl;
		cin >> choice;

		while (choice == 1) {
			cout << "\nPlayer balance: $" << player.getMoney() << endl;
			cout << "\nWhat would you like to do?\n" << "1. See balance\n2. Make a bet" << endl;
			cin >> choice;
		}

		cout << "\nHow much would you like to bet? " << endl;
		cin >> playerBet;

		while (playerBet <= 0 || playerBet > player.getMoney()) {
			cout << "Please enter a positive number that is less than your current balance: " << endl;
			cin >> playerBet;
		}

		// Player spins first
		playerSpin = player.spinWheel();

		int changeBet = 0;
		cout << "\nYour wheel landed on: " << playerSpin << endl;
		cout << "\nWould you like to change your bet?\n" << "1. Keep bet\n2. Double bet\n3. Cut bet in half" << endl;
		cin >> changeBet;

		while (changeBet == 2 && ((playerBet * 2) > player.getMoney())) {
			cout << "Whoops! You don't have enough money to do this." << endl;
			cout << "\nWould you like to change your bet?\n" << "1. Keep bet\n2. Double bet\n3. Cut bet in half" << endl;
			cin >> changeBet;
		}

		if (changeBet == 1) {
			cout << "\nThe house is spinning..." << endl;
			Sleep(2000); // Puts a ~2 second delay between spins for added realism, input is in ms (function obtained from ChatGPT)
			// House spins
			if (hardMode) {
				houseSpin = house->spin(playerSpin);
			}
			else {
				houseSpin = house->Wheel::spin(playerSpin);
			}
		}
		else if (changeBet == 2) {
			playerBet *= 2;
			cout << "\nBet doubled. New bet: $" << playerBet << endl;

			house->setAttemptDbl(true);
			cout << "\nThe house now has two chances to beat you!" << endl;
			cout << "\nFirst attempt..." << endl;
			Sleep(2000);
			if (hardMode) {
				houseSpin = house->spin(playerSpin);
			}
			else {
				houseSpin = house->Wheel::spin(playerSpin);
			}
			house->setAttemptDbl(false);
			if (playerSpin > houseSpin) {
				cout << "\nHouse lost! Final attempt..." << endl;
				Sleep(2000);
				if (hardMode) {
					houseSpin = house->spin(playerSpin);
				}
				else {
					houseSpin = house->Wheel::spin(playerSpin);
				}
			}
		}
		else if (changeBet == 3) {
			playerBet /= 2;

			house->setAttemptHalf(true);
			cout << "\nBet halved. New bet: $" << playerBet << endl;
			cout << "\nThe house will win now have to spin twice in a row. House wins the round if it wins both of its tries." << endl;
			cout << "\nFirst attempt..." << endl;
			Sleep(2000);
			if (hardMode) {
				houseSpin = house->spin(playerSpin);
			}
			else {
				houseSpin = house->Wheel::spin(playerSpin);
			}
			house->setAttemptHalf(false);
			if (playerSpin > houseSpin) {
				continue;
			}
			else {
				cout << "\nHouse won first attempt! Final attempt..." << endl;
				Sleep(2000);
				if (hardMode) {
					houseSpin = house->spin(playerSpin);
				}
				else {
					houseSpin = house->Wheel::spin(playerSpin);
				}
			}
		}

		if (playerSpin > houseSpin) {
			cout << "\nYou won the round!\n" << "House spin: " << houseSpin << "\nYour spin: " << playerSpin << endl;
			cout << "\n+$" << playerBet << endl;
			player.setMoney(playerBet);
		}
		else if (playerSpin == houseSpin) {
			cout << "\nRound resulted in a tie! The house wins all ties.\n" << "House spin: " << houseSpin << "\nYour spin: " << playerSpin << endl;
			cout << "\n-$" << playerBet << endl;
			player.setMoney(-playerBet);
		}
		else {
			cout << "\nThe house won the round!\n" << "House spin: " << houseSpin << "\nYour spin: " << playerSpin << endl;
			cout << "\n-$" << playerBet << endl;
			player.setMoney(-playerBet);
		}

		if (player.getMoney() <= 0) {
			cout << "\nYou lost all of your money! Better luck next time. " << endl;
			cout << "********************************* GAME OVER *********************************" << endl;
		}
		else {
			cout << "\nWould you like to continue playing? (y/n)" << endl;
			cin >> continuePlaying;
		}

		if (hardMode) { // Print out house's wheel after every round so player can keep track
			cout << "\nValues on house's wheel: " << house->getMin() << " - " << house->getMax() << endl;
		}
	} while ((continuePlaying == 'y' || continuePlaying == 'Y') && (player.getMoney() > 0));

	delete house;
	return 0;
}
