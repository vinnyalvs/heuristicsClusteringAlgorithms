#pragma once
#include <vector>
using namespace std;
class Object
{
public:

	Object();
	/**
	object constructor.
	@param  int id  object id
	@return none
	*/
	Object(int id);
	/**
	object constructor, with almost everything an object has
	@param  int      id                  object id
	@param  int      origId              the original id of object
	@param  int      pos                 object position
	@param  int      clusterId           id of obj cluster
	@param  double   origDoubleAttr  double attr original
	@param  int      origIntAttr         int attr original
	@param  Category origCatAttr    category attr original
	@return none
	*/
	
	/**
	object destructor.
	@param  none
	@return none
	*/
	~Object();

	/**
	return the double original attr.
	@param  none
	@return double orignal double attribute
	*/
	double getOrigDoubleAttr(int index);
	/**
	return the int original attr.
	@param  none
	@return int orignal int attribute
	*/
	int getOrigIntAttr(int index);
	/**
	return  the category original attribute
	@param  none
	@return Category category original attribute
	*/
	
	/**
	set the double original attribute
	@param  double origDoubleAttr  original double attr
	@return none
	*/
	void setOrigDoubleAttrs(vector <double> origDoubleAttrs);

	void addNewDoubleOrigAttr(double value);

	void setOrigDoubleAttr(double origDoubleAttr, int index);
	/**
	set the int original attr.
	@param  int origIntAttr orignal int attribute
	@return none
	*/
	void setOrigIntAttrs(vector <int> origIntAttrs);
	/**
	set  the category original attribute
	@param  Category origCatAttr original category attribute
	@return none
	*/
	

	/**
	return the double normalized attr.
	@param  none
	@return double normDoubleAttr normalized double attribute
	*/
	double getNormDoubleAttr(int index);
	/**
	return the int normalized attr.
	@param  int index   attr index
	@return int normIntAttr normalized int attribute
	*/

	int getNormIntAttr(int index);
	/**
	return the int normalized attr.
	@param  int index attr index
	@return int normCatAttr normalized Category attribute
	*/

	
	/**
	set object Id.
	@param  int id object id
	@return none
	*/
	void setId(int id);
	/**
	set object original Id.
	@param  int origId original id
	@return none
	*/

	void setOrigId(int origId);
	/**
	set object position.
	@param  int pos
	@return none
	*/
	void setPos(int pos);
	/**
	set which cluster object belongs
	@param  int clusterId
	@return none
	*/
	void setClusterId(int clusterId);
	void addNewDoubleNormAttr(double attr);
	void setNormDoubleAttr(double normDoubleAttr, int index);
	/**
	set all norm double attrs.
	@param  vector <double> values
	@return none
	*/
	void setNormDoubleAttrs(vector <double> values);
	/**
	set all norm int attrs.
	@param  vector <int> values
	@return none
	*/
	void setNormIntAttrs(vector <int> values);
	/**
	set all norm category attrs.
	@param  vector <Category> values
	@return none
	*/
	/**
	set all norm attrs in once.
	@param  vector <double> valueDoubleAttrs, vector <Int> valueIntAttrs, vector <Category> valueCatAttrs
	@return none
	*/
	
	/**
	return object id.
	@param  none
	@return int id
	*/
	int getId();
	/**
	return the id of the cluster which object belongs
	@param  none
	@return int clusterId
	*/
	int getClusterId();
	/**
	return the degree of the object
	@param  none
	@return int clusterId
	*/
	int getDegree();
	void setDegree(int degree);
	/**
	return tthe object
	@param  none
	@return Object object
	*/
	Object *getObject();

	void setDissimilaritySameCluster(double d);
	double getDissimilaritySameCluster();
	void setDissimilarityOtherCluster(double d);
	double getDissimilarityOtherCluster();

private:

	// orig = original , norm = normalized, simi = similarity, pos = position
	int id;
	int degree;
	int origId;
	int pos;
	int clusterId;
	vector <int>		objByProx;
	// Original attributes
	vector <double>		origDoubleAttrs;
	vector <int>		origIntAttrs;
	// Normalized Attributes
	vector <double>		normDoubleAttrs;
	vector <int>		normIntAttrs;

	double dissimilaritySameCluster;
	double dissimilarityOtherClusters;



};

