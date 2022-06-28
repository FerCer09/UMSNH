#include "Factorial.h"

int main(void){
	struct node *L,*L2,*L3;
	/*L=crear_lista(123);
	L2=crear_lista(56);
	//L2=crear_lista(9999);
	//L=invertir_valores(L);
	//L2=invertir_valores(L2);
	//L3=sumar_listas(L2,L);
	//L3=invertir_valores(L3);
	L3=multiplicar_listas(L,L2);
	print_list(L3);*/
	int n;
	printf("Este programa calcula el factorial de N:\n");
	printf("N: ");
	scanf("%d",&n);
	printf("Factorial de %d:\n",n);
	if(n>1){
		L= factorial(n);
		L=invertir_valores(L);
		print_list(L);
	}
	else{
	printf("1\n");	
	}	
}
