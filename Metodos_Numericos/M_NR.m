clc;
        fprintf('Método Newton Raphson\n');
        Xn = input('Ingrese el valor Inicial, Xn: ');
        Convergencia = input('Criterio de Convergencia: ');
        MaxIter = input('Máximo número de Iteraciones: ');
        f1 = input('Ingrese la función (introduzca "x" como variable estrictamente): ');
        Fun = inline(f1);
        df = diff(f1,'x'); 
        Dfun = inline(df);  
        df2 = diff(f1,'x',2); 
        D2fun = inline(df2);
        
        while error > Convergencia
            f = Fun(Xn);        %f es el valor al evaluar Xn
            d_f = Dfun(Xn);
            d2_f = D2fun(Xn);
            Xnew = Xn - f/d_f;
            valor_conv = abs( ( f * d2_f )/(d_f)^2 ); 
            if valor_conv > 1    %Compruebo que converga
                break
            end 
            error = abs((Xnew - Xn) / Xnew);
            tabla(k,:)=[k-1 Xn f d_f d2_f error]; %le doy el k-1 para poder iniciar la tabla en cero
            graf2(k,:) = error; 
       
            k = k + 1;
            Xn = Xnew;
            if(k > MaxIter)
                break
            end
        end
        fprintf('\nTabla de Iteraciones')
        fprintf('\n \t  k \t\tXn \t\tf(Xn) \t\tdf(Xn) \td2f(Xn)\t  error \n')
        disp(tabla)
        if k > MaxIter    %Compruebo si el metodo convergió o divergió
            fprintf('\nNo se cumplio en criterio de convergencia en %d Iteraciones\n',MaxIter)
            fprintf('Ultimo valor:\nX = %0.6f\nError = %0.9f\n',Xnew,error)
            fprintf('%%Error = %%%0.6f\n',error*100) 
        else
            fprintf('Solución:\nX = %f\nError = %0.9f\n',Xnew,error)  %para poder imprimir numeros complejos
            fprintf('%%Error = %0.6f\n',error*100) 
            plot(graf2,'-r','lineWidth',1)
            title('Gráfica de Convergencia "Newton-Raphson"')
            grid on
        end 
        fprintf('\n')