#pragma once
#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;
class ShortSolution
{
public:
	ShortSolution(int numObj, int numClusters);
	~ShortSolution();
	void addObject(int objectId, int clusterId);
	int getId();
	void setId(int id);
	double getSilhouette();
	void Silhouette();
	bool isObjectInCluster(int objId,int clusterId);
	int getNumClusters();
	int getNumObjs();
	vector <vector<int>> getClusters();
	void showSolution();
private:
	vector <int> objectByCluster; // for each object i have the clusters which it belongs
	vector <vector<int>> clusters; //for each cluster i have a subgroup of objects in it
	int **objByCluster;
	int id; // solution id
	int numObj;
	int numClusters;
	double silhouette; //metric
					   // add closest vertexs
};

