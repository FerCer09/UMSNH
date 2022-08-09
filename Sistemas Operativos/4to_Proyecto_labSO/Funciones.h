#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#define TR 50
#define quantum 3
#define T_MARCO 4.0

int EAX,EBX,ECX,EDX;
unsigned long int PC;
long unsigned int vel;
int PID;
int no_proceso;
int hora_actual;
int proceso_terminado;
char IR[TR];
char comando[50],argumento[50];
char nombre_archivo[50];
FILE *arch;
struct tm *tiempo_general;
time_t tiempo;
int numero_bloqueado;

//nuevas variables para el proyecto #4
FILE *binario;
typedef struct TMP{
	unsigned int presencia;		//0 no tiene presencia, y 1 si lo tiene 
	unsigned int marco_RAM;		
	unsigned int marco_swap;	

} TMP;

typedef struct TMM{
	unsigned int asignado;		//0 esta libre, 1 no esta libre
	unsigned int pid_dueno;		
	unsigned int pag_dueno;

} TMM;

typedef struct TMS{
	unsigned int asignado;		//0 esta libre, 1 no esta libre
	unsigned int pid_dueno;		

} TMS;


typedef struct PCB{
	unsigned long int pid;
	char nombre_archivo[50];
	unsigned long int PC;
	char IR[TR];		
	int EAX;
	int EBX;
	int ECX;
	int EDX;
	int hora_bloqueados;
	int tiempo_bloqueado;
	unsigned int MAXIMO[4];
	unsigned int NECESIDAD[4];
	unsigned int ASIGNADOS[4];
	unsigned int PETICION[4];
	unsigned int marcado;			//0 no esta marcado, 1 si esta marcado
	struct PCB *next;

	unsigned int no_paginas;
	unsigned long int no_inst;
	TMP *tmp;

} PCB;

typedef struct lru{
	unsigned int n;
	struct lru *next;

} lru;

lru *LRU;

//struct PCB *cola_procesos;
PCB *LISTOS, *EJECUCION,*TERMINADOS, *actual,*SUSPENDIDOS, *BLOQUEADOS, *NUEVOS;	//se cambio esta parte
unsigned int TOTALES[4];
unsigned int DISPONIBLES[4];

TMM *tmm;
TMS *tms;
unsigned int fallos_pag;
unsigned int libre_RAM;
unsigned int libre_swap;

FILE *fswap;

char RAM[64][50];

int archivo_existe(char nombre_archivo[]);
void leer_renglon(char cadena[],FILE *archivo);
void tokens(char instruccion[],char registro_destino[],char registro_origen[],char cadena[]);
int token_memoria(char instruccion[],char intruccion[]);
int vector_obtener_valores(int vector[],char cadena[]);
void limpiar_arreglo(char cadena[],char instruccion[],char registro_destino[],char registro_origen[]);
int tipo_instruccion(char instruccion[]);
int esNumero(char registro[]);
int identificar_registro(char registro[]);
int operaciones(int instruccion,int regnum,int regnum2,int *direcciones_registros[],int esnum);
int renglonCorrecto(char renglon[]);
int ejecutar_linea(PCB **proceso);
void verificar_comandos();
int kbhit(void);
void crear_proceso(int pid,char nombre_archivo[],FILE *archivo,struct PCB **cola_procesos);
void imprimir(struct PCB *cola_procesos);
void imprimir_ejecucion(struct PCB *cola_procesos);
void comando_entrada();
void purgar(PCB **terminados);
int mata_ejecucion(PCB *ejecucion,PCB **terminados,char argumento[]);
int mata_listos(PCB **listos, PCB **terminados,char argumento[]);
int mata_nuevos(PCB **listos, PCB **terminados,char argumento[]);
void inicializa_lista(PCB **lista);
PCB *crear_nodo();
void insertar_proceso(PCB **lista, PCB **ent);
PCB *obtener_frente(PCB **lista);
void restaurar_contexto(PCB *proceso);
void guardar_contexto(PCB *proceso);
void imprimirMonitor();

int revisar_bloqueados(struct PCB **bloqueados,struct PCB **listos);

void copiar_vector(int salida[], int entrada[]);
int banquero(PCB **actual);
void desmarcar_procesos(PCB **estado);
PCB *encontrar_proceso_valido(PCB **estado);
int todos_marcados(PCB *estado);
int ins_free(PCB **actual, int v[]);
void liberar_recursos(PCB **actual);
void verificar_suspendidos();

int valida_primera_linea(char IR[],char instruccion[], int v[]);
void crear_proceso_valido(int pid,char nombre_archivo[],FILE *archivo,struct PCB **cola_procesos, int valores[],int no_pag, unsigned long int no_inst, int bandera);

unsigned int obtener_marcoRAM();
unsigned int obtener_marcoSWAP();
void traer_instruccion( unsigned long int pc,char cadena[], PCB **proceso);
void liberarRAM(PCB **proceso);
void liberarSWAP(PCB **proceso);
int jnz_token(char IR[],char instruccion[]);
void revisar_nuevos(struct PCB **nuevos, struct PCB **listos);

//Funciones del LRU
lru *crear_nodo_LRU();
void imprimeLRU(lru *pila);
void insertarLRU(int num, lru **pila);
void mandar_final_LRU(int num, lru **pila);
void eliminar_LRU(int num, lru **pila);
int obtener_frente_LRU(lru *pila);
void buscar_estados(int pid, int pag_dueno);
int buscar_proceso(int pid, int pag_dueno, PCB **proceso);