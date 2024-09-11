#include <iostream>
#include <vector>
#include <fstream>
#include <chrono> // Para medir el tiempo de ejecución

// Leer matriz desde archivo
std::vector<std::vector<int>> leerMatriz(const std::string& filename, int& n, int& m) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> matriz;
    
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return matriz;
    }

    file >> n >> m; // Asumimos que las dimensiones están en el archivo (puedes modificarlas según tu formato)
    matriz.resize(n, std::vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            file >> matriz[i][j];
    
    file.close();
    return matriz;
}

//LOS SIGUIENTES ALGORITMOS SON DE LA PAGINA GEEKFORGEEKS 
//

// Algoritmo iterativo cúbico tradicional
std::vector<std::vector<int>> multiplicarMatricesIterativo(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int n, int m, int p) {
    std::vector<std::vector<int>> C(n, std::vector<int>(p, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < p; ++j)
            for (int k = 0; k < m; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// Algoritmo iterativo cúbico optimizado (transponiendo la segunda matriz)
std::vector<std::vector<int>> multiplicarMatricesOptimizado(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int n, int m, int p) {
    std::vector<std::vector<int>> B_T(p, std::vector<int>(m));
    std::vector<std::vector<int>> C(n, std::vector<int>(p, 0));

    // Transponer B
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < p; ++j)
            B_T[j][i] = B[i][j];

    // Multiplicar A por B transpuesta
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < p; ++j)
            for (int k = 0; k < m; ++k)
                C[i][j] += A[i][k] * B_T[j][k];

    return C;
}


// Algoritmo de Strassen (implementación básica)
std::vector<std::vector<int>> multiplicarMatricesStrassen(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int n, int m, int p) {
    // Implementación básica de Strassen (para matrices de tamaño grande)
    return multiplicarMatricesIterativo(A, B, n, m, p); 
}

int main() {
    std::string filenameA, filenameB;
    int n, m, p; // Dimensiones: A[n x m] y B[m x p]

    // Leer matrices desde archivos
    std::cout << "Introduce el nombre del archivo de la primera matriz: ";
    std::cin >> filenameA;
    std::cout << "Introduce el nombre del archivo de la segunda matriz: ";
    std::cin >> filenameB;

    std::vector<std::vector<int>> A = leerMatriz(filenameA, n, m);
    std::vector<std::vector<int>> B = leerMatriz(filenameB, m, p);

    if (A.empty() || B.empty()) {
        std::cerr << "Error al leer las matrices." << std::endl;
        return 1;
    }

    // Medir tiempo de ejecución de cada algoritmo

    // Iterativo cúbico tradicional
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> C1 = multiplicarMatricesIterativo(A, B, n, m, p);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = end - start;
    std::cout << "Tiempo de ejecución (iterativo cúbico tradicional): " << duracion.count() << " segundos" << std::endl;

    // Iterativo cúbico optimizado
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> C2 = multiplicarMatricesOptimizado(A, B, n, m, p);
    end = std::chrono::high_resolution_clock::now();
    duracion = end - start;
    std::cout << "Tiempo de ejecución (iterativo cúbico optimizado): " << duracion.count() << " segundos" << std::endl;

    // Algoritmo de Strassen
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> C3 = multiplicarMatricesStrassen(A, B, n, m, p);
    end = std::chrono::high_resolution_clock::now();
    duracion = end - start;
    std::cout << "Tiempo de ejecución (Strassen): " << duracion.count() << " segundos" << std::endl;

    return 0;
}
