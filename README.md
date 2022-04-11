# Graph_Edge_Classification
The program uses the DFS algorithm to classify the type of edge (tree, back, forward or cross edge) in the graph (directed or undirected)
It is assumed that the user will enter a correct simple graph, without loops and multiple edges. Although I have made sure that if a user enters the same vertex again, the create_edge funtion of my program does nothing and therefore repeated entry is not done.
The DFS algorithm has been implemented here.
The DFS algorithm updates the discovery and finishing times for each vertex correctly. The print_times function in my program prints them for all vertices.
For the edge classification, I have stored extra information in the linked list node (character), in the form of T/B/F/C which means tree, back, forward, cross edge respectively. The DFS function will update this information (type of edge) whenever it explores an edge (u,v).
I have created separate DFS functions for directed and undirected graphs since they have somewhat different conditions for edge classification whenever an edge (u,v) is explored.
Finally, the function print_edge_type prints all the edges present in the graph (in order of starting vertex from 0 to N-1) along with the type of these edges.
