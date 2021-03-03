#include <iostream>
#include <cctype>
#include <string>
#include <math.h>
#include "Environment.h"
using namespace std;


char getConfigType() { // TODO: MAKE THIS RETURN CONFIGURATION OR INSTANTIATE ONE IN HEAP
	char configInput;

	/* Config prompt & input */
	cout << "Which configuration would you like to use?" << endl;
	cout << "Enter \"r\" for random or \"f\" for a flat file configuration: ";
	cin >> configInput;

	/* Improper & proper config input handling */
	while ((configInput != 'r') && (configInput != 'f')) {
		cout << "Error: Invalid configuration input! Please try again." << endl;
		cout << "Enter \"r\" for random or \"f\" for a flat file configuration: ";
		cin >> configInput;
	}
	return configInput;
}


char getBoundaryType() {
	char boundaryInput;

	/* Boundary prompt & input */
	cout << "Which boundary mode would you like to use?" << endl;
	cout << "Enter \"c\" for classic mode, \"d\" doughnut mode, or \"m\" for mirror mode: ";
	cin >> boundaryInput;

	/* Improper & proper boundary input handling */
	while ((boundaryInput != 'c') && (boundaryInput != 'd') && (boundaryInput != 'm')) {
		cout << "Error: Invalid boundary input! Please try again." << endl;
		cout << "Enter \"c\" for classic mode, \"d\" doughnut mode, or \"m\" for mirror mode: ";
		cin >> boundaryInput;
	}

	return boundaryInput;
}


int getColumnsX() { //TODO: Type checking
	int x;

	/* Prompt for columns amt, input, and return */
	cout << "Columns (enter integer): ";
	cin >> x;
	return x;
}


int getRowsY() {//TODO: Validate x as an integer
	int y;

	/* Prompt for columns amt, input, and return */
	cout << "Rows (enter integer): ";
	cin >> y;
	return y;
}


int getDensity() { //TODO: Type checking
	float density;

	/* Prompt and input density as a float */
	cout << "Density (enter decimal greater than zero and less than or equal to one): ";
	cin >> density;

	/* Handle improper imput */
	while ((density < 0) || (density > 1)) {
		cout << "Error: Invalid input! Make sure the size is correct." << endl;
		cout << "Try again: ";
		cin >> density;
	}

	/* Convert density to an integer (round the float) for later use with % operator */
	density *= 100; //Ex: 0.54 -> 54
	int roundedDensityInt = round(density); //rounds & avoids truncation for precision

	return roundedDensityInt;
}


string getInputFileName() { //TODO: Type checking
	string fileName;

	/* Prompt for fileName, input, and return */
	cout << "Please enter your input file name: ";
	cin >> fileName;
	return fileName;
}


bool getPausePreference() {
	char pausePreference;

	/* Prompt for pause option between generations */
	cout << "Do you want the program to pause between generations?" << endl;
	cout << "Type \"y\" for yes and \"n\" for no: ";
	cin >> pausePreference;

	/* Handle improper input */
	while ((pausePreference != 'y') && (pausePreference != 'n')) {
		cout << "Error: Invalid boundary input! Please try again." << endl;
		cout << "Type \"y\" for yes and \"n\" for no: ";
		cin >> pausePreference;
	}

	/* Return true if yes and vise versa */
	if (pausePreference == 'y')
		return true;
	return false;
}


bool getSavePreference() {
	char savePreference;

	/* Prompt for save to output file option */
	cout << "Do you want the program to save the final environment after running?" << endl;
	cout << "Type \"y\" for yes and \"n\" for no: ";
	cin >> savePreference;

	/* Handle improper input */
	while ((savePreference != 'y') && (savePreference != 'n')) {
		cout << "Error: Invalid boundary input! Please try again." << endl;
		cout << "Type \"y\" for yes and \"n\" for no: ";
		cin >> savePreference;
	}

	/* Return true if yes and vise versa */
	if (savePreference == 'y')
		return true;
	return false;
}


int main(int argc, char** argv) {
	cout << "\nWelcome to Game of Life!" << endl;

	/* Get different program guidelines from user input */
	char configType = getConfigType();
	char boundaryType = getBoundaryType();
	bool pausePreference = getPausePreference();
	bool savePreference = getSavePreference();

	if (configType == 'r') { //calling constructor for random environment

		/* Prompt and input for dimensions and density */
		cout << "Which dimensions and density would you like to use?" << endl;
		int x = getColumnsX();
		int y = getRowsY();
		int roundedDensityInt = getDensity();

		/* Instantiate and simulate*/
		Environment life(x, y, roundedDensityInt, boundaryType, pausePreference, savePreference);
		life.simulate();
	}
	else { //calling constructor for inputted environment configuration
		string inputFileName = getInputFileName(); //get file name

		/* Instantiate and simulate*/
		Environment life(inputFileName, boundaryType, pausePreference, savePreference);
		life.simulate();
	}

	return 0;
}