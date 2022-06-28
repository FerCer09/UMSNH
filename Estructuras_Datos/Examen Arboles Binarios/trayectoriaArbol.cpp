/* 
 Compilar como: 
 
    $ g++ -o arbol arbol.cpp
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<queue>
#include<stack>
#include<list>

struct treeNode_t{
  int value;
  int nivel;
  int numFamiliar;
  int padre;
  char hijo[5];
  treeNode_t * lChild;
  treeNode_t * rChild;
};

typedef treeNode_t * treePtr;

treePtr createNode(int val,int padre)
{
  treePtr root=(treePtr)malloc(sizeof(treeNode_t));
  root->value = val;
  root->padre = padre;
  root->lChild = root->rChild = NULL;
  
  strcpy(root->hijo,"h");
  return root;
}

void printPreorder(treePtr root)
{
  if(root) {
     printf("%d ", root->value);
     printPreorder(root->lChild);
     printPreorder(root->rChild);
  }
}

void printPostorder(treePtr root)
{
  if(root) {
     printPostorder(root->lChild);
     printPostorder(root->rChild);
     printf("%d ", root->value);
  }
}

void printInorder(treePtr root)
{
  if(root) {
     printInorder(root->lChild);
     printf("%d ", root->value);
     printInorder(root->rChild);
  }
}

void printBreadthFirst(treePtr root)
{
  std::queue<treePtr> que;
  treePtr temp;
  que.push(root);
  while(!que.empty()) {
    temp = que.front();
    que.pop();
    printf("%d ",temp->value);
    if(temp->lChild)
      que.push(temp->lChild);
    if(temp->rChild)
      que.push(temp->rChild);
  }
}

void printBreadthFirstFull(treePtr root)
{
  std::queue<treePtr> que;
  treePtr temp;
  que.push(root);
  while(!que.empty()) {
    temp = que.front();
    que.pop();
    printf("%d(%d,%d) ",temp->value,temp->nivel,temp->numFamiliar);
    if(temp->lChild)
      que.push(temp->lChild);
    if(temp->rChild)
      que.push(temp->rChild);
  }
}

void printDepthFirst(treePtr root)
{
  std::stack<treePtr> st;
  treePtr temp;
  st.push(root);
  while(!st.empty()) {
    temp = st.top();
    st.pop();
    printf("%d ",temp->value);
    if(temp->lChild)
      st.push(temp->lChild);
    if(temp->rChild)
      st.push(temp->rChild);
  }
}

int treeDepth(treePtr root)
{
  if(!root)
    return 0;
  else {
    int lDepth=treeDepth(root->lChild);
    int rDepth=treeDepth(root->rChild);
    if(lDepth > rDepth)
      return lDepth+1;
    else
      return rDepth+1;
  }
}

treePtr insertaEnArbol(treePtr root, int valor, int padre)
{
  if(root==NULL){
    return createNode(valor,padre);
  }else {
    if(valor < root->value){
       root->lChild = insertaEnArbol(root->lChild,valor,root->value);
    }else{
       root->rChild = insertaEnArbol(root->rChild,valor,root->value);
       
    }
     return root;
  }
}

int existeElemento(treePtr root, int v)
{
  int existeL, existeR;
  if(root == NULL)
    return 0;
  else {
    if(root->value == v)
      return 1;
    else {
      existeL = existeElemento(root->lChild,v);
      existeR = existeElemento(root->rChild,v);
      if(existeL > 0) 
         return existeL + 1;
      if(existeR > 0) 
         return existeR + 1;
      return 0;
    }
  } 
}

void printList(std::list<int> L1)
{
  std::list<int>::iterator iterB=L1.begin(); 
  std::list<int>::iterator iterE=L1.end(); 
  while(iterB != iterE) {
    printf("%d ", *iterB);
    iterB++;
  }
}

std::stack<int> g_T;
int Trayectoria(treePtr root, int v)
{
  if(root == NULL)
    return 0;
  else {
    if(root->value == v) {
      g_T.push(root->value);
      return 1;
    } else if(Trayectoria(root->lChild,v) || Trayectoria(root->rChild,v)){
        g_T.push(root->value);
        return 1;
    } else
      return 0;  
  } 
}

void printTrayectoria(std::stack<int> T)
{
  while(!T.empty()){
    printf("%d ", T.top());
    T.pop();
  }
}

int g_numNodos=0;
int numNodosNivel(treePtr root, int nivel, int nivel_raiz)
{
  if(root == NULL)
    return 0;
  if(nivel_raiz == nivel) {
    g_numNodos++;
    if(nivel_raiz == 1){
       printf("%d ", root->value);
    }else{
       if(root->value > root->padre){
           printf("%d(%dh) ", root->value,root->padre);
       }else{
           printf("%d(h%d) ", root->value,root->padre);
       }
    }
    root->nivel = nivel;
    root->numFamiliar = g_numNodos;
  } else {
    numNodosNivel(root->lChild,nivel,nivel_raiz+1);
    numNodosNivel(root->rChild,nivel,nivel_raiz+1);
  } 
  return g_numNodos;
}

std::stack<int> g_T2;
int Trayectoria2(treePtr root, int v)
{
  if(root == NULL)
    return 0;
  else {
    if(root->value == v) {
      g_T2.push(root->padre);
      return 1;
    } else if(Trayectoria2(root->lChild,v) || Trayectoria2(root->rChild,v)){
        g_T2.push(root->padre);
        return 1;
    } else
      return 0;  
  } 
}

void printTrayectoriahijos(std::stack<int> T,std::stack<int> T2)
{
  int contar=0;
  while(!T.empty()){
    if(contar==0){
       printf("%d ", T.top());
    }else{
       if(T.top() > T2.top()){
            printf("%d(%dh) ", T.top(),T2.top());
       }else{
            printf("%d(h%d) ", T.top(),T2.top());
       }
    }
    contar++;
    T.pop();
    T2.pop();
  }
}

int main(int argc, char *argv[]){
	int num[argc-1];
	treePtr root = NULL;
	for(int i=0 ; i<argc-1 ; i++)
		num[i]= atoi(argv[i+1]);
	
	for(int i=0; i < argc-1; i++){
		root = insertaEnArbol(root,num[i],num[i]);
	}
	
	int depth=treeDepth(root);
	/*for(int i=1; i <= depth; i++) {
    		g_numNodos=0;
		numNodosNivel(root,i,1); printf("\n");
		//printf("numNodosNivel(%d) = %d\n", i, numNodosNivel(root,i,1));
  }
	printf("\n");*/
	printf("Número a buscar: ");	
	int n;
	scanf("%d",&n);
	
	Trayectoria(root,n);
	Trayectoria2(root,n);
	printTrayectoriahijos(g_T,g_T2);
	printf("\n");
	return 0;
}

