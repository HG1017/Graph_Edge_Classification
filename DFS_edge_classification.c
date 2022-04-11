#include<stdio.h>
#include<stdlib.h>
#define endl printf("\n")

int time;

char* color; // global pointer to array which will store colors of all vertices
int* d; // global pointer to array which stores discovery time
int* pi; // global pointer to array which stores previous vertex for all vertices
int* f; // global pointer to array which stores finishing time for all vertices

struct node // structure for each node of the linked list
{
    int conn;
    struct node* next;
    char edge;
};

struct list
{
    struct node* one; // points to the starting of the list
};

struct graph // structure for the graph
{
    int vert; // no. of vertices
    struct list* arr;
};

struct node* addlist (int x) // creates a new node with entry x
{
    struct node* first;
    first = (struct node*)malloc(sizeof(struct node));

    first->conn = x;
    first->next = NULL;

    return first;
}

struct graph* generate_graph (int x) // generates a graph of appropriate size with entries initialized to null
{
    struct graph* g;
    g = (struct graph*)malloc(sizeof(struct graph));

    g->vert = x;

    g->arr = (struct list*)malloc(sizeof(struct list) * x);

    for (int i = 0; i < x; i++)
    {
        g->arr[i].one = NULL;
    }

    return g;
}

int search_edge(struct graph* g, int pt1, int pt2)
{
    struct node* dup = g->arr[pt1].one;
    if (dup == NULL)
    {
        ;
    }
    else
    {
        while(dup!=NULL)
        {
            if (dup->conn == pt2)
            {
                return 1;
            }
            dup = dup->next;
        }
    }
    return 0;
}

void create_undirected_edge (struct graph* g, int pt1, int pt2) // function for adding an edge to an undirected graph
{
    int p;
    p = search_edge(g, pt1, pt2);

    if (p == 1)
    {
        return;
    }
    struct node* temp = addlist(pt2);

    temp->next = g->arr[pt1].one;
    g->arr[pt1].one = temp;

    temp = addlist(pt1);

    temp->next = g->arr[pt2].one;
    g->arr[pt2].one = temp;
}

void create_directed_edge (struct graph* g, int pt1, int pt2) // function for adding an edge to a directed graph
{
    int p;
    p = search_edge(g, pt1, pt2);

    if (p == 1)
    {
        return;
    }
    struct node* temp = addlist(pt2);

    temp->next = g->arr[pt1].one;
    g->arr[pt1].one = temp;
}

void display_graph (struct graph* g) // function for displaying the graph
{
    for (int i = 0; i < g->vert; i++)
    {
        printf("Vertex %d: ", i);

        struct node* dup = g->arr[i].one;

        if(dup == NULL)
        {
            printf("No Edge present");
        }
        else
        {
            while(dup->next!= NULL)
            {
                printf("%d -> ", dup->conn);
                dup = dup->next;
            }
            printf("%d", dup->conn);
        }
        endl;
    }
}

void DFS_VISIT (struct graph* g, int u) // DFS visit function as per CLRS pseudocode
{
    time = time + 1;
    *(d + u) = time;
    *(color + u) = 'g';

    int v;

    struct node* dup = g->arr[u].one;

    if(dup == NULL)
    {
        ;
    }
    else
    {
        while(dup!= NULL)
        {
            v = dup->conn;

                if(*(color + v) == 'w') // w stands for white color
                {
                    dup->edge = 'T'; // T stands for tree edge
                }
                else if (*(color + v) == 'g') // g stands for gray vertex
                {
                    dup->edge = 'B'; // B stands for back edge
                }
                else
                {
                    if(*(d + u) > *(d + v))
                    {
                        dup->edge = 'C'; // C stands for cross edge
                    }
                    else if (*(d + u) < *(d + v))
                    {
                        dup->edge = 'F'; // F stands for forward edge
                    }
                }

            if (*(color + v) == 'w')
            {
                *(pi + v) = u;
                DFS_VISIT (g, v);
            }
            dup = dup->next;
        }
    }
    *(color + u) = 'b'; // b stands for black color
    time = time + 1;
    *(f + u) = time;
}

void DFS (struct graph* g) // DFS function as per the CLRS pseudocode
{
    int n = g->vert;

    color = malloc(sizeof(char)*n);
    d = malloc(sizeof(int)*n);
    pi = malloc(sizeof(int)*n);
    f = malloc(sizeof(int)*n);

    for (int i = 0; i < n; i++)
    {
        *(color + i) = 'w'; // w stands for white color
        *(pi + i) = -10000; // indicates Nil
    }

    time = 0;

    for (int i = 0; i < n; i++)
    {
        if(*(color + i) == 'w')
        {
            DFS_VISIT(g,i);
        }
    }
}

void DFS_VISIT_undirected (struct graph* g, int u) // DFS VISIT function for undirected graph (classifies the edges as tree or back)
{
    time = time + 1;
    *(d + u) = time;
    *(color + u) = 'g';

    int v;

    struct node* dup = g->arr[u].one;

    if(dup == NULL)
    {
        ;
    }
    else
    {
        while(dup!= NULL)
        {
            v = dup->conn;

                if(*(color + v) == 'w')
                {
                    dup->edge = 'T';
                }
                else if (*(color + v) == 'g' && *(pi + u) != v)
                {
                    dup->edge = 'B';
                }

            if (*(color + v) == 'w')
            {
                *(pi + v) = u;
                DFS_VISIT_undirected (g, v);
            }
            dup = dup->next;
        }
    }
    *(color + u) = 'b'; // b stands for black color
    time = time + 1;
    *(f + u) = time;
}

void DFS_undirected (struct graph* g) // DFS function for undirected graph
{
    int n = g->vert;

    color = malloc(sizeof(char)*n);
    d = malloc(sizeof(int)*n);
    pi = malloc(sizeof(int)*n);
    f = malloc(sizeof(int)*n);

    for (int i = 0; i < n; i++)
    {
        *(color + i) = 'w'; // w stands for white color
        *(pi + i) = -10000; // indicates Nil
    }

    time = 0;

    for (int i = 0; i < n; i++)
    {
        if(*(color + i) == 'w')
        {
            DFS_VISIT_undirected(g,i);
        }
    }
}

void print_times (struct graph* g) // function for printing the discovery and finishing times
{
    int n = g->vert;
    for (int i = 0; i < n; i++)
    {
        printf("Vertex %d: discovery time %d, finishing time %d", i, *(d + i), *(f + i));
        endl;
    }
}

void print_edge_type (struct graph* g) // function for printing the edges with their types
{
    printf("The classification of edges are as follows:");
    endl;
    int u, v;
    for (int i = 0; i < g->vert; i++)
    {
        struct node* dup = g->arr[i].one;

        if(dup == NULL)
        {
            ;
        }
        else
        {
            while(dup!= NULL)
            {
                u = i;
                v = dup->conn;

                if (dup->edge == 'T')
                {
                    printf("Edge (%d,%d): ", u, v);
                    printf("Tree");
                    endl;
                }
                else if (dup->edge == 'B')
                {
                    printf("Edge (%d,%d): ", u, v);
                    printf("Back");
                    endl;
                }
                else if (dup->edge == 'C')
                {
                    printf("Edge (%d,%d): ", u, v);
                    printf("Cross");
                    endl;
                }
                else if (dup->edge == 'F')
                {
                    printf("Edge (%d,%d): ", u, v);
                    printf("Forward");
                    endl;
                }

                dup = dup->next;
            }
        }
    }
}

int main()
{
    int N;
    printf("Enter the number of vertices: ");
    scanf("%d", &N);

    printf("Your vertices are numbered from ");
    for (int i = 0; i<N-1; i++)
    {
        printf("%d, ",i);
    }
    printf("%d",N-1);
    endl;

    struct graph* G = generate_graph(N);

    int p,q,r;
    char c;
    again:
    printf("Enter D for directed or U for undirected graphs: ");
    scanf("%s", &c);
    if(c!='U' && c!='D')
    {
        printf("Invalid choice, try again...");
        endl;
        goto again;
    }
    else if(c == 'U')
    {
        printf("Enter edges (in format: a b), one by one of your Undirected graph. Once done, enter -1 -1 to quit:");
        endl;
        while(1)
        {
            scanf("%d %d", &p, &q);
            if(p == -1 || q == -1)
            {
                break;
            }
            else
            {
                create_undirected_edge (G,p,q);
            }
        }
        printf("Your undirected graph is as follows:");
        endl;
        display_graph(G);
        endl;
        printf("The program runs the DFS algorithm on the graph entered.");
        endl;
        printf("The discovery time and the finishing time for the vertices of the undirected graph are as follows:");
        endl;
        DFS_undirected(G);
        print_times(G);
        print_edge_type(G);
    }
    else
    {
        printf("Enter edges (in format: a b), one by one of your Directed graph. Once done, enter -1 -1 to quit:");
        endl;
        while(1)
        {
            scanf("%d %d", &p, &q);
            if(p == -1 || q == -1)
            {
                break;
            }
            else
            {
                create_directed_edge (G,p,q);
            }
        }
        printf("Your directed graph is as follows:");
        endl;
        display_graph(G);
        endl;
        printf("The program runs the DFS algorithm on the graph entered.");
        endl;
        printf("The discovery time and the finishing time for the vertices of the directed graph are as follows:");
        endl;
        DFS(G);
        print_times(G);
        print_edge_type(G);
    }
    return 0;
}

