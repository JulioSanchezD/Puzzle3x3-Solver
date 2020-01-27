#include <stdlib.h>

#ifndef INC_8_PUZZLE_HEURISTICS_H
#define INC_8_PUZZLE_HEURISTICS_H

void getPosition(int num, int grid[][3], int *row, int *col) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == num) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void transpose(int a[][3], int b[][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            b[i][j] = a[j][i];
}

int in(int num, int arr[], int length) {
    int found = 0;
    for (int j = 0; j<length; j++) {
        if(num == arr[j]) {
            found = 1;
            break;
        }
    }
    return found;
}

int shareElement(int arr1[], int arr2[], int length1, int length2) {
    for (int i = 0; i < length1; i++) {
        if (in(arr1[i], arr2, length2)) return 1;
    }
    return 0;
}

int getLCPairs(int arr1[3], int arr2[3], int pairs[3]) {
    int cont = 0;
    int num;
    for (int i = 0; i < 3; i++) {
        num = arr1[i];
        if (in(num, arr2, 3) && num != 0) pairs[cont++] = num;
    }
    if (cont == 1) return 0;
    else return 1;
}

int isArrayEqual(int arr1[], int arr2[], int length) {
    for (int i = 0; i < length; i++) {
        if (arr1[i] != arr2[i]) return 0;
    }
    return 1;
}

int linearConflict(int grid[][3], int goal[][3]) {
    int lc_res = 0, cost = 0, conflict_index = 0;
    int in_conflict[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    int grid_t[3][3], goal_t[3][3];
    int tj[3], ti[3];
    for (int i = 0; i < 3; i++) {
        tj[0] = ti[0] = tj[1] = ti[1] = tj[2] = ti[2] = 0;
        lc_res = getLCPairs(grid[i], goal[i], ti);
        if (lc_res && !shareElement(ti, in_conflict, 3, 8)) {
            getLCPairs(goal[i], grid[i], tj);
            if (!isArrayEqual(ti, tj, 3)) {
                for (int j = 0; j < 3; j++) if (ti[j] != 0) in_conflict[conflict_index++] = ti[j];
                if (ti[2] != 0 && ti[0] > ti[1] && ti[1] > ti[2]) cost += 2;
                cost += 2;
            }
        }
    }
    transpose(grid, grid_t), transpose(goal, goal_t);
    for (int i = 0; i < 3; i++) {
        tj[0] = ti[0] = tj[1] = ti[1] = tj[2] = ti[2] = 0;
        lc_res = getLCPairs(grid_t[i], goal_t[i], ti);
        if (lc_res && !shareElement(ti, in_conflict, 3, 8)) {
            getLCPairs(goal_t[i], grid_t[i], tj);
            if (!isArrayEqual(ti, tj, 3)) {
                for (int j = 0; j < 3; j++) if (ti[j] != 0) in_conflict[conflict_index++] = ti[j];
                if (ti[2] != 0 && ti[0] > ti[1] && ti[1] > ti[2]) cost += 2;
                cost += 2;
            }
        }
    }
    return cost;
}

int manhattan(int grid[3][3], int goal[3][3]) {
    int r2, c2, cost = 0;
    for (int r1 = 0; r1 < 3; r1++) {
        for (int c1 = 0; c1 < 3; c1++) {
            getPosition(grid[r1][c1], goal, &r2, &c2);
            cost += abs(r2 - r1) + abs(c2 - c1);
        }
    }
    return cost;
}

int hamming(int grid[][3], int goal[][3]) {
    int cost = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] != goal[i][j]) cost+= 1;
        }
    }
    return cost;
}

#endif //INC_8_PUZZLE_HEURISTICS_H
