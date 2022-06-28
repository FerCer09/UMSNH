X = X0;
        fprintf('Tabla de iteraciones:\n');
        while norma > criterio
            k=k+1;          Tabla(k,:) = k; 
            if(k > z)      %Paso 6   comprobando si cumple con el maximo número de iteraciones      
                fprintf('Falla la convergencia en %d Iteraciones\n',z); %paso 8 
                break
            end
            fprintf('%2d',k)    
            for i=1:numEc
                suma=0;
                for j=1:numEc
                    if i~=j
                        suma=suma+A(i,j)*X(j);
                    end
                end
                X(i)=(b(i)-suma)/A(i,i);
                fprintf('%10.4f',X(i));
            end
            norma = 0;
            for i=1:numEc
                Error(i) = abs((X(i)-X0(i)));      %Calculando el Error R. de cada variable
                X0(i) = X(i);                           %les asigno el nuevo valor a cada variable 
                fprintf('\tErr(%d) = %3.4f',i,Error(i));%Imprimo el error de cada variable
                Tabla(k,i+1) = X0(i);    %Guardo los valores de las variables en la tabla
                Tabla(k,i+numEc+1) = Error(i);   %Guardo el error en la tabla, a partir de la columna i + NumeroEcuaciones 
                norma = norma + Error(i)^2;     %sumatoria de errores al cuadrado
            end
            norma = norma^(1/2);        %Obtengo el error promedio
            errorArreglo(k,:) = norma;
            fprintf('\n');   
        end
        %Paso 5
        if(norma < criterio)
            fprintf('\nResultado:\n');
            for i=1:numEc
                fprintf('X(%d) = %0.4f\n',i,X(i));    %Imprimo Resultado Paso 7
            end
            plot(errorArreglo,'-r');
            title('Gráfica de la Norma "Gauss-Seidel"')    
        end