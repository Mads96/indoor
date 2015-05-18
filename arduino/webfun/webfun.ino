 #include <SPI.h>  //Importamos librería comunicación SPI
#include <Ethernet.h>  //Importamos librería Ethernet

//en este caso s= salidas (luz, ventilador, etc.., en ves de s se le puede asignar cualquier nombre). y declararemos E = entradas.
//al estar conectado el shield ethernet solo podemos contar con los pines digitales desde el 2 hasta el 9, exceptuando el pin 4 que sera usado por la MicroSD

 //DHT
 #include "DHT.h"
DHT dht1(2,DHT22); 
DHT dht2(3,DHT22); 
DHT dht3(5,DHT22); 
int l=0;
int lx=0;
 //fin DHT


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//Ponemos la dirección MAC de la Ethernet Shield que está con una etiqueta debajo la placa
IPAddress ip(192,168,0,24); //Asingamos la IP al Arduino
EthernetServer server(80); //Creamos un servidor Web con el puerto 80 que es el puerto HTTP por defecto
 
int s1=8; //Pin del led
int s2=4;
String est1="OFF"; //Estado del Led inicialmente "OFF"
String est2="OFF";
void setup()
{
  Serial.begin(9600);
 pinMode(10, INPUT);
  // Inicializamos la comunicación Ethernet y el servidor
  Ethernet.begin(mac, ip);
  ///DHT
  dht1.begin();
  //fin DHT
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
 
  pinMode(s1,OUTPUT);
}
 
void loop()
{
  Serial.println(analogRead(0)); //lectura analógica
	Serial.println(digitalRead(10)); //lectura digital
	delay(100);
  //DHT
   delay(2000);
  float h = dht1.readHumidity();
  float t = dht1.readTemperature();
  float h1 = dht2.readHumidity();
  float t1 = dht2.readTemperature();
   float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  lx=analogRead (1);
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Falla al leer el sensor DHT!");
    return;
  }
  //fin DHT
  
  EthernetClient cliente = server.available(); //Creamos un cliente Web
  //Cuando detecte un cliente a través de una petición HTTP
  if (cliente) {
    Serial.println("new client");
    boolean currentLineIsBlank = true; //Una petición HTTP acaba con una línea en blanco
    String cadena=""; //Creamos una cadena de caracteres vacía
    while (cliente.connected()) {
      if (cliente.available()) {
        char c = cliente.read();//Leemos la petición HTTP carácter por carácter
        Serial.write(c);//Visualizamos la petición HTTP por el Monitor Serial
        cadena.concat(c);//Unimos el String 'cadena' con la petición HTTP (c). De esta manera convertimos la petición HTTP a un String
 
         //Ya que hemos convertido la petición HTTP a una cadena de caracteres, ahora podremos buscar partes del texto.
        int p1=cadena.indexOf("a="); //Guardamos la posición de la instancia "LED=" a la variable 'posicion'
        int p2=cadena.indexOf("b=");
 
 
 
       if(cadena.substring(p1)=="a=OFF")//Si a la posición 'posicion' hay "LED=ON"
          {
            digitalWrite(s1,HIGH);
            est1="ON";
          }
       if(cadena.substring(p1)=="a=ON")//Si a la posición 'posicion' hay "LED=OFF"
          {
            digitalWrite(s1,LOW);
            est1="OFF";
          }



///////////////////////////////////////

if(cadena.substring(p2)=="b=OFF")//Si a la posición 'posicion' hay "LED=ON"
          {
            digitalWrite(s2,HIGH);
            est2="ON";
          }
if(cadena.substring(p2)=="b=ON")//Si a la posición 'posicion' hay "LED=OFF"
          {
            digitalWrite(s2,LOW);
            est2="OFF";
          }


//////////////////////////////////////
        //Cuando reciba una línea en blanco, quiere decir que la petición HTTP ha acabado y el servidor Web está listo para enviar una respuesta
        if (c == '\n' && currentLineIsBlank) {
 
            // Enviamos al cliente una respuesta HTTP
            cliente.println("HTTP/1.1 200 OK");
            cliente.println("Content-Type: text/html");
            cliente.println();
            
            
            
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////////////////////////////
           //AQUI COMIENZA LA PAGINA WEBSERVER 

//Cabecera HTTP estándar
cliente.println("<!DOCTYPE html>"); 
//cliente.println("Content-Type: text/html"); 
//cliente.println(); //Página Web en HTML 
cliente.println("<html>"); 
cliente.println("<head>"); 
cliente.println("<meta http-equiv=Content-Type content=text/html; charset=utf-8 />");
cliente.print("<meta http-equiv=\"Refresh\" content=\"15;url=http://localhost/indoor/lampm.php");
cliente.print("?s1=");
cliente.print(est1);
cliente.print("&s2=");
cliente.print(est2);


cliente.print("\">");
cliente.println("<title>Titulo de tu web</title>");
cliente.println("</head>");
cliente.println("<body>");
cliente.println("Cargando Datos,");
cliente.println("<br/>");
cliente.println("H1=");
cliente.println(h);
cliente.println("<br/>");
cliente.println("T1=");
cliente.println(t);
cliente.println("<br/>");
cliente.println("<br/>");
cliente.println("H2=");
cliente.println(h1);
cliente.println("<br/>");
cliente.println("T2=");
cliente.println(t1);
cliente.println("<br/>");
cliente.println("<br/>");
cliente.println("H3=");
cliente.println(h2);
cliente.println("<br/>");
cliente.println("T3=");
cliente.println(t2);

//cliente.println(h);
//cliente.println(h1);
//cliente.println(t1);
//cliente.println(lx);
cliente.println("</body>");
      
            break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    //Dar tiempo al navegador para recibir los datos
    delay(1);
    cliente.stop();// Cierra la conexión
  }
}
