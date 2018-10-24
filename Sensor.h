#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>

#include "Vector.h"

using namespace std;

class Sensor
{
public:
		Sensor();
		Sensor(string,size_t);
		Sensor(const Sensor &);
		~Sensor();

		void append(double data);
	
		size_t getAmountOfSensorData() const;
		string getSensorName() const;
		void displaySensor() const;
		
		const Sensor& operator=(const Sensor &s);
		double operator[](size_t) const;
		double &operator[](size_t);

private:
		string sensorName;
		Vector<double> dataSensor;
};

#endif
