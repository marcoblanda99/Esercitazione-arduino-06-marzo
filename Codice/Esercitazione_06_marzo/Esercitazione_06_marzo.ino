#include <HCSR04.h>
UltraSonicDistanceSensor distanceSensor(13, 12);

#include <DHT.h>
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

int ledG = 7;
int ledR1 = 3;
int ledR2 = 5;
int pushb = 2;
int value = 0;
unsigned long last_now = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(ledG, OUTPUT);
  pinMode(ledR1, OUTPUT);
  pinMode(ledR2, OUTPUT);
  pinMode(pushb, INPUT);
  Serial.println("time, prossimity, temperature, relative humidity");
  

}

void loop() {
  unsigned long now = millis();

  if (now - last_now >= 1000){
    last_now = now;
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print(now / 1000);
    digitalWrite (ledG, HIGH);
    delay(15);
    Serial.print(", ");
    Serial.print(t);
    Serial.print(F("°C, "));
    Serial.print(h);
    Serial.print(F("%, "));
    Serial.print(distanceSensor.measureDistanceCm());
    Serial.println("Cm");
    digitalWrite (ledG, LOW);
    delay(15);
 
 if (t > 30) {
      digitalWrite (ledR1, HIGH);
    } else {
      digitalWrite (ledR1, LOW);
    }
    if (h < 50) {
      digitalWrite (ledR2, HIGH);
    }
  }

  value= digitalRead(pushb);

   if (value==1){
   
      digitalWrite (ledR1, LOW);
      digitalWrite (ledR2, LOW); 
  }
  

}
