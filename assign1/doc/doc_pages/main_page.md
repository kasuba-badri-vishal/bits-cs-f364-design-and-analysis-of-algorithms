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