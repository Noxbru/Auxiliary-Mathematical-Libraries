#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NODE
#define NODE_LIST
struct node;
struct node_list_node;
struct node_list;

#ifndef EDGE
#include "edge.h"
#endif

struct node
{
    int id;
    struct edge_list edges;
    unsigned int n_neighbours;
};

struct node_list_node
{
    struct node *nod;
    struct node_list_node *next;
    struct node_list_node *back;
};

struct node_list
{
    struct node_list_node *first;
    struct node_list_node *last;
    unsigned int length;
};

void initialize_node_list(struct node_list *list)
{
    list->first=NULL;
    list->last=NULL;
    list->length=0;
}

void free_node_list(struct node_list *list)
{
    if(list->length==0)
        free(list);

    else
    {
        struct node_list_node *aux;
        aux=list->first;
        while (aux!=list->last)
        {
            aux=aux->next;
            free(aux->back->nod);
            free(aux->back);
        }
        free(aux->nod);
        free(aux);
        free(list);
    }
}

void add_node(struct node_list *list, struct node *nod1)
{
    if(list->length==0)
    {
        struct node_list_node *aux;
        aux=malloc(sizeof(struct node_list_node));
        aux->nod=nod1;
        aux->next=NULL;
        aux->back=NULL;

        list->first=aux;
        list->last=aux;
        list->length++;
    }
    else
    {
        struct node_list_node *aux;
        aux=malloc(sizeof(struct node_list_node));
        aux->nod=nod1;
        aux->next=NULL;
        aux->back=list->last;

        list->last->next=aux;
        list->last=aux;
        list->length++;
    }
}

/* Connect two nodes using an edge */
void connect(struct node * nod1, struct node * nod2, struct edge * edg)
{
    struct edge_list *list;
    list=&(nod1->edges);

    if(!check_neighbour(list,nod2))
    {
        edg->a=nod1;
        edg->b=nod2;
        add_edge(list,edg);

        list=&(nod2->edges);
        add_edge(list,edg);

        nod1->n_neighbours++;
        nod2->n_neighbours++;
        return;
    }
    edg->a=NULL;
    edg->b=NULL;
}
