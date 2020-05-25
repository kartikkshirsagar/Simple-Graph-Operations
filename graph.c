#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20
#define INITSIZE 4

typedef struct Node{
    int node_no;
    struct Node* next;
}Node;

typedef struct stack_tag
{
    Node* top;
}stack;

typedef struct queue_tag
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
typedef struct
{
	int *array;
	size_t used;
	size_t size;
} vector;

void initVector(vector *a)
{
	a->array = (int *)malloc(INITSIZE * sizeof(int));
	a->used = 0;
	a->size = INITSIZE;
}

void push_back(vector *a, int element)
{
	// a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
	// Therefore a->used can go up to a->size
	if (a->used == a->size)
	{
		a->size *= 2;
		a->array = (int *)realloc(a->array, a->size * sizeof(int));
	}
	a->array[a->used] = element;
	a->used++;
}
void removeAt(vector *a, int i)
{
	if (i > a->used || i < 0)
	{
		return;
	}
	int j = i;
	while (j < a->used)
	{
		a->array[j] = a->array[j + 1];
		j++;
	}
	a->used--;
	if (a->used <= (a->size / 2))
	{
		a->size = a->size / 2;
		a->array = (int *)realloc(a->array, a->size * sizeof(int));
	}
}
void clear(vector *a)
{
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}
void printVector(vector *a)
{
	int i;
	for (i = 0; i < a->used; i++)
	{
		printf("%d ", a->array[i]);
	}
	//printf(" --%ld-- ",a->size);
	printf("\n");
}

Node* makeNode(int data)
{
    Node* nptr=(Node*)malloc(sizeof(Node));
    nptr->node_no=data;
    nptr->next=NULL;
    return nptr;
}



void InsertAtStart(Node** llptr, int new_data) 
{ 
    /* 1. allocate node */
    Node* new_node=makeNode(new_data); 
   
    /* 2. put in the data  */
    new_node->node_no  = new_data; 
   
    /* 3. Make next of new node as head */
    new_node->next = (*llptr); 
   
    /* 4. move the head to point to the new node */
    (*llptr)    = new_node; 
} 

void InsertAtEnd(Node** llptr,int data)
{
    Node* lptr=*llptr;
    Node* new_node=makeNode(data);
    if(lptr==NULL)
    {
        *llptr=new_node;
    }
    else
    {
        Node* temp=lptr;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=new_node;
    }
    
}

void deleteAtEnd(Node** llptr)
{
    Node* lptr=*llptr;
    if(lptr==NULL)
    {
        printf("Nothing to delete");
        return;
    }
    else if(lptr->next==NULL)
    {
        free(lptr);
        *llptr=NULL;
    }
    else
    {
        Node* temp=lptr;
        while(temp->next->next!=NULL)
        {
            temp=temp->next;
        }
        free(lptr->next);
        lptr->next=NULL;
    }

}

void deleteAtStart(Node** llptr)
{
    if(*llptr==NULL)
    {
        printf("Nothing to delete");
        return;
    }
    Node* lptr=*llptr;
    *llptr=lptr->next;
    free(lptr);
}



void initStack(stack* sptr)
{
    sptr->top=NULL;
}

void initQ(queue* qptr)
{
    qptr->rear=qptr->front=NULL;
    
}
void PushQ(queue* qptr,int data)
{
    InsertAtEnd(&qptr->front,data);
}

void PushStack(stack* sptr,int data)
{
    InsertAtStart(&sptr->top,data);
}

void PopStack(stack* sptr)
{
    deleteAtStart(&sptr->top);
}

void PopQ(queue* qptr)
{
    deleteAtStart(&qptr->front);
}

bool isStackEmpty(stack* sptr)
{
    if(sptr->top==NULL)
    {
        return TRUE;
    }
    return FALSE;
}

bool isQEmpty(queue* qptr)
{
    if(qptr->front==NULL && qptr->rear==NULL)
    {
        return TRUE;
    }
    return FALSE;
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



void push_backL(Node** lptr,int data)
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

void removeList(Node** llptr,Node* ptr)
{
    Node* lptr=*llptr;
    if(lptr==ptr)
    {
        Node* nptr=lptr;
        free(nptr);
        *llptr=NULL;
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

bool isElementV(vector* seen,int element)
{
    bool retval=FALSE;
    for(int i=0;i<seen->used;i++)
    {
        if(seen->array[i]==element)
        {
            retval=TRUE;
        }
    }
    return retval;
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

void deleteWholeList(Node** llptr)
{
    Node* lptr=*llptr;
    if(lptr!=NULL)
    {
        if(lptr->next==NULL)
        {
            free(lptr);
            *llptr=NULL;
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
            *llptr=NULL;
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

int SearchNodeG(alist* graph,int node_no)
{
    for(int i=0;i<MAX;i++)
    {
        if(graph->arr[i].node_number==node_no)
        {
            return i;
        }
    }
}

void addNode(alist* graph,int node_no)
{
    graph->arr[graph->occupied].node_number=node_no;
    graph->occupied++;
}

void deleteEvidenceofNode(alist* graph,int number)
{
    for(int i=0;i<graph->occupied;i++)
    {
        if(graph->arr[i].list!=NULL)
        {
            Node* res=Search(graph->arr[i].list,number);
            if(res!=NULL)
            {
                removeList(&graph->arr[i].list,res);
            }
        }
        
    }
}

void deleteNode(alist* graph,int number)
{
    
    //graph->arr[SearchNodeG(graph,number)].node_number=-1;
    Node* lptr=graph->arr[SearchNodeG(graph,number)].list;
    deleteWholeList(&(graph->arr[SearchNodeG(graph,number)].list)); //deleting the edges that go out from the node to be deleted
    int j; 
    for(int i=0;i<graph->occupied;i++)
    {
        if(graph->arr[i].node_number==number)
        {
            j=i+1;
            while(j<MAX)
            {
                graph->arr[j-1]=graph->arr[j];
                j++;
            }
        }
    }
    graph->occupied--;
    deleteEvidenceofNode(graph,number); //deletes all edges pointing to the deleted node
    
    
    
}

void addEdgeD(alist* graph,int node1,int node2)// node1->node2 directed
{
    push_backL(&graph->arr[SearchNodeG(graph,node1)].list,node2);
}
void addEdgeU(alist* graph,int node1,int node2)// node1---node2 undirected
{
    push_backL(&graph->arr[SearchNodeG(graph,node1)].list,node2);
    push_backL(&graph->arr[SearchNodeG(graph,node2)].list,node1);
}

void deleteEdgeD(alist* graph,int node1,int node2)//node1--->node2 directed delete
{
    removeList(&graph->arr[node1].list,Search(graph->arr[SearchNodeG(graph,node1)].list,node2));
}

void deleteEdgeU(alist* graph,int node1,int node2)//node1--->node2 directed delete
{
    removeList(&graph->arr[node1].list,Search(graph->arr[SearchNodeG(graph,node1)].list,node2));
    removeList(&graph->arr[node2].list,Search(graph->arr[SearchNodeG(graph,node2)].list,node1));
}


vector neighbours(alist* graph,int node_no)
{
    Node* lptr=graph->arr[SearchNodeG(graph,node_no)].list;
    vector ret;
    initVector(&ret);
    Node* temp=lptr;
    while(temp!=NULL)
    {
        push_back(&ret,temp->node_no);
        temp=temp->next;
    }
    return ret;
}

void Traverse(int node_no)
{
    printf("%d-->",node_no);
}
void DepthFirstSearch(alist* graph)
{
    stack frontier;
    initStack(&frontier);
    vector seen;
    initVector(&seen);
    for(int i=0;i<graph->occupied && graph->occupied>seen.used;i++)
    {   
        if(graph->arr[i].node_number!=-1 && !isElementV(&seen,graph->arr[i].node_number))
        {
            PushStack(&frontier,graph->arr[i].node_number);
            while(!isStackEmpty(&frontier) && graph->occupied>seen.used)
            {
                
                vector neighbors;
                initVector(&neighbors);
                neighbors=neighbours(graph,frontier.top->node_no);
                Traverse(frontier.top->node_no);
                push_back(&seen,frontier.top->node_no);
                PopStack(&frontier);
                for(int i=0;i<neighbors.used;i++)
                {
                    if(!isElementV(&seen,neighbors.array[i]))
                    {
                        PushStack(&frontier,neighbors.array[i]);
                        
                    }
                }
            }
        }
        
    }
}


void BreadthFirstSearch(alist* graph)
{
    queue frontier;
    initQ(&frontier);
    vector seen;
    initVector(&seen);
    for(int i=0;i<graph->occupied && graph->occupied>seen.used;i++)
    {
        if(graph->arr[i].node_number!=-1 && !isElementV(&seen,graph->arr[i].node_number))
        {
            PushQ(&frontier,graph->arr[i].node_number);
            while(!isQEmpty(&frontier) && graph->occupied>seen.used)
            {
                
                vector neighbors;
                initVector(&neighbors);
                neighbors=neighbours(graph,frontier.front->node_no);
                Traverse(frontier.front->node_no);
                push_back(&seen,frontier.front->node_no);
                PopQ(&frontier);
                for(int i=0;i<neighbors.used;i++)
                {
                    if(!isElementV(&seen,neighbors.array[i]))
                    {
                        PushQ(&frontier,neighbors.array[i]);
                        
                    }
                }
            }
        }
        
    }
}


int main()
{
    alist graph=createGraph();
    addNode(&graph,70);
    addNode(&graph,50);
    addNode(&graph,10);
    addNode(&graph,12);
    addNode(&graph,32);
    addNode(&graph,54);
    addEdgeD(&graph,70,10);
    addEdgeD(&graph,70,50);
    addEdgeD(&graph,50,12);
    addEdgeD(&graph,10,32);
    addEdgeD(&graph,32,54);
    deleteNode(&graph,32);
    DepthFirstSearch(&graph);
    printf("\n");
    BreadthFirstSearch(&graph);
    

}