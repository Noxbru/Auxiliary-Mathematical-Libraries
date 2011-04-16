/* This is a library to use graphs in C
 * written by Bruno Jiménez
 * under the Catware licence && GPL licence
 * More info of the Catware licence can be
 * found here: http://lists.debian.org/debian-devel/1999/01/msg01921.html
 * but it says that if you find this code useful
 * you should pay for it petting some cats
 * Any request or bug or anything of the code
 * please, contact brunojimen(at)gmail(dot)com
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GRAPH

#ifndef NODE
#include "node.h"
#endif

#ifndef EDGE
#include "edge.h"
#endif

struct graph
{
    struct node *nodes;
    struct edge *edges;
    unsigned int n_nodes, n_edges;
};

/* Create an Erdös-Rényi Graph with nods nodes and
 * edgs edges.                                      */
struct graph create_erdos_renyi_graph(unsigned int nods, unsigned int edgs)
{
    srand(time(NULL));
    struct graph g;
    unsigned int i,j;
    g.n_nodes=nods;
    g.n_edges=edgs;

    /* We create the arrays for holding the total
     * number of nodes and edges                    */
    g.nodes=malloc(g.n_nodes*sizeof(struct node));
    g.edges=malloc(g.n_edges*sizeof(struct edge));
    
    /* The nodes are initiated with its id, the
     * list of neighbours is initiated as NULL
     * and the number of neighbours is 0.
     * The edges are initiated with NULL at
     * both sides                               */
    for (i = 0; i < g.n_nodes; i++)
    {
        g.nodes[i].id=i;
        g.nodes[i].edges.first=NULL;
        g.nodes[i].n_neighbours=0;
    }
    for (i = 0; i < g.n_edges; i++)
    {
        g.edges[i].a=NULL;
        g.edges[i].b=NULL;
    }

    struct node *aux1, *aux2;
    struct edge *aux3;

    /* While there's still edges to be added    */
    while (0<edgs)
    {
        /* We have to be sure that the two
         * ends of the edge aren't the same */
        do
        {
            i=(unsigned int)rand()%g.n_nodes;
            j=(unsigned int)rand()%g.n_nodes;
        }
        while (i==j);

        aux1=&g.nodes[i];
        aux2=&g.nodes[j];
        aux3=&g.edges[edgs-1];
        connect(aux1,aux2,aux3);

        /* If the edge already existed, both
         * of the ends of the were to be
         * edge are NULL                    */
        if(aux3->a!=NULL)
            edgs--;
    }

    return g;
}

/* Create a Barabási-Albert graph with m0 initial connected
 * nodes, then adds times nodes connected to m nodes that
 * already existed in the graph, the choice of preferential
 * attachment is passed as a parameter.                     */
struct graph create_barabasi_albert_graph(unsigned int m0, unsigned int times, unsigned int m, unsigned int pref_at)
{
    srand(time(NULL));
    struct graph g;
    unsigned int i,j,k,l;

    /* As we know how many nodes will be added, and how
     * many edges will have each, we can calculate
     * the total number of nodes and edges at the end   */
    g.n_nodes=m0+times;
    g.n_edges=m0*(m0-1)/2+m*times;

    /* We create the arrays for holding the total
     * number of nodes and edges                    */
    g.nodes=malloc(g.n_nodes*sizeof(struct node));
    g.edges=malloc(g.n_edges*sizeof(struct edge));
    
    /* The nodes are initiated with its id, the
     * list of neighbours is initiated as NULL
     * and the number of neighbours is 0.
     * The edges are initiated with NULL at
     * both sides                               */
    for (i = 0; i < g.n_nodes; i++)
    {
        g.nodes[i].id=i;
        g.nodes[i].edges.first=NULL;
        g.nodes[i].n_neighbours=0;
    }
    for (i = 0; i < g.n_edges; i++)
    {
        g.edges[i].a=NULL;
        g.edges[i].b=NULL;
    }

    struct node *aux1, *aux2;
    struct edge *aux3;

    /* We have to connect between themselves the
     * m0 first nodes                           */
    for (i = 0,k=0; i < m0; i++)
        for (j = i+1; j < m0; j++)
        {
            aux1=&g.nodes[i];
            aux2=&g.nodes[j];
            aux3=&g.edges[k];
            connect(aux1,aux2,aux3);
            k++;
        }

    /* While there's still nodes to add */
    while (0<times)
    {
        j=0;
        do
        {
            if(pref_at==0)
            {
                /* if we don't use preferential
                 * attachment, any of the
                 * existing nodes can be linked
                 * to the new one               */
                i=(unsigned int)rand()%m0;
                aux2=&g.nodes[i];
            }
            else
            {
                /* If we use preferential attachment
                 * we have to choose the node
                 * according to the number of neighbours
                 * it has                               */
                i=(unsigned int)rand()%(2*(k-j));
                for (l = 0; l < m0 && i>0; l++)
                    if((i-=g.nodes[l].n_neighbours)<=0)
                        aux2=&g.nodes[l];
            }
            aux1=&g.nodes[m0];
            aux3=&g.edges[k];
            connect(aux1,aux2,aux3);

            /* If the edge already existed, both
             * of the ends of the were to be
             * edge are NULL                    */
            if(aux3->a!=NULL)
            {
                j++;
                k++;
            }
        }
        while (j<m);
        m0++;
        times--;
    }

    return g;
}

void graph_to_dot_file(char *c, struct graph g, char over)
{
    FILE *f;
    if(over==0)
        f=fopen(c,"a");
    else
        f=fopen(c,"w");
    if(f==NULL)
        printf("Error opening file\n");

    unsigned int i;
    fprintf(f, "digraph G \{\n");
    for (i = 0; i < g.n_edges; i++)
    {
        fprintf(f, "\t%d -> %d;\n",g.edges[i].a->id,g.edges[i].b->id);
    }
    fprintf(f, "}");
    fclose(f);
}

void graph_to_file(char *c, struct graph g, char over)
{
    FILE *f;
    if(over==0)
        f=fopen(c,"a");
    else
        f=fopen(c,"w");
    if(f==NULL)
        printf("Error opening file\n");

    unsigned int i;
    fprintf(f, "Target\tSource\n");
    for (i = 0; i < g.n_edges; i++)
    {
        fprintf(f, "%d\t%d\n",g.edges[i].a->id,g.edges[i].b->id);
    }
    fclose(f);
}
