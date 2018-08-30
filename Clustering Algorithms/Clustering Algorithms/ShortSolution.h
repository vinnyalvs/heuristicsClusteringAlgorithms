#pragma once
#include "stdafx.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include <limits>
#include "Node.h"
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
	double euclideanDistance(Object * a, Object * b);
	void calculateSilhouette();
	bool isObjectInCluster(int objId,int clusterId);
	int getNumClusters();
	int getNumObjs();
	void setObjects(vector<Object*> objs);
	vector <vector<int>> getClusters();
	void showSolution();
	void setObjectByCluster(vector <int> objectByCluster);
	void setGraph(vector <Node> graph);
	vector <Node> getGraph();
	void calculateCostClusters();


private:
	vector <int> objectByCluster; // for each object i have the clusters which it belongs
	vector <vector<int>> clusters; //for each cluster i have a subgroup of objects in it
	vector <double> costClusters;
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
	vector <double> ratios;
	vector <Object*> objs;
	vector <Node> graph;
};

