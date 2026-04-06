#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct Node {
    int data;
    struct Node *next;
};

int check_duplicate(int data[], int size, int value) {
    for (int i = 1; i <= size; i++) {
        if (data[i] == value) {
            return 1; // duplicate found
        }
    }
    return 0; // no duplicate
}

void remover(struct Node **node_last_ptr, struct Node *node_current, struct Node *node_next, int data[]) {
    struct Node *node_last = *node_last_ptr;
    
    if (node_last == NULL) {
        // head; just store value
        data[0]++;
        data[data[0]] = node_current->data;
        node_last = node_current;
    } else {
        int isDuplicate = check_duplicate(data, data[0], node_current->data);

        if (isDuplicate == 1) {
            // remove current node
            node_last->next = node_next;
            free(node_current);
        } else {
            // store value
            data[0]++;
            data[data[0]] = node_current->data;
            node_last = node_current;
        }
    }

    // Update the pointer for the next call
    *node_last_ptr = node_last;
    
    // Check if we've reached the end
    if (node_next == NULL) {
        return;
    }
    
    if (node_next->next == NULL) {
        // reaching end, do final check
        int isDuplicate = check_duplicate(data, data[0], node_next->data);
        if (isDuplicate == 1) {
            node_last->next = NULL;
            free(node_next);
        } else {
            data[0]++;
            data[data[0]] = node_next->data;
        }
    } else {
        remover(node_last_ptr, node_next, node_next->next, data);
    }
}

int counter(struct Node *node) {
    if (node->next == NULL) {
        return 1;
    }
    return counter(node->next)+1;
}

void remove_duplicates(struct Node *head) {
    int count = counter(head);
    int data[count+1]; // max possible unique elements is count
    // data[0] will store the current count of unique elements
    data[0] = 0;

    struct Node *node_last = NULL;
    remover(&node_last, head, head->next, data);

    // return head;
}

int main() {
    struct Node* head = (struct Node*)malloc(sizeof(struct Node)); // Now requires separate initialization
    head->data = 1;
    head->next = (struct Node*)malloc(sizeof(struct Node));
    head->next->data = 2;
    head->next->next = (struct Node*)malloc(sizeof(struct Node));
    head->next->next->data = 2;
    head->next->next->next = (struct Node*)malloc(sizeof(struct Node));
    head->next->next->next->data = 3;
    head->next->next->next->next = (struct Node*)malloc(sizeof(struct Node));
    head->next->next->next->next->data = 3;
    head->next->next->next->next->next = NULL; // Explicitly set the last node's next to NULL

    remove_duplicates(head); 

    // Print the modified list: 1 -> 2 -> 3
    struct Node* curr = head;
    while (curr!= NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL) {
            printf(" -> ");
        }
        curr = curr->next;
    }
    
    printf("\n");

    return 0;
}