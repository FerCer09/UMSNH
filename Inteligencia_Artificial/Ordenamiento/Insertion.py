# -*- coding: utf-8 -*-help
lista = [4,3,2,1]
j=1
while( j<len(lista) ):
    key = lista[j];
    i = j-1
    while( i>-1 and lista[i]>key):
        lista[i+1] = lista[i]
        i = i-1
    lista[i+1]=key
    j = j+1
print(lista)