#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EDGE
#define EDGE_LIST
struct edge;
struct edge_list_node;
struct edge_list;

#ifndef NODE
#include "node.h"
#endif

struct edge
{
    struct node *a, *b;
};

struct edge_list_node
{
    struct edge *ed;
    struct edge_list_node *next;
    struct edge_list_node *back;
};

struct edge_list
{
    struct edge_list_node *first;
    struct edge_list_node *last;
    unsigned int length;
};

void initialize_edge_list(struct edge_list *list)
{
    list->first=NULL;
    list->last=NULL;
    list->length=0;
}

void free_edge_list(struct edge_list *list)
{
    if(list->length==0)
        free(list);

    else
    {
        struct edge_list_node *aux;
        aux=list->first;
        while (aux!=list->last)
        {
            aux=aux->next;
            free(aux->back->ed);
            free(aux->back);
        }
        free(aux->ed);
        free(aux);
        free(list);
    }
}

void add_edge(struct edge_list *list, struct edge *edg)
{
    if(list->length==0)
    {
        struct edge_list_node *aux;
        aux=malloc(sizeof(struct edge_list_node));
        aux->ed=edg;
        aux->next=NULL;
        aux->back=NULL;

        list->first=aux;
        list->last=aux;
        list->length++;
    }
    else
    {
        struct edge_list_node *aux;
        aux=malloc(sizeof(struct edge_list_node));
        aux->ed=edg;
        aux->next=NULL;
        aux->back=list->last;

        list->last->next=aux;
        list->last=aux;
        list->length++;
    }
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
int check_neighbour(struct edge_list *list, struct node *nod)
{
    if(list->length==0)
        return 0;

    else
    {
        unsigned int i;
        struct edge_list_node *aux;
        aux=list->first;

        do
        {
            if(check_end(aux->ed,nod))
                return 1;
            aux=aux->next;
        }
        while(aux!=NULL);
        return 0;
    }
}
