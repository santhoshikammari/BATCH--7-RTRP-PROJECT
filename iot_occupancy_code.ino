
#include <LiquidCrystal.h>
#include <stdio.h>
//LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

#include <WiFi.h>
#include <HTTPClient.h>

HTTPClient http;

const char *ssid = "iotserver";
const char *password = "iotserver123";

int httpResponseCode;
String servername = "http://projectsfactoryserver.in/storedata.php?name=";
String accountname = "iot1687";
String field1 = "&s1=";
String field2 = "&s2=";
String field3 = "&s3=";
String payload="";


unsigned char rcv,count,gchr,gchr1,robos='s';
 

int sti=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int buzzer  = 23;
int ir      = 18;

int light = 21;
int fan   = 19;


#define RXD2 16
#define TXD2 17


 
void beep()
{
  digitalWrite(buzzer, LOW);delay(2000);digitalWrite(buzzer, HIGH);
}
void okcheck()
{
  unsigned char rcr;
  do{
      rcr = Serial.read();
    }while(rcr != 'K');
}

int sts1=0,sts2=0,sts3=0,sts4=0,cntlmk=0;
int stn=0;

String iot_string="";

void iot_send()
{
        lcd.setCursor(15,1);lcd.print("U");
        http.begin(servername + accountname + field1 + iot_string);
        httpResponseCode = http.GET();
        if(httpResponseCode>0) 
          {
           payload="";
           //Serial.print("HTTP Response code: ");
           //Serial.println(httpResponseCode);
           payload = http.getString();
           //Serial.println(payload);
          }
        else 
          {
            ;
           //Serial.print("Error code: ");
           //Serial.println(httpResponseCode);
          }
        delay(8000);        
        lcd.setCursor(15,1);lcd.print(" ");
}

void setup() 
{
  Serial.begin(9600);//serialEvent();
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  pinMode(ir, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(light, OUTPUT);pinMode(fan, OUTPUT);
  
  digitalWrite(buzzer, HIGH);
  digitalWrite(light, LOW);digitalWrite(fan, LOW);
  
  lcd.begin(16, 2);  
  lcd.print("IOT Occupancy");
  lcd.setCursor(0,1);
  lcd.print("  Monitoring");
  delay(2500);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) 
       {
           delay(500);
       }
  //Serial.println(WiFi.localIP());
  delay(3000);
  
  lcd.clear();  
}



void loop() 
{    
  iot_string="";
  if(digitalRead(ir) == LOW)
    {
      lcd.setCursor(0,0);lcd.print("Occupancy   ");
      iot_string="Occupancy_Light_Fan_ON";
      digitalWrite(light, HIGH);digitalWrite(fan, HIGH);
          iot_send();
      while(digitalRead(ir) == LOW);
    }
  if(digitalRead(ir) == HIGH)
    {
      lcd.setCursor(0,0);lcd.print("No Occupancy ");
      iot_string="No_Occupancy_Light_Fan_OFF";
      digitalWrite(light, LOW);digitalWrite(fan, LOW);
          iot_send();
      while(digitalRead(ir) == HIGH);    
    }

 delay(1000);
}




void serialEvent() 
{
  while (Serial.available()) 
        {
         
         char inChar = (char)Serial.read();
           if(inChar == '*')
             {
              gchr = Serial.read();
             }
           if(inChar == '#')
             {
              gchr1 = Serial.read();
             }  
        }
}

void converts(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   Serial.write(a);
   Serial.write(c);
   Serial.write(e); 
   Serial.write(g);
   Serial.write(h);
}

void convertl(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
  // lcd.write(a);
   lcd.write(c);
   lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}
