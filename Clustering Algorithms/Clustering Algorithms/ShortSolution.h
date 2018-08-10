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
	double calculateIntraClusterDistance(int clusterId);
	double calculateInterclusterDistance(int clusterId);
	double calculateRatio(int clusterId);

private:
	vector <int> objectByCluster; // for each object i have the clusters which it belongs
	vector <vector<int>> clusters; //for each cluster i have a subgroup of objects in it
	int **objByCluster;
	int id; // solution id
	int numObj;
	int numClusters;
	double silhouette; //metric
					   // add closest vertexs
	//The intracluster is the average distance of all the points within a cluster from the cluster center
	vector <double> intraClusterDistances;
	//The intercluster is the minimum of the pair wise 	distance between any two cluster centers given
	vector <double> interClusterDistances;
	// In the evaluation of our clustering algorithm, the ratio is: intra/inter, and we want to minimize it
	//The clusterization with the best ratio
	vector <double> ratios
};

