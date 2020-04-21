@mainpage Kosaraju Algorithm and Divide and Conquer Algorithm

Two different algorithms have been implemented to find the Strongly Connected Components

1) Kosaraju's Algorithm.
    - This algorithm uses topological sort and dfs to find Strongly Connected Components of a given graph.

~~~~~~~~~~~~~~~~~~~~~~
    For each vertex u of the graph, mark u as unvisited. Let L be empty.
    For each vertex u of the graph do Visit(u), where Visit(u) is the recursive subroutine:
        If u is unvisited then:
            Mark u as visited.
            For each out-neighbour v of u, do Visit(v).
            Prepend u to L.
        Otherwise do nothing.
    For each element u of L in order, do Assign(u,u) where Assign(u,root) is the recursive subroutine:
        If u has not been assigned to a component then:
            Assign u as belonging to the component whose root is root.
            For each in-neighbour v of u, do Assign(v,root).
        Otherwise do nothing.
~~~~~~~~~~~~~~~~~~~~~~


2) Divide and Conquer Algorithm.
    - This algorithm follows a divide and conquer approach to divide the set of vertices into multiple disjoint sets and work on each set individually. The algorithm requires a function to find predecessors and descendents of a vertex.
        
~~~~~~~~~~~~~~~~~~~~~~
        DCSC(G)
            If G has no edges then
                forall v in V Output {v}.
            Else
                Select a random vertex v from V
                SCC <- Pred(G, v) \ Desc(G, v)
                Output SCC
                DCSC(Pred(G, v) \ SCC)
                DCSC(Desc(G, v) \ SCC)
                DCSC(Rem(G, v))
~~~~~~~~~~~~~~~~~~~~~~

A Comparison and Analysis of the Algorithms

1) We can find all strongly connected components in O(m+n) time, where 'n' is the number of vertices & 'm' is the number of edges, using Kosaraju’s algorithm. 
This calculation is asymptotically best calculation, however there are different algorithms like Tarjan's and path based algorithms having same time complexity yet look for strongly connected components utilizing single DFS.

2) This algorithm runs in O(m log n) time. The worst case (when the descendant set is very large) leads to Θ(mn) runtime. The best case (when the remainder set is very large) leads to Θ(m) runtime. By choosing the pivot vertex arbitrarily, the expected complexity of the algorithm is bounded as Θ(m lg n + n). The modified version has a worst–case complexity of O(m log n). Here, 'n' is the number of vertices and 'm' is the number of edges.

If we try to compare the time complexities of the 2 algorithms, either could be the better one depending on the situation. Assuming that they're equal, we have O(n) vs O(n log n), so the algorithm with O(n + m) complexity is faster. If, on the other hand, m is effectively constant while n grows quickly, then we have O(n) vs O(log n), so the second one is better. 
So, the second is better for large n, and the first is better for cases where both m and n are large. (If m dominates the equation then they're both linear.)


Applications: Algorithms to find strongly connected components are often used as a starting step in many graph algorithms that work only on strongly connected graphs. Another application is that in social networks, a group of people is generally considered a strongly connected component. People belonging to such groups often like similar kinds of pages or play common games. This calculation can be utilized to discover such groups and suggest these commonly preferred pages or games to the individuals in the group who haven't liked these pages or engaged in these games yet.

