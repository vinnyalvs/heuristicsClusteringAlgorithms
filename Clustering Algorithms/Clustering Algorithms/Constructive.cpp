#include "Constructive.h"
#include <algorithm>




Constructive::Constructive(int numVertex, int numClusters)
{
	solution = new ShortSolution(numVertex,numClusters);
	Graph.reserve(numVertex);
	MSTGraph.reserve(numVertex);
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
	for (vector <Node>::iterator it = MSTGraph.begin(); it != MSTGraph.end(); it++) {
		vector <Edge> edge = it->getEdges();
		cout << it->getID() << "edges" << endl;
		for (vector <Edge>::iterator a = edge.begin(); a != edge.end(); a++) {
			cout << a->getDest() << " ";
		}
		cout << endl;
	}

}

void Constructive::orderEdges()
{
	for (vector <Node>::iterator it = Graph.begin(); it != Graph.end(); it++) {
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



void Constructive::buildClusters()
{
	srand(time(0));
	numConvexComponents = Graph.size();
	int numVertex = Graph.size();
	int numEdges = candidatesEdges.size();
	double prob;
	double sum = 0.0, sumprob=0;
	double ran;
	vector <double> probabilityWeights;
	edgesInSolution.reserve(candidatesEdges.size());
	int count = 0;
	//soma todos os pesos de arestas
	for (vector <Edge>::iterator it = candidatesEdges.begin(); it != candidatesEdges.end(); it++) {
			sum += it->getWeightEdge();
	}

	//Value: divide 100% pela porcentagem que a aresta corresponde na soma total
	//para cada aresta com peso diferente de zero, colocamos Node array o value dividido por uma "Nodermalizacao" (pow) acresido com a somaAcumulada
	int c = 0;
	for (vector <Edge>::iterator it = candidatesEdges.begin(); it != candidatesEdges.end(); it++) {
		double value = (100 / (it->getWeightEdge() / sum));
		if (it->getWeightEdge() != 0) {
			probabilityWeights.push_back(  value/pow(10,5) + sumprob) ;
			sumprob = sumprob + ( value / pow(10, 5) ) ;
		}
		
	}
	
	//Gera um distribuição aleatória entre 0 e a soma das probabilidades

	random_device seed;
	mt19937 gen(seed());
	uniform_real_distribution<float> dis(0, sumprob);
	int j;


	//Enquanto existem mais componentes conexas que clusters, sorteamos um valor entre 0 e sumprob, para cada elemento do array, se o valor sorteado for meNoder que esse elemento
	//Tentamos montar a AGM
	while (numConvexComponents > numClusters) {
		int last = candidatesEdges.size() * rndParameter;
		double j;
		j = dis(seed);
		int i = 0;
		for (vector <double>::iterator it = probabilityWeights.begin(); it != probabilityWeights.end(); it++) {
			if (j <= *it) {
				int parentX = find(candidatesEdges[i].getSrc());
				int parentY = find(candidatesEdges[i].getDest());
				if (parentX != parentY) { //Se os "pais" deles forem os mesmos significa que há um circulo
					unionSETs(candidatesEdges[i].getSrc(), candidatesEdges[i].getDest());
				}
				candidatesEdges.erase(candidatesEdges.begin() + i);
				break;
			}
			i++;
		}
	}
	//O array ObjBYCluster guarda para cada elemento do array o seu "pai" na componente conexa
	count = 0;
	for (vector <int>::iterator c = objByCluster.begin(); c != objByCluster.end(); c++) {
		*c = find(count);
		count++;
	}
	//Faz a conversão das componentes conexas para clusters, para que seja possível guardar essas informações na solution
	//Basicamente para cada elemento distinto do ObjByCluster, define para a componenteConexa um id Node array clusters
	int clusterIndex = 0; // Contador para os ids dos objetos
	int conta = 0;
	
	for (vector <int>::iterator c = objByCluster.begin(); c != objByCluster.end(); c++) {
		//cout << *c << endl;
		vector <int>::iterator b;
		for (b = objByCluster.begin(); b != c; b++) {
			if (*c == *b)
				break;
		} 
		if (c == b) {
			cout << *c << endl;
			clusters[clusterIndex].idCluster = *c;
			clusterIndex++;
		}
	}

	//Adciona os objetos na solução
	count = 0;
	cout << "Cluster Index: " << clusterIndex << endl;
	for (vector <int>::iterator it = objByCluster.begin(); it != objByCluster.end(); it++) {
		for (vector <struct cluster>::iterator c = clusters.begin(); c != clusters.end(); c++) {
			if (c->idCluster == *it) {
				solution->addObject(count + 1, c->idClusterInSolution);
			}
		}
		count++;
	}
	

}

void Constructive::testeCluster()
{
	srand(time(0));
	numConvexComponents = Graph.size();
	int numVertex = Graph.size();
	int numEdges = candidatesEdges.size();
	vector <Edge> auxCandidatesEdges = candidatesEdges;
	int j = 0;
	edgesInSolution.reserve(auxCandidatesEdges.size());


	double sumDist = 0;
	int last = auxCandidatesEdges.size() * rndParameter;
	for (; j <= last; j++) {
		sumDist += (1-auxCandidatesEdges[j].getWeightEdge());
	}

	while (numConvexComponents > numClusters) {
		//j = ceil((rand() % last));
		
		int k = ceil((rand() % (int)(sumDist*1000)));
		int sum = 0;
		//cout << "k=" << k << endl << "sumDist=" << sumDist * 1000 << endl;
		for (j = 0; sum + (1 - auxCandidatesEdges[j].getWeightEdge()) * 1000 < k && j < last; j++) {
			sum += (1 - auxCandidatesEdges[j].getWeightEdge()) * 1000;
			/*cout  << "j=" << j << "\tw=" << auxCandidatesEdges[j].getWeightEdge() << 
				"\t1-w=" << 1-auxCandidatesEdges[j].getWeightEdge() << 
				"\tparc=" << sum + (1-auxCandidatesEdges[j].getWeightEdge())*1000 << "\tk=" << k << endl << endl;*/
		}

		int parentX = find(auxCandidatesEdges[j].getSrc());
		int parentY = find(auxCandidatesEdges[j].getDest());
		if (parentX != parentY) { //Se os "pais" deles forem os mesmos significa que h� um circulo
			unionSETs(auxCandidatesEdges[j].getSrc(), auxCandidatesEdges[j].getDest());
		}

		sumDist -= (1 - auxCandidatesEdges[j].getWeightEdge());
		auxCandidatesEdges.erase(auxCandidatesEdges.begin() + j);
		if(last != auxCandidatesEdges.size() * rndParameter)
			last = auxCandidatesEdges.size() * rndParameter;
		else
			sumDist += (1 - auxCandidatesEdges[last].getWeightEdge());
	}


	int count = 0;;
	for (vector <int>::iterator c = objByCluster.begin(); c != objByCluster.end(); c++) {
		*c = find(count);
		count++;
	}


	int clusterIndex = 0; // Contador para os ids dos objetos
						  //Faz a convers�o das componentes conexas para clusters


	for (vector <int>::iterator c = objByCluster.begin(); c != objByCluster.end(); c++) {
		vector <int>::iterator b;
		for (b = objByCluster.begin(); b != c; b++) {
			if (*c == *b)
				break;
		}
		if (c == b) {
			clusters[clusterIndex].idCluster = *c;
			clusterIndex++;
		}


	}
	solution->setObjectByCluster(objByCluster);
	//cout << "Cluster Index: " << clusterIndex << endl;
	count = 0;
	for (vector <int>::iterator it = objByCluster.begin(); it != objByCluster.end(); it++) {

		for (vector <struct cluster>::iterator c = clusters.begin(); c != clusters.end(); c++) {
			if (c->idCluster == *it) {
				solution->addObject(count + 1, c->idClusterInSolution);
			}
		}
		count++;
	}

	solutionClusters = solution->getClusters();


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

void Constructive::buildMST()
{
	int V = Graph.size();
	int e = 0;  // An index variable, used for result[]
	int i = 0;
	while (e < V - 2)
	{
		// Step 2: Pick the smallest edge. And increment 
		// the index for next iteration
		int src = candidatesEdges[i].getSrc();
		int dest = candidatesEdges[i].getDest();
		int x = find(src);
		int y = find(dest);
		// If including this edge does't cause cycle,
		// include it in result and increment the index 
		// of result for next edge
		try {
			if (x != y)
			{
				MSTGraph[src-1].addEdge(src, candidatesEdges[i].getWeightEdge(), dest);
				MSTGraph[dest-1].addEdge(dest, candidatesEdges[i].getWeightEdge(), src);
				edgesInSolution.push_back(candidatesEdges[i]);
				unionSETs(x, y);
				e++;
			}
		}
		catch (int ex) {
			cout << "Ecx" << ex << endl;
		}
		i++;
		// Else discard the next_edge
	}
	showEdgesInSol();

	
}




void Constructive::unionSETs(int idX, int idY)
{
	//return the root of the SET
	int xroot = find(idX);
	int yroot = find(idY);
	numConvexComponents--;
	// Attach smaller rank tree under root of high rank tree
	// (Union by Rank)
	if (subsets[xroot].rank < subsets[yroot].rank) {
		subsets[xroot].parent = yroot;

	}
	else if (subsets[xroot].rank > subsets[yroot].rank){
		subsets[yroot].parent = xroot;

	}
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;

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
	this->objects = objects;
	vector <Object*>::iterator it;
	vector <Object*>::iterator it2;
	it = objects.begin();
	for (i = 0; i < numVertex; i++) {
		it2 = it;
		it2++;
		//cria um Nodevo Node
		Node node = Node();
		node.setID((*it)->getId());
		node.setPesoX((*it)->getNormDoubleAttr(0));
		node.setPesoY((*it)->getNormDoubleAttr(1));
		if ((*it)->getId() == 58) {
			cout << (*it)->getNormDoubleAttr(0) << endl;
			cout << (*it)->getNormDoubleAttr(1) << endl;
		}
		Graph.push_back(node);
		MSTGraph.push_back(node);
		//para cada Node calcula a distancia para os objetos da instancia
		for (j = i+1; j < numVertex; j++) {
			//if (j = 57) {
				cout << "--" << endl;
				cout << i << endl;
				cout << j << endl;
				cout << (*it)->getId() << endl;
				cout << (*it2)->getId() << endl;
				cout << euclideanDistance(*it, *it2) << endl;
				cout << "--" << endl;
				if (i = 57)
					break;
			//}
			Graph[i].addEdge(node.getID(), euclideanDistance(*it, *it2),j);
			++it2;
		}
		++it;
	}
//	cout << Graph[58 - 1].getX() << endl;
//	cout << Graph[58 - 1].getY() << endl;
	//Em Graph o indice zero contém o nó de id = 1
	solution->setGraph(Graph);
}

double Constructive::euclideanDistance(Object *a, Object *b)
{
	double dist = 0.0;
	//cout << " Obj a " << a->getId() << " Obj b " << b->getId() << endl;
	// two is the dimension of the object
	for (int i = 0; i < 2; i++) {

		dist += pow((a->getNormDoubleAttr(i) - b->getNormDoubleAttr(i)), 2);
		//cout << " Obj a " << a->getNodermDoubleAttr(i) << " Obj b " << b->getNodermDoubleAttr(i) << endl;
	}
	
	
	//cout << dist << endl;
	return sqrt(dist);
}





void Constructive::calculateSilhouette()
{
	double dissimilarityA = 0;
	double dissimilarityB = 0;
	double s = 0; // Silhueta;
				  //Para cada Objeto
	int i = 0;
	vector <Object*>::iterator it;
	for ( it = objects.begin(); it != objects.end(); it++, i++) {
		//Para cada objeto Node cluster do objeto I
		//Calculamos a dissimilaridade do objeto I para todos os obj de seu cluster
		cout <<  solutionClusters[(*it)->getClusterId()].size()   << endl;
		if (solutionClusters[(*it)->getClusterId()].size() >= 1) {
			for (int j = 0; j < solutionClusters[(*it)->getClusterId()].size(); j++) {
				double distanceToSameCluster = 0;
				if ((*it)->getId() != solutionClusters[i][j]) {
					distanceToSameCluster += euclideanDistance(*it, objects[solutionClusters[i][j]]);
				}
				dissimilarityA = distanceToSameCluster / (solutionClusters.size() - 1);
			}
			//Para cada cluster j
			for (int j = 0; j < solutionClusters.size(); j++) {
				double distanceToOtherCluster = 0;
				double minDissimilarity = numeric_limits<double>::max();
				//Esse if serve para não compararmos com os obj do mesmo cluster;
				if (j != objects[i]->getClusterId()) {
					double auxDist = 0;
					//Para cada objeto do cluster j, calculamos a dist do objeto it ao objeto[j][k]
					for (int k = 0; k < solutionClusters[j].size(); k++) {
						auxDist += euclideanDistance(*it, objects[solutionClusters[j][k]]);
					}
					if (minDissimilarity > auxDist) {
						minDissimilarity = auxDist;
					}
				}
				dissimilarityB = minDissimilarity;
			}


		}
		//Salvo as dissimilaridades e distancias calculadas
		(*it)->setDissimilaritySameCluster(dissimilarityA);
		(*it)->setDissimilarityOtherCluster(dissimilarityB);
		double maxA_B = (dissimilarityA >= dissimilarityB) ? dissimilarityA : dissimilarityB;
		double silhueta = (dissimilarityA - dissimilarityB) / maxA_B;
		s += silhueta;
	}

	cout << dissimilarityA << endl;
	cout << dissimilarityB << endl;

	s = s / objects.size();

	silhouette = s;


}


void Constructive::showEdgesInSol() {
	cout << "Following are the edges in the constructed MST\n" << endl;
	for (vector <Edge>::iterator it = edgesInSolution.begin(); it != edgesInSolution.end(); it++)
		cout << it->getSrc() << "   -- " << it->getDest() << " == " << it->getWeightEdge() << endl;

}

void Constructive::cutMST(int numclusters)
{
	//sort(candidatesEdges.begin(), candidatesEdges.end(),[](Edge& cmp1, Edge& cmp2)->bool {return cmp1 > cmp2; });
	system("cls");
	bool *visited = new bool[numVertex];
	for (int i = 0; i < numVertex; i++)
		visited[i] = false;

	int numConvexComp = 0;
	int i = edgesInSolution.size() - 1;
	int clusterCount = 0;


	while (numConvexComp < numclusters) {
		int src = edgesInSolution[i].getSrc();
		int dest = edgesInSolution[i].getDest();

		MSTGraph[src - 1].removeEdge(dest);
		MSTGraph[dest - 1].removeEdge(src);

		DFS(src, visited, src);
		DFS(dest, visited, dest);


		cout << src << endl;
		cout << dest << endl;
		cout << "--" << endl;
		numConvexComp++;
		clusterCount++;
		i--;
	}

	//system("cls");
	cout << "clusters" << endl;
	for (vector <Node>::iterator it = MSTGraph.begin(); it != MSTGraph.end(); it++) {
		cout << it->getID() << " " << it->clusterParent << endl;
	}




}

void Constructive::DFS(int v, bool visited[], int clusterGroup)
{
	visited[v] = true;

	cout << " " << clusterGroup;
	// Recur for all the vertices adjacent
	// to this vertex
	for (vector <Node>::iterator it = MSTGraph.begin(); it != MSTGraph.end(); it++) {
		if (!visited[it->getID()]) {
			it->clusterParent = clusterGroup;
			DFS(it->getID(), visited, clusterGroup);
		}
	}
}

void Constructive::calculateSum()
{
	//Para cada cluster i com k objetos
	vector <double> costClusters;
	costClusters.assign(solutionClusters.size(), 0);
	for (int i = 0; i < solutionClusters.size(); i++) {
		//Para cada objeto j Node cluster i
		double soma = 0;
		cout << "-----------------" << endl;
		for (int j = 0; j < solutionClusters[i].size(); j++) {
			//Somatorio das distancias do obj j aos outros k-1 objetos do cluster
			// soma += distancia obj j
			for (int k = j; k < solutionClusters[i].size(); k++) {
				if (j != k) {
					//cout << "J: " << j << " K " << k << endl;
					double a = Graph[solutionClusters[i][j]].getDistance(solutionClusters[i][k]);
					soma += a;
					//cout << a << endl;
				}
			}
		}
		costClusters[i] = soma;
		cout << "cluster " << i << " size: " << solutionClusters[i].size() << endl;
		cout << "Custo CLuster i: "  << costClusters[i]  << endl;
		cout << "-----------------" << endl;
		//cout << costClusters[i] << endl;
	}

		
		


}


bool Constructive::hasCircle()
{
	int numVertex = Graph.size();
	int numEdges = candidatesEdges.size();
	int i;
	for (i = 0; i < numVertex; ++i)
	{
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}
	i = 0;
	for (vector <Edge>::iterator it = edgesInSolution.begin(); it != edgesInSolution.end(); it++) {
		int parentX = find(it->getSrc());
		int parentY = find(it->getDest());
		if (parentX == parentY)
			return true;
		unionSETs(it->getSrc(), it->getDest());
	}
	return false;
}