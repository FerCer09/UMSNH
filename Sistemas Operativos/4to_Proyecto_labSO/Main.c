/*
Si quieres borra esto cuando lo leas:
* Modifique la función operaciones para el caso 1, para que el registro R2 acepte, tanto registros como numeros
* Agregué la función renglon_correcto
*/

#include "Funciones.h"

int main()
{
	LRU = NULL;

	srand(time(NULL));
	LISTOS = EJECUCION = TERMINADOS = actual = NUEVOS = NULL;
    vel = 1000000;
    unsigned int v_inicio[4] ={10,7,9,15}; 
    copiar_vector(TOTALES,v_inicio);
    copiar_vector(DISPONIBLES,v_inicio);

	PID = 0;
	no_proceso = 0;
	PC = 0;

	fallos_pag = 0;
	libre_RAM = 16;
	libre_swap = 16384; //2^14

	tmm = malloc(sizeof(TMM)*libre_RAM);
	tms = malloc(sizeof(TMS)*libre_swap);

	int limite = 1;
	char renglon[50];
	memset(renglon,'\0',50);
	FILE *binario = fopen("swap.bin","w+b");
	while(limite <= libre_swap){
		fwrite(renglon,sizeof(char), 50,binario);
		fwrite(renglon,sizeof(char), 50,binario);
		fwrite(renglon,sizeof(char), 50,binario);
		fwrite(renglon,sizeof(char), 50,binario);
		limite++;
	}
	fclose(binario);

	fswap = fopen("swap.bin","r+b");

	initscr();
	while(1){
		memset(comando,'\0',50);
		memset(argumento,'\0',50);		//inicializa a caracter nulo el comando y argumento
		refresh();
		
		imprimirMonitor();
		if(kbhit() == 1){
			comando_entrada();
		}
		move(0,0);	
		//inicio de ejecución de los procesos
		int i = 1;

		revisar_bloqueados(&BLOQUEADOS,&LISTOS);
		
		//inicio de ejecución de los procesos
		if( LISTOS != NULL){
			//imprimir(LISTOS);
			
			//Seleccionando proceso que esta enfrente de listos
			EJECUCION = obtener_frente(&LISTOS);
			

			//Restaurando contexto;
			restaurar_contexto(EJECUCION);

			imprimirMonitor();
			//Proceso puesto en estado de Ejecución
			int control = 0;
			while(i++ <= quantum){
				memset(comando,'\0',50);
				memset(argumento,'\0',50);		//inicializa a caracter nulo el comando y argumento
				refresh();

				imprimirMonitor();
				control = ejecutar_linea(&EJECUCION);
        		if(control == 1 || control == 0){ //si hay un error o terminó, se acaba la ejecución
        			break;
        		}else if(control == 3){
        			break;
        		}

        		usleep(vel); 
				if(kbhit() == 1){
					//imprimirMonitor();
					comando_entrada();
				}
				move(0,0);
				if(EJECUCION == NULL){
					control = 3;
					break;
				}
			}
        	
        	if(control != 3){				//si el proceso no fue enviado a suspendidos o bloqueados.
        		guardar_contexto(EJECUCION);
        		//obtener_frente(&EJECUCION);
        		if(control == 1 || control == 0){
        			liberar_recursos(&EJECUCION);
        			liberarRAM(&EJECUCION);
        			liberarSWAP(&EJECUCION);
        			insertar_proceso(&TERMINADOS,&EJECUCION);
        			verificar_suspendidos();
					revisar_nuevos(&NUEVOS,&LISTOS);
        		}else{
        			insertar_proceso(&LISTOS,&EJECUCION);
        		}

        		obtener_frente(&EJECUCION);
        	}
        	
        	imprimirMonitor();
		}		

	}	
	endwin();
	fclose(fswap);
    
}
