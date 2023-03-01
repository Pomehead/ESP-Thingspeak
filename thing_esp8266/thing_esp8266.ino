
#include <ESP8266WiFi.h>
String apiKey = "P4V9BZIHR5AILQ7J";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "wifissid";     // replace with your wifi ssid 
const char *pass =  "123456789"; //replace with your wifi password
const char* server = "api.thingspeak.com";
 
#define sensor 0         //pin where the sensor is connected here A0
 
 
WiFiClient client;
 
void setup() 
{
       Serial.begin(9600);
       delay(10); 
       Serial.println("Connecting to ");
       Serial.println(ssid);
      pinMode(sensor,INPUT);
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  int temp_adc_val;
  float t;
  temp_adc_val = analogRead(sensor); // Read Temperature 
  t = ((temp_adc_val/1024.0) * 3300); 
  t = (t/10); 
             if (isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                           Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
