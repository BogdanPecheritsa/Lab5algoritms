#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <random>

struct Node {
	int data;
	struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void insertionSort(struct Node** head_ref) {
	struct Node* sorted = NULL;
	struct Node* current = *head_ref;
	while (current != NULL) {
		struct Node* next = current->next;
		struct Node* temp = sorted;
		struct Node* prev = NULL;
		while (temp != NULL && temp->data < current->data) {
			prev = temp;
			temp = temp->next;
		}
		if (prev == NULL) {
			current->next = sorted;
			sorted = current;
		}
		else {
			current->next = prev->next;
			prev->next = current;
		}
		current = next;
	}
	*head_ref = sorted;
}

int main() {
	int sizes[] = { 10, 100, 500, 1000, 2000, 5000, 10000 };
	int n = sizeof(sizes) / sizeof(sizes[0]);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10000);
	for (int i = 0; i < n; i++) {
		struct Node* head = NULL;
		for (int j = 0; j < sizes[i]; j++) {
			push(&head, dis(gen));
		}
		auto start = std::chrono::high_resolution_clock::now();
		insertionSort(&head);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop -
			start);
		printf("Час, витрачений на insertionSort для %d елементів: %lld ms\n",
			sizes[i], duration.count());
	}
	return 0;
}
