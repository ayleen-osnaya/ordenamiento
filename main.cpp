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

int main() {
    string nombreArchivo;
    cin >> nombreArchivo;

    vector<string> contenido;
    contenido = cargarVector(nombreArchivo);


   //nota para mi: enseñar que tiene el archivo, borrar despues
    for (int i = 0; i < contenido.size(); i++) {
        cout << contenido[i] << endl;
    }

    return 0;
}
