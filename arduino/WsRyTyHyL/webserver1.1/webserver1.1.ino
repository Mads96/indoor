//librerias
#include <SPI.h>
#include <Ethernet.h> 
//DTH
#include "DHT.h"
DHT dht1(2,DHT22); 
DHT dht2(3,DHT22); 
int l=0;
int lx=0;
//fin DTH

//Declaración de la direcciones MAC e IP. También del puerto 80 
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0,24);
EthernetServer servidor(80);


//declara los pines
//en este caso s= salidas (luz, ventilador, etc.., en ves de s se le puede asignar cualquier nombre). y declararemos E = entradas.
//al estar conectado el shield ethernet solo podemos contar con los pines digitales desde el 2 hasta el 9, exceptuando el pin 4 que sera usado por la MicroSD
int s1=8;
int s2=3;
int s3=5;
int s4=6;
int s5=7;
int s6=2;
int s7=9;



//lee los caracteres de una secuencia en una cadena. Los strings se representan como arrays de caracteres (tipo char)... ESTO NO LO ENTIENDO... ESTUDIARLO PRONTO...
String readString=String(30); 
String stado1=String(3);
String stado2=String(3);
String stado3=String(3);
String stado4=String(3);
String stado5=String(3);
String stado6=String(3);
String stado7=String(3);



//aqui declaro los estados las variables int (int son variables de numeros enteros):

void setup() {
  //inicio DTH
  Serial.begin(9600); 
  Serial.println("MADS96.cl\n\nIN DOOR!");
  Serial.println();
  dht1.begin();
  //fin DTH
  
Ethernet.begin(mac, ip); //Inicializamos con las direcciones asignadas 
servidor.begin(); 

pinMode(s1,OUTPUT); //asigno s1 (pin 2) como salida digital.
digitalWrite(s1,LOW); //indico que el estado inicial de s1 sera apagado.

pinMode(s2,OUTPUT); //asigno s2 (pin 3) como salida digital.
digitalWrite(s2,LOW); //indico que el estado inicial de s1 sera apagado.

pinMode(s3,OUTPUT); //asigno s1 (pin 5) como salida digital.
digitalWrite(s3,LOW); //indico que el estado inicial de s1 sera apagado.

pinMode(s4,OUTPUT); //asigno s1 (pin 6) como salida digital.
digitalWrite(s4,LOW); //indico que el estado inicial de s1 sera apagado.

pinMode(s5,OUTPUT); //asigno s1 (pin 7) como salida digital.
digitalWrite(s5,LOW); //indico que el estado inicial de s1 sera apagado.

pinMode(s6,OUTPUT); //asigno s1 (pin 8) como salida digital.
digitalWrite(s6,LOW); //indico que el estado inicial de s1 sera apagado.

pinMode(s7,OUTPUT); //asigno s1 (pin 9) como salida digital.
digitalWrite(s7,LOW); //indico que el estado inicial de s1 sera apagado.


//asigno valores iniciales a las variables creadas anteriormente como string (string son variables de texto):
stado1="OFF";
stado2="OFF";
stado3="OFF";
stado4="OFF";
stado5="OFF";
stado6="OFF";
stado7="OFF";

}



//aqui comienza el programa que se correra eternamente.
void loop() {
  
  //inicio DTH
    delay(2000);
  float h = dht1.readHumidity();
  float t = dht1.readTemperature();
  float h1 = dht2.readHumidity();
  float t1 = dht2.readTemperature();
  lx=analogRead (0);
  if (isnan(h) || isnan(t)) {
    Serial.println("Falla al leer el sensor DHT!");
    
  }
  Serial.print("Humedad: "); 
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("Temperatura: "); 
  Serial.print(t);
  Serial.println(" *C ");
  Serial.print("Humedad: "); 
  Serial.print(h1);
  Serial.println(" %\t");
  Serial.print("Temperatura: "); 
  Serial.print(t1);
  Serial.println(" *C ");
  Serial.print("LUZ: "); 
  Serial.print(lx);
  Serial.println(" brillo ");
  Serial.println();

  //Fin DTH
  
//NO LO ENTIENDO... Desde aqui   
//EthernetClient Crea un cliente que se puede conectar a una dirección específica de Internet IP...  
EthernetClient cliente= servidor.available(); 
if(cliente) {
boolean lineaenblanco=true; 
String cadena=""; 
while(cliente.connected()) {
if(cliente.available()) {
char c=cliente.read(); 
if(readString.length()<30) {
readString.concat(c);
Serial.write(c);
cadena.concat(c);
//Cliente conectado
//Leemos petición HTTP caracter a caracter
//Almacenar los caracteres en la variable readString
} 

//NO LO ENTIENDO... hasta aqui

//esto lo entiendo pero no lo COMPRENDO!!! ¿que diablos... ?

//S1
if(c=='\n' && lineaenblanco) //Si la petición HTTP ha finalizado 
{
int LED = cadena.indexOf("s1="); 
if(cadena.substring(LED)=="s1=ON") {
digitalWrite(s1,LOW);
stado1="OFF"; } 
else if (cadena.substring(LED)=="s1=OFF") {
digitalWrite(s1,HIGH); 
stado1="ON";
}


//AQUI COMIENZA LA PAGINA WEBSERVER 

//Cabecera HTTP estándar
cliente.println("HTTP/1.1 200 OK"); 
cliente.println("Content-Type: text/html"); 
cliente.println(); //Página Web en HTML 
cliente.println("<html>"); 
cliente.println("<head>"); 
cliente.println("<meta http-equiv=Content-Type content=text/html; charset=utf-8 />");

//cliente.println("<meta http-equiv=\"Refresh\" content=\"5;url=http://localhost/indoor/lampm.php?id=\"");
//cliente.println(stado1);
//cliente.println("/>");



cliente.print("<meta http-equiv=\"Refresh\" content=\"5;url=http://localhost/indoor/lampm.php");
cliente.print("?s1=");
cliente.print(stado1);
cliente.print("&");
cliente.print(cadena);
cliente.print("&");
cliente.print(LED);
cliente.print("\">");




//cliente.println("<script type=\"text/javascript\">");
//cliente.print("window.location=\"http://www.mads96.com");
//cliente.print("?e1=");
//cliente.print(stado1);
//cliente.print(";</script>");





cliente.println("<title>Titulo de tu web</title>");
cliente.println("</head>");
cliente.println("<body>");
cliente.println("<A HREF=\"http://www.google.com\">hola mundo</A>");
cliente.println(h);
cliente.println(h1);
cliente.println(t1);
cliente.println(lx);
cliente.println("</body>");
 break;
        }
        if (c == '\n') {
          lineaenblanco = true;
        }
        else if (c != '\r') {
          lineaenblanco = false;
        }
      }
    }
    //Dar tiempo al navegador para recibir los datos
    delay(1);
    cliente.stop();// Cierra la conexión
  }
}

