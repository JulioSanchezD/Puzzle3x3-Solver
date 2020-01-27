#ifndef INC_8_PUZZLE_LINKED_LISTS_H
#define INC_8_PUZZLE_LINKED_LISTS_H

#include "node.h"

typedef struct list_node {
    Node *puzzle_node;
    struct list_node *next;
} ListNode;

typedef struct linked_list {
    ListNode *head;
    int size;
} LinkedList;

void insertListNode(LinkedList *list, Node *node, int closed_list) {
//    If grid is already in closed nodes, compare costs and in case of a better cost, replace node
    if (closed_list) {
        ListNode *index;
        for (index = list->head; index != NULL; index = index->next) {
            if (isGridEqual(node->grid, index->puzzle_node->grid)) {
                if (node->depth < index->puzzle_node->depth) {
                    free(index->puzzle_node);
                    index->puzzle_node = node;
                }
                else {
                    free(node);
                }
                return;
            }
        }
    }

//    Insert node at the beginning of the list
    ListNode *new_list_node = (ListNode *) malloc(sizeof(ListNode));
    new_list_node->puzzle_node = node;
    new_list_node->next = list->head;
    list->head = new_list_node;
    list->size++;
}

void printLinkedList(LinkedList *list) {
    ListNode *index;
    for (index = list->head; index != NULL; index = index->next) {
        puts("     | ");
        puts("     V ");
        printNode(index->puzzle_node);
    }
}

int gridInLinkedList(int grid[][3], LinkedList *opened_nodes) {
    ListNode *index;
    for (index = opened_nodes->head; index != NULL; index = index->next)
        if (isGridEqual(grid, index->puzzle_node->grid)) {
            return 1;
        }
    return 0;
}

#endif //INC_8_PUZZLE_LINKED_LISTS_H
