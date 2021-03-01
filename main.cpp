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
	cout << "Columns (enter integer): ";
	cin >> x;
	
	return x;
}


int getRowsY() {
	int y;
	cout << "Rows (enter integer): ";
	cin >> y;
	//TODO: Validate x as an integer
	return y;
}


int getDensity() { //TODO: Type checking
	float density;

	/* Prompt and input density as a float */
	cout << "Density (enter decimal greater than zero and less than or equal to one): ";
	cin >> density;

	/* Convert density to an integer (round the float) for later use with % operator */
	density *= 100; //Ex: 0.54 -> 54
	int densityInt = round(density); //rounds & avoids truncation for precision

	return densityInt;
}


string getFileName() { //TODO: Type checking
	string fileName;
	cout << "Please enter your input file name: ";
	cin >> fileName;

	return fileName;
}


int main(int argc, char** argv) {
	cout << "\nWelcome to Game of Life!" << endl;

	char configType = getConfigType();
	char boundaryType = getBoundaryType();

	if (configType == 'r') { //calling constructor for random environment
		/* Prompt and input for dimensions and density */
		cout << "Which dimensions and density would you like to use?" << endl;
		int x = getColumnsX();
		int y = getRowsY();
		int density = getDensity();

		Environment life(x, y, density, boundaryType);
		life.printEnvironments(0);
	}
	else { //calling ocnstructor for inputted environment configuration
		string fileName = getFileName(); //get file name

		Environment life(fileName, boundaryType);
		life.printEnvironments(0);
		cout << "Neighbor avg 0: " << life.getNeighborAvg(0) << endl;
		//cout << "Neighbor avg 3: " << life.getNeighborAvg(3) << endl;
		//cout << "Neighbor avg 6: " << life.getNeighborAvg(6) << endl;

		//cout << "Neighbor avg 6: " << life.getNeighborAvg(6) << endl;
		//cout << "Neighbor avg 12: " << life.getNeighborAvg(12) << endl;
		//cout << "Neighbor avg 18: " << life.getNeighborAvg(18) << endl;
		//cout << "Neighbor avg 24: " << life.getNeighborAvg(24) << endl;
		//cout << "Neighbor avg 30: " << life.getNeighborAvg(30) << endl;
	}

	return 0;
}