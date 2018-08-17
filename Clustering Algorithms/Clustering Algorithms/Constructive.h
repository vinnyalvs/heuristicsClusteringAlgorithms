#pragma once
#include "ShortSolution.h"
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


class Edge {
private:
	double pesoAresta;
	int tail; // no destino
	int head;
public:
	Edge(int iD_No, float pesoA, int idHead);
	~Edge();
	double getWeightEdge();
	int getTail();
	int getHead();
	void setWeightEdge(float peso);
	bool operator<(const  Edge & other) //(1)
	{
		return pesoAresta < other.pesoAresta;
	}

	bool operator > (Edge& cmp1)
	{
		//Do your own calculations here
		if (cmp1.pesoAresta < pesoAresta)
		{
			return true;
		}

		return false;
	}
};

class No {
private:
	int id;
	int grau;
	int grauEntrada;
	int grauSaida;
	double pesoX;
	double pesoY;
	vector <Edge> edges;
	
public:
	int clusterParent;
	No();
	~No();
	int getID();
	int getGrau();
	void setID(int id);
	int	 getId();
	void setGrau(int g);
	void setPesoX(float pesoX);
	void setPesoY(float pesoY);
	
	void setNumEdges(int size);
	void addEdge(int id, double pesoA, int idHead);
	vector <Edge> getEdges();
	void removeEdge(int id);
	double getWeightEdge(int index);
};

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
	bool hasCircle();
	void buildClusters();
	ShortSolution *getSolution();
	void setRndParemeter(double rndParameter);
	double getParameter();
	void buildMST();
	void showEdgesInSol();
	void cutMST(int numclusters);
private:
	int unionSETs(int idX, int idY);
	void unionSETs(int idX, int idY, int type);
	int find(int id);
	double **mat;
	int numVertex;
	double rndParameter;
	vector <No> Graph;
	vector <No> MSTGraph;
	vector <Edge> candidatesEdges;
	vector <Edge> edgesInSolution;
	vector <int> parents;
	vector <struct subset> subsets;
	vector <struct cluster> clusters;
	vector <int> objByCluster;
	ShortSolution *solution;
	int numConvexComponents;
	int numClusters;
};

struct subset {
	int parent;
	int rank;
	int root;
	//talvez uma maneira de guardar o root do subconjunto seja interessante
};

struct cluster {
	vector <int> objsId;
	int idCluster;
	int idClusterInSolution;
};