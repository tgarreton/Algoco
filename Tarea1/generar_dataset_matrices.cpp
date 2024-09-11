#include <iostream>
#include <fstream>
#include <cstdlib>  
#include <ctime>    

void generarDatasetMatrices(int n, int m, const std::string& filename) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error abriendo el archivo para escribir el dataset." << std::endl;
        return;
    }
    
    srand(time(0));
    
    // Generar matriz n x m con valores aleatorios entre -100 y 100
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int val = rand() % 201 - 100; // Genera valores entre -100 y 100
            file << val << " ";
        }
        file << "\n"; 
    }
    
    file.close();
    std::cout << "Matriz generada y guardada en " << filename << std::endl;
}

int main() {
    int n, m;
    std::string filename;

    std::cout << "Introduce el numero de filas de la matriz: ";
    std::cin >> n;
    std::cout << "Introduce el numero de columnas de la matriz: ";
    std::cin >> m;
    std::cout << "Introduce el nombre del archivo donde se guardara la matriz: ";
    std::cin >> filename;
    
    generarDatasetMatrices(n, m, filename);
    
    return 0;
}
