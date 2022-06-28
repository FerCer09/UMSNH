    criterioNorma=input('Ingresar el criterio de norma= ');
    Max = input('Introduzca el número maximo de iteraciones: ');
    fprintf('Introduce las %d condiciones iniciales:\n',2);
    v0 = input('v0 : ');
    i0 = input('i0 : ');
    fprintf('Introduce las Ecuaciones con las variables (v y I) estrictamente\n');
    %Intoducir el caracter 'v' y el caracter 'I' estrictamente
    %Introduciendo las ecuaciones
    syms v;
    syms I;

    v1 = input('f1 = ');   
    V1 = inline(v1);

    %derivada respecto de v             %derivada respecto de I
    dvV1 = diff(v1,'v',1);              diV1 = diff(v1,'I',1);
    DvV1 = inline(dvV1);                DiV1 = inline(diV1);

    i1 = input('f2 = ');
    I1 = inline(i1);

    %derivada respecto de v             %derivada respecto de I
    dvI1 = diff(i1,'v',1);              diI1 = diff(i1,'I',1);
    DvI1 = inline(dvI1);                DiI1 = inline(diI1);

    norma=1;
    fprintf('\nk \t\t V(k) \t\t      I(k) \t\t      norma\n')
    fprintf ('%d \t\t %.4f \t\t %.4f \t\t %.4f\n', 0, v0, i0,norma)
    contador = 0;
    while norma >= criterioNorma && contador < Max
        contador = contador + 1;
        A=[DvV1(v0)  DiV1(i0);DvI1(i0) DiI1(v0,i0)];

        f1=v0/3+i0-1;
        f2=v0*(2+i0^2)^(1/2) - i0;
        b=[-f1;-f2];
        if det(A) == 0
            contador = contador - 1;
            fprintf("No tiene solución con estos valores iniciales")
            break
        end
        
        hj=inv(A)*b;
        vnew = v0+hj(1);      inew = i0 + hj(2);

        norma = ( (vnew-v0)^2 + (inew-i0)^2 )^(1/2);
        NormaGraf(contador, :) = norma;
        fprintf ('%d \t\t %.4f \t\t %.4f \t\t %.4f\n', contador, vnew, inew,norma)
        v0=vnew; i0=inew;    
    end

    if(norma <= criterioNorma)
       fprintf('\nSolución:\n')
       fprintf('V = %.4f\nI = %.4f\n\n',v0,i0)
       plot(NormaGraf,'-r','LineWidth',1)
       grid on
       title('Gráfica de la Norma "Newton-Raphson Multivarable"')    
    else
        fprintf('\nNo se cumplio el criterio de norma en %d iteraciones\n\n',contador)
    end