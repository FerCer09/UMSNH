%Proyecto Final
%Equipo 5
clc;
fprintf('Buen dia\n');
%Menu Principal
while true
clear all
fprintf('�Que tipos de ecuaciones quieres resolver?\n');
fprintf('a) Ec. Algebraica no lineal\n');
fprintf('b) Sistema de Ecs. Lineales\n');
fprintf('c) Ecs. Algebraicas no Lineales\n');
fprintf('d) Ec. diferencial de primer orden\n');
fprintf('s) Salir del programa\n');
texto = 'Ingresa la letra del inciso que quieres seleccionar : ';
seleccion = input(texto,'s');

if(seleccion == 'a')
% Menu de las Ecs. Algebraicas no lineales
    clc;    clear all
    fprintf('Ec. Algebraica no lineal\n');
    fprintf('�Con que m�todo N�merico lo quieres resolver?\n');
    fprintf('a) M�todo Newton-Raphson\n');
    fprintf('b) Falsa Posici�n\n');
    texto = 'Ingresa la letra del inciso que quieres seleccionar : ';
    seleccion = input(texto,'s');
    
    syms x;     error = 1;      k = 1;
    if(seleccion == 'a')
    %Newton Raphson Ec. algebraica no Lineal
        M_NR();
        
    elseif(seleccion == 'b')
    %Falsa Posici�n Ec. algebraica no Lineal
        M_FalsaP();
    end
    
elseif(seleccion == 'b')    
% Menu de los Sistema de Ecs. Lineales
    clc;    clear all
    fprintf('Sistema de Ecs. Lineales\n');
    fprintf('�Con que m�todo N�merico lo quieres resolver?\n');
    fprintf('a) Jacobi\n');
    fprintf('b) Gauss-Seidel\n');
    texto = 'Ingresa la letra del inciso que quieres seleccionar : ';
    seleccion = input(texto,'s');
    
    clc;
    if(seleccion == 'a')
        fprintf('M�todo Jacobi\n');     
    else
        fprintf('M�todo Gauss-Seidel\n');  
    end
    numEc=input('N�mero de Ecs= ');
    A=input('Ingresar la matriz de coeficientes ');
    b=input('Ingresar los t�rminos independientes ');
    z=input('Ingresar el n�mero m�ximo de iteraciones= ');
    criterio = input('Criterio de Norma= ');
    X0 = input('Ingresar los valores del vector inicial = ');
    k=0;
    Error = zeros(1,numEc);     %inicializo el error a cero de cada variable
    fprintf('\n')
    norma = 1;

    
    if(seleccion == 'a')
    %Jacobi Sistema de Ecs. Lineales
        M_Jacobi();
        
    elseif(seleccion == 'b')
    %Gauss-Seidel Sistema de Ecs. Lineales
        M_GaussS();
   
    end
    fprintf('\n');
    
elseif(seleccion == 'c')
%Secci�n Ecs. Algebraicas no Lineales
    clc;    clear all
    fprintf('Ecs. Algebraicas no Lineales\n');
    fprintf('Se usar� el m�todo Newton-Raphson\n');
    %Metodo Newton-Raphson
    M_NRmultivariable();
      
elseif(seleccion == 'd')
%Secci�n Ec. diferencial de primer orden
   M_Runge_Kutta();

elseif(seleccion == 's')
    clc; clear all
    fprintf('Hasta la Proxima\n');
    break
  
end

end    %ciclo