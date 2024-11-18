#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

const int ALPHABET_SIZE = 26;
vector<int> cost_insert(ALPHABET_SIZE, 1);
vector<int> cost_delete(ALPHABET_SIZE, 1);
vector<vector<int>> cost_replace(ALPHABET_SIZE, vector<int>(ALPHABET_SIZE, 1));
vector<vector<int>> cost_transpose(ALPHABET_SIZE, vector<int>(ALPHABET_SIZE, 1));

// Función para cargar un vector desde un archivo
bool loadVector(const string &filename, vector<int> &vec) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    for (int i = 0; i < ALPHABET_SIZE && file >> vec[i]; ++i);
    file.close();
    return true;
}

// Función para cargar una matriz 26x26 desde un archivo
bool loadMatrix(const string &filename, vector<vector<int>> &matrix) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        for (int j = 0; j < ALPHABET_SIZE && file >> matrix[i][j]; ++j);
    }
    file.close();
    return true;
}

// Inicializar costos de operación desde archivos
bool initializeCostTables() {
    if (!loadVector("cost_insert.txt", cost_insert)) {
        cerr << "Error al cargar cost_insert.txt" << endl;
        return false;
    }
    if (!loadVector("cost_delete.txt", cost_delete)) {
        cerr << "Error al cargar cost_delete.txt" << endl;
        return false;
    }
    if (!loadMatrix("cost_replace.txt", cost_replace)) {
        cerr << "Error al cargar cost_replace.txt" << endl;
        return false;
    }
    if (!loadMatrix("cost_transpose.txt", cost_transpose)) {
        cerr << "Error al cargar cost_transpose.txt" << endl;
        return false;
    }
    return true;
}

// Funciones de costo
int costo_insert(char b) {
    return cost_insert[b - 'a'];
}

int costo_delete(char a) {
    return cost_delete[a - 'a'];
}

int costo_replace(char a, char b) {
    return cost_replace[a - 'a'][b - 'a'];
}

int costo_transpose(char a, char b) {
    return cost_transpose[a - 'a'][b - 'a'];
}

// Algoritmo de Fuerza Bruta para la distancia mínima de edición
int minEditDistanceBruteForce(const string &S1, const string &S2, int i, int j) {
    // Casos base
    if (i == 0) return j; // Insertar todos los caracteres restantes de S2
    if (j == 0) return i; // Eliminar todos los caracteres restantes de S1
    
    // Comparar caracteres finales
    int costo_sust = minEditDistanceBruteForce(S1, S2, i - 1, j - 1);
    if (S1[i - 1] != S2[j - 1]) {
        costo_sust += costo_replace(S1[i - 1], S2[j - 1]);
    }
    
    // Otras operaciones
    int costo_ins = costo_insert(S2[j - 1]) + minEditDistanceBruteForce(S1, S2, i, j - 1);
    int costo_del = costo_delete(S1[i - 1]) + minEditDistanceBruteForce(S1, S2, i - 1, j);

    int costo_trans = INT_MAX;
    if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
        costo_trans = costo_transpose(S1[i - 2], S1[i - 1]) + minEditDistanceBruteForce(S1, S2, i - 2, j - 2);
    }
    
    return min({costo_sust, costo_ins, costo_del, costo_trans});
}

int main() {
    // Inicializar tablas de costo desde archivos
    if (!initializeCostTables()) {
        return 1;
    }

    // Archivos de entrada y salida
    ifstream inputFile("casos_prueba.txt");
    ofstream outputFile("resultados_fb.txt");

    if (!inputFile || !outputFile) {
        cerr << "Error al abrir el archivo de entrada o salida." << endl;
        return 1;
    }

    // Escribir encabezado para el archivo CSV
  outputFile << "Numero,Strings,Costo Edicion,Tiempo Ejecucion\n";

    string S1, S2;
    int count = 1; // Variable para numerar cada par de strings

    while (inputFile >> S1 >> S2) {
        // Medir el tiempo de ejecución
        auto start = high_resolution_clock::now();
        int resultado = minEditDistanceBruteForce(S1, S2, S1.length(), S2.length());
        auto stop = high_resolution_clock::now();
        
        // Calcular la duración en segundos
        auto duration = duration_cast<microseconds>(stop - start).count();
        double duration_in_seconds = duration / 1e6;

        // Guardar los resultados en el archivo CSV
        outputFile << count << "," << S1 << "-" << S2 << "," << resultado << "," << duration_in_seconds << "\n";
        
        count++; // Incrementar el contador
    }

    // Cerrar archivos
    inputFile.close();
    outputFile.close();

    cout << "Resultados guardados en resultados_fb.txt" << endl;
    return 0;
}
