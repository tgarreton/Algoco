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

// Función para intercambiar dos elementos
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Implementación del algoritmo Quick Sort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

    // Aplica Quick Sort al dataset
    quickSort(dataset, 0, dataset.size() - 1);

    // Termina el cronómetro
    auto end = std::chrono::high_resolution_clock::now();

    // Calcula la duración en segundos
    std::chrono::duration<double> duration = end - start;

    // Guarda el array ordenado en un archivo
    saveToFile("quicksortOutput.txt", dataset);

    // Muestra el tiempo de ejecución en la terminal
    std::cout << "Tiempo de ejecucion: " << duration.count() << " segundos" << std::endl;
    std::cout << "Array ordenado guardado en quicksortOutput.txt" << std::endl;

    return 0;
}
