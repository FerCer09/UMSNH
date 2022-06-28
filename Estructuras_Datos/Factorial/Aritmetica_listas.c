#include "Aritmetica_listas.h"
/*************función que suma listas********************************/
struct node *sumar_listas(struct node *L, struct node *L2){
	struct node *p,*p2,*psum;	
	p = L; p2 = L2;
	p=invertir_valores(p);	p2=invertir_valores(p2);
	psum=NULL;
	int acarreo=0;
	while(p != NULL || p2 != NULL){
			if(p==NULL){ //por si el numero de cifras no es el mismo
				if((p2->value+acarreo)>=10){ //condicionando para tener el acarreo
					add_to_list(&psum,(p2->value + acarreo-10)); 
					acarreo=1;	
						}
				else{
					add_to_list(&psum,(p2->value + acarreo));
					acarreo=0;
						}
				p2=p2->next; //solo muevo la lista que aun no esta en NULL
					}
			else if(p2==NULL){
				if((p->value + acarreo)>=10){
					add_to_list(&psum,(p->value + acarreo-10));
					acarreo=1;	
						}
				else{
					add_to_list(&psum,(p->value + acarreo));
					acarreo=0;
						} 
				p=p->next;
					}			
			else{
				if((p->value + p2->value + acarreo)>=10){
					add_to_list(&psum,(p->value + p2->value + acarreo-10));
					acarreo=1;	
						}
				else{
					add_to_list(&psum,(p->value + p2->value + acarreo));
					acarreo=0;
						}
			p= p->next;
			p2=p2->next;
				}
		}
	if(acarreo==1){ add_to_list(&psum,acarreo);}  //si el acarreo es 1, se le agrega primero el 1 a la lista.
	return psum;
}

/**********************************Función que multiplica el valor de las listas********************************************/
struct node *multiplicar_listas(struct node *L, struct node *L2){ //se basa casi lo mismo que la suma
	struct node *p,*p2,*pmul,*presultado;	
	presultado=NULL;
	p=L; p2=L2;
	p2=invertir_valores(L2);
	int acarreo=0;
	int digito=0;
	while(p2!=NULL){
		p=invertir_valores(L);	
		pmul=NULL;
		while(p!=NULL){
			if((p->value*p2->value + acarreo)>=10){
				add_to_list(&pmul,(p->value*p2->value + acarreo-( (int)((p->value*p2->value + acarreo)/10) )*10));
				acarreo=(int)((p->value*p2->value + acarreo)/10);	
			}
			else{
				add_to_list(&pmul,(p->value*p2->value + acarreo));
				acarreo=0;
			}
			p= p->next;
		}		
		if(acarreo>0){ add_to_list(&pmul, acarreo); acarreo=0;}	
		int i;
		if(digito!=0){
			for(i=0;i<digito;i++){ //agrega los ceros
				add_to_end(&pmul,0);
			}
		}
		presultado=sumar_listas(presultado,pmul);
		digito++;
		p2=p2->next;
	}
	return presultado;		
}
