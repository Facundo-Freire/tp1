all: tp0 clean

OBJECTS= main.obj calculateSensorData.obj cmdline.obj CSV.obj SensorNetwork.obj Sensor.obj Query.obj
CC=g++ -g -pedantic -Wall	

tp0: $(OBJECTS)
				$(CC) -o tp0 $(OBJECTS)

main.obj: main.cpp cmdline.h Vector.h Query.h Sensor.h SensorNetwork.h CSV.h 
	$(CC) -o main.obj -c main.cpp

calculateSensorData.obj: CalculateSensorData.cpp
	$(CC) -o calculateSensorData.obj -c CalculateSensorData.cpp

cmdline.obj: cmdline.cpp cmdline.h 
	$(CC) -o cmdline.obj -c cmdline.cpp

CSV.obj: CSV.cpp CSV.h Sensor.h SensorNetwork.h Query.h Vector.h
	$(CC) -o CSV.obj -c CSV.cpp

SensorNetwork.obj: SensorNetwork.cpp SensorNetwork.h Vector.h Sensor.h
	$(CC) -o SensorNetwork.obj -c SensorNetwork.cpp

Sensor.obj: Sensor.cpp Sensor.h Vector.h
	$(CC) -o Sensor.obj -c Sensor.cpp

Query.obj: Query.cpp Query.h 
	$(CC) -o Query.obj -c Query.cpp

clean:
				rm *.obj
