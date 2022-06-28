clc;    clear all
fprintf('Solución de Ecuaciones Diferenciales\n Usando el metodo de Runge-Kutta 4to Orden\n');
f = input('\nIngresar la ecuación diferencial: dy/dx = f(x,y)   ','s');
x0 = input('Ingrese x0: ');
x1 = input('Ingrese xf: ');
y0 = input('Ingrese la condición inicial y(x0): ');
n = input('Ingrese el numero de pasos N: ');

%Calculo del paso de integración
h = (x1-x0)/n;
xs = x0:h:x1;
y1 = y0;
fprintf('\n%-20s%-20s%-20s%-20s','iter','x','y','Error_Relativo');
yanterior = 0;
for i = 1:n
    it = i-1;
    x0 = xs(i);
    x = x0;
    y = y0;
    k1 = eval(f);
    x = x0 + h/2;
    y = y0 + h*k1/2;
    k2 = eval(f);
    x = x0 + h/2;
    y = y0 + h*k2/2;
    k3 = eval(f);
    x = x0 + h;
    y = y0 + h*k3;
    k4 = eval(f);
    y0 = y0 + h*(k1 + 2*k2 + 2*k3 + k4)/6;
    error = abs( (y0-yanterior)/y0 );
    tabla_error(i,:) = error;
    fprintf('\n%-20.0f%-20.6f%-20.6f%-20.6f%-20.6f\n',it,x0,y0,error);
    yanterior = y0;
end
fprintf('\nEl punto aproximado y(x1) es = %10.6f\n\n',y)
plot(tabla_error,'-r')
grid on
title('Gráfica del Error Relativo ( Runge-Kutta )')