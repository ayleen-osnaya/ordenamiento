#include <iostream>
using namespace std;

void ordenaIntercambio(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[i]) {
                int aux = arr[i];
                arr[i] = arr[j];
                arr[j] = aux;
            }
        }
    }
}


void ordenaBurbuja(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i ; j < size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
        }
    }
}

int main() {
    int size;
    cin >> size;

    int n[size];

    for(int i = 0; i < size; i++) {
        cin >> n[i];
    }


    ordenaIntercambio(n, size);
    for(int i = 0; i < size; i++) {
        cout << n[i] << " ";
    }
    cout << endl;


    ordenaBurbuja(n, size);
    for(int i = 0; i < size; i++) {
        cout << n[i] << " ";
    }
    cout << endl;

    return 0;
}

/
