#include "Input.h"
#include <fstream>
#include <iostream>


using namespace std;

Input::Input()
{
	numObj = 0;
	this->objects.reserve(300);
}


Input::~Input()
{
}

Input* Input::instance = 0;

Input * Input::getInstance()
{
	if (instance == 0)
	{
		instance = new Input();
	}

	return instance;
}

void Input::addObject(Object *object)
{
	this->objects.push_back(object);
}



void Input::readObjectInstances(string file)
{
	int m = 0;
	int n = 0;
	int count = 0;
	char comma;
	ifstream f;
	int id = 0;
	vector <Object*> objects;
	vector <double> attrs;
	int i = 0;
	f.open(file);
	if (f.is_open()) {
		f >> m;
		f >> comma;
		f >> n;
		while (true) {
			double value;
			if (count == n + 2)
				count = 0;
			if ((count % 2 == 0)) {
				if (!(f >> value)) {
					break;
				}
				else {
					if (count == 0) {
						objects.push_back(new Object(value));
						i++;
					}
					if (count == 2 || count == 4) {
						objects[i - 1]->addNewDoubleOrigAttr(value);


					}
				}
			}
			else {
				if (!(f >> comma)) {
					break;
				}
			}
			count++;
			this->objects = objects;

		}

		cout << "Leitura do arquivo concluida. Num Obj: " << m << endl;
		/*
		for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
			cout << "Objeto: " << (*it)->getId() << "Attr: " << (*it)->getOrigDoubleAttr(0) << " " << (*it)->getOrigDoubleAttr(1) <<  endl;

		} */

	}
	else {
		cerr << "Couldn't open file!" << endl;
	}
}

void Input::normEntry()
{
	const int numAttr = 2;
	double normAttrs[numAttr];
	double minDoubleAttrs[numAttr], maxDoubleAttrs[numAttr];
	for (int i = 0; i < numAttr; i++) {
		minDoubleAttrs[i] = getMinDoubleAttr(i);
		maxDoubleAttrs[i] = getMaxDoubleAttr(i);
	}
	

	for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		normAttrs[0] = (((*it)->getOrigDoubleAttr(0) - minDoubleAttrs[0]) / (maxDoubleAttrs[0] - minDoubleAttrs[0]));
		(*it)->addNewDoubleNormAttr(normAttrs[0]);
		normAttrs[1] = ((*it)->getOrigDoubleAttr(1) - minDoubleAttrs[1]) / (maxDoubleAttrs[1] - minDoubleAttrs[1]);
		(*it)->addNewDoubleNormAttr(normAttrs[1]);
	}


	
	cout << "------------------------------" << endl;
/*	for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		cout << "Objeto: " << (*it)->getId() << "Attr: " << (*it)->getNormDoubleAttr(0) << " "<< (*it)->getNormDoubleAttr(1) << endl;

	}*/

	//TO DO: Save norm input to file
	cout << "Entry normalized" << endl;



}

void Input::testNorm()
{


	const int numAttr = 2;
	long double normAttrs[numAttr];
	long double minDoubleAttrs[numAttr], maxDoubleAttrs[numAttr];

	

	for (int i = 0; i < numAttr; i++) {

		long double minAttr = objects[0]->getOrigDoubleAttr(i);
		vector <Object*>::iterator it;
		for (it = objects.begin(); it != objects.end(); ++it) {
			if (minAttr >(*it)->getOrigDoubleAttr(i)) {
				minAttr = (*it)->getOrigDoubleAttr(i);
			}
		}


		minDoubleAttrs[i] = getMinDoubleAttr(i);
		maxDoubleAttrs[i] = getMaxDoubleAttr(i);
	}


	for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		normAttrs[0] = (((*it)->getOrigDoubleAttr(0) - minDoubleAttrs[0]) / (maxDoubleAttrs[0] - minDoubleAttrs[0]));
		(*it)->testePesoX = normAttrs[0];
		normAttrs[1] = ((*it)->getOrigDoubleAttr(1) - minDoubleAttrs[1]) / (maxDoubleAttrs[1] - minDoubleAttrs[1]);
		(*it)->testePesoY = normAttrs[1];
	}



	cout << "------------------------------" << endl;
	for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
	cout << "Objeto: " << (*it)->getId() << "Attr: " << (*it)->testePesoX << " "<< (*it)->testePesoY << endl;

	}

	//TO DO: Save norm input to file
	cout << "Entry normalized" << endl;


}



double Input::getMaxDoubleAttr(int index)
{
	
	double maxAttr = objects[0]->getOrigDoubleAttr(index);
	vector <Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) {
		if (maxAttr < (*it)->getOrigDoubleAttr(index)) {
			maxAttr = (*it)->getOrigDoubleAttr(index);
		}
	}
	return maxAttr;
}

double Input::getMaxNormDoubleAttr(int index)
{
	
	double maxAttr = objects[0]->getNormDoubleAttr(index);
	vector <Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) {
		if (maxAttr < (*it)->getNormDoubleAttr(index)) {
			maxAttr = (*it)->getNormDoubleAttr(index);
		}
	}
	return maxAttr;
}



double Input::getMinDoubleAttr(int index)
{
	
	double minAttr = objects[0]->getOrigDoubleAttr(index);
	vector <Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) {
		if (minAttr > (*it)->getOrigDoubleAttr(index)) {
			minAttr = (*it)->getOrigDoubleAttr(index);
		}
	}
	return minAttr;
}


double Input::getMinNormDoubleAttr(int index)
{
	
	double minAttr = objects[0]->getNormDoubleAttr(index);
	vector <Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) {
		if (minAttr > (*it)->getNormDoubleAttr(index)) {
			minAttr = (*it)->getNormDoubleAttr(index);
		}
	}
	return minAttr;
}

vector<Object*> Input::getObjects()
{
	return this->objects;
}

int Input::getNumObjects()
{
	return this->objects.size();
}
