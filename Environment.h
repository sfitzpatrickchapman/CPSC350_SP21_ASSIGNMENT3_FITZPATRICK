#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Environment {
public:
	/* Constructors/Destructor */
	Environment();
	Environment(int x, int y, int density, char boundary); //random
	Environment(string fileName, char boundaryType); //given file
	~Environment();

	/* Core functions */
	void printEnvironments(int z);
	int getNeighborVal(int cellIndex, int neighborNum);
	float getNeighborAvg(int cellIndex);
	bool checkNeighborNull(int cellIndex);
	void simulate();

	/* Aux/helper functions */
	

private:
	int columnsX;
	int rowsY;
	char boundaryType;
	const int z = 3; //number of dimensions (generations)
	char* environments[3]; //must be the same as z
};