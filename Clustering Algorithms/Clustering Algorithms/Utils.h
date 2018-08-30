#pragma once
#include "ShortSolution.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


using namespace std;

class Utils
{
public:
	string colorTable(int colorIndex);
	void showSolution(ShortSolution *solution);
	void testShowSolution(ShortSolution *solution);


	Utils();
	~Utils();
private:
	int a;
};


