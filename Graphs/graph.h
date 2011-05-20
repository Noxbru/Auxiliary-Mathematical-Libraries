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
struct graph;

#ifndef NODE
#include "node.h"
#endif

#ifndef EDGE
#include "edge.h"
#endif

struct graph
{
    struct node_list nodes;
    struct edge_list edges;
    unsigned int n_nodes, n_edges;
};

/* Create an Erdös-Rényi Graph with nods nodes and
 * edgs edges.                                      */
struct graph create_erdos_renyi_graph(unsigned int nods, unsigned int edgs)
{
    srand(time(NULL));
    struct graph g;
    struct node **nod_ar_aux;
    nod_ar_aux=malloc(nods*sizeof(struct node *));
    unsigned int i,j;
    g.n_nodes=nods;
    g.n_edges=edgs;

    initialize_node_list(&(g.nodes));
    initialize_edge_list(&(g.edges));
    
    /* The nodes are initiated with its id, the
     * list of neighbours is initiated as NULL
     * and the number of neighbours is 0.
     * The edges are initiated with NULL at
     * both sides                               */
    for (i = 0; i < g.n_nodes; i++)
    {
        struct node *aux_nod;
        aux_nod->id=i;
        initialize_edge_list(&(aux_nod->edges));
        aux_nod->n_neighbours=0;
        add_node(&(g.nodes),aux_nod);
        nod_ar_aux[i]=aux_nod;
    }


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

        struct edge *aux_edg;
        connect(nod_ar_aux[i],nod_ar_aux[j],aux_edg);
        add_edge(&(g.edges),aux_edg);

        /* If the edge already existed, both
         * of the ends of the were to be
         * edge are NULL                    */
        if(aux_edg->a!=NULL)
            edgs--;
    }

    free(nod_ar_aux);
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
    struct node **nod_ar_aux;
    nod_ar_aux=malloc(nods*sizeof(struct node *));
    unsigned int i,j,k,l;

    /* As we know how many nodes will be added, and how
     * many edges will have each, we can calculate
     * the total number of nodes and edges at the end   */
    g.n_nodes=m0+times;
    g.n_edges=m0*(m0-1)/2+m*times;

    /* The nodes are initiated with its id, the
     * list of neighbours is initiated as NULL
     * and the number of neighbours is 0.
     * The edges are initiated with NULL at
     * both sides                               */
    for (i = 0; i < g.n_nodes; i++)
    {
        struct node *aux_nod;
        aux_nod->id=i;
        initialize_edge_list(&(aux_nod->edges));
        aux_nod->n_neighbours=0;
        add_node(&(g.nodes),aux_nod);
        nod_ar_aux[i]=aux_nod;
    }

    /* We have to connect between themselves the
     * m0 first nodes                           */
    for (i = 0,k=0; i < m0; i++)
        for (j = i+1; j < m0; j++)
        {
            struct edge *aux_edg;
            connect(nod_ar_aux[i],nod_ar_aux[j],aux_edg);
            add_edge(&(g.edges),aux_edg);
            k++;
        }

    /* While there's still nodes to add */
    while (0<times)
    {
        j=0;
        do
        {
            if(pref_at==0)
                /* if we don't use preferential
                 * attachment, any of the
                 * existing nodes can be linked
                 * to the new one               */
                i=(unsigned int)rand()%m0;
            else
            {
                /* If we use preferential attachment
                 * we have to choose the node
                 * according to the number of neighbours
                 * it has                               */
                i=(unsigned int)rand()%(2*k-j);
                for (l = 0; l < m0 && i>=0; l++)
                {
                    if(i<nod_ar_aux[l].n_neighbours)
                    {
                        i=l;
                        break;
                    }
                    else
                        i-=nod_ar_aux[l].n_neighbours;
                }
            }
            struct edge *aux_edg;
            connect(nod_ar_aux[m0],nod_ar_aux[j],aux_edg);
            add_edge(&(g.edges),aux_edg);

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

    free(nod_ar_aux);
    return g;
}

/* Prints the graph to a file that can be
 * converted to a image using the dot program
 * from the graphviz software
 * http://www.graphviz.org/                     */
void graph_to_dot_file(char *c, struct graph g, char over)
{
    FILE *f;
    if(over==0)
        f=fopen(c,"a");
    else
        f=fopen(c,"w");
    if(f==NULL)
    {
        printf("Error opening file\n");
        return;
    }

    struct edge_list_node *aux;
    aux=g.edges.first;
    fprintf(f, "digraph G \{\n");
    do
    {
        fprintf(f, "\t%d -> %d;\n",aux->edg->a->id,aux->edg->b->id);
        aux=aux->next;
    }
    while (aux->next!=NULL);
    fprintf(f, "}");
    fclose(f);
}

/* Prints a graph to a file */
void graph_to_file(char *c, struct graph g, char over)
{
    FILE *f;
    if(over==0)
        f=fopen(c,"a");
    else
        f=fopen(c,"w");
    if(f==NULL)
    {
        printf("Error opening file\n");
        return;
    }

    struct edge_list_node *aux;
    aux=g.edges.first;
    fprintf(f, "Target\tSource\n");
    do
    {
        fprintf(f, "%d\t%d\n",aux->edg->a->id,aux->edg->b->id);
        aux=aux->next;
    }
    while (aux->next!=NULL);
    fclose(f);
}

unsigned int max_neighbours(struct graph g)
{
    struct node_list_node *aux_nod;
    aux_nod=g.nodes.first;
    unsigned int aux=0;

    do
    {
        if(aux_nod->nod->n_neighbours>aux)
            aux=aux_nod->nod->n_neighbours;
        aux_nod=aux_nod->next;
    }
    while (aux_nod->next!=NULL);
    return aux;
}

unsigned int * grade_distribution(struct graph g)
{
    unsigned int *dist;
    dist=malloc((max_neighbours(g)+1)*sizeof(unsigned int));

    struct node_list_node *aux_nod;
    aux_nod=g.nodes.first;
    do
    {
        dist[aux_nod->nod->n_neighbours]++;
        aux_nod=aux_nod->next;
    }
    while (aux_nod->next!=NULL);

    return dist;
}

void free_graph(struct graph *g)
{
    struct node_list_node *aux_nod;
    aux_nod=g->nodes.first;
    do
    {
        free_edge_list(&(aux_nod->nod.edges));
        aux_nod=aux_nod->next;
    }
    while (aux_nod->next!=NULL);

    free_edge_list(g->edges);
    free_node_list(g->nodes);
}
