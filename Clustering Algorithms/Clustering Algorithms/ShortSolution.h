#pragma once
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> objectGroup;

class ShortSolution
{
public:
	ShortSolution();
	~ShortSolution();
	void addObject(int objectId,int clusterId);
	int getId();
	void setId();
	double getSilhouette();
	void setSilhouette();
private:
	vector <int> objectByCluster; // for each object i have the clusters which it belongs
	vector <objectGroup> clusters; //for each cluster i have a subgroup of objects in it
	int id; // solution id
	double silhouette; //metric to define if a clustrization is good
	// add closest vertexs
};

