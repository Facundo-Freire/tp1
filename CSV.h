#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Sensor.h"
#include "SensorNetwork.h"
#include "Vector.h"
#include "Query.h"


using namespace std;

typedef Vector<Query> Queries;
typedef std::string String;
typedef Vector<String> CSVRow;
typedef Vector<CSVRow> CSVDatabase;

class CSV {
	public:
		CSV();
		~CSV();
		void readCSV(istream &input);

		void importCSVdataSensors(SensorNetwork &);
		void importCSVdataQueries(Queries &);

		void displayCSV() const;
	private:
		CSVDatabase db;
};

#endif
