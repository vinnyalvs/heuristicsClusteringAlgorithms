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
	//Inicializa Instancia, le o arquivo e o normaliza
	Input* i = Input::getInstance();
    i->readObjectInstances("matrixO.txt");
	i->normEntry();
	int size = i->getNumObjects();

	//Inicializa Construtivo, calcula peso das arestas  
	Constructive *c = new Constructive(size, 10);
	c->buildGraph(i->getObjects());
	c->orderEdges();
	c->setRndParemeter(0.1);
	c->buildClusters();
	
	ShortSolution *sol = c->getSolution();
	sol->showSolution();
	cout << "------------------------------" << endl;
}



/*
	KMeans K = KMeans(10, 2000, s->getMaxNormDoubleAttr(0), s->getMaxNormDoubleAttr(1), s->getMinNormDoubleAttr(0), s->getMinNormDoubleAttr(1), s->getObjects());
	K.initializeMeans();
	K.showInfo();

*/

/*Constructive *c = new Constructive(size, 10);
c->buildGraph(s->getObjects());
c->orderEdges();
c->buildMST();
c->showGraph();
c->cutMST(10);
return 0; */