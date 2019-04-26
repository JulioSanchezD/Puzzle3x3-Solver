class Puzzle:

    def __init__(self, initial_state, goal, heuristic="hamming"):
        self.initial_state = initial_state
        self.goal = goal
        self.heuristic = heuristic

    def __str__(self):
        string = ""
        for index, row in enumerate(self.initial_state):
            string += str(row) + "  " + str(self.goal[index]) + "\n"
        return string

    @staticmethod
    def print(grid):
        for row in grid:
            print(row, end="")

    @staticmethod
    def getPosition(x, grid):
        for row_num, row in enumerate(grid):
            for col_num, num in enumerate(row):
                if num == x:
                    return (row_num, col_num)

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
                    r2, c2 = self.getPosition(grid[r1][c1], self.goal)
                    cost += abs(r2 - r1) + abs(c2 - c1)
        return cost

    def moveRight(self, grid):
        row, col = self.getPosition(0, grid)
        if col == 2:
            return False
        else:
            val = grid[row][col+1]
            grid[row][col] = val
            grid[row][col+1] = 0
            return grid 

    def moveLeft(self, grid):
        row, col = self.getPosition(0, grid)
        if col == 0:
            return False
        else:
            val = grid[row][col-1]
            grid[row][col] = val
            grid[row][col-1] = 0
            return grid 

    def moveUp(self, grid):
        row, col = self.getPosition(0, grid)
        if row == 0:
            return False
        else:
            val = grid[row-1][col]
            grid[row][col] = val
            grid[row-1][col] = 0
            return grid 
    
    def moveDown(self, grid):
        row, col = self.getPosition(0, grid)
        if row == 2:
            return False
        else:
            val = grid[row+1][col]
            grid[row][col] = val
            grid[row+1][col] = 0
            return grid 

if __name__ == "__main__":
    grid = [[2, 8, 3], [1, 0, 4], [7, 6, 5]]
    goal = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]
    puzzle = Puzzle(grid, goal, "manhattan")
    print(str(puzzle))
    node = puzzle.moveLeft(puzzle.initial_state)
    puzzle.print(node)