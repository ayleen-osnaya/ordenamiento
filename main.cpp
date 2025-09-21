#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Registro {
    string mes;   
    int dia;        
    string tiempo;    // hora:minuto:segundo
    string ip;      
    string mensaje; 
    long clave;       //(fecha y hora)
};

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

// Combina mes, día, hora, minuto, segundo en una clave
long claveDesdeBitacora(const string& mes, int dia, int hora, int minuto, int segundo) {
    int mesNumero = mesNum(mes);
    long clave = mesNumero * 100000000  //[01][00][00][00][00]
             + dia       * 1000000      //[00][01][00][00][00]
             + hora      * 10000        //[00][00][01][00][00]
             + minuto    * 100          //[00][00][00][01][00]
             + segundo;                 //[00][00][00][00][01]
    return clave;                       //[mes][dia][hora][minuto][segundo]
}

//Registra cada linea de la bitacora en un vector como un struct con su clave
bool cargarArchivo(string nombreArchivo, vector<Registro>& registros) {
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) { // si no abre el archivo o no se encuentra
        cerr << "Error: No se pudo abrir el archivo intente denuevo o utilize otro archivo" << endl;
        return false;
    }
    
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        //Declaracion de variables para asginar a struct
        Registro lectura; 
        string mesT;
        string tiempoT;
        string ipT;
        string mensajeT;
        int diaT; 

        istringstream iss(linea); // separamos la linea por espacios
        
        //asignacion de valores de bitacora.txt a struct
        iss >>  mesT >> diaT >> tiempoT >> ipT;     
        getline(iss, mensajeT); 
        lectura.mes = mesT;
        lectura.tiempo = tiempoT;
        lectura.ip = ipT;
        lectura.dia = diaT;
        if (mensajeT[0] == ' ')
            mensajeT.erase(0, 1);
        lectura.mensaje = mensajeT;
        //separar hora::minuto::segundo
        int hora = stoi(lectura.tiempo.substr(0, 2));
        int minuto = stoi(lectura.tiempo.substr(3, 2));
        int segundo = stoi(lectura.tiempo.substr(6, 2)); 
        //crear clave
        lectura.clave = claveDesdeBitacora(lectura.mes, lectura.dia, hora, minuto, segundo);
        //ingresar struct en registros
        registros.push_back(lectura);
    }
    archivo.close();
    return true;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partición de Lomuto para vector<Registro>, comparando por .clave
int particion(vector<Registro>& a, int low, int high) {
    long pivot = a[high].clave;       // clave del ultimo elemento
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (a[j].clave <= pivot) {    // orden ascendente por clave
            ++i;
            swap(a[i], a[j]);    // swap de Registro completo
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(vector<Registro>& a, int low, int high) {
    if (low < high) {
        int p = particion(a, low, high);
        quickSort(a, low, p - 1); 
        quickSort(a, p + 1, high);
    }
}

void buscarPorRango(const vector<Registro>& registros) {
    if (registros.empty()) { 
        cout << "Vacio\n"; 
        return; 
    }

    int mesInicioNum, mesFinNum, diaInicio, diaFin;

    cout << "Ingrese la fecha inicial (mes dia, e.g., 6 10): ";
    if (!(cin >> mesInicioNum >> diaInicio)) {
        cerr << "Entrada invalida.\n";
        cin.clear();                // limpia el estado de error
        cin.ignore(1000, '\n');     // descarta lo que quede en el buffer
        return;                     // salir de la función
    }

    cout << "Ingrese la fecha final (mes dia, e.g., 7 15): ";
    if (!(cin >> mesFinNum >> diaFin)) {
        cerr << "Entrada invalida.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    //validacion de rango valido
    if (mesInicioNum < 1 || mesInicioNum > 12 || mesFinNum < 1 || mesFinNum > 12 ||
        diaInicio < 1 || diaInicio > 31 || diaFin < 1 || diaFin > 31) {
        cout << "Fecha no valida.\n";
        return;
    }

    // Inclusion de las 23:59:59
    long claveInicio = mesInicioNum * 100000000 + diaInicio * 1000000 + 0  * 10000 + 0  * 100 + 0;
    long claveFin    = mesFinNum    * 100000000 + diaFin    * 1000000 + 23 * 10000 + 59 * 100 + 59;
    if (claveFin < claveInicio) swap(claveInicio, claveFin);

    vector<Registro> resultados;
    resultados.reserve(registros.size()); // reservar espacio

    for (const auto& r : registros) {
        if (r.clave < claveInicio) continue;
        if (r.clave > claveFin) break; // corte temprano
        resultados.push_back(r);
    }

    if (resultados.empty()) { 
        cout << "No se encontraron registros en el rango especificado.\n"; 
        return; 
    }

    cout << "\n>>> Registros del " << numMes(mesInicioNum) << " " << diaInicio
         << " al " << numMes(mesFinNum) << " " << diaFin << ":\n";

    for (const auto& r : resultados)
        cout << r.mes << ' ' << r.dia << ' ' << r.tiempo << ' ' << r.ip << ' ' << r.mensaje << '\n';

    ofstream outfile("sorted.txt", ios::out | ios::trunc);
    if (!outfile.is_open()) {
        cerr << "Error creando archivo sorted.txt\n";
        return;
    }
    for (const auto& r : resultados)
        outfile << r.mes << ' ' << r.dia << ' ' << r.tiempo << ' ' << r.ip << ' ' << r.mensaje << '\n';

    cout << "\nSe han guardado " << resultados.size()
         << " registros filtrados en sorted.txt\n";
}


int main() {

    vector<Registro> contenido;

    if (!cargarArchivo("bitacora.txt", contenido)) {
        return 1;
    }

    cout << "Cantidad de registros leidos: " << contenido.size() << endl;
   
    if (!contenido.empty()) {
        quickSort(contenido, 0, contenido.size() - 1);
        cout << " ";
    }
    buscarPorRango(contenido);
    return 0;
}