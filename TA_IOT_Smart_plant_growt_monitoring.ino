//library
#include <WiFiClient.h>
#include <Esp32WifiManager.h>
#include <FB_HTTPClient32.h>
#include <FirebaseESP32.h>
#include <FirebaseJson.h>
#include <WiFi.h>

//pengaturan firebase dan jaringan
#define FIREBASE_HOST "https://ujicoba-iot.firebaseio.com/"
#define FIREBASE_AUTH "L13MA019VXhpRVmbwuCQEuqjG2iC5S821ufDXViA"
#define WIFI_SSID "Hemat kuota"
#define WIFI_PASSWORD "mamacantiknih"

//pengaturan variabel di firebase
FirebaseData firebaseData;
FirebaseJson Suhu;
FirebaseJson Jarak;
FirebaseJson LDR;

//pengaturan variabel
int sensorValue;
const int trigPin = 23;
const int echoPin = 22;
int ledPin = 2;
long duration;
int distance;
float temp;


void setup() {
//pengaturan pin
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(9600);

//connect to WiFi
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("Connecting to Wi-Fi");
while (WiFi.status() !=WL_CONNECTED)
{
Serial.print(".");
delay(300);
}
Serial.println();
Serial.print("Connected with IP: ");
Serial.println(WiFi.localIP());
Serial.println();
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.reconnectWiFi(true);
Firebase.setReadTimeout(firebaseData, 1000*60);
Firebase.setwriteSizeLimit(firebaseData, "tiny");
Serial.println("----------------------------------------");
Serial.println("Connected...");
}


void loop() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration * 0.034 / 2;
sensorValue = analogRead(A0);
temp = (analogRead(35) * 0.1875)/1000;
temp = temp * 100;
delay(50);
Serial.print("Distance: ");
Serial.println(distance);
Serial.print("intensitas cahaya: ");
Serial.println(sensorValue);
Serial.print("suhu lingkunagan: ");
Serial.println(temp);
delay(100);
Jarak.set("Jarak", distance);
Firebase.updateNode(firebaseData,"ujicoba-iot",Jarak);
LDR.set("LDR", sensorValue);
Firebase.updateNode(firebaseData,"ujicoba-iot",LDR);
Suhu.set("Suhu", temp);
Firebase.updateNode(firebaseData,"ujicoba-iot",Suhu);
if (sensorValue<=2000)
{ digitalWrite(ledPin, HIGH);
}

else{
digitalWrite(ledPin, LOW);}
if (temp<25){
Serial.println("Tutup jendela ruangan atau panaskan ruangan");
}
if (temp>28){
Serial.println("Buka jendela ruangan atau dinginkan ruangan");
}
}
