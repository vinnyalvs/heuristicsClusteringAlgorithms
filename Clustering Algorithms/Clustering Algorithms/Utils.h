#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "ShortSolution.h"

using namespace std;

class Utils
{
public:
	string colorTable(int colorIndex);
	void showSolution(ShortSolution * solution);


	Utils();
	~Utils();
};


//
// Created by edson on 12/06/18.
//
