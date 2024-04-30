#include <stdio.h>
#include <chrono>
#include <random>

void insertionSort(int arr[], int n) {
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

int main() {
	int sizes[] = { 10, 100, 500, 1000, 2000, 5000, 10000 };
	int n = sizeof(sizes) / sizeof(sizes[0]);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10000);
	for (int i = 0; i < n; i++) {
		int* arr = new int[sizes[i]];
		for (int j = 0; j < sizes[i]; j++) {
			arr[j] = dis(gen);
		}
		auto start = std::chrono::high_resolution_clock::now();
		insertionSort(arr, sizes[i]);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop -
			start);
		printf("Час, витрачений на insertionSort для %d елементів: %lld ms\n",
			sizes[i], duration.count());
		delete[] arr;
	}
	return 0;
}