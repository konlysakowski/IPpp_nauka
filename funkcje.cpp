#include "funkcje.h"

int** alokacja(int numRows, int numCols)
{
	int size = 0;
	size |= numCols << 16;
	size |= numRows;

	int** tab2D = new int* [numRows];
	tab2D[0] = new int{ size };
	tab2D++;

	for (int i = 0; i < numRows; i++)
	{
		tab2D[i] = new int[numCols];
	}


	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			tab2D[i][j] = i * j;
		}
	}
	return tab2D;
}

void zapis(const char* nazwaPliku, int** tab2D, int numRows, int numCols)
{
	FILE* plik = nullptr;
	plik = fopen(nazwaPliku, "w+b");

	for (int i = 0; i < numRows; i++)
	{
		fwrite(tab2D[i], sizeof(int), numCols, plik);
	}

	fclose(plik);
}

int** odczyt(const char* nazwaPliku, int numRows, int numCols)
{

	FILE* plik = nullptr;
	plik = fopen(nazwaPliku, "r+b");

	auto tab = alokacja(numRows, numCols);

	for (int i = 0; i < numRows; i++)
	{
		fread(tab[i], sizeof(int), numCols, plik);
	}

	fclose(plik);

	return tab;
}