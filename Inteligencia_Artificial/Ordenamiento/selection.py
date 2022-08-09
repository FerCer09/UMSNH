# -*- coding: utf-8 -*-help
lista = [5,4,3,2,1]
n = len(lista)
for j in range(0,n-1):
    sma = j
    for i in range(j+1,n):
        if( lista[i] < lista[sma]):
            sma = i
    aux = lista[j]      #cambio de variables
    lista[j] = lista[sma]
    lista[sma]=aux   
print(lista)