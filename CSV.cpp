#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Vector.h"
#include "CSV.h"
#include "Sensor.h"
#include "SensorNetwork.h"
#include "Query.h"

using namespace std;

CSV::CSV() {

}

CSV::~CSV(){

}

void CSV::readCSV(istream &input){
  
	String csvLine;
  // read every line from the stream
  while( getline(input, csvLine) ){
		//csvLine.resize(csvLine.length()-1);
    istringstream csvStream(csvLine);
		CSVRow csvRow;
    String csvCol;
    // read every element from the line that is seperated by commas
    // and put it into the vector or strings
    while( getline(csvStream, csvCol, ',') ){
    	csvRow.append(csvCol);
		}
    db.append(csvRow);
  }
}

void CSV::importCSVdataSensors(SensorNetwork &sensors){

	size_t sensorQuantity = db[0].getSize();
	size_t sensorDataQuantity = db.getSize() - 1;

	size_t row,col;
	double value;

	for(col = 0; col<sensorQuantity; col++){
		Sensor sensor(db[0][col],sensorDataQuantity);
		for(row = 1; row<=sensorDataQuantity; row++){
			istringstream doubleString(db[row][col]);
			doubleString >> value;
		
			if ( doubleString.fail() ) {
				cerr <<"\nDato de sensor inválido: "
		  		<< db[row][col] << "." << endl;
				exit(1);
			}
			if (doubleString.bad()) {
				cerr << "\nNo se pudo efectuar la lectura del dato del sensor."<< endl;
				exit(1);
			}				
			sensor.append(value);
		}
		sensors.append(sensor);
	}
}

void CSV::importCSVdataQueries(Queries &queryVector){
  
	size_t queryQuantity = db.getSize();
	size_t row;

	size_t minimumRange;
	size_t maximumRange;
	
	for(row= 0; row<queryQuantity ; row++) {
			istringstream integerString1(db[row][1]);
			istringstream integerString2(db[row][2]);
			
			integerString1 >> minimumRange;
			integerString2 >> maximumRange;
		
			if ( integerString1.fail() ) {
				cerr <<"\nEl valor mínimo del rango es inválido: "
		  		<< db[row][1] << "." << endl;
				exit(1);
			}
			if (integerString1.bad()) {
				cerr << "\nNo se pudo efectuar la lectura del valor mínimo del rango."<< endl;
				exit(1);
			}	
			
			if ( integerString2.fail() ) {
				cerr <<"\nEl valor máximo del rango es inválido:"
		  		<< db[row][2] << "." << endl;
				exit(1);
			}
			if (integerString2.bad()) {
				cerr << "\nNo se pudo efectuar la lectura del valor máximo del rango."<< endl;
				exit(1);
			}

			if( minimumRange > maximumRange) {
				cerr <<"\nRango de datos inválido."<< endl;
				exit(1);							
			}

			Query query(db[row][0],minimumRange,maximumRange);
			queryVector.append(query);
	}
}

void CSV::displayCSV() const{

	
	size_t csvCols = db[0].getSize();
 	size_t csvRows = db.getSize();

	cout<<"CsvCols: "<<csvCols<<endl;
	cout<<"CsvRows: "<<csvRows<<endl;

	size_t i,j;
	
	for( i = 0; i<csvRows; i++) {
		for(j = 0; j<csvCols; j++){
			cout<<db[i][j]<<" ";
		}
	cout<<endl;
	}
	cout<<endl;
}
