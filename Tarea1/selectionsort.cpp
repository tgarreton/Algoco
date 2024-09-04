#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>  // Librería para medir el tiempo

// Función para leer el dataset desde un archivo
std::vector<int> readDataset(const std::string& filename) {
    std::vector<int> data;
    std::ifstream inFile(filename);

    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            int num;
            while (ss >> num) {
                data.push_back(num);
            }
        }
        inFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    }
    
    return data;
}

// Implementación del algoritmo Selection Sort
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

// Función para guardar el array ordenado en un archivo
void saveToFile(const std::string& filename, const std::vector<int>& data) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int num : data) {
            outFile << num << " ";
        }
        outFile.close();
    } else {
        std::cerr << "No se pudo crear el archivo: " << filename << std::endl;
    }
}

int main() {
    // Pregunta por el nombre del archivo al usuario
    std::string filename;
    std::cout << "Ingrese el nombre del archivo de texto que desea leer: ";
    std::cin >> filename;

    // Llama al dataset guardado en el archivo especificado
    std::vector<int> dataset = readDataset(filename);

    // Inicia el cronómetro
    auto start = std::chrono::high_resolution_clock::now();

    // Aplica Selection Sort al dataset
    selectionSort(dataset);

    // Termina el cronómetro
    auto end = std::chrono::high_resolution_clock::now();

    // Calcula la duración en segundos
    std::chrono::duration<double> duration = end - start;

    // Guarda el array ordenado en un archivo
    saveToFile("selectionsortOutput.txt", dataset);

    // Muestra el tiempo de ejecución en la terminal
    std::cout << "Tiempo de ejecucion: " << duration.count() << " segundos" << std::endl;
    std::cout << "Array ordenado guardado en selectionsortOutput.txt" << std::endl;

    return 0;
}
