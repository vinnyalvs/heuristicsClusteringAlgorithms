#include "ShortSolution.h"



ShortSolution::ShortSolution(int numObj, int numClusters)
{
	this->numObj = numObj;
	this->numClusters = numClusters;
	clusters.reserve(numClusters);
	vector <int> a;
	clusters.assign(numClusters, a);
	costClusters.assign(numClusters, 0.0);
	for (int i = 0; i < clusters.size(); i++) {
		clusters[i].reserve(numObj);
	}
	objectByCluster.reserve(numClusters);
	objectByCluster.assign(numObj, 0);

}


ShortSolution::~ShortSolution()
{
	
	
}

void ShortSolution::addObject(int objectId, int clusterId)
{




	clusters[clusterId].push_back(objectId);


}

int ShortSolution::getId()
{
	return this->id;
}

void ShortSolution::setId(int id)
{

	this->id = id;
}

double ShortSolution::getSilhouette()
{
	return silhouette;
}

double ShortSolution::euclideanDistance(Object *a, Object *b)
{
	double dist = 0.0;
	for (int i = 0; i < 2; i++) {

		dist += pow((a->getNormDoubleAttr(i) - b->getNormDoubleAttr(i)), 2);
	}
	return sqrt(dist);
}

void ShortSolution::calculateSilhouette()
{
	double dissimilarityA = 0;
	double dissimilarityB = 0;
	double s = 0; // Silhueta;
				  //Para cada Objeto
	int i = 0;
	for (vector <Object*>::iterator it = objs.begin(); it != objs.end(); it++, i++) {
		//Para cada objeto no cluster do objeto I
		//Calculamos a dissimilaridade do objeto I para todos os obj de seu cluster
		if (clusters[(*it)->getClusterId()].size() > 1) {
			for (int j = 0; j < clusters[(*it)->getClusterId()].size(); j++) {
				double distanceToSameCluster = 0;
				if ((*it)->getId() != clusters[i][j]) {
					distanceToSameCluster += euclideanDistance(*it, objs[clusters[i][j]]);
				}
				dissimilarityA = distanceToSameCluster / (clusters.size() - 1);
			}
			//Para cada cluster j
			for (int j = 0; j < clusters.size(); j++) {
				double distanceToOtherCluster = 0;
				double minDissimilarity = numeric_limits<double>::max();
				//Esse if serve para não compararmos com os obj do mesmo cluster;
				if (j != objs[i]->getClusterId()) {
					double auxDist = 0;
					//Para cada objeto do cluster j, calculamos a dist do objeto it ao objeto[j][k]
					for (int k = 0; k < clusters[j].size(); k++) {
						auxDist += euclideanDistance(*it, objs[clusters[j][k]]);
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

	s = s / objs.size();

	silhouette = s;





}



bool ShortSolution::isObjectInCluster(int objId, int clusterId)
{
	bool check = false;
	for (vector <int>::iterator it = clusters[clusterId].begin(); it != clusters[clusterId].end(); ++it) {
		if (*it == objId) {
			return check;
			break;
		}
	}
	return check;


}

int ShortSolution::getNumClusters()
{
	return numClusters;
}

int ShortSolution::getNumObjs()
{
	return numObj;
}

void ShortSolution::setObjects(vector<Object*> objs)
{
	this->objs = objs;
}

vector<vector<int>> ShortSolution::getClusters()
{
	return clusters;
}

void ShortSolution::showSolution()
{
	cout << "Para " << clusters.size() << " clusters: " << endl;
	for (int i = 0; i < clusters.size(); i++) {
		cout << "Cluster " << i + 1 << " Contem " << clusters[i].size() << " objetos" << endl;
		for (int j = 0; j < clusters[i].size(); j++) {
			cout << clusters[i][j] << " ";
		}
		cout << endl;
	}
}

void ShortSolution::setObjectByCluster(vector<int> objectByCluster)
{
	this->objectByCluster = objectByCluster;
}

void ShortSolution::setGraph(vector<Node>graph)
{
	this->graph = graph;

}

vector<Node> ShortSolution::getGraph()
{
	return graph;
}

void ShortSolution::calculateCostClusters()
{
	//Para cada cluster i com k objetos
	vector <double> costClusters;
	costClusters.assign(clusters.size(), 0);
	for (int i = 0; i < clusters.size(); i++) {
		//Para cada objeto j Node cluster i
		double soma = 0;
		cout << "-----------------" << endl;
		for (int j = 0; j < clusters[i].size(); j++) {
			//Somatorio das distancias do obj j aos outros k-1 objetos do cluster
			// soma += distancia obj j
			for (int k = j; k < clusters[i].size(); k++) {
				if (j != k) {
					cout << "J: " << j << " K " << k << endl;
					double a = graph[clusters[i][j]].getDistance(clusters[i][k]);
					soma += a;
					cout << a << endl;
				}
			}
		}
		costClusters[i] = soma;
		cout << "cluster " << i << " size: " << clusters[i].size() << endl;
		cout << "Custo CLuster i: " << costClusters[i] << endl;
		cout << "-----------------" << endl;
		//cout << costClusters[i] << endl;
	}

}


