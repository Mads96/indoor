//librerias
#include <SPI.h>
#include <Ethernet.h> 

//Declaración de la direcciones MAC e IP. También del puerto 80 
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0,24);
EthernetServer servidor(80);


//declara los pines
//en este caso s= salidas (luz, ventilador, etc.., en ves de s se le puede asignar cualquier nombre). y declararemos E = entradas.
//al estar conehctado el shield ethernet solo podemos contar con los pines digitales desde el 2 hasta el 9, exceptuando el pin 4 que sera usado por la MicroSD
int s1=2;
int s2=3;
int s3=5;
int s4=6;
int s5=7;
int s6=8;
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
  
  
//NO LO ENTIENDO... Desde aqui   
//EthernetClient Crea un cliente que se puede conectar a una dirección específica de Internet IP...  
EthernetClient cliente= servidor.available(); 
if(cliente) {
boolean lineaenblanco=true; 
while(cliente.connected()) {
if(cliente.available()) {
char c=cliente.read(); 
if(readString.length()<30) {
readString.concat(c);
//Cliente conectado
//Leemos petición HTTP caracter a caracter
//Almacenar los caracteres en la variable readString
} 

//NO LO ENTIENDO... hasta aqui

//esto lo entiendo pero no lo COMPRENDO!!! ¿que diablos... ?

//S1
if(c=='\n' && lineaenblanco) //Si la petición HTTP ha finalizado 
{
int LED = readString.indexOf("LED="); 
if(readString.substring(LED,LED+5)=="LED=a") {
digitalWrite(s1,HIGH);
stado1="ON"; } 
else if (readString.substring(LED,LED+5)=="LED=b") {
digitalWrite(s1,LOW); 
stado1="OFF";
}


//AQUI COMIENZA LA PAGINA WEBSERVER 

//Cabecera HTTP estándar
cliente.println("HTTP/1.1 200 OK"); 
cliente.println("Content-Type: text/html"); 
cliente.println(); //Página Web en HTML 
cliente.println("<html>"); 
cliente.println("<head>"); 
cliente.println("<meta http-equiv=Content-Type content=text/html; charset=utf-8 />");
cliente.println("<title>Titulo de tu web</title>");
cliente.println("</head>");
cliente.println("<body>");
cliente.println(stado1);
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



