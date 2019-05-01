import copy

def getPosition(x, grid):
    for row_num, row in enumerate(grid):
        for col_num, num in enumerate(row):
            if num == x:
                return (row_num, col_num)

class Puzzle:

    def __init__(self, initial_state, goal, heuristic="hamming"):
        self.initial_state = initial_state
        self.goal = goal
        self.heuristic = heuristic
        self.counter = 1
        self.initial_node = Node(self.counter, 0, self.getCost(self.initial_state), 0, None, self.initial_state)
        self.counter += 1

    def __str__(self):
        string = ""
        for index, row in enumerate(self.initial_state):
            string += str(row) + "  " + str(self.goal[index]) + "\n"
        return string

    def getCost(self, grid):
        cost = 0
        if self.heuristic == "hamming":
            for i in range(0, 3):
                for j in range(0, 3):
                    if grid[i][j] != self.goal[i][j]:
                        cost += 1
        else:
            for r1 in range(0, 3):
                for c1 in range(0, 3):
                    r2, c2 = getPosition(grid[r1][c1], self.goal)
                    cost += abs(r2 - r1) + abs(c2 - c1)
        return cost

    def createChilds(self, grids, node_sup):
        childs = []
        for grid, operator in grids:
            if grid != False:
                child = Node(self.counter, node_sup.id, self.getCost(grid), node_sup.depth+1, operator, grid)
                self.counter += 1
                childs.append(child)
        return childs

    def solve(self, node):
        if node.grid == self.goal:
            return True
        grids = node.expand()
        childs = self.createChilds(grids, node)
        for child in childs:
            child.print()
        


class Node:

    def __init__(self, id, id_sup, cost, depth, operator, grid):
        self.id = id
        self.id_sup = id_sup
        self.cost = cost
        self.depth = depth
        self.operator = operator
        self.grid = grid

    def __str__(self):
        return f"(id={self.id}, id_sup={self.id_sup}, cost={self.cost}, depth={self.depth}, operator={self.operator})"

    def print(self):
        print(self.__str__(), end="")
        for row in self.grid:
            print(row, end="")

    def moveRight(self):
        grid = copy.deepcopy(self.grid)
        row, col = getPosition(0, grid)
        if col == 2:
            return False
        else:
            val = grid[row][col+1]
            grid[row][col] = val
            grid[row][col+1] = 0
            return grid 

    def moveLeft(self):
        grid = copy.deepcopy(self.grid)
        row, col = getPosition(0, grid)
        if col == 0:
            return False
        else:
            val = grid[row][col-1]
            grid[row][col] = val
            grid[row][col-1] = 0
            return grid 

    def moveUp(self):
        grid = copy.deepcopy(self.grid)
        row, col = getPosition(0, grid)
        if row == 0:
            return False
        else:
            val = grid[row-1][col]
            grid[row][col] = val
            grid[row-1][col] = 0
            return grid 
    
    def moveDown(self):
        grid = copy.deepcopy(self.grid)
        row, col = getPosition(0, grid)
        if row == 2:
            return False
        else:
            val = grid[row+1][col]
            grid[row][col] = val
            grid[row+1][col] = 0
            return grid

    def expand(self):
        return [(self.moveLeft(), "left"), (self.moveUp(), "up"), (self.moveRight(), "rigth"), (self.moveDown(), "down")]

if __name__ == "__main__":
    grid = [[2, 8, 3], [1, 0, 4], [7, 6, 5]]
    goal = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]
    puzzle = Puzzle(grid, goal, "hamming")
    puzzle.solve(puzzle.initial_node)