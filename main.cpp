// Prueba de la clase cmdline: dado un factor entero pasado por la
// línea de comando, leemos una secuencia de números que ingresan
// por la entrada estándar, los multiplicamos por ese factor, y
// luego mostramos el resultado por std::cout.
//
// $Id: main.cc,v 1.5 2012/09/15 12:23:57 lesanti Exp $

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "cmdline.h"
#include "CSV.h"
#include "Sensor.h"
#include "SensorNetwork.h"
#include "Vector.h"
#include "Query.h"

using namespace std;

void calculateQueryData(const SensorNetwork &,size_t,size_t);
void calculateQueryData(const Sensor &,size_t,size_t);

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_data(string const &);
static void opt_help(string const &);

// Tabla de opciones de línea de comando. El formato de la tabla
// consta de un elemento por cada opción a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opción lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opción.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opción en caso que no esté explícitamente presente
//   en la línea de comandos del programa. Si la opción no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al método de parseo de la opción,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La última columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opción: cuando la
//   opción es obligatoria, deberá activarse OPT_MANDATORY.
//
// Además, la última entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//

/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "d", "data", NULL, opt_data, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static istream *inputData = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static istream *inputQuery = 0;
static ostream *output = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ifss;
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)



/*****************************************************/

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		inputQuery = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		inputQuery = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!inputQuery->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		output = &cout;	// Establezco la salida estandar cout como flujo de salida
	} 
	else {
		ofs.open(arg.c_str(), ios::out);
		output = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!output->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void
opt_data(string const &arg)
{
	ifss.open(arg.c_str(), ios::in);
	inputData = &ifss;
	
	if (!inputData->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_help(string const &arg)
{
	cout << "cmdline -f factor [-i file] [-o file]"
	     << endl;
	exit(0);
}


int main(int argc, char * const argv[])
{
	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline
	
  CSV csvSensors;
	CSV csvQueries;

	SensorNetwork sensors;
	Queries queries;

	csvSensors.readCSV(*inputData); //lee el archivo CSV que contiene los datos de los sensores.
	csvSensors.importCSVdataSensors(sensors);// almacena los datos en un vector de sensores.

	csvQueries.readCSV(*inputQuery); //lee el archivo CSV que contiene las consultas.
	csvQueries.importCSVdataQueries(queries);// almacena las consultas en un vector de consultas.

	size_t i,j;
	
	for(i = 0; i<queries.getSize(); i++){
		if(queries[i].getSensorQueryName() == "") { //si la consulta no especifica un nombre de un sensor,se realizan los cálculos para todos 																									los sensores.
			calculateQueryData(sensors,queries[i].getRangeMin(),queries[i].getRangeMax());
			continue;
		}		
		for(j = 0; j<sensors.getAmountOfSensors(); j++){
			if(queries[i].getSensorQueryName() == sensors[j].getSensorName() ) {
				calculateQueryData(sensors[j],queries[i].getRangeMin(),queries[i].getRangeMax());
				break;
			}
		}
		if( j == sensors.getAmountOfSensors()) //si no hay coincidencia entre el nombre del sensor de consulta y los nombres de los sensores de la base de datos.
			cerr<<"UNKNOWN ID"<<endl;	
	}

	return 0;
}
