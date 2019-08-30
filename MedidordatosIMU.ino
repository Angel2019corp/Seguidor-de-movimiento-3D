/*Este sketch realiza la comunicacion entre el MPU-6050
 * y la placa de arduino. La comunicacion se 
 * realiza mediante el protocolo de comunicion I2C
 * Las ideas generales de la comunicación pueden ser halladas
 * en el MPU-6000-Register-Map1 (Hoja de especificaciones)
 * AUTORES: Carmen Viridiana Barranco Díaz
 *          Angel Ricardo Sanchez Zeferino
 *          Dalí del Angel Perez Lima 
 *          Juan Castillo
 * Fecha: 6 de febrero de 2019
 * ESTADO: Version preliminar FUNCIONA
 * Version: 0.0
 * */
/* Las conexiones son las siguientes:
 *  MPU6050             Arduino
 *  Vcc                 3.3 V
 *  GND                 GND
 *  SCL                 A5
 *  SDA                 A4
 *  

*/
 
// LIBRERIAS
//+++++++++++++++++++++++++++++++++++++++++++++
#include <Wire.h>       // Libreria para I2C
#include <Math.h>       // Libreria para funciones matematicas

// DEFINICION DE CONSTANTES Y VARIABLES
//+++++++++++++++++++++++++++++++++++++++++++++
//Direccion I2C de la IMU
#define addresMPU 0x68
// Variables para filtrar
float ymMas1, ym, w0, delta_t, Ac, w, T;

// Valores de aceleracion y vel. ang.
//          Datos crudos
int16_t AcX,AcY,AcZ,GyX,GyY,GyZ,um,medida;
float roll, pitch, yaw,c,b;
float wx, wy, wz, wx_off, wy_off, wz_off;


// Varibales generales
char coordenada;   // Parametro para medir
char s, val;       // Estado de lectura por puerto serial
                   // y dato leido
byte dato;
// PROGRAMA PRINCIPAL
//+++++++++++++++++++++++++++++++++++++++++++

void setup() {
  // INICIAMOS LOS RECURSOS NECESARIOS
  // Iniciamos la comunicacion I2C
  Wire.begin();
  // Despertamos al "MPU"
  EscribirRegistro(0x6B,B00000000);
  // Programamos intervalos dinamicos:
  // Aceleracion: +- 2g
  EscribirRegistro(0x1C,B00000000);
  // Velocidad angular: +- 250 °/seg
  EscribirRegistro(0x1B,B00000000);
  
  // Inicializamos el puerto serial
  Serial.begin(38400);  // Vel. = 38400 bit/seg
  // Evaluamos 1as mediciones
  ym=LeerMedida(0x3B);
  // La frecuencia en 1/mseg (factor=1e-3)
  w0=1e-3*2*3.1416*.1;
  delta_t=100;    // Incremento en tiempo ms
  s=-1;
  val=0;



  
}





void loop() {

medida=LeerMedida(0x3B);
AcX=acBin2g(medida);

medida=LeerMedida(0x3D);
AcY=acBin2g(medida);

medida=LeerMedida(0x3F);
AcZ=acBin2g(medida);



medida=LeerMedida(0x43);
GyX=wBin2w(medida);


medida=LeerMedida(0x45);
GyY=wBin2w(medida);



medida=LeerMedida(0x47);
GyZ=wBin2w(medida);

  
  pitch=atan2(c,b);




 }





  // ESCRIBIR EN REGISTRO
  void EscribirRegistro(byte DirRegistro,byte Dato) {
    Wire.beginTransmission(addresMPU);
    Wire.write(DirRegistro);     // Registro de escritura
    Wire.write(Dato);            // Dato a escribir
    Wire.endTransmission(true);
  }

  // ACELERACION BINARIA -> ACELERACION EN G's
  // Se realiza la conversion de binario a g's
  float acBin2g(int acBin) {
    Ac=acBin/16384.0;
    return Ac;
  }

  // VELOCIDAD ANGULAR BINARIA A REAL °/seg
  // Se realiza la conversiond de binario a °/seg
  float wBin2w(int wBin) {
    w=wBin/131.0;
    return w; 
  }

  // TEMPERATURA BINARIA A TEMPERATURA °C
  // Conversión de binario a °C
  float TBin2T(int TBin) {
    T=(TBin/340.0) + 36.53;
    return T;
  }
