#include <iostream>
#include <climits>

#include "Vector.h"
#include "SensorNetwork.h"
#include "Sensor.h"
#include "Query.h"


using namespace std;

void calculateQueryData(const SensorNetwork &sensors,size_t rangeMinimum,size_t rangeMaximum)
{
	double total;
	double average = 0;
	double minimum = ULONG_MAX; //Se iniciaiza con un número muy alto para asegurarnos que al realizar la primera comparación entre el valor mínimo del primer sensor del vector de sensores y este número(ULONG_MAX), la variable minimum almacene el mínimo de los datos del primer sensor (un valor consistente). De esta forma, la variable minimum guardará el mínimo de los datos del primer sensor, y luego se procederá a realizar las restantes comparaciones con los mínimos de los otros sensores.
	double maximum = LONG_MIN; //Razonamiento análogo al anterior. 
	double min,max;
	size_t dataQuantity = 0;
	size_t i,j;
	size_t k = 0;


	for(i = 0; i < sensors.getAmountOfSensors();i++) {
		
		if(rangeMinimum > sensors[i].getAmountOfSensorData()-1){
			cerr<<"NO DATA"<<endl;
			k++; //si uno de los sensores no tiene datos en el rango especificado, ese sensor no se tendrá en cuenta en el cálculo del promedio general. Por ende, la cantidad de sensores que sí se tendrán en cuenta para el promedio general será menor que la cantidad total. Como i representa a la cantidad total de sensores y k a la cantidad de sensores que no poseen datos en ese rango, se promediarán (i-k) promedios de sensores.
			continue;
		}
	
		if(rangeMaximum > sensors[i].getAmountOfSensorData()-1)	{
			rangeMaximum = sensors[i].getAmountOfSensorData()-1;
			min = max = sensors[i][rangeMinimum];
			total = 0;
				for( j=rangeMinimum; j<=rangeMaximum; j++){
					total += sensors[i][j];
					if(sensors[i][j] < min)

						min = sensors[i][j];
					if(sensors[i][j] > max)
						max = sensors[i][j];
				}
				dataQuantity = rangeMaximum - rangeMinimum + 1;
				average += total/dataQuantity;
				if(min < minimum)
					minimum = min;
				if(max > maximum)
					maximum = max;
				continue;
		}

		min = max = sensors[i][rangeMinimum];
		total = 0;
		for( j=rangeMinimum; j<=rangeMaximum; j++){
			total += sensors[i][j];
			if(sensors[i][j] < min)
				min = sensors[i][j];
			if(sensors[i][j] > max)
				max = sensors[i][j];
		}
		dataQuantity = rangeMaximum - rangeMinimum + 1;
		average += total/dataQuantity;
		if(min < minimum)
				minimum = min;
		if(max > maximum)
				maximum = max;
	}

	if(i != k) //Si i es igual a k significa que ningún sensor tenía datos en el rango especificado por la consulta.
		cout<<average/(i-k)<<" "<<minimum<<" "<<maximum<<" "<<dataQuantity<<endl;
}

void calculateQueryData(const Sensor &sensor, size_t rangeMinimum, size_t rangeMaximum)
{
	double total = 0;
	double average,minimum,maximum;
	size_t dataQuantity;
	size_t i;

	if(rangeMinimum > sensor.getAmountOfSensorData()-1){
		cerr<<"NO DATA"<<endl;
		return;
	}
	if(rangeMaximum > sensor.getAmountOfSensorData()-1){

		rangeMaximum = sensor.getAmountOfSensorData()-1;
		minimum = maximum = sensor[rangeMinimum];

		for( i=rangeMinimum; i<=rangeMaximum; i++){
			total += sensor[i];
			if(sensor[i] < minimum)
				minimum = sensor[i];
			if(sensor[i] > maximum)
				maximum = sensor[i];
		}
		dataQuantity = rangeMaximum - rangeMinimum + 1;
		average = total/dataQuantity;
		cout<<average<<" "<<minimum<<" "<<maximum<<" "<<dataQuantity<<endl;
		return;
	}

	minimum = maximum = sensor[rangeMinimum];
	for( i=rangeMinimum; i<=rangeMaximum; i++){
		total += sensor[i];
		if(sensor[i] < minimum)
			minimum = sensor[i];
		if(sensor[i] > maximum)
			maximum = sensor[i];
	}
	dataQuantity = rangeMaximum - rangeMinimum + 1;
	average = total/dataQuantity;

	cout<<average<<" "<<minimum<<" "<<maximum<<" "<<dataQuantity<<endl;
		
}
