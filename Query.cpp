#include <iostream>
#include <string>

#include "Query.h"

using namespace std;

Query::Query() {
		querySensorName = "\0";
		rangeMinimumQuery = 0;
		rangeMaximumQuery= 0;
}

Query::Query(string sensorName,size_t minRange,size_t maxRange)
{
	querySensorName = sensorName;
	rangeMinimumQuery = minRange;
	rangeMaximumQuery = maxRange;
}
Query::~Query(){

}

string Query::getSensorQueryName() const
{
	return querySensorName;
}

size_t Query::getRangeMin() const
{
	return rangeMinimumQuery;
}
		
size_t Query::getRangeMax() const
{
	return rangeMaximumQuery;
}

void Query::displayQuery() const
{
	cout<<querySensorName<<" "<<"("<<rangeMinimumQuery<<","<<rangeMaximumQuery<<")"<<endl;
}
