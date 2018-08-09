#include "Constructive.h"
#include <algorithm>




Constructive::Constructive(int numVertex, int numClusters)
{
	solution = new ShortSolution(numVertex,numClusters);
	Graph.reserve(numVertex);
	cluster newCluster;
	//Inicializo os clusters
	for (int i = 0; i < numClusters; i++) {
		newCluster.idCluster = 0;
		newCluster.idClusterInSolution = i;
		clusters.push_back(newCluster);
	}
	this->numVertex = numVertex;
	this->numClusters = numClusters;
	//Inicializo os subconjuntos
	subset newSet;
	for (int i = 0; i < numVertex; ++i)
	{
		newSet.parent = i;
		newSet.rank = 0;
		subsets.push_back(newSet);
	}
	objByCluster.assign(numVertex, 0);
	int a = 0;
	for (vector <int>::iterator it = objByCluster.begin(); it != objByCluster.end(); it++) {
		*it = a;
		a++;
	}

}


Constructive::~Constructive()
{
	for (int i = 0; i < numVertex; i++)
		delete[] mat[i];
	delete[] mat;
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

	sort(candidatesEdges.begin(), candidatesEdges.end());
	

}

bool Constructive::orderFunction(Edge a, Edge b)
{
	return 	( a.getWeightEdge() <  b.getWeightEdge());
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
	srand(time(0));
	numConvexComponents = Graph.size();
	int numVertex = Graph.size();
	int numEdges = candidatesEdges.size();
	double prob;
	double sum = 0.0, sumprob=0;
	double  ran;

	vector <double> probabilityWeights;
	edgesInSolution.reserve(candidatesEdges.size());

	int count = 0;
	for (vector <Edge>::iterator it = candidatesEdges.begin(); it != candidatesEdges.end(); it++) {
			sum += it->getWeightEdge();
	}
	cout << candidatesEdges.front().getWeightEdge() << endl;
	int c = 0;
	for (vector <Edge>::iterator it = candidatesEdges.begin(); it != candidatesEdges.end(); it++) {
		//cout << candidatesEdges[c].getWeightEdge() << endl;
		double value = (100 / (it->getWeightEdge() / sum));
		if (it->getWeightEdge() != 0) {
			probabilityWeights.push_back(  value/pow(10,5) + sumprob) ;
			sumprob = sumprob + ( value / pow(10, 5) ) ;
			//cout << it->getWeightEdge() << endl;
		}
		
	}
	
	
	
	
	cout << "Sum" << sumprob << endl;
	random_device seed;
	mt19937 gen(seed());
	uniform_real_distribution<float> dis(0, sumprob);
	int j;
	/*for (vector <double>::iterator it = probabilityWeights.begin(); it != probabilityWeights.end(); it++) {
		cout <<  *it << endl;
		// Verificar sumprob float
		j  = rand() %  (int)sumprob  ;
	   cout << "J:" <<  j << endl;
	} */
	
	
	

	cout << "a" << endl;

	while (numConvexComponents > numClusters) {
		int last = candidatesEdges.size() * rndParameter;
		double j;
		// Verificar sumprob float
		j = dis(seed);
		int i = 0;
		for (vector <double>::iterator it = probabilityWeights.begin(); it != probabilityWeights.end(); it++) {
			if (j <= *it) {
				int parentX = find(candidatesEdges[i].getHead());
				int parentY = find(candidatesEdges[i].getTail());
				if (parentX != parentY) { //Se os "pais" deles forem os mesmos significa que há um circulo
					int clusterId = unionSETs(candidatesEdges[i].getHead(), candidatesEdges[i].getTail());
					objByCluster[candidatesEdges[i].getHead()] = parentX;
					objByCluster[candidatesEdges[i].getTail()] = parentY;
				}
				candidatesEdges.erase(candidatesEdges.begin() + i);
				break;

			}
			i++;
		}
		
		
	}

	for (vector <int>::iterator c = objByCluster.begin(); c != objByCluster.end(); c++) {
		cout << *c << endl;
	}
	
	/*int objId=0; // Contador para os ids dos objetos
	//Faz a conversão das componentes conexas para clusters
	for (vector <struct subset>::iterator it = subsets.begin(); it != subsets.end(); it++) {
		for (vector <struct cluster>::iterator c = clusters.begin(); c != clusters.end(); c++) {
			if (c->idCluster == 0) {
				c->idCluster = find(it->parent);
				solution->addObject(objId, c->idClusterInSolution);
				break;
			}
			else if (c->idCluster == find(it->parent)) {
				solution->addObject(objId, c->idClusterInSolution);
				break;
			}

		}
		objId++;
	}*/
	cout << "--" << endl;


	cout << "num Convex Comp: " << numConvexComponents << endl;
	cout << "num Convex Comp: " << numClusters << endl;
	int clusterIndex = 0; // Contador para os ids dos objetos
	int conta = 0;
	cout << "--fim--" << endl;
	//Faz a convers�o das componentes conexas para clusters
	for (vector <int>::iterator c = objByCluster.begin(); c != objByCluster.end(); c++) {
		//cout << *c << endl;
		vector <int>::iterator b;
		for (b = objByCluster.begin(); b != c; b++) {
			if (*c == *b)
				break;
		}
		if (c == b) {
			//cout << *c << endl;
			//clusters[clusterIndex].idCluster = *c;
			clusterIndex++;
		}
		


	}
	cout << "--" << endl;
/*	cout << "Cluster Index: " << clusterIndex << endl;
	for (vector <int>::iterator it = objByCluster.begin(); it != objByCluster.end(); it++) {

		for (vector <struct cluster>::iterator c = clusters.begin(); c != clusters.end(); c++) {
			if (c->idCluster == *it) {
				solution->addObject(count + 1, c->idClusterInSolution);
			}
		}
		count++;
	}*/
	

	

}




ShortSolution *Constructive::getSolution()
{
	return this->solution ;
}

void Constructive::setRndParemeter(double rndParameter)
{
	this->rndParameter = rndParameter;
}

double Constructive::getParameter()
{
	return this->rndParameter;
}

int Constructive::unionSETs(int idX, int idY)
{
	//return the root of the SET
	int xroot = find(idX);
	int yroot = find(idY);
	numConvexComponents--;
	// Attach smaller rank tree under root of high rank tree
	// (Union by Rank)
	if (subsets[xroot].rank < subsets[yroot].rank) {
		subsets[xroot].parent = yroot;
		cout << yroot << endl;
		return yroot;
	}
	else if (subsets[xroot].rank > subsets[yroot].rank){
		subsets[yroot].parent = xroot;
		cout << yroot << endl;
		return xroot;
	}
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
		cout << yroot << endl;
		return xroot;
	}
	// If ranks are same, then make one as root and increment
	// its rank by one
	
}

int Constructive::find(int id)
{
	if (subsets[id].parent != id)
		subsets[id].parent = find(subsets[id].parent);
	subsets[id].root = subsets[id].parent;
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
		//cria um novo No
		No no = No();
		no.setID((*it)->getId());
		no.setPesoX((*it)->getNormDoubleAttr(0));
		no.setPesoY((*it)->getNormDoubleAttr(1));
		Graph.push_back(no);
		//para cada No calcula a distancia para os objetos da instancia
		for (j = i+1; j < numVertex; j++) {
			Graph[i].addEdge(j, euclideanDistance(*it, *it2),no.getID());
			++it2;
		}
		++it;
	}
}

double Constructive::euclideanDistance(Object *a, Object *b)
{
	double dist = 0.0;
	// two is the dimension of the object
	for (int i = 0; i < 2; i++) {

		dist += pow((a->getNormDoubleAttr(i) - b->getNormDoubleAttr(i)), 2);
	}
	return sqrt(dist);
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
