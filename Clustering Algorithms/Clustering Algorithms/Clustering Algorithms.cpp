// Clustering Algorithms.cpp : Defines the entry point for the console application.
//

#include "Constructive.h"
#include  "Object.h"
#include  "Input.h"
#include  "KMeans.h"
#include  "ShortSolution.h"
#include  "LocalSearch.h"
#include "math.h"
#include <random>
using namespace std;

int main()
{
	Input* s = Input::getInstance();
    s->readObjectInstances("matrixO.txt");
	s->normEntry();
	
	int size = s->getNumObjects();
	/*for (int i = 10; i <= 15; i++) {
		Constructive *c = new Constructive(size, i);
		c->buildGraph(s->getObjects());
		c->orderEdges();
		c->setRndParemeter(0.1);
		c->buildClusters();
		ShortSolution *sol = c->getSolution();
		sol->showSolution();
		cout << "------------------------------" << endl;
	} */
	Constructive *c = new Constructive(size, 10);
	c->buildGraph(s->getObjects());
	c->orderEdges();
	c->buildMST();
	c->showGraph();
	c->cutMST(10);
    return 0;
}

