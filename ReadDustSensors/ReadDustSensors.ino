#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiHelper.h>
#include <CMDust.h>
const char* ssid     = "";
const char* pass     = "";

byte buff[2];
int pinDust = 14;
unsigned long duration,starttime,endtime,sampletime_ms = 30000,lowpulseoccupancy = 0;
float ratio = 0,concentrations = 0;
int i=0;   
char test[20];
 
Dust *dust;
WiFiHelper *wifi;
LiquidCrystal_I2C lcd(0x21, 16, 2);

void init_wifi()
{
    wifi = new WiFiHelper(ssid, pass);
    wifi->on_connected([](const char* message)
    {
        Serial.println (message);
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());     
    });
    wifi->on_disconnected([](const char* message)
    {
        Serial.println (message);
    });
    wifi->begin(); 
}

void init_hardware()
{
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println();   
}

void setup()
{
    lcd.begin();
    lcd.backlight();
    init_hardware();
    init_wifi();
    pinMode(pinDust,INPUT);
    starttime = millis();   
    lcd.setCursor(4,0);
    lcd.print("Dust Now");
    lcd.setCursor(1,1);
    lcd.print("Dust : ");
    lcd.setCursor(8, 1);
    lcd.print("0.00  ");    
   dust = new Dust(pinDust,30000);        
}

void loop()
{  
wifi->loop();
concentrations = dust->read_dust();

lcd.setCursor(8, 1);
lcd.print(concentrations);   
uploadThingsSpeak(concentrations);
}

void uploadThingsSpeak(float d) {
    static const char* host = "api.thingspeak.com";
    static const char* apiKey = "API KEY";
 
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        DEBUG_PRINTLN("connection failed");
        return;
    }  
    String url = "/update/";
    //  url += streamId;
    url += "?key=";
    url += apiKey;
    url += "&field1=";
    url += d;
 
    Serial.print("Requesting URL: ");
    Serial.println(url);
 

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
}




