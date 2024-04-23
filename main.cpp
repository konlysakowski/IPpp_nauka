#include "funkcje.h"


int main()
{
	int numRows = 3, numCols = 5;
	auto tab = alokacja(numRows, numCols);
	
	zapis("pliczek.txt", tab, numRows, numCols);
	
	auto tab_2 = odczyt("pliczek.txt", numRows, numCols);

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			cout << tab_2[i][j] << " ";
		}
		cout << endl;
	}
}

