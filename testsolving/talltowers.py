# Ford-Fulkerson (copied from https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/)

from collections import defaultdict
 
# This class represents a directed graph
# using adjacency matrix representation
class Graph:
 
    def __init__(self, graph):
        self.graph = graph  # residual graph
        self.ROW = len(graph)
 
    '''Returns true if there is a path from source 's' to sink 't' in
    residual graph. Also fills parent[] to store the path '''
 
    def BFS(self, s, t, parent):
 
        # Mark all the vertices as not visited
        visited = [False]*(self.ROW)
 
        # Create a queue for BFS
        queue = []
 
        # Mark the source node as visited and enqueue it
        queue.append(s)
        visited[s] = True
 
         # Standard BFS Loop
        while queue:
 
            # Dequeue a vertex from queue and print it
            u = queue.pop(0)
 
            # Get all adjacent vertices of the dequeued vertex u
            # If a adjacent has not been visited, then mark it
            # visited and enqueue it
            for ind, val in enumerate(self.graph[u]):
                if visited[ind] == False and val > 0:
                    # If we find a connection to the sink node,
                    # then there is no point in BFS anymore
                    # We just have to set its parent and can return true
                    visited[ind] = True
                    parent[ind] = u
                    if ind == t:
                      return True
                    queue.append(ind)
        # We didn't reach sink in BFS starting
        # from source, so return false
        return False
             
     
    # Returns tne maximum flow from s to t in the given graph
    def FordFulkerson(self, source, sink):
 
        # This array is filled by BFS and to store path
        parent = [-1]*(self.ROW)
 
        max_flow = 0 # There is no flow initially
 
        # Augment the flow while there is path from source to sink
        while self.BFS(source, sink, parent) :
 
            # Find minimum residual capacity of the edges along the
            # path filled by BFS. Or we can say find the maximum flow
            # through the path found.
            path_flow = float("Inf")
            s = sink
            while(s !=  source):
                path_flow = min (path_flow, self.graph[parent[s]][s])
                s = parent[s]
 
            # Add path flow to overall flow
            max_flow +=  path_flow
 
            # update residual capacities of the edges and reverse edges
            # along the path
            v = sink
            while(v !=  source):
                u = parent[v]
                self.graph[u][v] -= path_flow
                self.graph[v][u] += path_flow
                v = parent[v]
 
        return max_flow

############################

n,x,y = map(int, input().split(" "))
m = 2*n+2
adj = []
for i in range(m):
    adj.append([0]*m)

blocks = []
for i in range(n):
    l,w = map(int, input().split(" "))
    blocks.append((l,w))

# 0 = source, 2n+1 = sink
for i in range(n):
    adj[0][i+1] = 1
    adj[n+i+1][m-1] = 1

mill = 1000000
for k in range(n):
    for j in range(n):
        if k == j: continue
        b1 = blocks[k]
        b2 = blocks[j]
        if x*b1[0] <= mill*b2[0] and mill*b2[0] <= y*b1[0]:
            if x*b1[1] <= mill*b2[1] and mill*b2[1] <= y*b1[1]:
                adj[k+1][n+j+1] = 1

g = Graph(adj)
print(n-g.FordFulkerson(0,m-1))
