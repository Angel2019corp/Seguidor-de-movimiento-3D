%% Este script muestra el funciuonamineto de un filtro pasabajas digital 
% Este programa va a simular una señal de baja frecuencia que contiene
% ruido de alta frecuencia.
%% PROGRAMA PRINCIPAL
% Numero de datos
numData=100;
% Definimos la variable temporal
t=linspace(0,1,numData);
% Determinamos el incremento en el tiempo
delta_t=t(2)-t(1);
% Definimos las frecuencias presentes en nuestra señal
f1=1;
f2=.5;
% Generamos ruido
ruido=(0.5-rand(1,numData))*1;
% Definimos la señal de baja frecuencia
sig=cos(2*pi*f1*t)+cos(2*pi*f2*t)+ruido;
%% GENERAMOS EL FILTRO DIGITAL
ym=sig(1);
ymMas1=0;
% Definimos la feecuencia de corte del filtro
f_0=.5;
omega_0=2*pi*f_0;
for m=1:numData
    ymMas1=(1-omega_0*delta_t)*ym + ...
        omega_0*delta_t*sig(m);
    sigFil(m)=ymMas1;
    % Nos preparamos para la siguiente medicion 
    ym=ymMas1;
    
    
   
    
    %Graficamos datos
    plot(t(1:m),sig(1:m));
    hold on;
    plot(t(1:m),sig(1:m)-ruido(1:m),'r');
    plot(t(1:m),sigFil(1:m),'sk');
    hold off;
    xlabel('Tiempo (seg)');
    ylabel('Amplitud de la señal (U.A.)');
    pause(0.1)
end


