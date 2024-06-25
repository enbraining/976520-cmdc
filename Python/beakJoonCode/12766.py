import os
import sys
from io import BytesIO, IOBase

from heapq import heappop, heappush

def dijkstra(graph, start_node):
    num_nodes = len(graph)
    distances = [float("inf")] * num_nodes
    parents = [-1] * num_nodes
    distances[start_node] = 0

    priority_queue = [(0, start_node)]
    while priority_queue:
        current_dist, current_node = heappop(priority_queue)
        if current_dist == distances[current_node]:
            for neighbor, edge_length in graph[current_node]:
                new_dist = current_dist + edge_length
                if new_dist < distances[neighbor]:
                    distances[neighbor] = new_dist
                    parents[neighbor] = current_node
                    heappush(priority_queue, (new_dist, neighbor))

    return distances, parents

def main():
    num_nodes, start_node, num_segments, num_roads = map(int, input().split())
    forward_graph = [[] for _ in range(num_nodes)]
    backward_graph = [[] for _ in range(num_nodes)]

    for _ in range(num_roads):
        node_a, node_b, length = map(int, input().split())
        forward_graph[node_a - 1].append((node_b - 1, length))
        backward_graph[node_b - 1].append((node_a - 1, length))

    dist_from_start, _ = dijkstra(forward_graph, start_node)
    dist_to_start, _ = dijkstra(backward_graph, start_node)

    combined_distances = []
    for i in range(start_node):
        combined_distances.append(dist_from_start[i] + dist_to_start[i])
    combined_distances.sort()

    cumulative_sum = [0]
    for distance in combined_distances:
        cumulative_sum.append(cumulative_sum[-1] + distance)

    INF = 10 ** 20
    dp = [[INF] * (num_segments + 1) for _ in range(start_node + 1)]
    dp[0][0] = 0

    for i in range(start_node):
        for j in range(1, num_segments + 1):
            for l in range((i + 1) // j):
                dp[i + 1][j] = min(dp[i + 1][j], (l + 1) * (cumulative_sum[i + 1] - cumulative_sum[i - l]) + dp[i - l][j - 1])

    print(dp[-1][-1] - sum(combined_distances))

BUFSIZE = 8192
class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")

if __name__ == "__main__":
    main()
