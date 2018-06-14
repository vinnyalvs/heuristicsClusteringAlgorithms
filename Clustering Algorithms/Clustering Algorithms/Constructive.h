#pragma once
#include "ShortSolution.h"
#include <stack>
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
private:
	int unionSETs(int idX, int idY);
	int find(int id);
	double **mat;
	int numVertex;
	vector <No> Graph;
	vector <Edge> candidatesEdges;
	vector <Edge> edgesInSolution;
	vector <int> parents;
	vector <struct subset> subsets;
	ShortSolution *solution;
	int numConvexComponents;
	int numClusters;
};

struct subset {
	int parent;
	int rank;
};