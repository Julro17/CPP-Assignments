/*
* 9-10-19
* This program takes a long long integer input and "rolls" a pair of six-sided "dice" that many times. 
* After the rolling is complete, the number of times a given possible result occurred is
* shown and compared to the calculated odds, or expected # of times, of it occurring. The % 
* error between the expected and actual number of rolls is then calculated and tabulated as well. 
* The user can repeat this process as many times as desired. 
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <string>


using namespace std;

//The highest possible numeric result of a roll
const int MAX_ROLL = 12;
//The chance that each possible result (2-12) occurs
const double odds[] = { 0, 0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1 };
//Will store the results of the series of dice rolls.
int results[MAX_ROLL + 1];

//establish functions defined after main
long long int getUserNum();

void roll(long long int);

void findOdds(long long int*, long long int);

void setResults();

void printResults(long long int);

int validInput(string&);



int main() {

	//format numeric output
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(4);

	srand(time(NULL));

	string again;

	do {
		
		setResults();
		long long int numRolls;

		cout << "This program rolls two dice the specified number of times "
			<< "& tabulates the results as percentages."
			<< "\nEnter # rolls (positive int): " << endl;
		 
		numRolls = getUserNum();

		roll(numRolls);
		printResults(numRolls);
		
		do{
			cin.clear();
			cout << "Continue (y/n)?" << endl;
			getline(cin, again);
		} while (!validInput(again));

	}while (again == "Y" || again == "y");

	return 0;
}

//get and validate that user input is a positive long long int. Ask for input until one is received.
long long int getUserNum() {
	string in;
	long long int userNum = -1;
	int repeat = 1;

	while (repeat) {
		try {
			getline(cin, in);
			userNum = stoll(in);

			while (userNum <= 0) {
				cin.clear();
				cout << "Enter positive #" << endl;
				getline(cin, in);
				userNum = stoll(in);
			}

			repeat = 0;
		}
		catch (...) {
			cin.clear();
			cout << "Input invalid. Please try again." << endl;
		}
	}
	return userNum;
}

//validates input when program asks to continue
int validInput(string& check) {
	return (check == "Y" || check == "y" || check == "N" || check == "n");
}

//randomly generate a number (1-6) twice, then adds them together numRolls number of times
void roll(long long int numRolls) {
	
	for (long long int i = 1; i <= numRolls; i++) {
		results[((rand() % 6) + 1) + ((rand() % 6) + 1)]++;
	}
}

//sets value of all dice roll result array elements to 0
void setResults() {
	for (int i = 2; i <= MAX_ROLL; i++) {
		results[i] = 0;
	}
}

//formats and prints the actual and expected roll results in table format to the std output stream
void printResults(long long int rolls) {
	long long int resultOdds[MAX_ROLL + 2];
	findOdds(resultOdds, rolls);

		//first rows of tabular output
	cout << setw(10) << left << "Sum" << setw(10) << left << "#Rolled" << setw(10) << left << "Odds"
		<< setw(10) << left << "%Error" << endl;

	for (int i = 2; i <= MAX_ROLL; i++) {
		//format rows of output
		cout << setw(10) << left << i << setw(10) << left << results[i] << setw(10) << left
			<< resultOdds[i];

		cout << setw(10) << left
			<< (fabs((static_cast<double>(results[i]) - static_cast<double>(resultOdds[i]))) / static_cast<double>(resultOdds[i]) * 100.0)
			<< endl;
	}
}

//find the odds of rolling each possible result when the pair of dice are rolled the specified # of times
void findOdds(long long int *temp, long long int rolls) {
		for (int i = 2; i <= MAX_ROLL; i++) {
			temp[i] = odds[i] /36.0 * rolls;
		}
	}



