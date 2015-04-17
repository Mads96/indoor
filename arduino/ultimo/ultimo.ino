
#include "DHT.h"
DHT dht1(2,DHT22); 
DHT dht2(3,DHT22); 
int l=0;
int lx=0;
void setup() {
  Serial.begin(9600); 
  Serial.println("InternetdelasCosas.cl\n\nPrueba de sensor DHTxx!");
  dht1.begin();
}

void loop() {

  delay(2000);
  float h = dht1.readHumidity();
  float t = dht1.readTemperature();
  float h1 = dht2.readHumidity();
  float t1 = dht2.readTemperature();
  lx=analogRead (0);
  if (isnan(h) || isnan(t)) {
    Serial.println("Falla al leer el sensor DHT!");
    return;
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
}
