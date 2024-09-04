#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>

void saveToFile(const std::string& filename, const std::vector<int>& data) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int num : data) {
            outFile << num << " ";
        }
        outFile.close();
    }
}

std::vector<int> generateRandomArray(int size, int minVal, int maxVal) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minVal, maxVal);
    for (int& num : arr) {
        num = dis(gen);
    }
    return arr;
}

std::vector<int> generateNearlySortedArray(int size, int swaps) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < swaps; ++i) {
        std::swap(arr[gen() % size], arr[gen() % size]);
    }
    return arr;
}

std::vector<int> generateReverseSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    return arr;
}

std::vector<int> generateArrayWithDuplicates(int size, int numUnique) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, numUnique);
    for (int& num : arr) {
        num = dis(gen);
    }
    return arr;
}

int main() {
    int size = 1000;

    std::vector<int> randomArray = generateRandomArray(size, 1, 10000);
    saveToFile("random.txt", randomArray);

    std::vector<int> nearlySortedArray = generateNearlySortedArray(size, 10);
    saveToFile("parcialmente_ordenados.txt", nearlySortedArray);

    std::vector<int> reverseSortedArray = generateReverseSortedArray(size);
    saveToFile("ordenado_invertido.txt", reverseSortedArray);

    std::vector<int> arrayWithDuplicates = generateArrayWithDuplicates(size, 100);
    saveToFile("con_duplicados.txt", arrayWithDuplicates);

    std::cout << "Datasets generados y guardados." << std::endl;

    return 0;
}
