%% Este script permite la comunicacion de la computadora con arduino
% Via puerto serial para medir la velocidad angukar y la acelacion
%%   PROGRAMA PRINCIPAL
%  Generamos el objeto del puerto serial
mpu=serial('com3','baudrate',38400)
% Abrimos el puerto serial
fopen(mpu);
% Esperamos a que el puero este estable
disp('Estamos abriendo el puerto serial...')
pause(2)
disp('El puerto esta abierto')
%% adquirimos datos por puerto serial
Medida(1).A='0x';
Medida(2).A='0y';
Medida(3).A='0z';

Medida(1).Vang='1x';
Medida(2).Vang='1y';
Medida(3).Vang='1z';

Medida(1).Temp='2a';

color=['r','g','b']
for n=1:100
    % Medir
    for m=1:3
        %Solicitamos aceleracion
        fprintf(mpu, '%s',Medida(m).A);
        %Leemos la respuesta    
        A(n,m)=str2num(fscanf(mpu)); %2 sirve para convertir
    
        %Solicitamos velocidad angular
        fprintf(mpu, '%s',Medida(m).Vang);
        %Leemos la respuesta    
        A(n,m+3)=str2num(fscanf(mpu)); %2 sirve para convertir
        
        %Solicitamos temperatura
        fprintf(mpu, '%s',Medida(1).Temp);
        %Leemos la respuesta    
        A(n,7)=str2num(fscanf(mpu)); %2 sirve para convertir
    end

    for m=1:3
        % Graficamos aceleracion
        subplot(3,3,m)
        plot(A(1:n,m),color(m))
        % etiquetas en los ejes
        xlabel('Numero de medida')
        ylabel('Valor de medida')
        
        % Graficamos vel. ang
        subplot(3,3,m+3)
        plot(A(1:n,m+3),color(m))
        % etiquetas en los ejes
        xlabel('Numero de medida')
        ylabel('Valor de medida')
        
        % Graficamos temperatura
        subplot(3,1,3)
        plot(A(1:n,7),color(m))
        % etiquetas en los ejes
        xlabel('Numero de medida')
        ylabel('Valor de medida')
    end

    pause(.1)    
end
% Cerramos el puerto serial
fclose(mpu)

