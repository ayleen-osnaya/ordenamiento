#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> cargarVector(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<string> contenido;
    string linea;

    if (!archivo) {
        cout << "No se pudo abrir el archivo :(" << endl;
        return contenido;
    }

    while (getline(archivo, linea)) {
        contenido.push_back(linea);
    }

    return contenido;
}

int numMes(string mes) {
    if (mes == "Jan") return 1;
    if (mes == "Feb") return 2;
    if (mes == "Mar") return 3;
    if (mes == "Apr") return 4;
    if (mes == "May") return 5;
    if (mes == "Jun") return 6;
    if (mes == "Jul") return 7;
    if (mes == "Aug") return 8;
    if (mes == "Sep") return 9;
    if (mes == "Oct") return 10;
    if (mes == "Nov") return 11;
    if (mes == "Dec") return 12;
    return 0;
}

int main() {

    // pedir al usuario mes (aun no tiene para fijar fecha de inicio y fin)
    string mes;
    cin >> mes;

    vector<string> contenido;
    contenido = cargarVector("bitacora.txt");


    return 0;
}
