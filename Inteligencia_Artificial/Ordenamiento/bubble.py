# -*- coding: utf-8 -*-help
lista = [4,3,2,1]
i=1
while( i<len(lista) ):
    j=0
    while( j<len(lista)-i):
        if(lista[j]>lista[j+1]):
               aux= lista[j]
               lista[j]=lista[j+1]
               lista[j+1]=aux
        j = j+1
    i= i+1
print(lista)