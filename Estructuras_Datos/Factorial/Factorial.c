#include "Factorial.h"

/*****************************************************Función del factorial*********************/
struct node *factorial(int n){
	struct node *L,*L1,*L2,*L3;
	L=crear_lista(1);
	for(int i=2;i<=n;i++){
		L1=crear_lista(i);
		L2=multiplicar_listas(L,L1);
		L=L2;
	}
	L2=invertir_valores(L2);
	return L2;
}

