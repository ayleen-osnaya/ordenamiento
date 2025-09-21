#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> cargarVector(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<string> contenido;
    string linea;

    while (getline(archivo, linea)) {
        contenido.push_back(linea);
    }

    return contenido;
}
int mesNum(string mes) {
    string meses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    for (int i = 0; i < 12; i++) {
        if (mes == meses[i]) {
            return i + 1;
        }
    }
    return 0;
}

string numMes(int num) {
    string meses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    if (num >= 1 && num <= 12) {
        return meses[num - 1];
    } else {
        return "mes invalido :(";
    }
}

int main() {
    // pedir al usuario mes (aun no tiene para fijar fecha de inicio y fin)
    string mes;
    cin >> mes;

    vector<string> contenido;
    contenido = cargarVector("bitacora.txt");


    return 0;
}
