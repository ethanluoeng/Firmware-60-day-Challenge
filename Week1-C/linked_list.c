#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int data;
    struct node *next_node;
} node;


node *insert(int data, node *head_node)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        printf("ERROR allocating memory");
        return NULL;
    }

    new_node->data = data;
    new_node->next_node = head_node;
    
    return new_node;
}


node *search(int search_data, node *head_node)
{
    node *cur_node = head_node;
    while (cur_node != NULL) {
        if (cur_node->data == search_data) {
            printf("Search data %d was found!\n", search_data);
            return cur_node;
        }

        cur_node = cur_node->next_node;
    }
    printf("Search data %d was NOT found!\n", search_data);
    return NULL;
}


void delete(int delete_data, node **head_node)
{
    node *cur_node = *head_node;
    node *last_node;

    // Special case for deleting the head node
    if (cur_node->data == delete_data) {
        *head_node = (*head_node)->next_node;
        free(cur_node);
        printf("Deleted HEAD node with %d\n", delete_data);
        return;
    }
    last_node = cur_node;
    cur_node = cur_node->next_node;
    
    // Deleting the other nodes
    while (cur_node != NULL) {
        if (cur_node->data == delete_data) {
            last_node->next_node = cur_node->next_node;
            free(cur_node);
            printf("Deleted Non-head node with %d\n", delete_data);
            return;
        }
        last_node = cur_node;
        cur_node = cur_node->next_node;
    }
    printf("Delete data %d NOT found...\n", delete_data);
}


void free_list(node *head_node)
{
    node *cur_node = head_node;
    int freed = 0;
    while (cur_node != NULL) {
        node *next_node = cur_node->next_node;
        free(cur_node);
        cur_node = next_node;
        freed++;
    }

    printf("Done! Freed %d nodes.\n", freed);
}


void print(node *head_node)
{
    node *cur_node = head_node;
    while (cur_node != NULL) {
        printf("%d\n", cur_node->data);
        cur_node = cur_node->next_node;
    }
}


int main(void) 
{
    node *start; 
    start = insert(1, NULL);
    start = insert(2, start);
    start = insert(3, start);

    search(5, start);

    print(start);

    // Must pass in address of pointer because delete accepts a pointer to a pointer
    delete(3, &start);

    print(start);

    free_list(start);
    start = NULL; // Must include this or the dangling pointers still exist even though the memory has been freed.

    print(start);
}