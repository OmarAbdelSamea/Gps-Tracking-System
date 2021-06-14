/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>



const char* ssid = "Omar AbdelSamea";
const char* password = "bringMeThanos";

//Your Domain name with URL path or IP address with path
String serverName = "http://csegps.herokuapp.com/update";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

int i=0; 
char temp;
char lat[50] ;
char lon[50] ;
char distance[50] ;
unsigned char str[300];
bool firstTime = true;


WiFiClient wifiClient;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  //Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}
//S100L100D100N
void loop() {
      //Check WiFi connection status
      if(WiFi.status()== WL_CONNECTED){
        HTTPClient http;
        Serial.print("S not found");
        // Your Domain name with URL path or IP address with path'
        if(firstTime){
          while(Serial.available()==0);
          temp = Serial.read();
          firstTime= false;
          }

        if(temp=='S'){
        Serial.print("S found");
        while(Serial.available()==0);
        temp = Serial.read();
        while(temp != 'L'){   
            Serial.print("L not found");     
            lat[i] = temp;
            while(Serial.available()==0);
            temp = Serial.read();
            i++;
            }
            lat[i]='\0';
            Serial.print("lat done");
          }
          /*for(int i =0;i<4;i++){
            Serial.println(lat[i]);
           }*/
        i=0;
        if(temp=='L'){
          while(Serial.available()==0);
          temp = Serial.read();
          while(temp != 'D'){  
            lon[i] = temp;
            while(Serial.available()==0);
            temp = Serial.read();
            i++;
            }
            lon[i]='\0';
          }
          /*for(int i =0;i<4;i++){
            Serial.println(lon[i]);
            }*/
        i=0;
        if(temp=='D'){
          while(Serial.available()==0);
          temp = Serial.read();
          while(temp != 'N'){  
            distance[i] = temp;
            while(Serial.available()==0);
            temp = Serial.read();
            i++;
            }
            distance[i]='\0';
          }
          /*for(int i =0;i<4;i++){
            Serial.println(distance[i]);
            }*/
        // Send HTTP GET request
        if(temp=='N'){
        Serial.print("N here");
        String test;
        test.concat(lat);
        String test2;
        test2.concat(lon);
        String test3;
        test3.concat(distance);
        
        //String postdata="{lat="+test+",long="+test2+",distance="+test3+"}";//{lat=1,long=2,distance=3}
        String postdata = "?lat="+test+"&long="+test2+"&distance="+test3;
        Serial.print(postdata);
        String serverPath = serverName + postdata;
        http.begin(wifiClient,serverPath);
        //http.addHeader("Content-Type", "application/json");
        
        int httpResponseCode = http.GET();
        Serial.print("Sent");
        if (httpResponseCode>0) {
          //Serial.print("HTTP Response code: ");
          //Serial.println(httpResponseCode);
          String payload = http.getString();
          //Serial.println(payload);
        }
        else {
          //Serial.print("Error code: ");
          //Serial.println(httpResponseCode);
          String payload = http.getString();
          //Serial.println(payload);
        }
        // Free resources
        http.end();
        firstTime =true;
      }
    }
    else {
            Serial.print("spam  ");
    }
}
