#include <iostream>
#include <string>
#include <cstdlib>

#include "Sensor.h"
#include "Vector.h"

using namespace std;

Sensor::Sensor()
{
	sensorName = "\0";
}

Sensor::Sensor(string s,size_t l)
{
	sensorName = s;
	dataSensor.resize(l);
}

Sensor::Sensor(const Sensor &orig)
		:sensorName(orig.sensorName)	
{
	dataSensor = orig.dataSensor;
}

Sensor::~Sensor()
{

}

void Sensor::append(double data)
{
	dataSensor.append(data);
}
 
size_t Sensor::getAmountOfSensorData() const
{
	return dataSensor.getSize();
}

string Sensor::getSensorName() const
{
	return sensorName;
}

void Sensor::displaySensor() const
{
	cout<<getSensorName()<<" ";
	cout<<dataSensor<<endl;
}
 
const Sensor& Sensor::operator=(const Sensor &s)
{
	sensorName = s.sensorName;
	dataSensor = s.dataSensor;
	return *this;
}

double Sensor::operator[](size_t i) const
{
	return dataSensor[i];
}

double &Sensor::operator[](size_t i)
{
	return dataSensor[i];
}
