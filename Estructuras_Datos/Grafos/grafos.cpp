#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;
struct ListNode{
	int peso;
	int indice;
	ListNode *sig;
};

typedef ListNode *ListPtr;

typedef struct Graph_t{
	ListPtr *dpHead;
	int count;
} Graph;

typedef Graph *GraphPtr;

void Graphinit(GraphPtr pGraph, int nodeCount){ //inicializa el grafo
	ListPtr *dpHead = (ListPtr*)malloc((nodeCount)*sizeof(ListPtr));
	for(int i=0 ; i<=nodeCount ; i++)
		dpHead[i] = NULL;
	pGraph->dpHead = dpHead;
	pGraph->count = nodeCount;
}

int GraphInsert(GraphPtr G, int src, int dst, int peso){
	ListPtr temp = (ListPtr)malloc(sizeof(ListNode));
	temp->peso = peso;
	temp->indice = dst;
	temp->sig = G->dpHead[src];
	G->dpHead[src] = temp;
}

void UndirectedGraphInsert(GraphPtr G, int src, int dst, int peso){
	GraphInsert(G, src, dst, peso);
	GraphInsert(G, dst,src, peso);
}

void GraphPrint(GraphPtr G){
	int count = G->count, indice;
	for(indice=0 ; indice<count ; indice++){
		ListPtr head = G->dpHead[indice];
		printf("\n Adjacency list of index %d are[",indice);
		while(head){
			printf(" %d",head->indice);
			head = head->sig;
		}
	printf("]\n");
	}
	
}

void BFSQue(GraphPtr G, int indice, int *visited){
	queue<int> que;
	int actual;
	visited[indice]=1;
	que.push(indice);
	while( !que.empty() ){
		actual = que.front();
		que.pop();
		printf("%d ",actual);
		ListPtr head = G-> dpHead[actual];
		while(head){
			if(!visited[ head->indice ]){
				visited[ head->indice ] = 1;
				que.push( head->indice );
			}
			head = head->sig;
		}
	}
}

void DFSStack(GraphPtr G, int index, int visited[])
{
  int curr;
  std::stack<int> stk;
  visited[index]= 1;
  stk.push(index);
  while(!stk.empty()){
    curr = stk.top();
    stk.pop();
    printf(" %d", curr);
    ListPtr head = G->dpHead[curr];
    while(head){
      if(!visited[head->indice]) {
        visited[head->indice] = 1;
        stk.push(head->indice);
      }
      head = head->sig;
    }
  }
}

int *visited_init(int vertices){
	int *visited = (int*)malloc((vertices)*sizeof(int));	
	for(int i=0 ; i<vertices ; i++)
		visited[i]=0;
	return visited;
}


int ExisteCamino(GraphPtr G, int src, int dst){
	int Count = G->count;
	int *visited = visited_init(Count);
	if( dst > Count ){
		return visited[dst]=0;
	}else{
	visited[src] = 1;
	DFSStack(G,src,visited);
	printf(" ");
	return visited[dst];
	}
}

int estaConectado(GraphPtr G){	//nos dice que si todos los vertices ó nodos son visitados
	int count = G->count;
	int *visited = visited_init(count);
	visited[0] = 1;
	DFSStack(G,0,visited);
	printf(" ");
	for(int i=0 ; i<count; i++)
		if(visited[i]== 0)
			return 0;
	return 1;
}

int grafoCiclico(GraphPtr G, int indice, int *visited){
	visited = visited_init(G->count);
  int curr;
  std::stack<int> stk;
  visited[indice]= 1;
  stk.push(indice);
  while(!stk.empty()){
    curr = stk.top();
    stk.pop();
   // printf(" %d", curr);
    ListPtr head = G->dpHead[curr];
    while(head){
      if(!visited[head->indice]) {
        visited[head->indice] = 1;
        stk.push(head->indice);
      }else
		return 1;
      head = head->sig;
    }
  }
  return 0;
}
stack<int> g_stk;
void ordenTopologicoDFS(GraphPtr G, int index, int *visited, stack<int>*stk){
	static stack <int> aux;
	ListPtr head = G->dpHead[index];
	while(head){
		if(!visited[head->indice]){
			visited[head->indice] = 1;
			ordenTopologicoDFS(G,head->indice,visited,&aux);
		}
		head = head->sig;
	}
	aux.push(index);
	*stk=aux;
}

void ordenTopologico(GraphPtr G){ //deber ser un grafo dirigido sin ciclos
	stack<int> stk;
	int count = G->count;
	int *visited = visited_init(count);
	for (int i=0 ; i<count; i++)
		if(visited[i]==0){
			visited[i]=1;
			ordenTopologicoDFS(G,i,visited,&stk);
		}
	while(!stk.empty()){
		int a = stk.top();
		stk.pop();
		printf(" %d ",a);
	}
}
int main(){
	int nodeCount = 8;
	int *visited = visited_init(nodeCount);

	Graph gph;
	Graphinit(&gph,nodeCount);
	GraphInsert(&gph,0,1,1); //(inicio,destino,peso)
	GraphInsert(&gph,0,2,1);
	GraphInsert(&gph,0,3,1);
	GraphInsert(&gph,1,4,1);
	GraphInsert(&gph,2,5,1);
	GraphInsert(&gph,3,6,1);
	GraphInsert(&gph,4,7,1);
	/*UndirectedGraphInsert(&gph,5,7,1);
	UndirectedGraphInsert(&gph,6,7,1);	
*/
	GraphPrint(&gph);
	printf("\n");
	printf("BFS: ");
	BFSQue(&gph,0, visited );
	printf("\n");

	printf("DFS: ");
	visited = visited_init(nodeCount);
	DFSStack(&gph,0, visited );
	printf("\n");
	
	int src=3;	int dst=9;
	printf("Existe camino del %d al %d: ",src,dst);
	if( ExisteCamino(&gph,src,dst) )
		printf("SI\n");
	else
		printf("NO\n");
	
	printf("El grafo es conectado: ");
	if( estaConectado(&gph) )
		printf("SI\n");
	else
		printf("NO\n");
	
	printf("El grafo es ciclico: ");
	if( grafoCiclico(&gph,0,visited) )
		printf("SI\n");
	else
		printf("NO\n");
	
	printf("Orden Topologico");
	ordenTopologico(&gph);
	printf("\n");	
	return 0;


}
