#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *next;
};
void add_to_list(struct node **L, int n);
void print_list(struct node *L);
struct node *crear_lista(int n);
struct node *invertir_valores(struct node *L);
void borra_lista(struct node **L);
void add_to_end(struct node **L,int n);
