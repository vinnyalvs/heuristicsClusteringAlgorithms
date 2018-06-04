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
	s->readObjectInstances("matrix.txt");
	s->normEntry();
	//int size = s->getNumObjects();
	Constructive *c = new Constructive(200);
	c->buildGraph(s->getObjects());
	c->showGraph();




    return 0;
}

