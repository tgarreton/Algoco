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

// Algoritmo de Programación Dinámica para la distancia mínima de edición
int minEditDistanceDP(const string &S1, const string &S2) {
    int m = S1.length();
    int n = S2.length();

    // Crear tabla DP
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Inicializar la tabla
    for (int i = 0; i <= m; ++i) dp[i][0] = i; // Costo de eliminar caracteres de S1
    for (int j = 0; j <= n; ++j) dp[0][j] = j; // Costo de insertar caracteres de S2

    // Llenar la tabla DP
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int costo_sust = dp[i - 1][j - 1];
            if (S1[i - 1] != S2[j - 1]) {
                costo_sust += costo_replace(S1[i - 1], S2[j - 1]);
            }

            int costo_ins = costo_insert(S2[j - 1]) + dp[i][j - 1];
            int costo_del = costo_delete(S1[i - 1]) + dp[i - 1][j];
            
            dp[i][j] = min({costo_sust, costo_ins, costo_del});

            // Verificar transposición
            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
                dp[i][j] = min(dp[i][j], costo_transpose(S1[i - 2], S1[i - 1]) + dp[i - 2][j - 2]);
            }
        }
    }
    return dp[m][n];
}

int main() {
    // Inicializar tablas de costo desde archivos
    if (!initializeCostTables()) {
        return 1;
    }

    // Archivos de entrada y salida
    ifstream inputFile("casos_prueba.txt");
    ofstream outputFile("resultados_pd.txt");

    if (!inputFile || !outputFile) {
        cerr << "Error al abrir el archivo de entrada o salida." << endl;
        return 1;
    }

    
    outputFile << "Numero,Strings,Costo Edicion,Tiempo Ejecucion\n";

    string S1, S2;
    int count = 1; // Variable para numerar cada par de strings

    while (inputFile >> S1 >> S2) {
        // Medir el tiempo de ejecución
        auto start = high_resolution_clock::now();
        int resultado = minEditDistanceDP(S1, S2);
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

    cout << "Resultados guardados en resultados_pd.txt" << endl;
    return 0;
}
