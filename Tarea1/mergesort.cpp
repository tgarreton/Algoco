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

// Función para combinar dos subarrays ordenados
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Implementación del algoritmo Merge Sort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
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

    // Aplica Merge Sort al dataset
    mergeSort(dataset, 0, dataset.size() - 1);

    // Termina el cronómetro
    auto end = std::chrono::high_resolution_clock::now();

    // Calcula la duración en segundos
    std::chrono::duration<double> duration = end - start;

    // Guarda el array ordenado en un archivo
    saveToFile("mergesortOutput.txt", dataset);

    // Muestra el tiempo de ejecución en la terminal
    std::cout << "Tiempo de ejecucion: " << duration.count() << " segundos" << std::endl;
    std::cout << "Array ordenado guardado en mergesortOutput.txt" << std::endl;

    return 0;
}
