#include "Object.h"
Object::Object()
{


}

Object::Object(int id)
{
	setId(id);

}




Object::~Object()
{
	objByProx.end();
}


double Object::getOrigDoubleAttr(int index)
{
	return origDoubleAttrs[index];
}

int Object::getOrigIntAttr(int index)
{
	return origIntAttrs[index];
}


void Object::setOrigDoubleAttrs(vector <double> origDoubleAttrs)
{
	this->origDoubleAttrs = origDoubleAttrs;
}

void Object::addNewDoubleOrigAttr(double value)
{
	this->origDoubleAttrs.push_back(value);
}

void Object::setOrigDoubleAttr(double origDoubleAttr, int index)
{
	this->origDoubleAttrs[index] = origDoubleAttr;
}

void Object::setOrigIntAttrs(vector <int> origIntAttrs)
{
	this->origIntAttrs = origIntAttrs;
}


double Object::getNormDoubleAttr(int index)
{
	return normDoubleAttrs[index];
}

int Object::getNormIntAttr(int index)
{
	return normIntAttrs[index];
}


void Object::setId(int id) {
	this->id = id;
}

void Object::setOrigId(int origId)
{
	this->origId = origId;
}

void Object::setPos(int pos)
{
	this->pos = pos;
}

void Object::setClusterId(int clusterId)
{
	this->clusterId = clusterId;
}


void Object::addNewDoubleNormAttr(double value) {
	this->normDoubleAttrs.push_back(value);
}

void Object::setNormDoubleAttr(double normDoubleAttr, int index)
{
	this->normDoubleAttrs[index] = normDoubleAttr;
}

void Object::setNormDoubleAttrs(vector <double> values)
{
	this->normDoubleAttrs = values;

}

void Object::setNormIntAttrs(vector <int> values)
{
	this->normIntAttrs = values;
}





int Object::getId()
{
	return this->id;
}

int Object::getClusterId()
{
	return this->clusterId;
}

int Object::getDegree()
{
	return this->degree;
}

void Object::setDegree(int degree)
{
	this->degree = degree;
}

Object *Object::getObject()
{
	return this;
}





