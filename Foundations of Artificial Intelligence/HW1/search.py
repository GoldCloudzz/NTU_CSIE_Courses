# search.py
# ---------------
# Licensing Information:  You are free to use or extend this projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to the University of Illinois at Urbana-Champaign
#
# Created by Michael Abir (abir2@illinois.edu) on 08/28/2018
# Modified by Shang-Tse Chen (stchen@csie.ntu.edu.tw) on 03/03/2022

"""
This is the main entry point for HW1. You should only modify code
within this file -- the unrevised staff files will be used for all other
files and classes when code is run, so be careful to not modify anything else.
"""
# Search should return the path.
# The path should be a list of tuples in the form (row, col) that correspond
# to the positions of the path taken by your search algorithm.
# maze is a Maze object based on the maze from the file specified by input filename
# searchMethod is the search method specified by --method flag (bfs,dfs,astar,astar_multi,fast)

# discuss with b08502041
# reference: https://github.com/Mingjunzha/cs440/tree/main/mp1-code

import sys
import copy

import heapq
from queue import PriorityQueue

class Node:
    def __init__(self, position, g, f):
        self.position = position
        self.parent = None
        self.objectives = []
        self.g = g
        self.f = f

    # less than
    def __lt__(self, other):
        return self.f < other.f
        

def manhattan_dist(start, end):
    return (abs(start[0] - end[0]) + abs(start[1] - end[1]))

def manhattan_heuristic(start, objectives):
    min_dist = sys.maxsize
    for objective in objectives:
        min_dist = min(min_dist, manhattan_dist(start, objective))
    return min_dist

def get_path(start, end, parent):
    path = [end]
    cur = end
    while cur != start:
        path.append(parent[cur])
        cur = parent[cur]
    path.reverse()
    return path

def mst_cost(objectives, length):
    start = objectives[0]
    cost = 0

    visited = set()
    visited.add(start)
    mst = set()

    while len(visited) < len(objectives):
        queue = []
        for u in visited:
            for v in objectives:
                if v not in visited:
                    edge = (u, v)
                    heapq.heappush(queue, ((length[edge] - 1), edge))

        edge = heapq.heappop(queue)
        mst.add(edge[1])
        cost += edge[0]
        visited.add(edge[1][1])

    return cost

def search(maze, searchMethod):
    return {
        "bfs": bfs,
        "astar": astar,
        "astar_corner": astar_corner,
        "astar_multi": astar_multi,
        "fast": fast,
    }.get(searchMethod)(maze)

def bfs(maze):
    """
    Runs BFS for part 1 of the assignment.

    @param maze: The maze to execute the search on.

    @return path: a list of tuples containing the coordinates of each state in the computed path
    """
    # TODO: Write your code here

    start = maze.getStart()
    objective = maze.getObjectives()[0]

    # keep track of parent node of each node
    parent = {}
    parent[start] = None

    queue = []
    queue.append(start)

    while queue:
        cur = queue.pop(0)
        if cur == objective:
            break

        neighbors = maze.getNeighbors(cur[0], cur[1])
        for neighbor in neighbors:
            if neighbor not in parent:
                parent[neighbor] = cur
                queue.append(neighbor)
    
    return get_path(start, objective, parent)

def astar(maze):
    """
    Runs A star for part 1 of the assignment.

    @param maze: The maze to execute the search on.

    @return path: a list of tuples containing the coordinates of each state in the computed path
    """
    # TODO: Write your code here

    # g: path cost, h: manhattan distance
    
    start = maze.getStart()
    objective = maze.getObjectives()[0]

    # parent node of each node
    parent = {}

    # cost of each node
    cost = {}
    cost[start] = 0

    queue = []
    heapq.heappush(queue, (0, start))

    while queue:
        cur = heapq.heappop(queue)[1]
        if (cur == objective):
            break
            
        neighbors = maze.getNeighbors(cur[0], cur[1])
        for neighbor in neighbors:
            if neighbor not in cost or cost[cur] + 1 < cost[neighbor]:
                cost[neighbor] = cost[cur] + 1
                parent[neighbor] = cur
                f = cost[neighbor] + manhattan_dist(neighbor, objective)
                heapq.heappush(queue, (f, neighbor))
                
    return get_path(start, objective, parent)

def astar_corner(maze):
    """
    Runs A star for part 2 of the assignment in the case where there are four corner objectives.

    @param maze: The maze to execute the search on.

    @return path: a list of tuples containing the coordinates of each state in the computed path
        """
    # TODO: Write your code here

    return astar_multi(maze)

def astar_multi(maze):
    """
    Runs A star for part 3 of the assignment in the case where there are
    multiple objectives.

    @param maze: The maze to execute the search on.

    @return path: a list of tuples containing the coordinates of each state in the computed path
    """
    # TODO: Write your code here

    start = maze.getStart()
    objectives = maze.getObjectives()
    objectives.insert(0, start)

    # path between each two objectives
    edge = {}

    # length between each two objectives
    length = {}

    for u in objectives:
        for v in objectives:
            if u != v:
                cost = {}

                queue = []
                heapq.heappush(queue, (manhattan_dist(u, v), [u]))

                while queue:
                    path = heapq.heappop(queue)[1]
                    cur = path[-1]

                    if cur == v:
                        break

                    if cur not in cost:
                        cost[cur] = manhattan_dist(cur, v) + len(path) / 1.5 - 1
                        neighbors = maze.getNeighbors(cur[0], cur[1])
                        for neighbor in neighbors:
                            new_cost = manhattan_dist(neighbor, v) + len(path) / 1.5 - 1
                            if neighbor not in cost:
                                heapq.heappush(queue, (new_cost, path + [neighbor]))
                            elif cost[neighbor] > new_cost:
                                cost[neighbor] = new_cost
                                heapq.heappush(queue, (new_cost, path + [neighbor]))

                edge[(u, v)] = path
                length[(u, v)] = len(path)

    start_node = Node(start, 0, mst_cost(objectives, length))
    start_node.objectives = maze.getObjectives()

    queue = []
    heapq.heappush(queue, start_node)

    while len(objectives):
        cur = heapq.heappop(queue)
        if not cur.objectives:
            break
        for neighbor in cur.objectives:
            new_cost = cur.g + length[(cur.position, neighbor)]
            neighbor_node = Node(neighbor, new_cost, 0)
            neighbor_node.parent = cur
            neighbor_node.objectives = copy.copy(cur.objectives)
            neighbor_node.objectives.remove(neighbor)
            neighbor_node.f = new_cost + mst_cost(cur.objectives, length)
            if len(objectives):
                neighbor_node.f += len(neighbor_node.objectives)
            heapq.heappush(queue, neighbor_node)

    nodes = []

    while cur:
        nodes.append(cur.position)
        cur = cur.parent

    path = []
    for i in range(len(nodes) - 1):
        path += edge[(nodes[i], nodes[i + 1])][:-1]
    path.append(start)
    path.reverse()
    return path

def fast(maze):
    """
    Runs suboptimal search algorithm for part 4.

    @param maze: The maze to execute the search on.

    @return path: a list of tuples containing the coordinates of each state in the computed path
    """
    # TODO: Write your code here
    
    start = maze.getStart()
    objectives = maze.getObjectives()

    path = []

    while objectives:
        node = Node(start, manhattan_heuristic(start, objectives), 0)

        # parent node of each node
        parent = {}

        visited = set()

        queue = []
        heapq.heappush(queue, node)

        while queue:
            cur = heapq.heappop(queue)
            cur_pos = cur.position
            visited.add(cur_pos)

            if cur_pos in objectives:
                target = cur_pos
                break

            neighbors = maze.getNeighbors(cur_pos[0], cur_pos[1])
            for neighbor in neighbors:
                if neighbor not in visited:
                    parent[neighbor] = cur_pos
                    heapq.heappush(queue, Node(neighbor, len(get_path(start, cur_pos, parent)), 0))

        edge = get_path(start, target, parent)
        new_start = edge[-1]
        if len(objectives) > 1:
            edge.remove(new_start)
            
        path.extend(edge)
        objectives.remove(new_start)
        start = new_start

    return path
        