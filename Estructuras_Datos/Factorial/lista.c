#include "lista.h"
void add_to_list(struct node **L,int n){
	struct node *new_node;

	new_node = malloc(sizeof(struct node));
	new_node->value = n;
	new_node->next = *L;
	*L = new_node;
}

void print_list(struct node *L){
	struct node *p;
	p = L;
	while(p != NULL){
		printf("%d",p->value);
		p = p->next;
	}
	printf("\n");
}

/****************************Fución que crea lista*****************************/
struct node *crear_lista(int n){
	struct node *L;
	L=NULL;
	int numdes;
	while(n!=0){ //Este ciclo descompone un numero
		numdes=n%10;
		n=n/10;
		add_to_list(&L,numdes);
	}
	return L;

}

/*************************************Función que invierte los valores de la lista**************************************/
struct node *invertir_valores(struct node *L){
	struct node *p,*pinvertida;
	p=L;
	pinvertida=NULL;
	while(p!=NULL){
		add_to_list(&pinvertida,p->value); //vamos guardando los valores de forma invertida a la lista
		p=p->next;
	}
	return pinvertida;	
}

void borra_lista(struct node **L){
	struct node *p,*next;
	p = *L;
	while(p != NULL){
		next= p-> next;
		free(p);
		p= next;
	}
	*L=NULL;
}

void add_to_end(struct node **L,int n){
	struct node *new_node;
	struct node *p;

	new_node = malloc(sizeof(struct node));
	new_node->value = n;
	new_node->next = NULL;

	if(*L==NULL){	
		*L=new_node; //si hay un NULL, agrega otro nodo
	}
	else{
		p=*L;
		while(p->next !=NULL){
		p=p->next;
	}
	
	p->next =new_node;
	}
}
