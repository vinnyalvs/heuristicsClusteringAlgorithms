// Clustering Algorithms.cpp : Defines the entry point for the console application.
//

#include "Constructive.h"
#include  "Object.h"
#include  "Input.h"
#include  "KMeans.h"
#include  "ShortSolution.h"
#include  "LocalSearch.h"
#include "math.h"

using namespace std;

int main()
{
	Input* s = Input::getInstance();
    s->readObjectInstances("matrixO.txt");
	
	s->normEntry();
	int size = s->getNumObjects();
	for (int i = 1; i <= 7; i++) {
		Constructive *c = new Constructive(size, i);
		c->buildGraph(s->getObjects());
		c->orderEdges();
		c->setRndParemeter(0.01);
		c->buildClusters();
		ShortSolution *sol = c->getSolution();
		sol->showSolution();
		cout << "------------------------------" << endl;
	}
	
    return 0;
}

