#include <iostream>
#include <string>
#include <cstdlib>

#include "SensorNetwork.h"
#include "Sensor.h"
#include "Vector.h"

using namespace std;

SensorNetwork::SensorNetwork()
{

}

SensorNetwork::SensorNetwork(size_t l)
{
	sensors.resize(l);
}

SensorNetwork::SensorNetwork(const SensorNetwork &orig)
{
	sensors = orig.sensors;
}

SensorNetwork::~SensorNetwork()
{

}

void SensorNetwork::append(Sensor sensor)
{
	sensors.append(sensor);
}

size_t SensorNetwork::getAmountOfSensors() const
{
	return sensors.getSize();
}

void SensorNetwork::displaySensorNetwork() const
{
	size_t i;
	for(i= 0; i < sensors.getSize() ; i++)
		sensors[i].displaySensor();

}
	
const SensorNetwork& SensorNetwork::operator=(const SensorNetwork &s)
{
	sensors = s.sensors;
	return *this;
}

Sensor SensorNetwork::operator[](size_t i) const
{
	return sensors[i];
}

Sensor &SensorNetwork::operator[](size_t i )
{
	return sensors[i];
}
