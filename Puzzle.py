class Puzzle:

    def __init__(self, puzzle, goal, heuristic="hamming"):
        self.puzzle = puzzle
        self.goal = goal
        self.heuristic = heuristic

    def __str__(self):
        string = ""
        for index, row in enumerate(self.puzzle):
            string += str(row) + "  " + str(self.goal[index]) + "\n"
        return string

    @staticmethod
    def getPosition(x, grid):
        for row_num, row in enumerate(grid):
            for col_num, num in enumerate(row):
                if num == x:
                    return (row_num, col_num)

    def getCost(self):
        cost = 0
        if self.heuristic == "hamming":
            for i in range(0, 3):
                for j in range(0, 3):
                    if self.puzzle[i][j] != self.goal[i][j]:
                        cost += 1
        else:
            for r1 in range(0, 3):
                for c1 in range(0, 3):
                    r2, c2 = self.getPosition(self.puzzle[r1][c1], self.goal)
                    cost += abs(r2 - r1) + abs(c2 - c1)
        return cost


if __name__ == "__main__":
    grid = [[2, 8, 3], [1, 0, 4], [7, 6, 5]]
    goal = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]
    puzzle = Puzzle(grid, goal, "manhattan")
    print(puzzle.getCost())