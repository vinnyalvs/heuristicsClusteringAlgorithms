#include "Constructive.h"
#include <algorithm>




Constructive::Constructive(int numVertex, int numClusters)
{
	Graph.reserve(numVertex);
	//for (int i = 0; i < numVertex; i++)
	//Graph[i].setArestaSize(numVertex);
	this->numVertex = numVertex;
	this->mat = new double*[numVertex];
	for (int i = 0; i < numVertex; i++) {
		mat[i] = new double[numVertex];
	}
	this->numClusters = numClusters;

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
	for (i = 0; i < numVertex; i++) {
		for (j = i; j < numVertex; j++) {
			cout << Graph[i].getWeightEdge(j) << "  ";
		}

	}

}

void Constructive::orderEdges()
{
	for (vector <No>::iterator it = Graph.begin(); it != Graph.end(); it++) {
		vector <Edge> edge = it->getEdges();
		for (vector <Edge>::iterator a = edge.begin() ; a != edge.end(); a++) {
			candidatesEdges.push_back(*a);
		}
	}

	sort(candidatesEdges.begin(), candidatesEdges.end(), orderFunction);

}

bool Constructive::orderFunction(Edge a, Edge b)
{
	return 	(a.getWeightEdge() < b.getWeightEdge());
}

int Constructive::getNumComponents()
{
	return numConvexComponents;
}

void Constructive::buildSolution()
{

}

bool Constructive::hasCircle()
{
	int numVertex = Graph.size();
	int numEdges = candidatesEdges.size();
	int i;
	for (i=0; i < numVertex; ++i)
	{
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}
	i = 0;
	for (vector <Edge>::iterator it = edgesInSolution.begin(); it != edgesInSolution.end(); it++) {
		int parentX = find(it->getHead());
		int parentY = find(it->getTail());
		if (parentX == parentY)
			return true;
		unionSETs(it->getHead(), it->getTail());
	}
	return false;
}

void Constructive::buildClusters()
{
	solution = ShortSolution(Graph.size, numClusters);
	subsets.reserve(numClusters);
	numConvexComponents = Graph.size();
	int i;
	int numVertex = Graph.size();
	int numEdges = candidatesEdges.size();
	for (i = 0; i < numVertex; ++i)
	{
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}
	i = 0;
	vector <Edge>::iterator it = edgesInSolution.begin();
	//it != edgesInSolution.end();
	while (numConvexComponents >= numClusters) {
		edgesInSolution.push_back(candidatesEdges[i]);
		int parentX = find(it->getHead());
		int parentY = find(it->getTail());
		if (parentX != parentY) { //Se os "pais" deles forem os mesmos significa que há um circulo
			int clusterId = unionSETs(it->getHead(), it->getTail());
			solution.addObject(it->getHead(), clusterId);
			solution.addObject(it->getTail(), clusterId);
		}
		else {
			edgesInSolution.pop_back();
		}
		i++;
		it++;
	}

}

int Constructive::unionSETs(int idX, int idY)
{
	int xroot = find(idX);
	int yroot = find(idY);
	numConvexComponents--;
	// Attach smaller rank tree under root of high rank tree
	// (Union by Rank)
	if (subsets[xroot].rank < subsets[yroot].rank) {
		subsets[xroot].parent = yroot;
		return yroot;
	}
	else if (subsets[xroot].rank > subsets[yroot].rank){
		subsets[yroot].parent = xroot;
		return xroot;
	}
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
		return xroot;
	}
	// If ranks are same, then make one as root and increment
	// its rank by one
	
}

int Constructive::find(int id)
{
	if (subsets[id].parent != id)
		subsets[id].parent = find(subsets[id].parent);

	return subsets[id].parent;
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
			Graph[i].addEdge(j, euclideanDistance(*it, *it2),no.getID());
			++it2;
		}
		++it;
	}
}

Edge::Edge(int iD_No, float pesoA, int idHead)
{
	this->tail = iD_No;
	this->head = idHead;
	pesoAresta = pesoA;
}

Edge::~Edge()
{
}

double Edge::getWeightEdge()
{
	return this->pesoAresta;
}

int Edge::getTail()
{
	return this->tail;
}

int Edge::getHead()
{
	return this->head;
}




void Edge::setWeightEdge(float peso)
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
	return this->id;
}

int No::getGrau()
{
	return this->grau;
}

void No::setID(int id)
{
	this->id = id;
}

int No::getId()
{
	return this->id ;
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

void No::setNumEdges(int size)
{
	edges.reserve(size);
}

void No::addEdge(int id, double pesoA, int idHead)
{
	Edge* a = new Edge(id, pesoA, idHead);
	if (id == id)
		grau += 2;
	else
		grau += 1;
	edges.push_back(*a);
}

vector <Edge> No::getEdges()
{
	return edges;
}

void No::removeEdge(int id)
{
	edges.erase(edges.begin() + id);
}

double No::getWeightEdge(int index)
{
	return edges[index].getWeightEdge();
}
