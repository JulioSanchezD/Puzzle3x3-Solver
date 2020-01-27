#include "heuristics.h"
#include <stdio.h>
#ifndef INC_8_PUZZLE_NODE_H
#define INC_8_PUZZLE_NODE_H

typedef enum {
    left, up, right, down, null
} Operator;
typedef enum {
    Hamming, Manhattan, Linear_conflict, Null
} Heuristic;

typedef struct node {
    int id;
    struct node *parent;
    int cost;
    int depth;
    Operator operator;
    int grid[3][3];
}Node;

int getCost(const Heuristic heuristic[3], int grid[][3], int goal[][3]) {
    int cost = 0;
    for (int i = 0; i < 3; i++) {
        switch (heuristic[i]) {
            case Hamming:
                cost += hamming(grid, goal);
                break;
            case Manhattan:
                cost += manhattan(grid, goal);
                break;
            case Linear_conflict:
                cost += linearConflict(grid, goal);
                break;
            case Null:
                break;
        }
    }
    return cost;
}

int isSolvable(int grid[][3], int goal[][3]) {
    int initial_nums[8], final_nums[8];
    int cont = 0, cont2 = 0, aux;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            aux = grid[i][j];
            if (aux != 0) initial_nums[cont++] = aux;
            aux = goal[i][j];
            if (aux != 0) final_nums[cont2++] = aux;
        }
    }
    int initial_inversions = 0, final_inversions = 0;
    int initial_num, initial_num2, final_num, final_num2;
    int initial_cont, final_cont;
    for (int i = 0; i < 8; i++) {
        initial_cont = final_cont = 0;
        initial_num = initial_nums[i];
        final_num = final_nums[i];
        if (initial_num != 1) {
            for (int j = i + 1; j < 8; j++) {
                initial_num2 = initial_nums[j];
                if (initial_num2 < initial_num) initial_cont++;
            }
            initial_inversions += initial_cont;
        }
        if (final_num != 1) {
            for (int j = i + 1; j < 8; j++) {
                final_num2 = final_nums[j];
                if (final_num2 < final_num) final_cont++;
            }
            final_inversions += final_cont;
        }
    }
    return (initial_inversions + final_inversions) % 2 == 0;
}

void printGrid(int grid[][3], int plain) {
    for (int row = 0; row < 3; row++) {
        if (!plain && row % 1 == 0 && row > 0) puts("---------");
        for (int col = 0; col < 3; col++) {
            if (!plain && col % 1 == 0 && col > 0) printf("| ");
            printf("%d ", grid[row][col]);
        }
        if (!plain) puts("");
    }
    if (!plain) puts("");
}

char *getOperatorName(Operator operator) {
    switch (operator) {
        case left:
            return "left";
        case up:
            return "up";
        case right:
            return "right";
        case down:
            return "down";
        default:
            return "null";
    }
}

void printNode(Node *node) {
    if (node == NULL) {
        puts("NULL Node");
        return;
    }
    printf("id: %d\n", node->id);
    if(node->parent != NULL) printf("parent_id: %d\n", node->parent->id);
    else printf("parent_id: %d\n", -1);
    printf("cost: %d\n", node->cost);
    printf("depth: %d\n", node->depth);
    printf("operator: %s\n", getOperatorName(node->operator));
    puts("Grid:");
    printGrid(node->grid, 0);
}

void moveLeft(int grid[][3], int row, int col) {
    int aux = grid[row][col-1];
    grid[row][col-1] = 0;
    grid[row][col] = aux;
}

void moveUp(int grid[][3], int row, int col) {
    int aux = grid[row-1][col];
    grid[row-1][col] = 0;
    grid[row][col] = aux;
}

void moveRight(int grid[][3], int row, int col) {
    int aux = grid[row][col+1];
    grid[row][col+1] = 0;
    grid[row][col] = aux;
}

void moveDown(int grid[][3], int row, int col) {
    int aux = grid[row+1][col];
    grid[row+1][col] = 0;
    grid[row][col] = aux;
}

void moveZero(int grid[][3], Operator operator, int z_row, int z_col) {
    switch (operator) {
        case left:
            moveLeft(grid, z_row, z_col);
            break;
        case up:
            moveUp(grid, z_row, z_col);
            break;
        case right:
            moveRight(grid, z_row, z_col);
            break;
        case down:
            moveDown(grid, z_row, z_col);
            break;
        default:
            break;
    }
}

int isGridEqual(int grid1[][3], int grid2[][3]) {
    for (int i = 0; i < 3; i++) {
        if (!isArrayEqual(grid1[i], grid2[i], 3)) return 0;
    }
    return 1;
}

Node* newNode(int id, Node *parent, Operator operator, Heuristic heuristic[3], int goal[][3], int z_row, int z_col) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->id = id;
    node->parent = parent;
    node->operator = operator;
    node->depth = parent->depth + 1;
    memcpy(node->grid, parent->grid, sizeof(parent->grid));
    moveZero(node->grid, operator, z_row, z_col);
    node->cost = getCost(heuristic, node->grid, goal);
    return node;
}
#endif //INC_8_PUZZLE_NODE_H
