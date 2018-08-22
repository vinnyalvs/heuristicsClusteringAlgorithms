#pragma once
#pragma once
#include "Object.h";




class KMeans
{
public:
	KMeans(int k, int maxInterations, double maximaX, double maximaY, double minimaX, double minimaY, vector <Object*> objects);
	double euclideanDistance(Object *a, Object *b);
	void initializeMeans();
	int findNearestMean(Object *obj);
	void setmaximaX(double value);
	void setmaximaY(double value);
	void setminimaX(double value);
	void setminimaY(double value);
	double getNewCentroid(int mean, int dimAttr);
	void showInfo();

	~KMeans();
private:
	int k; //num of clusters;
	int valuesTotal, objectsTotal, maxInterations;
	vector <Object*> objects;
	vector <Object> means;
	double maximaX, maximaY;
	double minimaX, minimaY;
};

