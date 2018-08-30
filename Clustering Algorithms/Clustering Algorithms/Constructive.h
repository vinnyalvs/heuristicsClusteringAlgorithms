#pragma once
#include "ShortSolution.h"
#include "Node.h"
#include <random>
#include <algorithm>
#include <cstdlib>
#include <time.h>
enum {
	maxV = 300
};

#include <vector>
#include "Object.h"
#include <iostream>
using namespace std;






class Constructive
{
public:
	Constructive(int numVertex, int numClusters );
	~Constructive();
	void buildGraph(vector <Object*> objects);
	double euclideanDistance(Object *a, Object *b);
	void showGraph();
	void orderEdges();
	bool orderFunction( Edge a,  Edge b);
	int getNumComponents();
	void buildSolution();
	void testeCluster();
	void calculateSilhouette();
	bool hasCircle();
	void buildClusters();
	ShortSolution *getSolution();
	void setRndParemeter(double rndParameter);
	double getParameter();
	void buildMST();
	void showEdgesInSol();
	void cutMST(int numclusters);
	void DFS(int v, bool visited[],int clusterGroup);

	void calculateSum();

private:
	double silhouette;
	vector <Object*> objects;
	void unionSETs(int idX, int idY);
	int find(int id);
	double **mat;
	int numVertex;
	double rndParameter;
	vector <Node> Graph;
	vector <Node> MSTGraph;
	vector <Edge> candidatesEdges;
	vector <Edge> edgesInSolution;
	vector <int> parents;
	vector <struct subset> subsets;
	vector <struct cluster> clusters;
	vector <vector<int>> solutionClusters;
	vector <int> objByCluster;
	ShortSolution *solution;
	int numConvexComponents;
	int numClusters;
};

struct subset {
	int parent;
	int rank;
};

struct cluster {
	vector <int> objsId;
	int idCluster;
	int idClusterInSolution;
};