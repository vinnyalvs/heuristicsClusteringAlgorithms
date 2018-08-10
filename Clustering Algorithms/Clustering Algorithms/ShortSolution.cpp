#include "ShortSolution.h"



ShortSolution::ShortSolution(int numObj,int numClusters)
{
	this->numObj = numObj;
	this->numClusters = numClusters;
	clusters.reserve(numClusters);
	vector <int> a;
	clusters.assign(numClusters,a);
	for (int i = 0; i < clusters.size(); i++) {
		clusters[i].reserve(numObj);
	}
	objectByCluster.reserve(numClusters);

}


ShortSolution::~ShortSolution()
{

}

void ShortSolution::addObject(int objectId, int clusterId)
{
	

	//cout << "objeto de id: " << objectId << "Esta sendo inserido no cluster: " << clusterId << endl;
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

void ShortSolution::Silhouette()
{
}

bool ShortSolution::isObjectInCluster(int objId, int clusterId)
{
	bool check=false;
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

vector<vector<int>> ShortSolution::getClusters()
{
	return clusters;
}

void ShortSolution::showSolution()
{
	cout << "Para " << clusters.size() << " clusters: " << endl;
	for (int i = 0; i < clusters.size(); i++) {
		cout << "Cluster " << i +  1 << " Contem " << clusters[i].size()  << " objetos" << endl;
		for (int j = 0; j < clusters[i].size(); j++) {
			cout << clusters[i][j] << " ";
		}
		cout << endl;
	}
}

double ShortSolution::calculateIntraClusterDistance(int clusterId)
{
	return 0.0;
}

double ShortSolution::calculateInterclusterDistance(int clusterId)
{
	return 0.0;
}

double ShortSolution::calculateRatio(int clusterId)
{
	return 0.0;
}




