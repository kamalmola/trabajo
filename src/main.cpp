/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Lucas Cauhé y Kamal Bouizzy 
 * Ultima revisión: ¡¡¡!!!
 * Resumen: ¡¡¡!!!
 * Nota: El código de este programa está repartido en varios módulos.
 *       Para compilarlo, hay que ejecutar el comando
 *           make all
 *       o, en Windows,
 *           mingw32-make all
 *       o ejecutar la tarea "Compilar «electricidad»" de VSC.
 * 
 *       Para ejecutarlo, una vez compilado, hay que ejecutar el comando
 *           bin/electricidad
 *       o, en Windows,
 *           bin\electricidad.exe
 *       o ejecutar la tarea "Ejecutar «electricidad»" de VSC.
\******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"
#include "vector-gastos.hpp"
#include "tarifas-comerciales.hpp"
using namespace std;

struct Usuario {
    char nombre;
    int mesInicial, mesFinal;
    string ficheros[12];
};

/*
 * Pre:  «f» es «cout» o un flujo de la clase «ofstream» asociado con un fichero
 *       externo abierto para escritura. Las «numRegs» primeras componentes
 *       del vector «regDiarios» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: Ha escrito en el flujo «f» el informe sobre consumo eléctrico indicado
 *       en el enunciado de este trabajo.
 */
void escribirInforme(ostream& f, const GastoDiario regDiarios[], const unsigned numRegs, const string nombreCliente, 
const unsigned mesInicial, const unsigned mesFinal) {
    string cabecera = "INFORME DEL CLIENTE " + nombreCliente + " ENTRE LOS MESES "+ to_string(mesInicial) + 
    " Y " + to_string(mesFinal) + " DE 2021\n-------------------------------------\n";
    f << cabecera;


}   

bool pedirDatos(string& usuario, unsigned& mesInicial, unsigned& mesFinal, string& fichero){
    cout << "Escriba el nombre del usuario: ";

    cin >> usuario;

    cout << endl;
    cout << "Escriba el mes inicial y el final: ";
    cin >> mesInicial >> mesFinal;
    
    while (mesInicial > mesFinal){
        cout << "El mes inicial tiene que ser menor o igual que el mes final." << endl << endl;
        cout << "Escriba el mes inicial y el final: ";
        cin >> mesInicial >> mesFinal;
    }
    
    short n_veces_error = 0;
    while ((mesInicial > 11 || mesInicial < 1) || (mesFinal > 11 || mesFinal < 1)){
        cout << "El mes inicial tiene que estar entre 1 y 11.\n";
        cout << "El mes final tiene que estar entre 1 y 11.\n";
        if (!n_veces_error){
            cout << "El mes inicial tiene que ser menor o igual que el mes final.\n" << endl;
            n_veces_error++;
        }
        cout << "Escriba el mes inicial y el final: ";
        cin >> mesInicial >> mesFinal;
    }
    
    cout << endl;

    cout << "Escriba el nombre del fichero del informe\n";
    cout << "(presione solo ENTRAR para escribirlo en la pantalla): ";
    cin.ignore();
    char crtr = cin.get();
    if (crtr == '\n') {
        return false;
    }
    getline(cin, fichero);
    fichero = crtr + fichero;
    return true;
}


/*
 * ¡ESCRIBID LA ESPECIFICACIÓN DE ESTA FUNCIÓN!
 */
int main() {

    
    string usuario;
    unsigned mesInicial, mesFinal;
    string fichero = "";

    bool nuevoArchivo = pedirDatos(usuario, mesInicial, mesFinal, fichero);
    Fecha fechaInicio = {1, mesInicial, 2021};
    Fecha fechaFinal = {1, mesFinal+1, 2021};

    unsigned numRegs = diasTranscurridos(fechaInicio, fechaFinal);
    GastoDiario regsDiarios[numRegs];
    leerPrecios("datos/tarifas-2021-ene-nov.csv", mesInicial, mesFinal, regsDiarios);
    leerConsumos(usuario, mesInicial, mesFinal, regsDiarios);
<<<<<<< HEAD
    for (unsigned i=0; i<10; i++){
        for (unsigned j=0; j<24; j++){
            cout << regsDiarios[i].consumos[j] << endl;
        }
    } 
    

     
=======
    
>>>>>>> d08ae64f3c0baf4280c7fd23ef6554f2fc77d3cc
    if (nuevoArchivo){
        ofstream f(fichero);
        if (!f.is_open()){
            cerr << "El archivo no se pudo abrir correctamente";
            return 1;
        }
        escribirInforme(f, regsDiarios, numRegs, usuario, mesInicial, mesFinal);
    } else {
        escribirInforme(cout, regsDiarios, numRegs, usuario, mesInicial, mesFinal);
    }
    return 0;
}