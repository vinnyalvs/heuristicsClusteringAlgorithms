// Clustering Algorithms.cpp : Defines the entry point for the console application.
//

#include "Constructive.h"
#include  "Object.h"
#include  "Input.h"
#include  "KMeans.h"
#include  "ShortSolution.h"
#include  "LocalSearch.h"
#include "Utils.h"
#include "math.h"
#include <random>
using namespace std;

int main()
{
	//Inicializa Instancia, le o arquivo e o normaliza
	Input* i = Input::getInstance();
    i->readObjectInstances("DS1-maronna.txt");
	i->normEntry();
	//i->testNorm();
	int size = i->getNumObjects();

	//Inicializa Construtivo, calcula peso das arestas  
	Constructive *c = new Constructive(size, 4);
	c->buildGraph(i->getObjects());
	c->orderEdges();
	c->setRndParemeter(0.01);
	//c->buildClusters();
	c->testeCluster();
	//c->calculateSum();
	c->showGraph();
	ShortSolution *sol = c->getSolution();
	//sol->showSolution();
	//sol->calculateCostClusters();
	Utils *util = new Utils();
	//util->testShowSolution(sol);

	
	
	
}



/*
	cout << "------------------------------" << endl;
	KMeans K = KMeans(10, 1, i->getMaxNormDoubleAttr(0), i->getMaxNormDoubleAttr(1), i->getMinNormDoubleAttr(0), i->getMinNormDoubleAttr(1), i->getObjects());
	K.initializeMeans();
	ShortSolution *sol = K.getSolution();
	sol->showSolution();

*/

/*Constructive *c = new Constructive(size, 10);
c->buildGraph(s->getObjects());
c->orderEdges();
c->buildMST();
c->showGraph();
c->cutMST(10);
return 0; */