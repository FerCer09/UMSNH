clc;
        fprintf('Método Falsa Posición\n');
        f1 = input('Ingrese la función (introduzca "x" como variable estrictamente): ');
        Fun = inline(f1);
        %Definir las dos aproximaciones iniciales
        fprintf('Introduzca los dos puntos iniciales, de tal manera que f(Xn)<0 y f(Xp)>0\n');
        Xn = input('Xn: ');
        fun = Fun(Xn);
           
        while fun > 0       %%Si el numero es positivo, debo pedir otro valor para Xn
            display('El resultado de F(Xn) es positivo, ingresa otro número');
            Xn = input('Xn: ');
            fun = Fun(Xn);
        end

        Xp = input('Xp: ');
        fun = Fun(Xp);
        while fun < 0       %%Si el numero es negativo, debo pedir otro valor para Xn
            display('El resultado de F(Xp) es negativo, ingresa otro número');
            Xp = input('Xp: ');
            fun = Fun(Xp);
        end 
        Xanterior = Xp;
        iMax = input('Número maximo de iteraciones: ');
        Convergencia = input('Criterio de Convergencia: ');
        
        for k=1:iMax                %Paso 4, hago solo las numero iteraciones que pidio el usuario 
            Xc = (Xp*Fun(Xn)-Xn*Fun(Xp)) / (Fun(Xn)-Fun(Xp));     %Paso 2 estimar la nueva aproximacion para Xc
            fun = Fun(Xc);
            error = abs((Xc-Xanterior)/Xc);
            tabla(k,:)=[k Xn Xp Xc fun error];
            tablaError(k,:) = error;
            if(error < Convergencia)      %Paso 3 Verifico la convergencia
                break;
            else
                if(fun > 0)
                    Xp = Xc;         %Cambio el valor de Xp        
                else
                    Xn = Xc;         %Cambio el valor de Xn
                end
            Xanterior = Xc;
            end  
        end    
        fprintf('\n \tk \t\tXn \t\t\tXp \t\t\tXc \t\tf(Xc) \terror \n')
        disp(tabla)
        fprintf('Solución:\nXc=\t\t\t\t%0.6f\n',Xc)
        fprintf('Funcion(Xc)=\t%0.6f\n',Fun(Xc))
        fprintf('Error=\t\t\t%0.5f%%\n\n',error*100)
        plot(tablaError,'-r','lineWidth',1)
        title('Gráfica de Convergencia "Falsa Posición"')
        grid on