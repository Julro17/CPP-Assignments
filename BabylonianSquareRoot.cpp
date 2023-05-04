/*9-6-2019
This program takes a double input from the user and applies the Babylonian square root algorithm until a
number within 0.001 of the input's square root is found. The user may repeat the process as many times
as desired by entering "y" or "Y" when prompted ("N" or "n" to quit).*/

#include"iostream"
#include"limits"
#include"string"


using namespace std;

int validateInput(string &check) {
	string validInputs[4] = { "Y", "y", "N", "n"};

	for (auto i : validInputs) {
		if (check == i) {
			return 1;
		}
	}
	return 0;
}


//method for applying the Babylonian square root algorithm
double sroot(double in) {
	//format number output
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(3);

	//apply Babylonian square root algorithm to the input
	double guess = in / 2.0;

	do {
		double r = in / guess;
		guess = ((guess + r) / 2);

		cout << "Guessing " << guess << endl;

	} while (fabs(in - (guess * guess)) > 0.001); //apply the algorithm until guess is within 0.001 of the actual answer

	return guess;
}


int main() {
	char choice;
	string in;
	double userNum;
	int repeat;

	do {
		//reset the repeat indicator
		repeat = 1;
		
		cout << "Enter a positive digit & I will apply the Babylonian Square Root "
			<< "Algorithm until I am within .001 of the correct answer." << endl;


		while (repeat) {
			try {
				getline(cin, in);
				userNum = stod(in);

				//get user input until a positive digit is entered
				while (cin.fail() || userNum <= 0) {
					cin.clear();
					cout << "Invalid input. Please try again." << endl;
					cin >> userNum;
				}

				double result = sroot(userNum);

				cout << "You entered " << userNum << " The Babylonian Square Root Algorithm "
					<< "gives " << result << "." << "\nChecking: " << result << "*" << result
					<< "= " << (result * result) << endl;
				
				//indicate success so the while loop does not cause a repetition
				repeat = 0;
			}
			catch (...) {
				cin.clear();
				cout << "Invalid input. Please try again." << endl;
			}
		}
		
		//see whether user would like to repeat the process. validate their input and ask again if 
		//invalid.
		do {
			cin.clear();
			cout << "Continue (y/n)?" << endl;
			getline(cin, in);
		} while (validateInput(in) == 0);

	//only repeat if the user responds with Y or y
	} while (in == "Y" || in == "y");

	return 0;

}
