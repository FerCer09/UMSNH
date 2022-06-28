/* 
 Compilar como: 
 
    $ g++ -o arbol arbol.cpp
*/
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<stack>
#include<list>

struct treeNode_t{
  int value;
  int nivel;
  int numFamiliar;
  treeNode_t * lChild;
  treeNode_t * rChild;
};

typedef treeNode_t * treePtr;

treePtr createNode(int val)
{
  treePtr root=(treePtr)malloc(sizeof(treeNode_t));
  root->value = val;
  root->lChild = root->rChild = NULL;
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

treePtr creaArbol(void)
{
  treePtr root, n1, n2, n3,n4, n5, n6, n7;
  n1 = createNode(1);
  n2 = createNode(2);
  n3 = createNode(3);
  n4 = createNode(4);
  n5 = createNode(5);
  n6 = createNode(6);
  n7 = createNode(7);
  n1->lChild = n2; 	n1->rChild = n3;
  n2->lChild = n4; 	n2->rChild = n5;
  n3->lChild = n6; 	n3->rChild = n7;
  return n1;
}

treePtr CreateBinaryTree(int arr[], int start, int end)
{
  treePtr root = NULL;
  if(start > end)
    return NULL;
  int mid = (start + end) / 2;
  root = createNode(arr[mid]);
  root->lChild = CreateBinaryTree(arr,start,mid-1);
  root->rChild = CreateBinaryTree(arr, mid+1,end);
  return root;
}

treePtr insertaEnArbol(treePtr root, int valor)
{
  if(root==NULL)
    return createNode(valor);
  else {
    if(valor < root->value)
       root->lChild = insertaEnArbol(root->lChild,valor);
    else
       root->rChild = insertaEnArbol(root->rChild,valor);
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
    root->nivel = nivel;
    root->numFamiliar = g_numNodos;
  } else {
    numNodosNivel(root->lChild,nivel,nivel_raiz+1);
    numNodosNivel(root->rChild,nivel,nivel_raiz+1);
  } 
  return g_numNodos;
}

int nodosNivel(treePtr root, int nivel, int nivel_raiz)
{
  if(root == NULL)
    return 0;
  if(nivel_raiz == nivel) {
    printf("%d ", root->value);
    root->nivel = nivel;
  } else {
    nodosNivel(root->lChild,nivel,nivel_raiz+1);
    nodosNivel(root->rChild,nivel,nivel_raiz+1);
  } 
  return 1;
}

int main(int argc, char *argv[]){
	int num[argc-1];
	treePtr root = NULL;
	for(int i=0 ; i<argc-1 ; i++)
		num[i]= atoi(argv[i+1]);
	
	for(int i=0; i < argc-1; i++){
		root = insertaEnArbol(root,num[i]);
	}
	
	int depth=treeDepth(root);
	for(int i=1; i <= depth; i++) {
		nodosNivel(root,i,1); printf("\n");
        }
	printf("\n");
	return 0;
}

