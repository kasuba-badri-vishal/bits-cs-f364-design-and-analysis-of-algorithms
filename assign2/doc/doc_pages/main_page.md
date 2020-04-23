@mainpage Ford-Fulkerson Algorithm and Bipartite Matching

## Ford-Fulkerson Algorithm

- The Ford-Fulkerson algorithm tackles the max-flow min-cut problem. If a network with vertices and edges between those vertices that have certain weights is given, it gives an answer to how much "flow" the network is capable of processing at a time. 
- It was put forth in 1956 by Ford and Fulkerson.
- The Ford-Fulkerson algorithm assumes that the input will be a graph, along with a source vertex, and a sink vertex.

- This algorithm has been used to find maxflow-mincut of a given flow graph. The following is the pseudo code of the algorithm.

~~~~~~~~~~~~~~~~~~~~~~
Ford-Fulkerson()
    Initially f(e) = 0 for all e in G.
    While there is an s-t path in the residual graph Gf 
        Let P be a simple s-t path in Gf
        f’ = augment(f,P)
        Update f to be f’
        Update the residual graph Gf  to be Gf’ 
    Endwhile
    Return f.
~~~~~~~~~~~~~~~~~~~~~~

~~~~~~~~~~~~~~~~~~~~~~
Augment(f,P)
    Let b = bottleneck(P,f)
    For each edge (u,v) ∈ P
        If e=(u,v) is a forward edge then increase f(e) in G by b.
        Else((u,v) is a backward edge,  and let e=(v,u))
            decrease f(e) in G by b.
        Endif
    Endfor
    Return(f)
~~~~~~~~~~~~~~~~~~~~~~


### Time complexity

The Ford-Fulkerson algorithm, computing max-flow in the network runs in O(mC) time. <br>
where m = No. of edges, C = max. flow (sum of weights of edges leaving the source)
<br>
## Maximum Bipartite Match

This can be converted into a network flow problem to find the maximal match. Turn the given graph into a directed one and add source and sink vertices. The next step would be to add edges directed from the source to all nodes in the 1st set, and from all nodes in the 2nd set to the sink. All these edges have a weight of 1 unit. 
Now, running the Ford-Fulkerson algorithm on this graph gives us the maximal match (corresponding to the maximum flow).

### Time complexity:
Ford-Fulkerson runs in O(mC) time. Let the number of vertices in the given bipartite graph be 'n'. Then, 'C' in O(mC) is 'n' in this case (as there are n edges of weight 1 each coming out from the source.) <br>
The total no. of edges = No. of edges in the given bipartite graph (say 'm')+ 2n (edges from source and to sink)= m+2n <br>
O((m+2n)n) = O(mn) <br>
Hence, this takes O(mn) time <br>
where m = Given no. of edges, n = No. of vertices
