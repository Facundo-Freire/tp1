#ifndef QUERY_H
#define QUERY_H

#include <iostream>
#include <string>

using namespace std;

class Query {
	public:
		Query();
		Query(string,size_t,size_t);
		~Query();
		
		string getSensorQueryName() const;
		size_t getRangeMin() const;
		size_t getRangeMax() const;

		void displayQuery() const;
	private:
		string querySensorName;
		size_t rangeMinimumQuery;
		size_t rangeMaximumQuery;
		
};

#endif
