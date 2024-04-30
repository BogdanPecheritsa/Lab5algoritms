#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <random>

struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
};

void append(struct Node** head_ref, int new_data) {
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	struct Node* last = *head_ref;
	new_node->data = new_data;
	new_node->next = NULL;
	if (*head_ref == NULL) {
		new_node->prev = NULL;
		*head_ref = new_node;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return;
}

void selectionSort(struct Node* head) {
	struct Node* i, * j, * min;
	for (i = head; i != NULL && i->next != NULL; i = i->next) {
		min = i;
		for (j = i->next; j != NULL; j = j->next) {
			if (j->data < min->data) {
				min = j;
			}
		}
		if (min != i) {
			int temp = min->data;
			min->data = i->data;
			i->data = temp;
		}
	}
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
			append(&head, dis(gen));
		}
		auto start = std::chrono::high_resolution_clock::now();
		selectionSort(head);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop -
			start);
		printf("Час, витрачений на selectionSort для %d елементів: %lld ms\n",
			sizes[i], duration.count());
	}
	return 0;
}
