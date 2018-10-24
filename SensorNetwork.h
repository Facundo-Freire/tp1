#ifndef SENSORNETWORK_H
#define SENSORNETWORK_H

#include <iostream>
#include <string>

#include "Vector.h"
#include "Sensor.h"

using namespace std;

class SensorNetwork
{
public:
		SensorNetwork();
		SensorNetwork(size_t);
		SensorNetwork(const SensorNetwork &);
		~SensorNetwork();

		void append(Sensor sensor);

		size_t getAmountOfSensors() const;
		void displaySensorNetwork() const;
		
		const SensorNetwork& operator=(const SensorNetwork &s);

		Sensor operator[](size_t) const;
		Sensor &operator[](size_t);

private:
		Vector<Sensor> sensors;
};

#endif
