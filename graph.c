#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20

typedef struct Node{
    int node_no;
    struct Node* next;
}Node;

typedef struct stack_tag
{
    Node* top;
}stack;

typedef struct stack_tag
{
    Node* front;
    Node* rear;
}queue;

typedef enum{FALSE,TRUE} bool;

typedef struct node{
    Node* list;
    int node_number;
}graph_node;

typedef struct adjacency_list{
    graph_node arr[MAX];
    int occupied; 
}alist;



void InsertAtStart(Node** llptr, int new_data) 
{ 
    /* 1. allocate node */
    Node* new_node = (Node*) malloc(sizeof(Node)); 
   
    /* 2. put in the data  */
    new_node->node_no  = new_data; 
   
    /* 3. Make next of new node as head *
    new_node->next = (*llptr); 
   
    /* 4. move the head to point to the new node */
    (*llptr)    = new_node; 
} 

int listSize(Node* lptr)
{
    Node* ptr=lptr;
    int count=1;
    while(ptr!=NULL)
    {
        count++;
        ptr=ptr->next;
    }
    return count;
}

Node* makeNode(int data)
{
    Node* nptr=(Node*)malloc(sizeof(Node));
    nptr->node_no=data;
    nptr->next=NULL;
    return nptr;
}

void push_back(Node** lptr,int data)
{
    Node* nptr=makeNode(data);
    Node* temp=*lptr;
    if(*lptr==NULL)
    {
        temp=nptr;
        *lptr=nptr;
        return;
    }
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=nptr;

}

void removeList(Node* lptr,Node* ptr)
{
    if(lptr==ptr)
    {
        Node* nptr=lptr;
        free(nptr);
        lptr=NULL;
        return;    
    }
    Node* temp=lptr;
    while(temp->next!=ptr)
    {
        temp=temp->next;
    }
    temp->next=ptr->next;
    free(ptr);
}

Node* Search(Node* lptr,int data)
{
    Node* temp=lptr;
    while(temp!=NULL)
    {
        if(data==temp->node_no)
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}


alist createGraph(){
    alist g;
    g.occupied=0;
    for(int i=0;i<MAX;i++)
    {
        g.arr[i].node_number=-1;
        g.arr[i].list=NULL;
    }
    return g;
}

void deleteWholeList(Node* lptr)
{
    if(lptr!=NULL)
    {
        if(lptr->next==NULL)
        {
            free(lptr);
        }
        else
        {
            Node* temp=lptr;
            while(temp!=NULL)
            {
                temp=temp->next;
                free(lptr);
                lptr=temp;
            }
        }
    }   
}

bool nodeExists(alist* g,int number){
    bool retval=TRUE;
    if(g->arr[number].node_number==-1)
    {
        retval=FALSE;
    }
    return retval;
}

void addNode(alist* graph)
{
    graph->arr[graph->occupied].node_number=graph->occupied;
    graph->occupied++;
}

void deleteNode(alist* graph,int number)
{
    graph->occupied--;
    graph->arr[number].node_number=-1;
    Node* lptr=graph->arr[number].list;
    
}

void addEdgeD(alist* graph,int node1,int node2)// node1->node2 directed
{
    push_back(&graph->arr[node1].list,node2);
}
void addEdgeU(alist* graph,int node1,int node2)// node1---node2 undirected
{
    push_back(&graph->arr[node1].list,node2);
    push_back(&graph->arr[node2].list,node1);
}

void deleteEdgeD(alist* graph,int node1,int node2)//node1--->node2 directed delete
{
    removeList(graph->arr[node1].list,Search(graph->arr[node1].list,node2));
}

void deleteEdgeU(alist* graph,int node1,int node2)//node1--->node2 directed delete
{
    removeList(graph->arr[node1].list,Search(graph->arr[node1].list,node2));
    removeList(graph->arr[node2].list,Search(graph->arr[node2].list,node1));
}


void pushStack()