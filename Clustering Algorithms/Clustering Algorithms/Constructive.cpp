#include "stdafx.h"
#include "Constructive.h"




Constructive::Constructive(int numVertex)
{
	Graph.reserve(numVertex);
	//for (int i = 0; i < numVertex; i++)
		//Graph[i].setArestaSize(numVertex);
	this->numVertex = numVertex;
	this->mat = new double*[numVertex];
	for (int i = 0; i < numVertex; i++) {
		mat[i] = new double[numVertex];
	}
}

Constructive::~Constructive()
{
	for (int i = 0; i < numVertex; i++)
		delete[] mat[i];
	delete[] mat;
}

double Constructive::euclideanDistance(Object *a, Object *b)
{
	double dist = 0.0;
	for (int i = 0; i < 2; i++) {

		dist += pow((a->getNormDoubleAttr(i) - b->getNormDoubleAttr(i)), 2);
	}
	return sqrt(dist);
}

void Constructive::showGraph()
{
	int i, j;
	cout << Graph[32].getPesoAresta(180) << endl;
	for (i = 0; i < numVertex; i++) {
		for (j = i; j < numVertex; j++) {
			//cout << Graph[i].getPesoAresta(j) << "  ";
		}
		
	}
	cout << i*j << endl;
}

void Constructive::buildGraph(vector <Object*> objects)
{
	int i;
	int j;
	vector <Object*>::iterator it;
	vector <Object*>::iterator it2;
	it = objects.begin();
	for (i = 0; i < numVertex; i++) {
		it2 = it;
		No no = No();
		no.setID((*it)->getId());
		no.setPesoX((*it)->getNormDoubleAttr(0));
		no.setPesoY((*it)->getNormDoubleAttr(1));
		Graph.push_back(no);
		for (j = i; j < numVertex; j++) {
			//mat[i][j] = euclideanDistance(*it, *it2);
			Graph[i].adicionaAresta(j, euclideanDistance(*it, *it2));
			++it2;
		}
		++it;
	}
}

Aresta::Aresta(int iD_No, float pesoA)
{
	this->iD_No = iD_No;
	pesoAresta = pesoA;
}

Aresta::~Aresta()
{
}

double Aresta::getPesoAresta()
{
	return this->pesoAresta;
}

int Aresta::getIDNo()
{
	return this->iD_No;
}


void Aresta::setPesoAresta(float peso)
{
	this->pesoAresta = peso;
}


No::No()
{
}

No::~No()
{
}

int No::getID()
{
	return this->iD;
}

int No::getGrau()
{
	return this->grau;
}

void No::setID(int id)
{
	this->iD = id;
}

void No::setGrau(int g)
{
	this->grau = g;
}

void No::setPesoX(float pesoX)
{
	this->pesoX = pesoX;
}

void No::setPesoY(float pesoY)
{
	this->pesoY = pesoY;
}

void No::setArestaSize(int size)
{
	listaAresta.reserve(size);
}

void No::adicionaAresta(int id, double pesoA)
{
	Aresta* a = new Aresta(id, pesoA);
	if (id == iD)
		grau += 2;
	else
		grau += 1;
	listaAresta.push_back(*a);
}

void No::removeAresta(int id)
{
	listaAresta.erase(listaAresta.begin() + id);
}

double No::getPesoAresta(int index)
{
	return listaAresta[index].getPesoAresta();
}
