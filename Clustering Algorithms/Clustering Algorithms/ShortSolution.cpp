#include "ShortSolution.h"



ShortSolution::ShortSolution(int numObj,int numClusters)
{
	this->numObj = numObj;
	this->numClusters = numClusters;
	clusters.reserve(numClusters);
	for (int i = 0; i < numObj; i++) {
		clusters[i].reserve(numObj);
	}
	objectByCluster.reserve(numClusters);

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


