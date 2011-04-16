#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EDGE
#define EDGE_LIST

#ifndef NODE
#include "node.h"
#endif

struct edge
{
    struct node *a,*b;
};

struct edge_list_node
{
    struct edge *ed;
    struct edge_list_node *next;
};

struct edge_list
{
    struct edge_list_node *first;
    unsigned int n_edges;
};

/* Adds an edge to a list
 * If the list is empty it is created   */
void add_edge(struct edge_list *list, struct edge *edg)
{
    if(list->first==NULL)
    {
        struct edge_list_node *aux;
        aux=malloc(sizeof(struct edge_list_node));
        aux->ed=edg;
        aux->next=NULL;
        list->first=aux;
        list->n_edges=1;
        return;
    }

    struct edge_list_node *aux;
    aux=list->first;
    while (aux->next!=NULL)
        aux=aux->next;
    struct edge_list_node *aux2;
    aux2=malloc(sizeof(struct edge_list_node));
    aux2->ed=edg;
    aux2->next=NULL;
    aux->next=aux2;
    list->n_edges++;
}

/* Checks if the node nod is in one of the
 * ends of the edge edg.
 * Returns 1 if it is
 * Returns 0 if it isn't                    */
int check_end(struct edge *edg, struct node *nod)
{
    if(nod==edg->a||nod==edg->b)
        return 1;
    return 0;
}

/* Checks if the node nod is in the
 * neighbour list
 * Returns 1 if it is
 * Returns 0 if it isn't                    */
int check_neighbour(struct edge_list * list, struct node * nod)
{
    if(list->first==NULL)
        return 0;

    struct edge_list_node *aux;
    aux=list->first;
    do
        if(check_end(aux->ed,nod))
            return 1;
    while ((aux=aux->next)!=NULL);
    return 0;
}
