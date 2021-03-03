#include "Environment.h"


/* Constructors and Destructor */
Environment::Environment() {}


Environment::Environment(int x, int y, int density, char boundary, bool pausePreference, bool savePreference) { //random environment
	/* Set private class values */
	columnsX = x;
	rowsY = y;
	boundaryType = boundary;
	pausePref = pausePreference;
	savePref = savePreference;
	envSize = columnsX * rowsY;

	/* If saving output is prefered, get file name */
	if (savePreference)
		outputFile = getInputFileName();

	/* Allocate memory according to environment size &
	empty prior generations (which shouldn't exist yet) */
	environments[0] = (char*)malloc(envSize);
	environments[1] = NULL;
	environments[2] = NULL;

	/* Randomly fill the environment[0] with either '-' or 'X' */
	bool cellLifeTrue;
	for (int j = 0; j < (envSize); j++) {
		int randomInt = rand() % 100;
		cellLifeTrue = randomInt < density; //calculates density odds
		if (cellLifeTrue)
			environments[0][j] = 'X';
		else
			environments[0][j] = '-';
	}
}


Environment::Environment(string inputFileName, char boundary, bool pausePreference, bool savePreference) { //inputted environment
	/* Set private class values */
	boundaryType = boundary;
	pausePref = pausePreference;
	savePref = savePreference;

	/* reset/empty the prior generations */
	environments[1] = NULL;
	environments[2] = NULL;

	/* If saving output is prefered, get file name */
	if (savePreference)
		outputFile = getInputFileName();

	/* Open file w/ error checking */
	ifstream ifile(inputFileName);
	if (ifile.is_open()) {
		string line;
		char* buffer = NULL;
		int bufferPosition = 0;
		int counter = 0;

		while (getline(ifile, line)) { //while there is a line to read
			if (counter == 0) //first row of input file represents rows amount
				rowsY = stoi(line); //convert line 1 to int and assign to rows
			else if (counter == 1) { //second row of input file represents columns amount
				columnsX = stoi(line); //convert line 2 to int and assign to columns
				buffer = (char*)malloc(columnsX * rowsY); //allocate memory at buffer
			}
			else { //read through 2d environment and add values to buffer
				for (int i = 0; i < columnsX; i++) { //loops through one row
					buffer[bufferPosition++] = line[i]; //retrieves cell val
				}
			}
			counter++; //represents which row starting at 0
		}
		environments[0] = buffer; //assign buffer data to initial environment

		envSize = columnsX * rowsY; //set private variable
		ifile.close();
	}
	else { //Error handling for invalid files
		cout << inputFileName << " could not be opened." << endl;
		exit(1);
	}
}


Environment::~Environment() {
	//destruct?
}


/* Functions */
void Environment::printEnvironments(int envGen) {
	/* Loop through array and print as 2d matrix */
	for (int i = 0; i < (columnsX * rowsY); i++) {
		cout << environments[envGen][i] << " ";

		if ((i + 1) % columnsX == 0) // for every row,
			cout << endl; //create newline so it appears 2d
	}
	cout << endl;
}


string Environment::getInputFileName() {
	string fileName;

	/* Prompt, input input file name, and return */
	cout << "Please enter your output file name: ";
	cin >> fileName;
	cout << "Warning: Your file will not save if the simulation is infinite!" << endl << endl;
	return fileName;
}


int Environment::getCellVal(int envGen, int cellIndex) {
	/* If the value in that index in that environment is X
	return X, otherwise return 0 which represents a '-' */
	if (environments[envGen][cellIndex] == 'X')
		return 1;
	return 0;
}


int Environment::getNeighborVal(int envGen, int cellIndex, int neighborNum) {
	int neighborIndex;

	/* Assume:
	0 1 2
	3 A 4
	5 6 7
	-A is spot w/ neighbors to be analyzed
	-Numbers are the labeled neighbors
	-In reality it is not 2D, it is 1D like: ...012...3A4...567... */

	/* Calculate the neighbor index (depending on which neighbor) */
	if (neighborNum == 0)
		neighborIndex = cellIndex - columnsX - 1;
	else if (neighborNum == 1)
		neighborIndex = cellIndex - columnsX;
	else if (neighborNum == 2)
		neighborIndex = cellIndex - columnsX + 1;
	else if (neighborNum == 3)
		neighborIndex = cellIndex - 1;
	else if (neighborNum == 4)
		neighborIndex = cellIndex + 1;
	else if (neighborNum == 5)
		neighborIndex = cellIndex + columnsX - 1;
	else if (neighborNum == 6)
		neighborIndex = cellIndex + columnsX;
	else // (neighborNum == 7)
		neighborIndex = cellIndex + columnsX + 1;

	/* Return int 1 if cell exists and 0 otherwise */
	if (environments[envGen][neighborIndex] == 'X')
		return 1;
	else //if (environments[envGen][neighborIndex] == '-')
		return 0;
}


float Environment::getNeighborAvg(int envGen, int cellIndex) {
	int combinedNeighborAmt = 0; //total of all living neighbors
	int existingNeighbors = 0; //total of all surrounding cells

	for (int i = 0; i <= 7; i++) { //for all possible neighbors
		int neighborIndex = 0;

		/* 0 1 2
		   3 A 4
		   5 6 7
		Above is representation of neighboring indexes. For loop looks for all of those */

		/* If the current cell (cellIndex) is on a boundary, we must be careful about how
		we calculate the neighbors. For classic we must ignore neighbors out of bounds, for
		donut we must return other side of matrix, and for mirror we must return itself.
		Since we are dealing with a 1d array representing a matrix, we must use special math
		to get the correct indexes. See getCellVal params to find corresponding equations*/

		if (isBoundary(cellIndex)) { //if calculatig for outside cell, be careful
			if (boundaryType == 'c') { //apply classic mode neighbor additions
				if (i == 0) { //top left
					neighborIndex = cellIndex - (columnsX + 1); //calc top left index
					if (isLeftEdge(cellIndex) || isOutOfBounds(neighborIndex))
						continue; //if out of bounds, just ignore and continue
					else { //if cell is in bounds
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
						existingNeighbors++;
					}
				}
				else if (i == 1) { //top
					neighborIndex = cellIndex - columnsX; //calc top index
					if (isOutOfBounds(neighborIndex))
						continue; //if out of bounds, just ignore and continue
					else { //if cell is in bounds
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
						existingNeighbors++;
					}
				}
				else if (i == 2) { //top right
					neighborIndex = cellIndex - (columnsX - 1); //calc top right index
					if (isRightEdge(cellIndex) || isOutOfBounds(neighborIndex))
						continue; //if out of bounds, just ignore and continue
					else { //if cell is in bounds
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
						existingNeighbors++;
					}
				}
				else if (i == 3) { //left
					neighborIndex = cellIndex - 1; //calc left index
					if (isLeftEdge(cellIndex) || isOutOfBounds(neighborIndex))
						continue; //if out of bounds, just ignore and continue
					else { //if cell is in bounds
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
						existingNeighbors++;
					}
				}
				else if (i == 4) { //right
					neighborIndex = cellIndex + 1; //calc right index
					if (isRightEdge(cellIndex) || isOutOfBounds(neighborIndex))
						continue; //if out of bounds, just ignore and continue
					else { //if cell is in bounds
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
						existingNeighbors++;
					}
				}
				else if (i == 5) { //bottom left
					neighborIndex = cellIndex + (columnsX - 1); //calc bottom left index
					if (isLeftEdge(cellIndex) || isOutOfBounds(neighborIndex))
						continue; //if out of bounds, just ignore and continue
					else { //if cell is in bounds
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
						existingNeighbors++;
					}
				}
				else if (i == 6) { //bottom
					neighborIndex = cellIndex + columnsX; //calc bottom index
					if (isOutOfBounds(neighborIndex))
						continue; //if out of bounds, just ignore and continue
					else { //if cell is in bounds
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
						existingNeighbors++;
					}
				}
				else { //(if i == 7); bottom right
					neighborIndex = cellIndex + (columnsX + 1); //calc right index
					if (isRightEdge(cellIndex) || isOutOfBounds(neighborIndex))
						continue; //if out of bounds, just ignore and continue
					else { //if cell is in bounds
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
						existingNeighbors++;
					}
				}
			}
			else if (boundaryType == 'd') { //apply donut mode neighbor additions
				if (i == 0) { //top left corner; param requires bottom right (last index)
					neighborIndex = cellIndex - (columnsX + 1); //calc top left index
					if (isLeftEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, envSize - 1);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 1) { //top; param below is index of same column & bottom row
					neighborIndex = cellIndex - columnsX; //calc top index
					if (isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex + (columnsX) * (rowsY - 1));
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 2) { //top right corner; param reqiures bottom left
					neighborIndex = cellIndex - (columnsX - 1); //calc top right index
					if (isRightEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, columnsX * (rowsY - 1));
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 3) { //left; param below is index of right column & same row
					neighborIndex = cellIndex - 1; //calc left index
					if (isLeftEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex + (columnsX - 1));
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 4) { //right; param below is index of left column & same row
					neighborIndex = cellIndex + 1; //calc right index
					if (isRightEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex - (columnsX - 1));
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 5) { //bottom left corner; param requires top right
					neighborIndex = cellIndex + (columnsX - 1); //calc bottom left index
					if (isLeftEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, columnsX - 1);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 6) { //bottom; param below is index of same column & top row
					neighborIndex = cellIndex + columnsX; //calc bottom index
					if (isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex - (columnsX) * (rowsY - 1));
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else { //bottom right corner; param requires top left (first index)
					neighborIndex = cellIndex + (columnsX + 1); //calc right index
					if (isRightEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, 0);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}

				existingNeighbors = 8; //donut mode will always have all neighbors
			}
			else if (boundaryType == 'm') { //apply mirror mode neighbor additions
				if (i == 0) { //top left
					neighborIndex = cellIndex - (columnsX + 1); //calc top left index
					//If out of bounds, reflect & add cellIndex value
					if (isLeftEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 1) { //top
					neighborIndex = cellIndex - columnsX; //calc top index
					//If out of bounds, reflect & add cellIndex value
					if (isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 2) { //top right
					neighborIndex = cellIndex - (columnsX - 1); //calc top right index
					//If out of bounds, reflect & add cellIndex value
					if (isRightEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 3) { //left
					neighborIndex = cellIndex - 1; //calc left index
					//If out of bounds, reflect & add cellIndex value
					if (isLeftEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 4) { //right
					neighborIndex = cellIndex + 1; //calc right index
					//If out of bounds, reflect & add cellIndex value
					if (isRightEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 5) { //bottom left
					neighborIndex = cellIndex + (columnsX - 1); //calc bottom left index
					//If out of bounds, reflect & add cellIndex value
					if (isLeftEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else if (i == 6) { //bottom
					neighborIndex = cellIndex + columnsX; //calc bottom index
					//If out of bounds, reflect & add cellIndex value
					if (isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}
				else { //if (i == 7); bottom right
					neighborIndex = cellIndex + (columnsX + 1); //calc right index
					//If out of bounds, reflect & add cellIndex value
					if (isRightEdge(cellIndex) || isOutOfBounds(neighborIndex))
						combinedNeighborAmt += getCellVal(envGen, cellIndex);
					else //otherwise if cell is in bounds, add that value
						combinedNeighborAmt += getCellVal(envGen, neighborIndex);
				}

				existingNeighbors = 8; //mirror mode will always have all neighbors
			}
		}
		else { //if not a boundary, increment neighborAmt & existingNeighbors normally
			combinedNeighborAmt += getNeighborVal(envGen, cellIndex, i);
			existingNeighbors++;
		}
	}
	return ((float)combinedNeighborAmt / (float)existingNeighbors); //divide and return avg
}


bool Environment::isBoundary(int cellIndex) {
	/* Check if a cell index is a boundary */
	if (cellIndex <= columnsX - 1) //check top
		return true;
	else if (cellIndex % columnsX == 0) //check left side
		return true;
	else if ((cellIndex + 1) % columnsX == 0) //check right size
		return true;
	else if (cellIndex >= (envSize - columnsX) && (cellIndex < envSize)) //check bottom
		return true;
	else //if all boundary checks passed, it is not a boundary
		return false;
}


bool Environment::isLeftEdge(int cellIndex) {
	/* Calculate if index is on left edge */
	if (cellIndex % columnsX == 0) {
		return true;
	}
	return false;
}


bool Environment::isRightEdge(int cellIndex) {
	/* Calculate if index is on right edge */
	if ((cellIndex + 1) % columnsX == 0) {
		return true;
	}
	return false;
}


bool Environment::isOutOfBounds(int cellIndex) {
	/* Calculate if index is out of bounds */
	if ((0 > cellIndex) || (cellIndex > (envSize - 1))) {
		return true;
	}
	return false;
}


void Environment::simulate() {
	int counter = 0; //for tracking generation iterations
	char* newGen; //create temp environment pointer

	/* Simulation Loop */
	while (true) {
		newGen = (char*)malloc(envSize); //allocate memory for temp

		/* For the current environment, calculate all of the future
		cells and put them in newGen as a temporary environment */
		for (int i = 0; i < envSize; i++) {
			/* Create avg vars */
			int divisor = 3; //for calculating avg
			float currGenAvg = 0.0;
			float priorGenAvg = 0.0;
			float oldestGenAvg = 0.0;
			float pastGenAvg = 0.0;

			/* For each cell inactive envs, find n averages */
			currGenAvg = getNeighborAvg(0, i); //gen 0

			if (counter > 0) //if at least 1 gen simulated
				priorGenAvg = getNeighborAvg(1, i); //gen 1
			else if (counter > 1) //if at least 2 gens simulated
				oldestGenAvg = getNeighborAvg(2, i); //gen 2

			/* If the sumulation has recently started,
			adjust the divisor so avg division works */
			if (counter == 0)
				divisor = 1;
			else if (counter == 1)
				divisor = 2;

			// Calculate the average of all the generations
			pastGenAvg = (currGenAvg + priorGenAvg + oldestGenAvg) / divisor;

			/* Properly populate newGen, which will later go into enviornment[0] */
			if (pastGenAvg < 0.150)
				newGen[i] = '-'; //cell was a computer scientist
			else if ((pastGenAvg >= 0.150) && (pastGenAvg < 0.251))
				newGen[i] = environments[0][i]; //stays the same
			else if ((pastGenAvg >= 0.251) && (pastGenAvg < .351))
				newGen[i] = 'X'; //cell remains or is born
			else //if (pastGenAvg > 0.351)
				newGen[i] = '-'; //cell dies from overcrowding
		}

		/* Cycling environments whilst considering simulation youth */
		if (counter >= 2)
			free(environments[2]); //delete environments[2] in memory once it starts to exist
		if (counter >= 1)
			environments[2] = environments[1]; //shift environment 1 to 2
		if (counter >= 0)
			environments[1] = environments[0]; //shift environment 0 to 1
		environments[0] = newGen; //set environment 0 to the newly calculated values

		/* Print environment 0 */
		cout << "Generation " << counter << endl;
		printEnvironments(0);

		/* Pause after every cycle is pause preference is true */
		if (pausePref) {
			cout << "Press <ENTER> to continue: " << endl;
			cin.ignore();
		}

		/* Check if environments have reached equilibrium. If so, save, and prompt to exit */
		if (isEnvironmentEmpty()) {
			if (savePref) //save file (if requested)
				saveFile();

			/* Prompt to exit */
			cout << "The environment is empty!" << endl;
			cout << "Press <ENTER> to exit: " << endl;
			cin.ignore();
			exit(0);
		}
		else if ((counter > 0) && (isEnvironmentStable())) {
			cout << "The environment has stabilized!" << endl;

			if (savePref) //save file (if requested)
				saveFile();

			/* Prompt to exit */
			cout << "Press <ENTER> to exit: " << endl;
			cin.ignore();
			exit(0);
		}

		counter++;
	}
}


bool Environment::isEnvironmentEmpty() {
	/* Searches for living cell and returns false if found */
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < envSize; j++)
			if (environments[i][j] == 'X') //[environmentGen][index]
				return false;
	}
	return true; //if none found, then env empty
}


bool Environment::isEnvironmentStable() {
	/* Loop through all envs and compare them to see if they are equal to each other */
	for (int i = 0; i < envSize; i++) {
		if ((environments[0][i] == environments[1][i]) && (environments[1][i] == environments[2][i]))
			continue;
		else
			return false;
	}
	return true; //if they're all the same
}


void Environment::saveFile() {
	/* Instantiate and open file to write to */
	fstream writeFile;
	writeFile.open(outputFile, ios::out);

	/* Write to saveFile just how input.txt is formatted */
	writeFile << rowsY << endl;
	writeFile << columnsX << endl;

	/* Recycled printEnvironments() for writing */
	for (int i = 0; i < (envSize); i++) {
		writeFile << environments[0][i];

		if ((i + 1) % columnsX == 0) //print newline for every row
			writeFile << endl; //accurately illustrates 2D array
	}

	writeFile.close();
	cout << "File Saved as " << outputFile << "!" << endl;
}