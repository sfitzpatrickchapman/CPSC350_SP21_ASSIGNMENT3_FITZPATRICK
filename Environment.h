#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
using namespace std;

class Environment {
public:
	/* Constructors/Destructor */
	Environment();
	Environment(int x, int y, int density, char boundary, bool pausePreference, bool savePreference); //random
	Environment(string fileName, char boundaryType, bool pausePreference, bool savePreference); //given file
	~Environment();

	/* Core functions */
	void printEnvironments(int z);
	string getInputFileName();
	int getNeighborVal(int envGen, int cellIndex, int neighborNum);
	int getCellVal(int envGen, int cellIndex);
	float getNeighborAvg(int envGen, int cellIndex);
	bool isBoundary(int cellIndex);
	bool isLeftEdge(int cellIndex);
	bool isRightEdge(int cellIndex);
	bool isOutOfBounds(int cellIndex);
	void simulate();
	bool isEnvironmentEmpty();
	bool isEnvironmentStable();
	void saveFile();

	/* Aux/helper functions */


private:
	int columnsX;
	int rowsY;
	int envSize;
	char boundaryType;
	bool pausePref;
	bool savePref;
	string outputFile;
	const int z = 3; //number of dimensions (generations)
	char* environments[3]; //must be the same as z
};