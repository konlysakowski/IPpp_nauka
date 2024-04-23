#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>

using namespace std;

int** alokacja(int numRows, int numCols);
void zapis(const char* nazwaPliku, int** tab2D, int numRows, int numCols);
int** odczyt(const char* nazwaPliku, int numRows, int numCols);