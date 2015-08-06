#include <SPI.h>  //Importamos librería comunicación SPI
#include <Ethernet.h>  //Importamos librería Ethernet

//en este caso s= salidas (luz, ventilador, etc.., en ves de s se le puede asignar cualquier nombre). y declararemos E = entradas.
//al estar conectado el shield ethernet solo podemos contar con los pines digitales desde el 2 hasta el 9, exceptuando el pin 4 que sera usado por la MicroSD

 //DHT
 #include "DHT.h"
DHT dht1(2,DHT22); //sensor 1
DHT dht2(3,DHT22); //sensor 2
 //fin DHT
float tierra1;
float tierrax1;
float tierra2;
float tierrax2;
float luz1;
float luzx1;
float luz2;
float luzx2;





byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//Ponemos la dirección MAC de la Ethernet Shield que está con una etiqueta debajo la placa
IPAddress ip(192,168,1,24); //Asingamos la IP al Arduino
EthernetServer server(80); //Creamos un servidor Web con el puerto 80 que es el puerto HTTP por defecto
 
void setup()
{
  Serial.begin(9600);
  // Inicializamos la comunicación Ethernet y el servidor
  Ethernet.begin(mac, ip);
  ///DHT
  dht1.begin();
  //fin DHT
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
 
}
 
void loop()
{
  
  //DHT
   delay(2000);
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  
  luzx1=analogRead (2);
  luz1=((100*luzx1)/1024);

  luzx2=analogRead (3);
  luz2=((100*luzx2)/1024);
  
  tierrax1 = analogRead(0);
  tierra1=((100*tierrax1)/1024);

  tierrax2 = analogRead(1);
  tierra2=((100*tierrax2)/1024);

  
  if (isnan(h1) || isnan(t1)) {
    Serial.println("Falla al leer el sensor DHT_1!");
    
  }
    if (isnan(h2) || isnan(t2)) {
    Serial.println("Falla al leer el sensor DHT_2!");
    
  }
  //fin DHT

  //MONITOREO POR CONSOLA!!//////////////////////////////////////
  Serial.print("Tierra 1= ");
  Serial.println(tierra1); //lectura analógica
    Serial.print("Tierra 2= ");
    
  Serial.println(tierra2); //lectura analógica
    Serial.print("Tierra 3= ");

  Serial.println(h1); //lectura analógica
    Serial.print("Humedad 2= ");
  Serial.println(h2); //lectura analógica

    Serial.print("Temperatura 1= ");
  Serial.println(t1); //lectura analógica
    Serial.print("Temperatura 2= ");
  Serial.println(t2); //lectura analógica

  delay(50);
  //FIN MONITOREO POR CONSOLA!!//////////////////////////////////////
  
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
cliente.print("<meta http-equiv=\"Refresh\" content=\"2;url=http://desarrollo.mads96.cl/monitoreo.php");
//cliente.print("GET http://desarrollo.mads96.cl/sensorarduino.php");
cliente.print("?iduser=01");
cliente.print("&h1=");
cliente.print(h1);
cliente.print("&t1=");
cliente.print(t1);
cliente.print("&h2=");
cliente.print(h2);
cliente.print("&t2=");
cliente.print(t2);
cliente.print("&ht1=");
cliente.print(tierra1);
cliente.print("&ht2=");
cliente.print(tierra2);
cliente.print("&l1=");
cliente.print(luz1);
cliente.print("&l2=");
cliente.print(luz2);



cliente.print("\">");
cliente.println("<title>Monitoreo</title>");
cliente.println("<meta name=\"viewport\" content=\"width=device-width, minimum-scale=1.0, maximum-scale=1.0\" />");
cliente.println("</head>");
cliente.println("<body bgcolor=\"green\">");
cliente.println("<img src=\"http://desarrollo.mads96.cl/imagenes/cargando.gif\"><font color=\"white\"><h2>cargando datos...</h2></font>");
cliente.println("<br/>");
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
