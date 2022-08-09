#include "Funciones.h"

//Funcion que se encarga de ver si el archivo a leer existe o no.
int archivo_existe(char nombre_archivo[]){
    FILE *arch;
	arch = fopen(nombre_archivo,"r");
	if(arch == NULL){	//Si el archivo no existe
		return 0;
	}
    else{
        return 1;       //El archivo si existe retorna 1
    }
}

//Funcion que se encarga de leer un renglon del archivo.
void leer_renglon(char cadena[],FILE *archivo){
	int i = 0;
	char letra;
	while (fscanf(archivo,"%c",&letra) != EOF){		
		if(letra == '\n' || letra == EOF){
			break;
		}
		cadena[i] = letra;
		i++;
	}
	cadena[i] = '\0';
}

//Funcion que se encarga de sacar los tokens del renglon leido anteriormente
void tokens(char instruccion[],char registro_destino[],char registro_origen[],char cadena[]){

	int i=0;

	//Se llena el registro de intruccion
	for(int j=0; j<3; j++){
		
		instruccion[j] = cadena[i];
		i++;
	}
	
	instruccion[3] = '\0'; //Se pone el fin de cadena para evitar basura
	i++;

	//Se llena el registro destino
	for(int j=0 ; j<3 ; j++){

		registro_destino[j] = cadena[i];
		i++;
	}

	registro_destino[3] = '\0'; //Se pone el fin de cadena para evitar basura

	i++;

	// se llena el registro origen si existe
	if(cadena[i] != '\0'){ //Si todavia hay texto lo mete en el registro origen
		int j = 0;
		while(cadena[i] != '\0'){
			registro_origen[j] = cadena[i];
			i++;
			j++;
		}

		registro_origen[j] = '\0'; //Se pone el fin de cadena para evitar basura
	}
}

//Funcion que limpia todos los arreglo esto para eliminar la basura que quedo de la anterior lectura y obtencion de los tokens
void limpiar_arreglo(char cadena[],char instruccion[],char registro_destino[],char registro_origen[]){

	for(int i=0; i<13; i++){
		cadena[i]='\0';	//Se limpia la lectura del renglon anterior
	}

	for(int j=0 ; j < 4 ; j++){
		instruccion[j] = '\0'; //e limpia la intruccion
	}

	for(int j=0 ; j < 4 ; j++){
		registro_destino[j] = '\0'; //Se limpia el registro de destino
	}

	for(int j=0 ; j < 4 ; j++){
		registro_origen[j] = '\0'; //Se limpia el registro de origen
	}
}

/*
Esta función regresa el tipo de instrucción en entero,
por ejemplo si es MOV regresa 1, si es ADD es 2 y asi 
sucesivamente. Regresa 0, si no existe la instrucción
*/
int tipo_instruccion(char instruccion[]){
    if( strcmp(instruccion,"MOV") == 0 ){
        return 1;
    }else if ( strcmp(instruccion,"ADD") == 0 ){
        return 2;
    }else if ( strcmp(instruccion,"SUB") == 0 ){
        return 3;
    }else if ( strcmp(instruccion,"MUL") == 0 ){
        return 4;
    }else if ( strcmp(instruccion,"DIV") == 0 ){
        return 5;
    }else if ( strcmp(instruccion,"INC") == 0 ){
        return 6;
    }else if ( strcmp(instruccion,"DEC") == 0 ){
        return 7;
    }else if ( strcmp(instruccion,"END") == 0 ){
        return 8;
    }else{
        return 0;
    }
}

/*
Esta función regresa un 1 si el registro de entrada es un numero decimal, regresa 0 si no lo es
*/
int esNumero(char registro[]){
    int i = 0;
    int aux = 1;    // variable que supone al principio que es un numero por eso es uno 1

    if( strlen(registro) == 0){     // si el registro esta vacio
        return 0;
    }
    
    while( registro[i] != '\0'){        
        if( isdigit(registro[i]) == 0 ){ //si el caracter no es digito
            if(i == 0){         //si es la primera posición
                if(registro[i] != '-'){     //si no tiene el "-"" guion de negativo
                    aux = 0;
                    return aux;
                }
            }else{
                aux = 0;
                return aux;
            }
        }
        i++;
    }
    return aux; //regreso 1
}

/*
Esta función identifica que tipo de registro es:
    si es numero regresa 0
    si es EAX regresa 1
    si es EBX regresa 2
    si es ECX regresa 3
    si es EDX regresa 4
    si no existe el registro regresa -1
*/
int identificar_registro(char registro[]){
    if( esNumero(registro) == 1 ){  //Si es un número
        return 0;
    }else if ( strcmp(registro,"EAX") == 0){
        return 1;
    }else if ( strcmp(registro,"EBX") == 0){
        return 2;
    }else if ( strcmp(registro,"ECX") == 0){
        return 3;
    }else if ( strcmp(registro,"EDX") == 0){
        return 4;
    }else {
        return -1;
    }
}

//La funcion realiza las operaciones con la intruccion recibida y los registros, si existe un error matematico devuelve un 1
int operaciones(int instruccion,int numreg,int numreg2,int *direcciones_registros[],int esnum){

    switch (instruccion){

    case 1:
        if(esnum == 1)
            *direcciones_registros[numreg-1]=numreg2;
        else
            *direcciones_registros[numreg-1]=*direcciones_registros[numreg2-1];
        break;
    
    case 2:
        if(esnum == 1)
            *direcciones_registros[numreg-1]+=numreg2;
        else
            *direcciones_registros[numreg-1]+=*direcciones_registros[numreg2-1];
        break;

    case 3:
        if(esnum == 1)
            *direcciones_registros[numreg-1]-=numreg2;
        else
            *direcciones_registros[numreg-1]-=*direcciones_registros[numreg2-1];
        break;

    case 4:
        if(esnum == 1)
            *direcciones_registros[numreg-1]*=numreg2;
        else
            *direcciones_registros[numreg-1]*=*direcciones_registros[numreg2-1];
        break;

    case 5:
        if(esnum == 1){
            if(numreg2 == 0)
                return 1;
            else
                *direcciones_registros[numreg-1]/=numreg2;
        }

        else{
            if(*direcciones_registros[numreg2-1] == 0)
                return 1;
            else
                *direcciones_registros[numreg-1]/=*direcciones_registros[numreg2-1];
        }
        break;

    case 6:
        *direcciones_registros[numreg-1]+=1;
        break;

    case 7:
        *direcciones_registros[numreg-1]-=1;
        break;
    
    default:
        break;
    }

    return 0;
}

//La función regresa un 1 si esta correcta el renglon, y cero si no lo esta.
int renglonCorrecto(char renglon[]){
    if( renglon[3] == '\0') //si ya no hay nada despues de la posicion 3, esta bien
        return 1;

    if( renglon[3] != ' ' )      //si la posición 3 del renglón no tiene espacio
        return 0;       //esta mal        
    else{
        if( renglon[7] != ','){// || renglon[7] != '\0')     // si la posición 7 del arreglo no la coma ',' 
            if(renglon[7] != '\0')                  // y si la posicion 7 no es el caracter nulo
                return 0;                           //esta mal
        }
    }
    return 1;           //si no se cumple algun error, esta bien.
}

int vector_obtener_valores(int vector[],char cadena[]){		//regresa 1 si se realizo exitosamente y un cero si ocurrio un error
	int  i = 4;			//apuntador a la cadena
	int j = 0;			// apuntador al vector
	char vector_cadena[15];

	while( cadena[i] != '-' && cadena[i] != '\0'){
		vector_cadena[j] = cadena[i];
		i++;
		j++;
	}
	vector_cadena[j] = '\0';

	if(esNumero(vector_cadena) == 1){
		vector[0] = atoi(vector_cadena);
	}else{
		if(vector_cadena[0] != '\0')
			mvprintw(31,0,"\"%s\" No es un número", vector_cadena);
		return 0;
	}


	i++;
	j = 0;
	while( cadena[i] != '-' && cadena[i] != '\0'){
		vector_cadena[j] = cadena[i];
		i++;
		j++;
	}
	vector_cadena[j] = '\0';

	if(esNumero(vector_cadena) == 1){
		vector[1] = atoi(vector_cadena);
	}else{
		if(vector_cadena[0] != '\0')
			mvprintw(31,0,"\"%s\" No es un número", vector_cadena);
		return 0;
	}

	i++;
	j = 0;
	while( cadena[i] != '-' && cadena[i] != '\0'){
		vector_cadena[j] = cadena[i];
		i++;
		j++;
	}
	vector_cadena[j] = '\0';

	if(esNumero(vector_cadena) == 1){
		vector[2] = atoi(vector_cadena);
	}else{
		if(vector_cadena[0] != '\0')
			mvprintw(31,0,"\"%s\" No es un número", vector_cadena);
		return 0;
	}

	i++;
	j = 0;
	while( cadena[i] != '-' && cadena[i] != '\0'){
		vector_cadena[j] = cadena[i];
		i++;
		j++;
	}
	vector_cadena[j] = '\0';

	if(esNumero(vector_cadena) == 1){
		vector[3] = atoi(vector_cadena);
	}else{
		if(vector_cadena[0] != '\0')
			mvprintw(31,0,"\"%s\" No es un número", vector_cadena);
		return 0;
	}

	if(cadena[i] != '\0'){		//si ya se obtieron los 4 valores pero hay mas, entonces
		mvprintw(31,0,"Se especificaron mas valores");
		return 0;
	}
	return 1;
}

void copiar_vector(int salida[], int entrada[]){
    int i = 0;
    while(i < 4){
        salida[i] = entrada[i];
        i++;
    }
}

void desmarcar_procesos(PCB **estado){
	PCB *proceso = *estado;
	PCB *cabeza = proceso;		//apunta a la cabeza
	while(proceso != NULL){
		proceso->marcado = 0;
		proceso = proceso->next;
	}
	proceso = cabeza;
	*estado = proceso;
}

PCB *encontrar_proceso_valido(PCB **estado){
	PCB *actual = *estado;
	PCB *cabeza = actual;

	while(actual != NULL){
		if(actual->marcado ==0){
			if( actual->NECESIDAD[0] <= DISPONIBLES[0] &&
				actual->NECESIDAD[1] <= DISPONIBLES[1] &&
				actual->NECESIDAD[2] <= DISPONIBLES[2] &&
				actual->NECESIDAD[3] <= DISPONIBLES[3]
			){
				actual->marcado = 1;			//lo marco
				*estado = cabeza;
				return actual;
			}
		}
		actual = actual->next;
	}
	*estado = cabeza;
	return NULL;
}

int todos_marcados(PCB *estado){			//1 si todos estan marcados, 0 si hay alguno que no esta marcado
	if(estado != NULL){
		if(estado->marcado == 0){
			return 0;
		}
		estado = estado->next;
	}
	return 1;
}


int banquero(PCB **actual){			//1 si es posible asignar el proceso, 0 no es posible asignar el proceso
	PCB *proceso = *actual;
	int asig_buffer[4];
	int nec_buffer[4];
	int disp_buffer[4];

	if( proceso->NECESIDAD[0] >= proceso->PETICION[0] &&
		proceso->NECESIDAD[1] >= proceso->PETICION[1] &&
		proceso->NECESIDAD[2] >= proceso->PETICION[2] &&
		proceso->NECESIDAD[3] >= proceso->PETICION[3] ){

		if( proceso->PETICION[0] <= DISPONIBLES[0] &&
			proceso->PETICION[1] <= DISPONIBLES[1] &&
			proceso->PETICION[2] <= DISPONIBLES[2] &&
			proceso->PETICION[3] <= DISPONIBLES[3] ){

			copiar_vector(asig_buffer,proceso->ASIGNADOS);
			copiar_vector(nec_buffer,proceso->NECESIDAD);
			copiar_vector(disp_buffer,DISPONIBLES);

			proceso->ASIGNADOS[0] = proceso->ASIGNADOS[0] + proceso->PETICION[0];
			proceso->ASIGNADOS[1] = proceso->ASIGNADOS[1] + proceso->PETICION[1];
			proceso->ASIGNADOS[2] = proceso->ASIGNADOS[2] + proceso->PETICION[2];
			proceso->ASIGNADOS[3] = proceso->ASIGNADOS[3] + proceso->PETICION[3];

			proceso->NECESIDAD[0] = proceso->MAXIMO[0] - proceso->ASIGNADOS[0];
			proceso->NECESIDAD[1] = proceso->MAXIMO[1] - proceso->ASIGNADOS[1];
			proceso->NECESIDAD[2] = proceso->MAXIMO[2] - proceso->ASIGNADOS[2];
			proceso->NECESIDAD[3] = proceso->MAXIMO[3] - proceso->ASIGNADOS[3];

			DISPONIBLES[0] = DISPONIBLES[0] - proceso->PETICION[0];
			DISPONIBLES[1] = DISPONIBLES[1] - proceso->PETICION[1];
			DISPONIBLES[2] = DISPONIBLES[2] - proceso->PETICION[2];
			DISPONIBLES[3] = DISPONIBLES[3] - proceso->PETICION[3];

			desmarcar_procesos(&EJECUCION);
			desmarcar_procesos(&LISTOS);
			desmarcar_procesos(&SUSPENDIDOS);
			desmarcar_procesos(&BLOQUEADOS);

			PCB *obt_eje, *obt_lis, *obt_susp, *obt_blo;

			while(1){
				while(1){
					obt_eje = encontrar_proceso_valido(&EJECUCION);
					if(obt_eje != NULL){
						DISPONIBLES[0] = DISPONIBLES[0] + obt_eje->ASIGNADOS[0];
						DISPONIBLES[1] = DISPONIBLES[1] + obt_eje->ASIGNADOS[1];
						DISPONIBLES[2] = DISPONIBLES[2] + obt_eje->ASIGNADOS[2];
						DISPONIBLES[3] = DISPONIBLES[3] + obt_eje->ASIGNADOS[3];
						break;
					}

					obt_lis = encontrar_proceso_valido(&LISTOS);

					if(obt_lis != NULL){
						DISPONIBLES[0] = DISPONIBLES[0] + obt_lis->ASIGNADOS[0];
						DISPONIBLES[1] = DISPONIBLES[1] + obt_lis->ASIGNADOS[1];
						DISPONIBLES[2] = DISPONIBLES[2] + obt_lis->ASIGNADOS[2];
						DISPONIBLES[3] = DISPONIBLES[3] + obt_lis->ASIGNADOS[3];
						break;
					}

					obt_susp = encontrar_proceso_valido(&SUSPENDIDOS);

					if(obt_susp != NULL){
						DISPONIBLES[0] = DISPONIBLES[0] + obt_susp->ASIGNADOS[0];
						DISPONIBLES[1] = DISPONIBLES[1] + obt_susp->ASIGNADOS[1];
						DISPONIBLES[2] = DISPONIBLES[2] + obt_susp->ASIGNADOS[2];
						DISPONIBLES[3] = DISPONIBLES[3] + obt_susp->ASIGNADOS[3];
						break;
					}

					obt_blo = encontrar_proceso_valido(&BLOQUEADOS);

					if(obt_blo != NULL){
						DISPONIBLES[0] = DISPONIBLES[0] + obt_blo->ASIGNADOS[0];
						DISPONIBLES[1] = DISPONIBLES[1] + obt_blo->ASIGNADOS[1];
						DISPONIBLES[2] = DISPONIBLES[2] + obt_blo->ASIGNADOS[2];
						DISPONIBLES[3] = DISPONIBLES[3] + obt_blo->ASIGNADOS[3];
						break;
					}
					break;
				}
			
				if(obt_eje == NULL && obt_lis == NULL && obt_susp == NULL && obt_blo == NULL)
					break;
			}

			if(todos_marcados(EJECUCION) == 1 && todos_marcados(LISTOS) == 1 && todos_marcados(SUSPENDIDOS) == 1 && todos_marcados(BLOQUEADOS) == 1){
				copiar_vector(DISPONIBLES, disp_buffer);
				DISPONIBLES[0] = DISPONIBLES[0] - proceso->PETICION[0];
				DISPONIBLES[1] = DISPONIBLES[1] - proceso->PETICION[1];
				DISPONIBLES[2] = DISPONIBLES[2] - proceso->PETICION[2];
				DISPONIBLES[3] = DISPONIBLES[3] - proceso->PETICION[3];

				proceso->PETICION[0] = 0;
				proceso->PETICION[1] = 0;
				proceso->PETICION[2] = 0;
				proceso->PETICION[3] = 0;

				return 1;
			}else{
				copiar_vector(DISPONIBLES, disp_buffer);
				copiar_vector(proceso->ASIGNADOS, asig_buffer);
				copiar_vector(proceso->NECESIDAD, nec_buffer);
				return 0;
			}
			
		}else{
			return  0;
		}
		



	}else{
		return -1;
	}
}

void verificar_suspendidos(){
	PCB *actual = NULL;
	PCB *anterior = NULL;
	actual = SUSPENDIDOS;
	int bandera_ban;
	if(actual == NULL){
		SUSPENDIDOS = NULL;
	}else{
		while (actual != NULL){
			bandera_ban = banquero(&actual);
			if( bandera_ban == 1){		//si es posible asignar el proceso a la cabeza de la lista
			
				SUSPENDIDOS = actual->next;

				insertar_proceso(&LISTOS,&actual);
				actual = SUSPENDIDOS;
			}else if(bandera_ban == 0){
				actual = SUSPENDIDOS->next;
				anterior = SUSPENDIDOS;
				while(actual != NULL){
					bandera_ban = banquero(&actual);
					if( banquero(&actual) == 1){		//si es posible asignar el proceso entre en medio de la lista
						anterior->next = actual->next;
						insertar_proceso(&LISTOS,&actual);
						actual = anterior->next;
					}else if(bandera_ban == 0){
						actual = actual->next;
						anterior = anterior->next;
					}
				}
			}	
		}
		
	}
}


void liberar_recursos(PCB **actual){
	PCB *proceso = *actual;
	DISPONIBLES[0] = DISPONIBLES[0] + proceso->ASIGNADOS[0];
	DISPONIBLES[1] = DISPONIBLES[1] + proceso->ASIGNADOS[1];
	DISPONIBLES[2] = DISPONIBLES[2] + proceso->ASIGNADOS[2];
	DISPONIBLES[3] = DISPONIBLES[3] + proceso->ASIGNADOS[3];

	proceso->ASIGNADOS[0] = 0;
	proceso->ASIGNADOS[1] = 0;
	proceso->ASIGNADOS[2] = 0;
	proceso->ASIGNADOS[3] = 0;

	proceso->NECESIDAD[0] = proceso->MAXIMO[0] - proceso->ASIGNADOS[0];
	proceso->NECESIDAD[1] = proceso->MAXIMO[1] - proceso->ASIGNADOS[1];
	proceso->NECESIDAD[2] = proceso->MAXIMO[2] - proceso->ASIGNADOS[2];
	proceso->NECESIDAD[3] = proceso->MAXIMO[3] - proceso->ASIGNADOS[3];

}

int ins_free(PCB **actual, int v[]){
	PCB *proceso = *actual;
	if( v[0] <= proceso->ASIGNADOS[0] &&
		v[1] <= proceso->ASIGNADOS[1] &&
		v[2] <= proceso->ASIGNADOS[2] &&
		v[3] <= proceso->ASIGNADOS[3] ){			//si quiere liberar mas recursos de los que tiene

		DISPONIBLES[0] = DISPONIBLES[0] + v[0];
		DISPONIBLES[1] = DISPONIBLES[1] + v[1];
		DISPONIBLES[2] = DISPONIBLES[2] + v[2];
		DISPONIBLES[3] = DISPONIBLES[3] + v[3];

		proceso->ASIGNADOS[0] = proceso->ASIGNADOS[0] - v[0];
		proceso->ASIGNADOS[1] = proceso->ASIGNADOS[1] - v[1];
		proceso->ASIGNADOS[2] = proceso->ASIGNADOS[2] - v[2];
		proceso->ASIGNADOS[3] = proceso->ASIGNADOS[3] - v[3];

		proceso->NECESIDAD[0] = proceso->MAXIMO[0] - proceso->ASIGNADOS[0];
		proceso->NECESIDAD[1] = proceso->MAXIMO[1] - proceso->ASIGNADOS[1];
		proceso->NECESIDAD[2] = proceso->MAXIMO[2] - proceso->ASIGNADOS[2];
		proceso->NECESIDAD[3] = proceso->MAXIMO[3] - proceso->ASIGNADOS[3];
		return 1;
		
	}

	mvprintw(31,0,"El proceso %d quiere liberar mas recursos de los que tiene.",proceso->pid);
	guardar_contexto(proceso);
	liberarRAM(&proceso);
	liberarSWAP(&proceso);
	liberar_recursos(&proceso);
	insertar_proceso(&TERMINADOS,&proceso);
    revisar_nuevos(&NUEVOS,&LISTOS);
	*actual = proceso;
	return 0;
	
}

int token_memoria(char IR[],char instruccion[]){

    unsigned int v[4];


    if(IR[3] != ' '){
        if(strcmp(IR,"END") == 0){
            return 0;
        }
        mvprintw(31,0,"Error en la intruccion %s",IR);
        return 2; //Retorno de dos por que la instrucciojn esta mal formada
    }
    else{

        for(int i=0; i < 3; i++){

            instruccion[i] = IR[i];
        }

        instruccion[3]='\0';

       /* if(PC == 1 && strcmp(instruccion,"MAX") !=  0 ){
        	mvprintw(31,0,"El proceso %d no es valido porque no se especifico los recuros maximos que usará",EJECUCION->pid);
        	guardar_contexto(EJECUCION);
        	insertar_proceso(&TERMINADOS,&EJECUCION);
        	verificar_suspendidos();
        	return 1;
        }*/

        //Esta parte se verifica que comando es
        if(strcmp(instruccion,"GET") == 0){

            if(vector_obtener_valores(v,IR) == 0){

                mvprintw(31,0,"Error en la intruccion %s",IR);
                return 2; //Retorno de dos por que la instrucciojn esta mal formada
            }

            copiar_vector(EJECUCION->PETICION,v);

            int bandera_ban = banquero(&EJECUCION);
            if(bandera_ban == 0){
            	PC++;
            	guardar_contexto(EJECUCION);
				insertar_proceso(&SUSPENDIDOS,&EJECUCION);
            }else if(bandera_ban == -1){
            	mvprintw(31,0,"EL proceso %d esta solicitando mas recursos de los que necesita",EJECUCION->pid);
            	
            	guardar_contexto(EJECUCION);
            	liberarRAM(&EJECUCION);
            	liberarSWAP(&EJECUCION);
            	liberar_recursos(&EJECUCION);
				insertar_proceso(&TERMINADOS,&EJECUCION);
				verificar_suspendidos();
                revisar_nuevos(&NUEVOS,&LISTOS);

            }
            return 1;
        }
        
        else if(strcmp(instruccion,"MAX") == 0){

        	
        		mvprintw(31,0,"El proceso %d volvio a usar la instruccion Max",EJECUCION->pid);
        		guardar_contexto(EJECUCION);
        		liberarRAM(&EJECUCION);
        		liberarSWAP(&EJECUCION);
            	liberar_recursos(&EJECUCION);
				insertar_proceso(&TERMINADOS,&EJECUCION);
				verificar_suspendidos();
                revisar_nuevos(&NUEVOS,&LISTOS);
				return 1;
        }

        else if(strcmp(instruccion,"USE") == 0){
            
            if(vector_obtener_valores(v,IR) == 0){
                
                mvprintw(31,0,"Error en la intruccion %s",IR);
                return 2; //Retorno de dos por que la instrucciojn esta mal formada
            }

            tiempo = time(NULL);
            tiempo_general = localtime(&tiempo);
            hora_actual=(tiempo_general->tm_hour*3600)+(tiempo_general->tm_min*60)+tiempo_general->tm_sec;

            if( v[0] == 0 &&
            	v[1] == 0 &&
            	v[2] == 0 &&
            	v[3] == 0
            	){
            	
            }else if( 
            	v[0] <= EJECUCION->ASIGNADOS[0] &&
            	v[1] <= EJECUCION->ASIGNADOS[1] &&
            	v[2] <= EJECUCION->ASIGNADOS[2] &&
            	v[3] <= EJECUCION->ASIGNADOS[3] ){
            	PC++;
                numero_bloqueado = 5 + rand()%(10-5+1);
                //mvprintw(26,0,"%d",numero_bloqueado);
            	guardar_contexto(EJECUCION);
            	insertar_proceso(&BLOQUEADOS,&EJECUCION);

            }else{
            	liberar_recursos(&EJECUCION);
            	liberarRAM(&EJECUCION);
            	liberarSWAP(&EJECUCION);
            	guardar_contexto(EJECUCION);
            	mvprintw(31,0,"EL proceso %d quiere usar mas recursos de los que tiene asignados.",EJECUCION->pid);
            	insertar_proceso(&TERMINADOS,&EJECUCION);
            	verificar_suspendidos();
                revisar_nuevos(&NUEVOS,&LISTOS);
            }

            return 1;
        }

        else if(strcmp(instruccion,"FRE") == 0){
            
            if(vector_obtener_valores(v,IR) == 0){

                mvprintw(31,0,"Error en la intruccion %s",IR);
                return 2; //Retorno de dos por que la instrucciojn esta mal formada
            }

            ins_free(&EJECUCION,v);

            verificar_suspendidos();

            return 1;
        }
        
        else{
            return 0;//Se retorna 0 si la instruccion no es ninguna de asignar memoria
        }
    }
}

int revisar_bloqueados(struct PCB **bloqueados, struct PCB **listos){

    struct PCB *siguiente = NULL,*anterior = NULL;

    siguiente = *bloqueados;

    if(*bloqueados != NULL) {

        tiempo = time(NULL);

        tiempo_general = localtime(&tiempo);

        hora_actual = (tiempo_general->tm_hour*3600)+(tiempo_general->tm_min*60)+tiempo_general->tm_sec;

        if((hora_actual - siguiente->hora_bloqueados) >= siguiente->tiempo_bloqueado){

            *bloqueados = siguiente->next;

            insertar_proceso(listos,&siguiente);
        }

        anterior = * bloqueados;
        if(anterior != NULL){

            siguiente = anterior->next;

            for(; siguiente!= NULL;){

                tiempo = time(NULL);

                tiempo_general = localtime(&tiempo);

                hora_actual = (tiempo_general->tm_hour*3600)+(tiempo_general->tm_min*60)+tiempo_general->tm_sec;

                if((hora_actual - siguiente->hora_bloqueados) >= siguiente->tiempo_bloqueado){

                    //mvprintw(33,0,"tiempo actual=%d\ntiempobloqueo=%d\nsegundosnloqueado=%d\n",hora_actual,ayuda->hora_bloqueados,ayuda->tiempo_bloqueado);

                    anterior->next = siguiente->next;

                    insertar_proceso(listos,&siguiente);

                    siguiente = anterior->next;
                }

                else{
                    siguiente=siguiente->next;
                    anterior=anterior->next;
                }

            }
        }
        
    }
}

int ejecutar_linea(PCB **proceso){        //regresa 1 si termino con exito, -1 si se mato el proceso, regresa 0 si ocurrio un error y 2 si se realizo la ejecución de manera correcta
	//Registros de datos
	char instruccion[4],registro_destino[4],registro_origen[7],teclado[10];
    int tipo,esnum=0,error_mate=0;
    int tipo_registro=0,tipo_registro2=0;
    int *direcciones_registros[4] = {&EAX,&EBX,&ECX,&EDX};

    PCB *ap_proceso = *proceso;

    error_mate=0;
    esnum=0;
    tipo = 0;
    limpiar_arreglo(IR,instruccion,registro_destino,registro_origen); //Se limpia la basura de los arreglos de la anterior lectura


    //obtener siguiente instrucción IR, PC
    traer_instruccion(PC,IR,&ap_proceso);
    *proceso = ap_proceso;
    //eer_renglon(IR,archivo); //Se lee un renglon del txt


    //Se imprime los datos
    mvprintw(1,0,"PC\t\t\tIR\t\t\tEAX\t\t\tEBX\t\t\tECX\t\t\tEDX\n");
    mvprintw(2,0,"------------------------------------------------------------------------------------------------------------------------------\n\n");
    mvprintw(3,0,"%d\t\t\t%s\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n\n", PC,IR,EAX,EBX,ECX,EDX);
    refresh();

    if(strlen(IR) == 0){
    	mvprintw(31,0,"La IR esta vacia");
    	return 1;
    }

    if(strcmp(IR, "\0") == 0){	// si ya termino de leer el archivo
                return 1;			//rompo el ciclo
    }

    if( jnz_token(IR,instruccion) ==  1){
    	if(EJECUCION == NULL){
    		return 3;				//el proceso se bloqueo o se suspendio
    	}
    	return 2;
    }

    int bandera_recurso = token_memoria(IR,instruccion);
   if(bandera_recurso == 2){
       return 0;
   }
   else if(bandera_recurso == 1){
       PC++;
       if(EJECUCION == NULL){
       		return 3;				//el proceso se bloqueo o se suspendio
       }
       return 2;
   }

    tokens(instruccion,registro_destino,registro_origen,IR); //Se crean los tokens (instruccion,registro destino y registro origen)
    tipo = tipo_instruccion(instruccion);   //Se analiza que tipo de intruccion que es y devuelve un valor entero

    if( tipo == 0 ){    //Si no existe la instrucción
        mvprintw(31,0,"La instruccion \"%s\" no existe\n", instruccion);
        refresh();
        return 0;
    }

    if(tipo == 8){     //Si la instrucccion es END se termina las ejecucion de ese archivo
        if( strlen(registro_destino) != 0 || strlen(registro_origen) != 0){  // si los registros no estan vacios
            mvprintw(31,0,"Intruccion mal formada \"%s\"\n",IR);
            refresh();
        }else{
            refresh();
            PC++;
        }
        return 1;
    }

    if((tipo == 6 || tipo == 7) && strlen(registro_origen) != 0){ //Si en las instrucciones "INC" o "DEC" y eciste un registro origen
        mvprintw(31,0,"Instruccion mal formada \"%s\"\n",IR);
        refresh();
        return 0;
    }

    if((tipo == 6 || tipo == 7) && strlen(registro_destino) == 0){ //Si en las instrucciones "INC" o "DEC" y no existe registro de destino
        mvprintw(31,0,"Instruccion mal formada \"%s\"\n",IR);
        refresh();
        return 0;
    }


    //agrege este error
    if((tipo == 1 || tipo == 2 || tipo == 3 || tipo == 4 || tipo == 5) && strlen(registro_origen) == 0 ){ //Si en las instrucciones "INC" o "DEC" y eciste un registro origen
        mvprintw(31,0,"Instruccion mal formada \"%s\"\n",IR);
        refresh();
        return 0;
    }

    tipo_registro = identificar_registro(registro_destino); //Se identifica que registro es el registro destino

    if(tipo_registro == -1 || tipo_registro == 0) {    //Si el registro origen no existe o es un numero se lanza un error y termina el programa
        mvprintw(31,0,"El registro de destino no exite o es un numero\n",tipo_registro);
        refresh();
        return 0;
    }

    tipo_registro2= identificar_registro(registro_origen); //Se identifica que registro es el registro origen


    if(tipo_registro2 == 0){    //Se analiza si el registro origen es un numero y asi se manda a hacer la operaciones como un numero 
        tipo_registro2 = atoi(registro_origen);
        esnum=1;
    }

    else if(tipo_registro2 == -1 && strlen(registro_origen) != 0){  //Se analiza si el registro origen no existe
        mvprintw(31,0,"El registro no existe\n");
        refresh();
        return 0;
    }

    //agregue este error, Opinio que se evuale aqui para que primero detecte si la instruccion y registros existen 
    if (renglonCorrecto(IR) == 0){
        mvprintw(31,0,"La instruccion \"%s\" no existe o no hay una coma \",\" entre el R1 y R2\n",IR);
        refresh();
        return 0;
    }

    error_mate=operaciones(tipo,tipo_registro,tipo_registro2,direcciones_registros,esnum); //Se realiza la operacion dada con la intruccion y sus registros

    if(error_mate == 1){    //Si existio un error matematico en las operaciones imprime un error y termina la ejecucion
        mvprintw(31,0,"Ocurrio un error matematico (division entre cero)\n");
        refresh();
        return 0;
    }
    PC++; 
    return 2;
}

/*
 Regresa: 	1 si hay un teclazo pendiente por capturar
 		0 en caso contrario
*/
int kbhit(void) 
{
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);

    if (select(1, &read_fd, NULL, NULL, &tv) == -1)
        return 0;

    if (FD_ISSET(0, &read_fd))
        return 1;

    return 0;
}

//metodos de la lista
void crear_proceso(int pid,char nombre_archivo[],FILE *archivo,struct PCB **cola_procesos){

    struct PCB *proceso =NULL,*recorrer = NULL; 
    proceso = malloc(sizeof(struct PCB));
    /*
        Aqui se llenan todos los datos para crear el nodo
    */
    int v[4]={0,0,0,0};
    proceso->pid = pid;
    memset(proceso->IR,'\0',50);
    strcpy(proceso->nombre_archivo,nombre_archivo);
    proceso->PC = 0;
    proceso->EAX = 0;
    proceso->EBX = 0;
    proceso->ECX = 0;
    proceso->EDX = 0;
    //proceso->archivo = archivo;
    copiar_vector(proceso->MAXIMO,v);
    copiar_vector(proceso->NECESIDAD,v);
    copiar_vector(proceso->ASIGNADOS,v);
    copiar_vector(proceso->PETICION,v);
    proceso->marcado = 0;
    proceso->next = NULL;

    if( *cola_procesos == NULL ){
        *cola_procesos = proceso;
    }

    else{
        /*
        Se recorre toda la lista para que se pueda insertar el nuevo nodo creado
        */
        for( recorrer = *cola_procesos ; recorrer != NULL ; recorrer = recorrer->next ){
            if(recorrer->next == NULL){
                recorrer->next = proceso;
                //mvprintw(10,0,"njskjdshkasdhkadshdsl");
                break;
            }
        }
    }  
}

void imprimir(struct PCB *cola_procesos){
    struct PCB *recorrer = NULL;
    int h=5;
   // mvprintw(h,0,"%d\n%d\n%d\n%d\n%d\n%d\n\n",cola_procesos->pid,cola_procesos->PC,cola_procesos->EAX,cola_procesos->EBX,cola_procesos->ECX,cola_procesos->EDX);
    for( recorrer = cola_procesos ; recorrer != NULL ; recorrer = recorrer->next ){
        printw("\t%8d\t%10s\t%5d\t%15s\t%5d\t%5d\t%5d\t%5d\t",recorrer->pid,recorrer->nombre_archivo ,recorrer->PC,recorrer->IR,recorrer->EAX,recorrer->EBX,recorrer->ECX,recorrer->EDX);
        int i = 0;
        for (int i = 0; i < 4; i++){
            printw("%d",recorrer->MAXIMO[i]);
            if(i < 3)
                printw(",");
        }
        printw("   ");
        for (int i = 0; i < 4; i++){
            printw("%d",recorrer->NECESIDAD[i]);
            if(i < 3)
                printw(",");
        }
        printw("    ");
        for (int i = 0; i < 4; i++){
            printw("%d",recorrer->ASIGNADOS[i]);
            if(i < 3)
                printw(",");
        }
        printw("   ");
        for (int i = 0; i < 4; i++){
            printw("%d",recorrer->PETICION[i]);
            if(i < 3)
                printw(",");
        }
		printw("         ");
		printw("%d",recorrer->no_paginas);
        printw("\n");          
    }
}

void imprimir_ejecucion(struct PCB *cola_procesos){
    struct PCB *recorrer = NULL;
    int h=5;
   // mvprintw(h,0,"%d\n%d\n%d\n%d\n%d\n%d\n\n",cola_procesos->pid,cola_procesos->PC,cola_procesos->EAX,cola_procesos->EBX,cola_procesos->ECX,cola_procesos->EDX);
    for( recorrer = cola_procesos ; recorrer != NULL ; recorrer = recorrer->next ){
            printw("\t%8d\t%10s\t%5s\t%15s\t%5s\t%5s\t%5s\t%5s\t",recorrer->pid,recorrer->nombre_archivo ,"-","-","-","-","-","-");
            int i = 0;
            for (int i = 0; i < 4; i++){
                printw("%d",recorrer->MAXIMO[i]);
                if(i < 3)
                    printw(",");
            }
            printw("   ");
            for (int i = 0; i < 4; i++){
                printw("%d",recorrer->NECESIDAD[i]);
                if(i < 3)
                    printw(",");
            }
            printw("    ");
            for (int i = 0; i < 4; i++){
                printw("%d",recorrer->ASIGNADOS[i]);
                if(i < 3)
                    printw(",");
            }
            printw("   ");
            for (int i = 0; i < 4; i++){
                printw("%d",recorrer->PETICION[i]);
                if(i < 3)
                    printw(",");
            }
			printw("         ");
			printw("%d",recorrer->no_paginas);
            printw("\n");

        }  
}

void inicializa_lista(PCB **lista){
    *lista = NULL;
}

PCB *crear_nodo(){
    PCB *nuevo = NULL;
    nuevo = malloc(sizeof(struct PCB));
    nuevo->next = NULL;
    return nuevo;
}


void insertar_proceso(PCB **lista, PCB **ent){
	PCB *entrada = *ent; 
    PCB *recorrer = NULL;
    if(entrada != NULL){
        PCB *nuevo = crear_nodo();
        nuevo->pid = entrada->pid;
        strcpy(nuevo->nombre_archivo, entrada->nombre_archivo);
        nuevo->PC = entrada->PC;
        strcpy(nuevo->IR,entrada->IR);        //pon 13 en lugar de TR, si vas hacer pruebas en otros archivos
        nuevo->EAX = entrada->EAX;
        nuevo->EBX = entrada->EBX;
        nuevo->ECX = entrada->ECX;
        nuevo->EDX = entrada->EDX;
        //nuevo->archivo = entrada->archivo;
        nuevo->hora_bloqueados=hora_actual;
        nuevo->tiempo_bloqueado=entrada->tiempo_bloqueado;
        copiar_vector(nuevo->MAXIMO, entrada->MAXIMO);
        copiar_vector(nuevo->NECESIDAD, entrada->NECESIDAD);
        copiar_vector(nuevo->ASIGNADOS, entrada->ASIGNADOS);
        copiar_vector(nuevo->PETICION, entrada->PETICION);
        nuevo->marcado = entrada->marcado;
    	nuevo->no_paginas = entrada->no_paginas;
    	nuevo->no_inst = entrada->no_inst;
        nuevo->tmp = malloc(sizeof(TMP)*nuevo->no_paginas);
        nuevo->tmp = entrada->tmp;

        if( *lista == NULL ){
            *lista = nuevo;
        }

        else{
            for( recorrer = *lista ; recorrer != NULL ; recorrer = recorrer->next ){
                if(recorrer->next == NULL){
                    recorrer->next = nuevo;
                    break;
                }
            }
        }
        //limpiando nodo
        free(entrada);  
        inicializa_lista(&entrada);
        *ent = entrada;
    }
}

PCB *obtener_frente(PCB **lista){
    PCB *frente;
    frente = *lista;
    if(frente == NULL){
        return NULL;
    }
    else{
        *lista = frente->next;
        frente->next = NULL;
        return frente;
    }

}


void restaurar_contexto(PCB *proceso){
    PID = proceso->pid;
    PC = proceso->PC;
    EAX = proceso->EAX;
    EBX = proceso->EBX; 
    ECX = proceso->ECX;
    EDX = proceso->EDX;
    strcpy(IR,proceso->IR);
}

void guardar_contexto(PCB *proceso){
    proceso->pid = PID;
    proceso->PC = PC;
    proceso->EAX = EAX;
    proceso->EBX = EBX; 
    proceso->ECX = ECX;
    proceso->EDX = EDX ;
    proceso->hora_bloqueados=hora_actual;
    proceso->tiempo_bloqueado = numero_bloqueado;
    strcpy(proceso->IR, IR);
}

void imprimirMonitor(){
    mvprintw(10,0,"%s%10s\t%10s\t%5s\t%15s\t%5s\t%5s\t%5s\t%5s\tMAXIMO%12s%12s%10s%13s\n","Estado","PID","nombre_archivo","PC","IR","EAX","EBX","ECX","EDX","NECESIDAD","ASIGNADOS","PETICION","No.Paginas");
    printw("%s\n","EJECUCION");
    imprimir_ejecucion(EJECUCION);
    printw("\n");
    printw("%s\n","LISTOS");
    imprimir(LISTOS);
    printw("\n");
    printw("%s\n","SUSPENDIDOS");
    imprimir(SUSPENDIDOS);
    printw("\n");
    printw("%s\n","BLOQUEADOS");
    imprimir(BLOQUEADOS);
    printw("\n");
    printw("%s\n","NUEVOS");
    imprimir(NUEVOS);
    printw("\n");
    printw("%s\n","TERMINADOS");
    imprimir(TERMINADOS);
    printw("\n");
    
	mvprintw(26,0,"LRU:");
    mvprintw(30,0,"Errores:");
    mvprintw(30,110,"Recursos:\n");
    mvprintw(31,110,"TOTALES:\t\t");
    int i = 0;
    for (int i = 0; i < 4; i++){
        printw("%d",TOTALES[i]);
        if(i < 3)
            printw(",");
    }   printw("\n");

    mvprintw(32,110,"DISPONIBLES:\t");
    i = 0;
    for (int i = 0; i < 4; i++){
        printw("%d",DISPONIBLES[i]);
        if(i < 3)
            printw(",");
    }   printw("\n");

	mvprintw(34,60,"TMM");
	mvprintw(35,45,"Indice  PID dueño  Asignado");
	for(int z=0; z < 16; z++){
		mvprintw(37,z*8,"%d %d %d",z,tmm[z].pid_dueno,tmm[z].asignado);
	}
    mvprintw(26,110,"Fallos de pag: %d\n",fallos_pag);
    mvprintw(27,110,"Libre en swap: %d\n",libre_swap);
    mvprintw(28,110,"Libre en la RAM:%d\n",libre_RAM);
    
	imprimeLRU(LRU);
    
}

int mata_ejecucion(PCB *ejecucion,PCB **terminados,char argumento[]){

    PCB *puntero = NULL;

    puntero = EJECUCION;

    if(ejecucion == NULL){
        return 0;
    }
    else{
        if( atoi(argumento) == puntero->pid ){
        	guardar_contexto(EJECUCION);
        	liberarRAM(&EJECUCION);
        	liberarSWAP(&EJECUCION);
        	liberar_recursos(&EJECUCION);
        	insertar_proceso(&TERMINADOS,&EJECUCION);
        	verificar_suspendidos();
            revisar_nuevos(&NUEVOS,&LISTOS);
            return 1;
        }
        else{
            return 0;
        } 
    }
}

int mata_listos(PCB **listos, PCB **terminados,char argumento[]){

    PCB *anterior=NULL,*siguiente=NULL;

    siguiente = *listos;
    
    if(*listos == NULL){
        return 0;
    }

    else{
        
        if(siguiente->pid == atoi(argumento)){
            *listos = siguiente->next;
            liberar_recursos(&siguiente);
            liberarRAM(&siguiente);
        	liberarSWAP(&siguiente);
            insertar_proceso(terminados,&siguiente);
            verificar_suspendidos();
            revisar_nuevos(&NUEVOS,&LISTOS);
            return 1;
        }
        else{
            anterior = *listos;
            siguiente = siguiente->next;
            for( ;siguiente != NULL; siguiente = siguiente->next){
                if(siguiente->pid == atoi(argumento)){
                    anterior->next = siguiente->next;

                    liberar_recursos(&siguiente);
                    liberarRAM(&siguiente);
                    liberarSWAP(&siguiente);
                    insertar_proceso(terminados,&siguiente);
                    verificar_suspendidos();
                    revisar_nuevos(&NUEVOS,&LISTOS);
                    return 1;
                }
                anterior = anterior->next;
            }
            return 0;
        }
    }
}

int mata_nuevos(PCB **listos, PCB **terminados,char argumento[]){

    PCB *anterior=NULL,*siguiente=NULL;

    siguiente = *listos;
    
    if(*listos == NULL){
        return 0;
    }

    else{
        
        if(siguiente->pid == atoi(argumento)){
            *listos = siguiente->next;
            liberar_recursos(&siguiente);
            insertar_proceso(terminados,&siguiente);
            verificar_suspendidos();
            revisar_nuevos(&NUEVOS,&LISTOS);
            return 1;
        }
        else{
            anterior = *listos;
            siguiente = siguiente->next;
            for( ;siguiente != NULL; siguiente = siguiente->next){
                if(siguiente->pid == atoi(argumento)){
                    anterior->next = siguiente->next;

                    liberar_recursos(&siguiente);
                    insertar_proceso(terminados,&siguiente);
                    verificar_suspendidos();
                    revisar_nuevos(&NUEVOS,&LISTOS);
                    return 1;
                }
                anterior = anterior->next;
            }
            return 0;
        }
    }
}

void purgar(PCB **terminados){

    PCB *siguiente=NULL,*anterior=NULL;

    for(siguiente = *terminados; siguiente!=NULL;){
        anterior = siguiente->next;
        free(siguiente);
        siguiente = anterior;
    }
    *terminados=NULL;
}

void comando_entrada(){

	FILE *nuevo_archivo, *aux;
			mvscanw(25,0,"%s %s",comando, argumento);
			/*
				Se analizan todos los comandos de entrada
			*/
			if( strcmp( comando,"salir") == 0 ){ //Se analiza el comando salir
				erase();
				refresh();
				endwin();
				exit(-1);
			}

			else if( strcmp(comando,"ejecuta") == 0 ){ //Se analiza el comando ejecuta
				erase();
				if( strlen(argumento) != 0 ){
					//strcpy(nombre_archivo,argumento);
					if(archivo_existe(argumento) != 1){
						mvprintw(31,0,"No se encuentra el archivo \" %s \"\n",argumento);
						//refresh();
					}

					else{

						char linea[TR];
						memset(linea,'\0',50);

	    				nuevo_archivo = fopen(argumento,"r");
	    				no_proceso++;

	    				aux = fopen(argumento,"r");
						leer_renglon(linea,aux);
						char instruccion[4];
						int v[4] = {0,0,0,0};

						if( valida_primera_linea(linea,instruccion, v) == 1 ){
							
							int num_pag = 0;
							unsigned long int num_inst = 0;
							int con;
							char letra[50];

							unsigned long int pos_ant = ftell(aux);
							do{
								memset(letra,'\0',50);
								fgets(letra,50,aux);
								con = 0;
								if(strlen(letra) != 0){
									num_inst++;
								}

							} while( feof(aux) == 0);
				
							num_pag = (int)ceil(num_inst/T_MARCO );
							int bandera = 0;
							fseek(aux,pos_ant, SEEK_SET);
							num_inst--;

							if(num_pag > 16384){
								crear_proceso(no_proceso,argumento,nuevo_archivo,&TERMINADOS);
								mvprintw(31,0,"El proceso requiere mas memoria de disco que existe!n");
							}else{
								if(num_pag > libre_swap){
									crear_proceso_valido(no_proceso,argumento,aux,&NUEVOS,v,num_pag, num_inst, 1);
								}else{
									crear_proceso_valido(no_proceso,argumento,aux,&LISTOS,v,num_pag, num_inst, 0);
								}
							}

						}else{
							crear_proceso(no_proceso,argumento,nuevo_archivo,&TERMINADOS);
						}
					}
				}

				else{
					mvprintw(31,0,"No se especifico el nombre del archivo\n");
				}
			}

			else if( strcmp(comando,"vel") == 0 ){
        		erase();
        		if( strlen(argumento) == 0){
            		mvprintw(31,0,"No introduciste el argumento en microsegundos\n");
        		} else if( esNumero(argumento) == 1 ){
            		if(atoi(argumento) > 0){
                		vel = atoi(argumento);
                		printw("Se cambio la velocidad de ejecución a %d microsegundos\n",vel);
            		}else{
                		mvprintw(31,0,"ERROR: Insertaste un número negativo\n");
            		}
        		} else{
            		mvprintw(31,0,"\" %s \" No es un número\n",argumento);
        		}
    		}

            else if( strcmp(comando,"mata") == 0){
                erase();
                if(esNumero(argumento) == 1){
                    if(atoi(argumento)>0){
                        if(mata_ejecucion(EJECUCION,&TERMINADOS,argumento) == 0){
                            
                            if(mata_listos(&LISTOS,&TERMINADOS,argumento) != 1){
                                
                                if(mata_listos(&BLOQUEADOS,&TERMINADOS,argumento) != 1){

                                    if(mata_listos(&SUSPENDIDOS,&TERMINADOS,argumento) != 1){

                                        if(mata_nuevos(&NUEVOS,&TERMINADOS,argumento) !=1){

                                            if( atoi(argumento) <= PID){
                                                mvprintw(31,0,"El proceso con el PID ingresado ya fue terminado");
                                            }else{
                                                mvprintw(31,0,"El PID ingresado no existe"); 
                                            }
                                        }
                                    }
                                }  
                            } 
                        }
                    }
                    else{
                        mvprintw(31,0,"El numero ingresado no puede ser cero o un numero negativo!\n");
                    }
                }
                else{
                    mvprintw(31,0,"!!El argumento %s no es un numero!!!\n",argumento);
                }
            }

            else if(strcmp(comando,"purgar") == 0){
                erase();
                purgar(&TERMINADOS);
            }

			else{
				if( strlen(comando) != 0){			//si el comando no esta vacio, se usa debido a que esta en un ciclo
					erase();
					mvprintw(31,0,"Comando \" %s \" no reconocido!\n",comando);	//timprime que no se reconoce
				}
			}
}

int valida_primera_linea(char IR[],char instruccion[], int v[]){

    if(IR[3] != ' '){
        mvprintw(31,0,"Error en la intruccion %s",IR);
        return 0; //Retorno de dos por que la instrucciojn esta mal formada
    }
    else{

        for(int i=0; i < 3; i++){

            instruccion[i] = IR[i];
        }

        instruccion[3]='\0';

        if(strcmp(instruccion,"MAX") !=  0 ){
        	mvprintw(31,0,"El nuevo proceso introducido no es valido porque no se especifico los recuros maximos que usará");
        	verificar_suspendidos();
        	return 0;
        }

        if(vector_obtener_valores(v,IR) == 0){
           	mvprintw(31,0,"Error en la instrucción");
            //mvprintw(31,0,"Error en la intruccion %s",IR);
            return 0; //Retorno de dos por que la instrucciojn esta mal formada
        }

        if( v[0] <= TOTALES[0] &&
            v[1] <= TOTALES[1] &&
            v[2] <= TOTALES[2] &&
            v[3] <= TOTALES[3] 
            ){
        	return 1;
            	
        }else{
        	mvprintw(31,0,"El nuevo proceso definio mas recursos que los recursos totales que existen.\n");
        	verificar_suspendidos();    
        	return 0;	
        }
        
        
    }

}

void crear_proceso_valido(int pid,char nombre_archivo[],FILE *archivo,struct PCB **cola_procesos, int valores[],int no_pag, unsigned long int no_inst, int bandera){

    struct PCB *proceso =NULL,*recorrer = NULL; 
    proceso = malloc(sizeof(struct PCB));
    /*
        Aqui se llenan todos los datos para crear el nodo
    */
    int v[4]={0,0,0,0};
    proceso->pid = pid;
    memset(proceso->IR,'\0',50);
    strcpy(proceso->nombre_archivo,nombre_archivo);
    proceso->PC = 0;
    proceso->EAX = 0;
    proceso->EBX = 0;
    proceso->ECX = 0;
    proceso->EDX = 0;
  //  proceso->archivo = archivo;
    copiar_vector(proceso->MAXIMO,valores);
    copiar_vector(proceso->NECESIDAD,valores);
    copiar_vector(proceso->ASIGNADOS,v);
    copiar_vector(proceso->PETICION,v);
    proceso->marcado = 0;
    proceso->next = NULL;

    proceso->tmp = malloc(sizeof(TMP)*no_pag);
    
    proceso->no_paginas = no_pag;
    proceso->no_inst = no_inst;

    if(bandera == 0 ){
    	FILE *arch_text = archivo;
    	int i = 0;
    	char letra[50];

    	while (i < no_pag){
    		int j = 1;
    		unsigned int pos_swap_libre = obtener_marcoSWAP();
    		fseek(fswap, pos_swap_libre*T_MARCO*50 ,SEEK_SET);

    		while(j <= 4){
    			memset(letra,'\0',50);
    			int con = 0;
    			if(feof(arch_text) == 0){
    				fgets(letra,50,arch_text);
    				con = 0;
    				while( con < 50){
    					if(letra[con] == '\n' || letra[con] == '\0'){
    						letra[con] = '\0';
    						break;
    					}
    					con++;
    				}
    				fwrite(letra,sizeof(char),50,fswap);
    			}else{
    				fwrite(letra,sizeof(char),50,fswap);
    			}
    			j++;	
    		}
    		libre_swap--;
    		tms[pos_swap_libre].asignado = 1;
    		tms[pos_swap_libre].pid_dueno = pid;

    		proceso->tmp[i].presencia = 0;
    		proceso->tmp[i].marco_swap = pos_swap_libre;
    		i++;
    	} 
    }

    if( *cola_procesos == NULL ){
        *cola_procesos = proceso;
    }

    else{
        /*
        Se recorre toda la lista para que se pueda insertar el nuevo nodo creado
        */
        for( recorrer = *cola_procesos ; recorrer != NULL ; recorrer = recorrer->next ){
            if(recorrer->next == NULL){
                recorrer->next = proceso;
                break;
            }
        }
    }  
}

unsigned int obtener_marcoRAM(){
	int i = 0;
	while( i < 16 ){
		if(tmm[i].asignado == 0){
			return i;
		} 
		i++;
	}
}

unsigned int obtener_marcoSWAP(){
	int i = 0;
	while( i < 16384 ){
		if(tms[i].asignado == 0){
			return i;
		} 
		i++;
	}
}


void traer_instruccion(unsigned long int pc,char cadena[], PCB **proceso){
	
	int no_pag = 0,desplazamiento=0;
	desplazamiento = pc&3;
	no_pag=pc>>2;
	

	PCB *actual = *proceso;
	int pos_RAM_libre;
	char renglon[50];
	memset(renglon,'\0',50);


	unsigned int pag_swap;
	if( actual->tmp[no_pag].presencia == 0){
		mvprintw(32,0,"Ocurrio un fallo de página para el proceso \" %d \" ",EJECUCION->pid);
		fallos_pag++;
		if(libre_RAM != 0){
			pos_RAM_libre = obtener_marcoRAM();
			insertarLRU(pos_RAM_libre,&LRU);
			libre_RAM--;
		}else{
			pos_RAM_libre = obtener_frente_LRU(LRU);
			int dueno = tmm[pos_RAM_libre].pid_dueno;
			int pag_dueno = tmm[pos_RAM_libre].pag_dueno;
			mandar_final_LRU(pos_RAM_libre,&LRU);
			buscar_estados(dueno,pag_dueno);

		}

		pag_swap = actual->tmp[no_pag].marco_swap;
		fseek(fswap,pag_swap*50*(int)T_MARCO,SEEK_SET);

		//lectura completa de la pagina en el swap hacia la RAM
		fread(RAM[pos_RAM_libre*4 ], sizeof(char), 50*(int)T_MARCO, fswap);
		
		tmm[pos_RAM_libre].asignado = 1;
		tmm[pos_RAM_libre].pid_dueno = actual->pid;
		tmm[pos_RAM_libre].pag_dueno= no_pag;

		//actualizar tmp del proceso
		actual->tmp[no_pag].marco_RAM = pos_RAM_libre;
		actual->tmp[no_pag].presencia = 1;

		strcpy(cadena,RAM[pos_RAM_libre*4 + desplazamiento]);
	}else{
		mvprintw(32,0,"                                                      ",EJECUCION->pid);
		mandar_final_LRU(actual->tmp[no_pag].marco_RAM, &LRU);
		strcpy(cadena,RAM[actual->tmp[no_pag].marco_RAM*4 + desplazamiento]);
	}
	*proceso = actual;
}

void liberarRAM(PCB **proceso){
	PCB *actual =*proceso; 
	int j = 0;
	int marco_pag;
	while(j < actual->no_paginas){
		if(actual->tmp[j].presencia == 1){
			actual->tmp[j].presencia = 0;
			marco_pag = actual->tmp[j].marco_RAM;
			eliminar_LRU(marco_pag,&LRU);
			tmm[marco_pag].asignado = 0;
			tmm[marco_pag].pid_dueno = 0;
			tmm[marco_pag].pag_dueno = 0;
			libre_RAM++;
		}
		j++;
	}
}

void liberarSWAP(PCB **proceso){
	PCB *actual =*proceso; 
	int j = 0;
	int contador = 0;
	int marco_swap;
	while(j < actual->no_paginas){
		marco_swap = actual->tmp[j].marco_swap;
		tms[marco_swap].asignado = 0;
		tms[marco_swap].pid_dueno = 0;
		libre_swap++;
		j++;
	}
}

int jnz_token(char ir[],char instruccion[]){

	int i;
	if(ir[3] == ' '){
		for(i=0; i < 3; i++){
	    	instruccion[i] = ir[i];
		}
		instruccion[3]='\0';
		if(strcmp(instruccion,"JNZ") == 0){

			long int valor;
			
			char vector_cadena[8];
			memset(vector_cadena,'\0',8);
		
			int j = 0;
			i = 4;
			while( ir[i] != '\0'){
				vector_cadena[j] = ir[i];
				i++;
				j++;
			}
			vector_cadena[j] = '\0';

			if(ECX != 0){
				if(esNumero(vector_cadena) == 1){
					valor = atoi(vector_cadena);
					if(valor < 0){
						mvprintw(31,0,"\"%s\" Se especifico un número negativo", vector_cadena);
						guardar_contexto(EJECUCION);
						liberarRAM(&EJECUCION);
						liberarSWAP(&EJECUCION);
						liberar_recursos(&EJECUCION);
						insertar_proceso(&TERMINADOS,&EJECUCION);
						verificar_suspendidos();
                        revisar_nuevos(&NUEVOS,&LISTOS);
						return 1;
					}
				}else{
					if(vector_cadena[0] != '\0')
						mvprintw(31,0,"\"%s\" No es un número", vector_cadena);
						guardar_contexto(EJECUCION);
						liberarRAM(&EJECUCION);
						liberarSWAP(&EJECUCION);
						liberar_recursos(&EJECUCION);
						insertar_proceso(&TERMINADOS,&EJECUCION);
						verificar_suspendidos();
                        revisar_nuevos(&NUEVOS,&LISTOS);
						return 1;
				}
				if(valor > EJECUCION->no_inst){
					mvprintw(31,0,"El proceso %d hizo un salto fuera de los limites del tamaño del proceso", EJECUCION->pid);
					guardar_contexto(EJECUCION);
					liberarRAM(&EJECUCION);
					liberarSWAP(&EJECUCION);
					liberar_recursos(&EJECUCION);
					insertar_proceso(&TERMINADOS,&EJECUCION);
					verificar_suspendidos();
                    revisar_nuevos(&NUEVOS,&LISTOS);
					return 1;
				}else{


					PC = valor;
					return 1;
				}
			}else{
				PC++;
			}

			return 1;
		}
		
	}
	return 0;
}

void revisar_nuevos(struct PCB **nuevos, struct PCB **listos){

    struct PCB *siguiente = NULL,*anterior = NULL;

	char linea[TR];

    siguiente = *nuevos;

    if(*nuevos != NULL) {

        while(1){

            siguiente=*nuevos;

            if(*nuevos == NULL){
                siguiente=NULL;
                break;
            }
            if(siguiente->no_paginas <= libre_swap){

                *nuevos = siguiente->next;

				FILE *nuevos_archivo = fopen(siguiente->nombre_archivo,"r");

				//valida_primera_linea
				leer_renglon(linea,nuevos_archivo);
				char instruccion[4];
				int v[4] = {0,0,0,0};
				valida_primera_linea(linea,instruccion, v);

                crear_proceso_valido(siguiente->pid,siguiente->nombre_archivo,nuevos_archivo,listos,siguiente->MAXIMO,siguiente->no_paginas,siguiente->no_inst,0);
                free(siguiente);
            }

            else{
                break;
            }
        }

        anterior = *nuevos;
        if(anterior != NULL){

            siguiente = anterior->next;

            for(; siguiente!= NULL;){
                    
                if(siguiente->no_paginas <= libre_swap){
                    anterior->next = siguiente->next;

					FILE *nuevos_archivo = fopen(siguiente->nombre_archivo,"r");

					//valida_primera_linea
					leer_renglon(linea,nuevos_archivo);
					char instruccion[4];
					int v[4] = {0,0,0,0};
					valida_primera_linea(linea,instruccion, v);

                    crear_proceso_valido(siguiente->pid,siguiente->nombre_archivo,nuevos_archivo,listos,siguiente->MAXIMO,siguiente->no_paginas,siguiente->no_inst,0);

                    free(siguiente);

                    siguiente = anterior->next;
                }

                else{
                    siguiente=siguiente->next;
                    anterior=anterior->next;
                }

            }

            if(siguiente== NULL && anterior->no_paginas <= libre_swap){
                
                *nuevos = anterior->next;

				FILE *nuevos_archivo = fopen(anterior->nombre_archivo,"r");

				//valida_primera_linea
				leer_renglon(linea,nuevos_archivo);
				char instruccion[4];
				int v[4] = {0,0,0,0};
				valida_primera_linea(linea,instruccion, v);

                crear_proceso_valido(anterior->pid,anterior->nombre_archivo,nuevos_archivo,listos,anterior->MAXIMO,anterior->no_paginas,anterior->no_inst,0);
           
                free(anterior);

                anterior=siguiente;
            }
        }
    }
}

//FUNCIONES DEL LRU
lru *crear_nodo_LRU(){
	lru *nuevo = NULL;
    nuevo = malloc(sizeof(lru));
    nuevo->next = NULL;
    return nuevo;
} 

void imprimeLRU(lru *pila){
	lru *aux;
	aux = pila;
	int i = 0;
	
	while(aux != NULL){
		mvprintw(27,i*3,"%d ",aux->n);
		aux = aux->next;
		i++;
	}

}

void insertarLRU(int num, lru **pila){
	lru *nuevo, *aux, *actual;
	nuevo = crear_nodo_LRU();
	nuevo->n = num;
	aux = NULL;

	if(*pila == NULL){
		*pila = nuevo;
	}else{
		aux = *pila;
		while(aux->next != NULL){
			aux = aux->next;
		}
		aux->next = nuevo;
	}
}

void mandar_final_LRU(int num, lru **pila){
	lru *anterior, *actual;
	anterior = NULL;
	actual = *pila;

	if(actual->n == num){
		*pila = actual->next;
		insertarLRU(actual->n,&*pila);
		free(actual);
	}else{
		anterior = actual;
		actual = actual->next;

		while( actual != NULL){
			if(actual->n == num){
				insertarLRU(actual->n,&*pila);
				anterior->next = actual->next;
				free(actual);
				break;
			}
			actual = actual->next;
			anterior = anterior->next;
		}
	}
}

void eliminar_LRU(int num, lru **pila){
	lru *anterior, *actual;
	anterior = NULL;
	actual = *pila;

	if(actual->n == num){
		*pila = actual->next;
		free(actual);
	}else{
		anterior = actual;
		actual = actual->next;

		while( actual != NULL){
			if(actual->n == num){
				anterior->next = actual->next;
				free(actual);
				break;
			}
			actual = actual->next;
			anterior = anterior->next;
		}
	}
}

int obtener_frente_LRU(lru *pila){
	return pila->n;
}

void buscar_estados(int pid, int pag_dueno){

	if(EJECUCION->pid == pid){
		EJECUCION->tmp[pag_dueno].presencia = 0;
	}else if(buscar_proceso(pid, pag_dueno, &SUSPENDIDOS) == 1){
	}else if(buscar_proceso(pid, pag_dueno, &BLOQUEADOS) == 1){
	}else if(buscar_proceso(pid, pag_dueno, &LISTOS) == 1){
	}
}

int buscar_proceso(int pid, int pag_dueno, PCB **proceso){		//1 lo encontro, 0 no lo encontro

	PCB *actual = *proceso;
	while(actual != NULL){
		if(pid == actual->pid){
			actual->tmp[pag_dueno].presencia = 0;
			return 1;
		}
		actual = actual->next;
	}

	return 0;
	
}
