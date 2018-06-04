#pragma once
enum {
	maxV = 300
};

#include <vector>
#include "Object.h"
#include <iostream>
using namespace std;


class Aresta {
private:
	double pesoAresta;
	int iD_No; // no destino
public:
	Aresta(int iD_No, float pesoA);
	~Aresta();
	double getPesoAresta();
	int getIDNo();
	void setPesoAresta(float peso);
};

class No {
private:
	int iD;
	int grau;
	int grauEntrada;
	int grauSaida;
	double pesoX;
	double pesoY;
	vector <Aresta> listaAresta;
public:
	No();
	~No();
	int getID();
	int getGrau();
	void setID(int id);
	void setGrau(int g);
	void setPesoX(float pesoX);
	void setPesoY(float pesoY);
	void setArestaSize(int size);
	void adicionaAresta(int id, double pesoA);
	void removeAresta(int id);
	double getPesoAresta(int index);
};

class Constructive
{
public:
	Constructive(int numVertex);
	~Constructive();
	void buildGraph(vector <Object*> objects);
	double euclideanDistance(Object *a, Object *b);
	void showGraph();
private:
	double **mat;
	int numVertex;
	vector <No> Graph;
};