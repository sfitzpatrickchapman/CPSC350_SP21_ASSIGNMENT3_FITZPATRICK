#include "Environment.h"


Environment::Environment() { }


Environment::Environment(int x, int y, int density, char boundary) { //random environment
	boundaryType = boundary;
	columnsX = x;
	rowsY = y;

	/* Randomly fill the environments with either '-' or 'X' */
	//TODO: Instead of randomly fill them all up, fill them up organically
	for (int i = 0; i < z; i++) { //z is number of dimensions (generations)
		environments[i] = (char*)malloc(columnsX * rowsY); //allocates memory for total amt of cells (x * y)

		bool cellTrue;
		for (int j = 0; j < (columnsX * rowsY); j++) {
			cellTrue = (rand() % 100) < density; //calculates the odds depending on density
			if (cellTrue) 
				environments[i][j] = 'X';
			else
				environments[i][j] = '-';
		}
	}
}


Environment::Environment(string fileName, char boundary) { //inputted environment
	boundaryType = boundary;

	/* Open file w/ error checking */
	ifstream ifile(fileName);
	if (ifile.is_open()) {
		string line;
		char* buffer;
		int bufferPosition = 0;
		int counter = 0;

		while (getline(ifile, line)) {
			if (counter == 0)
				rowsY = stoi(line); //convert line 1 to int and assign to rows
			else if (counter == 1) {
				columnsX = stoi(line); //convert line 2 to int and assign to columns
				buffer = (char*)malloc(columnsX * rowsY); //allocate memory at buffer
			}
			else {
				for (int i = 0; i < columnsX; i++) {
					buffer[bufferPosition++] = line[i];
				}
			}
			counter++;
		}
		environments[0] = buffer;
		// TODO: DELETE BUFFER WHEN IT'S NO LONGER BEING USED
		// (find it somewhere)

		ifile.close();
	}
	else { //Error handling for invalid files
		cout << fileName << " could not be opened." << endl;
		exit(1);
	}
}


Environment::~Environment() {
	//destruct
}


/* Core Functions */
void Environment::printEnvironments(int env) { 
	cout << "\nEnvironment generation " << env << ":" << endl;

	for (int i = 0; i < (columnsX * rowsY); i++) {
		cout << environments[env][i] << " ";

		if ((i + 1) % columnsX == 0) //print newline for every row
			cout << endl; //accurately illustrates 2D array
	}
	cout << endl;
}


int Environment::getNeighborVal(int cellIndex, int neighborNum) {
	int neighborIndex;

	/* Assume:
	0 1 2
	3 A 4
	5 6 7
	-A is spot w/ neighbors to be analyzed
	-Numbers are the labeled neighbors
	-In reality it is not 2D, it is like: ...012...3A4...567... */

	/* Calculate the neighbor index (depending on which neighbor) */
	if (neighborNum == 0) {
		neighborIndex = cellIndex - columnsX - 1;
	}
	else if (neighborNum == 1) {
		neighborIndex = cellIndex - columnsX;
	}
	else if (neighborNum == 2) {
		neighborIndex = cellIndex - columnsX + 1;
	}
	else if (neighborNum == 3) {
		neighborIndex = cellIndex - 1;
	}
	else if (neighborNum == 4) {
		neighborIndex = cellIndex + 1;
	}
	else if (neighborNum == 5) {
		neighborIndex = cellIndex + columnsX - 1;
	}
	else if (neighborNum == 6) {
		neighborIndex = cellIndex + columnsX;
	}
	else { // (neighborNum == 7)
		neighborIndex = cellIndex + columnsX + 1;
	}

	/* Return int 1 if cell exists and 0 otherwise */
	if (environments[0][neighborIndex] == 'X')
		return 1;
	else if (!environments[0][neighborIndex]) {
		//cout << "Returning -1" << endl;
		return -1;
	}
	else //if (environments[0][neighborIndex] == '-')
		return 0;
}


float Environment::getNeighborAvg(int cellIndex) {
	float neighborAmt;
	int existingNeighbors;

	/* Combine all neighbor values to later divide */
	if (getNeighborVal(cellIndex, 0) != -1) {
		cout << "Neighbor 0 exists" << endl;
		neighborAmt += getNeighborVal(cellIndex, 0);
		existingNeighbors++;
	}
	if (getNeighborVal(cellIndex, 1) != -1) {
		cout << "Neighbor 1 exists" << endl;
		neighborAmt += getNeighborVal(cellIndex, 1);
		existingNeighbors++;
	}
	if (getNeighborVal(cellIndex, 0) != -1) {
		cout << "Neighbor 2 exists" << endl;
		neighborAmt += getNeighborVal(cellIndex, 2);
		existingNeighbors++;
	}
	if (getNeighborVal(cellIndex, 0) != -1) {
		cout << "Neighbor 3 exists" << endl;
		neighborAmt += getNeighborVal(cellIndex, 3);
		existingNeighbors++;
	}
	if (getNeighborVal(cellIndex, 0) != -1) {
		cout << "Neighbor 4 exists" << endl;
		neighborAmt += getNeighborVal(cellIndex, 4);
		existingNeighbors++;
	}
	if (getNeighborVal(cellIndex, 0) != -1) {
		cout << "Neighbor 5 exists" << endl;
		neighborAmt += getNeighborVal(cellIndex, 5);
		existingNeighbors++;
	}
	if (getNeighborVal(cellIndex, 0) != -1) {
		cout << "Neighbor 6 exists" << endl;
		neighborAmt += getNeighborVal(cellIndex, 6);
		existingNeighbors++;
	}
	if (getNeighborVal(cellIndex, 0) != -1) {
		cout << "Neighbor 7 exists" << endl;
		neighborAmt += getNeighborVal(cellIndex, 7);
		existingNeighbors++;
	}

	return neighborAmt / existingNeighbors; //divide and return avg
}


bool Environment::checkNeighborNull(int cellIndex) {
	if (getNeighborVal(cellIndex, 0) != 0) {
		return true;
	}
	return false;
}


void Environment::simulate() {
	if (boundaryType == 'c') { //classic

	}
	else if (boundaryType == 'd') { //doughnut TODO
		cout << "Doughnut mode not finished yet." << endl;
	}
	else { //mirror TODO
		cout << "Mirror mode not finished yet." << endl;
	}
}