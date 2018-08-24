#pragma once
#include "Object.h"
#include <vector>
using namespace std;
enum Attr {

};

enum Metrics {
	eucldDist, // Euclidean distance
	hummDist,  // Humming distance
	manhDist,  // Manhatam distance
	metrc3
};

class Parameters {
	int masterProblemTimeLimit;
	int solver;

};


class Input
{
public:
	/**
	Input destructor
	@param none
	@return none
	*/
	~Input();
	/**
	This method should be called to instantiate Input. The class is Singleton, so we can do this only once: Input* s = Input::getInstance();
	@param none
	@return none
	*/
	static Input* getInstance();
	/**
	Add an Object to solution
	@param Object object    object to be added
	@return none
	*/
	void addObject(Object *object);
	/**
	Read a file. The file should be a CSV in format: m,n and then the values. And then fills object vector Eg:
	2,2 </br>
	1,1 </br>
	0,1
	@param string filename. The file to be read, the file can be and project folder. Only the name should work fine.
	@return none
	*/
	void readObjectInstances(string fileName);
	/**
	Normalize entry instances and fills object double normalized attrs.
	@param none
	@return none
	*/
	void normEntry();

	void testNorm();

	double getMaxDoubleAttr(int index);

	double getMaxNormDoubleAttr(int index);

	double getMinDoubleAttr(int index);

	double getMinNormDoubleAttr(int index);

	vector <Object*>  getObjects();

	int getNumObjects();
private:
	Input();
	int numObj;
	static Input *instance;
	vector <Object*> objects;
	vector <double> simiByMetric;
	Parameters param;
};

