#include <string.h>
#include "node.h"
#include "linked_lists.h"

void expandNode(Node *node, LinkedList *opened_nodes, LinkedList *closed_nodes, int goal[][3], Heuristic heuristic[3]) {
    int z_row, z_col;
    static int id;
    Node *child_left, *child_right, *child_up, *child_down;
    getPosition(0, node->grid, &z_row, &z_col);
    if (z_row != 0 && node->operator != down) {
        child_up = newNode(++id, node, up, heuristic, goal, z_row, z_col);
        if (gridInLinkedList(child_up->grid, opened_nodes))
            free(child_up);
        else
            insertListNode(closed_nodes, child_up, 1);
    }
    if (z_row != 2 && node->operator != up) {
        child_down = newNode(++id, node, down, heuristic, goal, z_row, z_col);
        if (gridInLinkedList(child_down->grid, opened_nodes))
            free(child_down);
        else
            insertListNode(closed_nodes, child_down, 1);
    }
    if (z_col != 0 && node->operator != right) {
        child_left = newNode(++id, node, left, heuristic, goal, z_row, z_col);
        if (gridInLinkedList(child_left->grid, opened_nodes))
            free(child_left);
        else
            insertListNode(closed_nodes, child_left, 1);
    }
    if (z_col != 2 && node->operator != left) {
        child_right = newNode(++id, node, right, heuristic, goal, z_row, z_col);
        if (gridInLinkedList(child_right->grid, opened_nodes))
            free(child_right);
        else
            insertListNode(closed_nodes, child_right, 1);
    }
    insertListNode(opened_nodes, node, 0);
}

Node* getBestNode(LinkedList *list) {
    ListNode *index, *previous, *min_previous;
    min_previous = previous = NULL;
    Node *best_node = NULL;
    int node_cost, node_depth, min_cost = 999;
    for (index = list->head; index != NULL; index = index->next) {
        node_cost = index->puzzle_node->cost;
        node_depth = index->puzzle_node->depth;
        if (node_cost == 0) {
            min_previous = previous;
            break;
        }
        else if (node_cost + node_depth < min_cost) {
                min_cost = node_cost + node_depth;
                min_previous = previous;
        }
        previous = index;
    }
    if (min_previous == NULL) {
        index = list->head;
        list->head = index->next;
    }
    else {
        index = min_previous->next;
        min_previous->next = index->next;
    }
    best_node = index->puzzle_node;
    free(index);
    list->size--;
    return best_node;
}

int a_star(int goal[][3], Heuristic heuristic[3], LinkedList *opened_nodes, LinkedList *closed_nodes, Node *solution_node) {
   Node *node = getBestNode(closed_nodes);
    if (node->cost == 0) {
        solution_node->id = node->id;
        solution_node->parent = node->parent;
        solution_node->cost = 0;
        solution_node->depth = node->depth;
        solution_node->operator = node->operator;
        memcpy(solution_node->grid, node->grid, sizeof(node->grid));
        return 1;
    }
    expandNode(node, opened_nodes, closed_nodes, goal, heuristic);
    if (a_star(goal, heuristic, opened_nodes, closed_nodes, solution_node)) {
        return 1;
    }
}

void printSolution(Node *index) {
    int path_length = index->depth;
    int aux = path_length;
    Operator path[path_length];
    do {
        path[--path_length] = index->operator;
        index = index->parent;
    }while (index->parent != NULL);
    for(int i = 0; i < aux; i++) {
        printf("%s, ", getOperatorName(path[i]));
    }
    printf("\b\b");
}

int main() {
    Heuristic heuristic[3] = {Hamming, Manhattan, Linear_conflict};
    int initial[3][3] = {{8, 6, 7},
                         {2, 5, 4},
                         {3, 0, 1}};
    int goal[3][3] = {{1, 2, 3},
                      {4, 5, 6},
                      {7, 8, 0}};

    // Initialization of root node
    Node *root = (Node *) malloc(sizeof(Node));
    root->id = 0;
    root->parent = NULL;
    root->cost = getCost(heuristic, initial, goal);
    root->depth = 0;
    root->operator = null;
    memcpy(root->grid, initial, sizeof(initial));

    // Initialization of Linked Lists and solution node
    LinkedList *opened_nodes = (LinkedList *) malloc(sizeof(LinkedList));
    opened_nodes->head = NULL;
    opened_nodes->size = 0;
    LinkedList *closed_nodes = (LinkedList *) malloc(sizeof(LinkedList));
    closed_nodes->head = NULL;
    closed_nodes->size = 0;
    Node *solution_node = (Node *) malloc(sizeof(Node));

    insertListNode(closed_nodes, root, 0);

    if (isSolvable(initial, goal)) {
        a_star(goal, heuristic, opened_nodes, closed_nodes, solution_node);
        printNode(solution_node);
        printf("Nodes explored: %d\n", opened_nodes->size);
        printf("Path: ");
        printSolution(solution_node);
    }
    else {
        puts("Not solvable");
    }

    return 0;
}

