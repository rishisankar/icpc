# source: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
 
from collections import defaultdict

class Graph:
 
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    def addEdge(self, u, v, w):
        self.graph.append([u, v, w])

    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])
 
    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1
 
    def KruskalMST(self):
        result = []
        i = 0
        e = 0

        self.graph = sorted(self.graph,
                            key=lambda item: item[2])
 
        parent = []
        rank = []

        for node in range(self.V):
            parent.append(node)
            rank.append(0)

        while e < self.V - 1:
            u, v, w = self.graph[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent, v)
            if x != y:
                e = e + 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)
        minimumCost = 0
        for u, v, weight in result:
            minimumCost += weight

        return minimumCost

n = int(input())
g = Graph(n)

st = []
for i in range(n):
  x,y = map(int, input().split(" "))
  for j,t in enumerate(st):
    g.addEdge(i, j, abs(t[0]-x)+abs(t[1]-y))
  st.append((x,y))

print(g.KruskalMST()*2)
