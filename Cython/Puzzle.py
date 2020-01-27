import app.algorithms.Heuristics as heuristics
import copy


class Node:

    def __init__(self, node_id, id_sup, cost, depth, operator, grid):
        self.id = node_id
        self.id_sup = id_sup
        self.cost = cost
        self.depth = depth
        self.operator = operator
        self.grid = grid

    def move_right(self):
        grid = copy.deepcopy(self.grid)
        row, col = heuristics.get_position(0, grid)
        if col == 2:
            return []
        else:
            val = grid[row][col+1]
            grid[row][col] = val
            grid[row][col+1] = 0
            return grid

    def move_left(self):
        grid = copy.deepcopy(self.grid)
        row, col = heuristics.get_position(0, grid)
        if col == 0:
            return []
        else:
            val = grid[row][col-1]
            grid[row][col] = val
            grid[row][col-1] = 0
            return grid

    def move_up(self):
        grid = copy.deepcopy(self.grid)
        row, col = heuristics.get_position(0, grid)
        if row == 0:
            return []
        else:
            val = grid[row-1][col]
            grid[row][col] = val
            grid[row-1][col] = 0
            return grid

    def move_down(self):
        grid = copy.deepcopy(self.grid)
        row, col = heuristics.get_position(0, grid)
        if row == 2:
            return []
        else:
            val = grid[row+1][col]
            grid[row][col] = val
            grid[row+1][col] = 0
            return grid

    def expand(self):
        return [(self.move_left(), "left"), (self.move_up(), "up"), (self.move_right(), "right"), (self.move_down(), "down")]


class Puzzle:

    def __init__(self, initial_state, goal, hamming, manhattan, linear):
        self.initial_state = initial_state
        self.goal = goal
        self.hamming = hamming
        self.manhattan = manhattan
        self.linear = linear
        self.counter = 1
        self.initial_node = Node(self.counter, 0, self.get_cost(self.initial_state), 0, "", self.initial_state)
        self.counter += 1
        self.closed_nodes = [self.initial_node]
        self.opened_nodes = []
        self.observed_grids = []
        self.prohibited_operators = {'left':'right', 'right':'left', 'up':'down', 'down':'up'}
        self.nodes_explored = 0

    def is_solvable(self):
        initial_nums = []
        for row in self.initial_state:
            for number in row:
                if number != 0:
                    initial_nums.append(number)
        initial_inversions = 0
        for index, num in enumerate(initial_nums):
            cont = 0
            if num != 1:
                for num2 in initial_nums[index+1:]:
                    if num2 < num:
                        cont += 1
                initial_inversions += cont

        final_nums = []
        for row in self.goal:
            for number in row:
                if number != 0:
                    final_nums.append(number)
        final_inversions = 0
        for index, num in enumerate(final_nums):
            cont = 0
            if num != 1:
                for num2 in final_nums[index+1:]:
                    if num2 < num:
                        cont += 1
                final_inversions += cont
        return (initial_inversions + final_inversions) % 2 == 0

    def get_cost(self, grid):
        cost = 0
        if self.hamming:
            cost += heuristics.hamming(grid, self.goal)
        if self.manhattan:
            cost += heuristics.manhattan(grid, self.goal)
        if self.linear:
            cost += heuristics.linear_conflict(grid, self.goal)
        return cost

    def create_childs(self, grids, node_sup):
        childs = []
        if node_sup.operator == "":
            prohibited_operator = ""
        else:
            prohibited_operator = self.prohibited_operators[node_sup.operator]
        for grid, operator in grids:
            if grid != [] and (grid not in self.observed_grids) and prohibited_operator != operator:
                child = Node(self.counter, node_sup.id, self.get_cost(grid), node_sup.depth+1, operator, grid)
                self.counter += 1
                childs.append(child)
        return childs

    def add_childs(self, childs):
        for child in childs:
            self.closed_nodes.append(child)
        self.closed_nodes.sort(key=lambda obj: obj.cost + obj.depth)

    @property
    def solution(self):
        sol = []
        node = self.goal_node
        while node.id != 1:
            sol.append(node.operator)
            for observed in self.opened_nodes:
                if observed.id == node.id_sup:
                    node = observed
                    break
        return sol[::-1]

    def solve(self):
        node = self.closed_nodes.pop(0)
        if node.cost == 0:
            self.goal_node = node
            return True
        grids = node.expand()
        self.nodes_explored += 1
        self.opened_nodes.append(node)
        self.observed_grids.append(node.grid)
        childs = self.create_childs(grids, node)
        self.add_childs(childs)
        if self.solve():
            return True
