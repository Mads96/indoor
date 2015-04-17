
#include "DHT.h"

#define DHTPIN 2     // Pin del Arduino al cual esta conectado el pin 2 del sensor

// Descomentar segun el tipo de sensor DHT usado
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Diagrama
// Pin 1 Sensor a +5V de Arduino
// Pin 2 Sensor a HDTPIN (en este sketch es el pin 2)
// Pin 4 Sensor a GROUND de  Arduino
// Resistencia de 10K desde Pin 2 de sensor a Pin 1 de Sensor o +5V

// Inicializa el sensor
DHT dht(DHTPIN, DHTTYPE);

// Configura Arduino 
void setup() {
  Serial.begin(9600); 
  Serial.println("InternetdelasCosas.cl\n\nPrueba de sensor DHTxx!");
 
  dht.begin();
}

void loop() {
  // Espera dos segundos para realizar la primera medición.
  delay(2000);

  // Lee los datos entregados por el sensor, cada lectura demora 250 milisegundos
  // El sensor muestrea la temperatura cada 2 segundos}
  
  // Obtiene la Humedad
  float h = dht.readHumidity();
  // Obtiene la Temperatura en Celsius
  float t = dht.readTemperature();
  
  // Control de errores, valida que se obtuvieron valores para los datos medidos
  if (isnan(h) || isnan(t)) {
    Serial.println("Falla al leer el sensor DHT!");
    return;
  }

  Serial.print("Humedad: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: "); 
  Serial.print(t);
  Serial.println(" *C ");
}
