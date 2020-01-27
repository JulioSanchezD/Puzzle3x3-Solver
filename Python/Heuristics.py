def LinearConflict(grid, goal):
    cost = 0
    in_conflict = []
    for i, row_grid in enumerate(grid):
        row_goal = goal[i]
        ti = getLCPairs(row_grid, row_goal)
        if ti and notIn(ti, in_conflict):
            tj = getLCPairs(row_goal, row_grid)
            if ti != tj:
                in_conflict += tj
                cost += 2
    grid = transpose(grid)
    goal = transpose(goal)
    for i, row_grid in enumerate(grid):
        row_goal = goal[i]
        ti = getLCPairs(row_grid, row_goal)
        if ti and notIn(ti, in_conflict):
            tj = getLCPairs(row_goal, row_grid)
            if ti != tj:
                in_conflict += tj
                cost += 2
    return cost


def getLCPairs(row1, row2):
    tx = []
    for num in row1:
        if num in row2 and num != 0:
            tx.append(num)

    return tx if len(tx) > 1 else False


def notIn(list1, list2):
    for num in list1:
        if num in list2:
            return False
    return True


def transpose(matrix):
    return [[matrix[j][i] for j in range(len(matrix))] for i in range(len(matrix[0]))]


def Hamming(grid, goal):
    cost = 0
    for i in range(0, 3):
        for j in range(0, 3):
            if grid[i][j] != goal[i][j]:
                cost += 1
    return cost


def Manhattan(grid, goal):
    cost = 0
    for r1 in range(0, 3):
        for c1 in range(0, 3):
            r2, c2 = getPosition(grid[r1][c1], goal)
            cost += abs(r2 - r1) + abs(c2 - c1)
    return cost


def getPosition(x, grid):
    for row_num, row in enumerate(grid):
        for col_num, num in enumerate(row):
            if num == x:
                return row_num, col_num


if __name__ == "__main__":
    grid = [[4, 2, 5], [1, 0, 6], [3, 8, 7]]
    goal = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
    grid2 = [[3, 2, 1], [4, 5, 6], [7, 8, 0]]
    goal2 = [[1, 2, 3], [4, 5, 6], [8, 0, 7]]
    grid3 = [[1, 2, 3], [0, 5, 4], [6, 7, 8]]
    goal3 = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]
    print(Hamming(grid3, goal3))
