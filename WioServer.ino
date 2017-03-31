
/* 
  WioServer - Use WioSwitch To Switch Digital Pins On/Off ( D0 to D8)  
  Written by Chiming Lee 01-01-2017 under a GPL license
*/


#include <ESP8266WiFi.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";
String readStrings = "";

// GPIO16 = D0
int pinD0 = 16;

// GPIO05 = D1
int pinD1 = 5;

// GPIO04 = D2
int pinD2 = 4;

// GPIO00 = D3
int pinD3 = 0;

// GPIO02 = D4
int pinD4 = 2;

// GPIO14 = D5
int pinD5 = 14;

// GPIO12 = D6
int pinD6 = 12;

// GPIO13 = D7
int pinD7 = 13;

// GPIO15 = D8
int pinD8 = 15;

boolean pinStatus = LOW;

boolean flag = LOW;

WiFiServer server(80);

IPAddress gateway(192, 168, 1, 1);
IPAddress ip(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize serial communication
  Serial.begin(115200);
  delay(10);

  // set the LED pin mode
  pinMode(pinD0, OUTPUT);
  pinMode(pinD1, OUTPUT);
  pinMode(pinD2, OUTPUT);
  pinMode(pinD3, OUTPUT);
  pinMode(pinD4, OUTPUT);
  pinMode(pinD5, OUTPUT);
  pinMode(pinD6, OUTPUT);
  pinMode(pinD7, OUTPUT);
  pinMode(pinD8, OUTPUT);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  // attempt to connect to Wifi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(100);
  //  Serial.print(".");
  }
                                                                
  server.begin();
  Serial.println("WioServer started");
  
  // print the IP address of the network you're attached to
  Serial.println("Your Device IP address is:");
  Serial.println(WiFi.localIP());
  Serial.println("");
}

// the loop function runs over and over again forever
void loop() 
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();




  // Match the request
  if (request.indexOf("/") > 0 ) {

    // Return the response
    client.println("HTTP/1.1 200 OK\r\n");
    client.println("Content-Type: text/html\r\n");
    client.println("");
    client.println("Thank you for using WioServer and WioSwitch!\r\n");
        
    Serial.print("WioServer: ");
      
  }

  if (request.indexOf("/hello") > 0 ) {
    
    // Return the response
    client.println("HTTP/1.1 200 OK\r\n");
    client.println("Content-Type: text/html\r\n");    
    client.print("Hello, WioSwitch!\r\n");
    client.println("");
    //delay(1);
    Serial.println("Hello, WioSwitch!"); 
     
  }

  if (request.indexOf("/status") > 0 ) {
    
    // Return the response
    checkStatus();
     
  }



  if (request.indexOf("/on") > 0 ) {

    digitalWrite(pinD0, HIGH);
    digitalWrite(pinD1, HIGH);
    digitalWrite(pinD2, HIGH);
    digitalWrite(pinD3, HIGH);
    digitalWrite(pinD4, HIGH);
    digitalWrite(pinD5, HIGH);
    digitalWrite(pinD6, HIGH);
    digitalWrite(pinD7, HIGH);
    digitalWrite(pinD8, HIGH);

    Serial.println("");
    checkD0Status();
    checkD1Status();
    checkD2Status();
    checkD3Status();
    checkD4Status();
    checkD5Status();
    checkD6Status();
    checkD7Status();
    checkD8Status();
  }
  
  if (request.indexOf("/off") > 0) {

    digitalWrite(pinD0, LOW);
    digitalWrite(pinD1, LOW);
    digitalWrite(pinD2, LOW);
    digitalWrite(pinD3, LOW);
    digitalWrite(pinD4, LOW);
    digitalWrite(pinD5, LOW);
    digitalWrite(pinD6, LOW);
    digitalWrite(pinD7, LOW);
    digitalWrite(pinD8, LOW);
    
    Serial.println("");
    checkD0Status();
    checkD1Status();
    checkD2Status();
    checkD3Status();
    checkD4Status();
    checkD5Status();
    checkD6Status();
    checkD7Status();
    checkD8Status();
  }
  
  if (request.indexOf("/d0on") > 0 ) {
    
    digitalWrite(pinD0, HIGH);
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D0 is On");
    delay(1);
  
    checkD0Status();
  }

  if (request.indexOf("/d0off") > 0) {
    
    digitalWrite(pinD0, LOW);
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D0 is Off");
    delay(1);

    checkD0Status();
  }  

  if (request.indexOf("/d1on") > 0 ) {
    
    digitalWrite(pinD1, HIGH);

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D1 is On");
    delay(1);
    
    checkD1Status();
  }
  
  if (request.indexOf("/d1off") > 0) {
    
    digitalWrite(pinD1, LOW);
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D1 is Off");
    delay(1);
    
    checkD1Status();
  }
  

  if (request.indexOf("/d2on") > 0 ) {
    
    digitalWrite(pinD2, HIGH);
        
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D2 is On");
    delay(1);
    
    checkD2Status();
  }
  
  if (request.indexOf("/d2off") > 0) {
    
    digitalWrite(pinD2, LOW);
       
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D2 is Off");
    delay(1);
    
    checkD2Status();
  }
  

  if (request.indexOf("/d3on") > 0 ) {
    
    digitalWrite(pinD3, HIGH);
        
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D3 is On");
    delay(1);
    
    checkD3Status();
  }
  
  if (request.indexOf("/d3off") > 0) {
    
    digitalWrite(pinD3, LOW);
       
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D3 is Off");
    delay(1);
    
    checkD3Status();
  }
  
  if (request.indexOf("/d4on") > 0 ) {
    
    digitalWrite(pinD4, HIGH); 
       
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D4 is On");
    delay(1);
    
    checkD4Status();
  }
  
  if (request.indexOf("/d4off") > 0) {
    
    digitalWrite(pinD4, LOW);
       
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D4 is Off");
    delay(1);
    checkD4Status();
  }
  
  if (request.indexOf("/d5on") > 0 ) {
    
    digitalWrite(pinD5, HIGH);
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D5 is On");
    delay(1);
    
    checkD5Status();
  }
  
  if (request.indexOf("/d5off") > 0) {
    
    digitalWrite(pinD5, LOW);
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D5 is Off");
    delay(1);
    checkD5Status();
  }
  
  if (request.indexOf("/d6on") > 0 ) {
    
    digitalWrite(pinD6, HIGH);
       
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D6 is On");
    delay(1);
    
    checkD6Status();
  }
  
  if (request.indexOf("/d6off") > 0) {
    
    digitalWrite(pinD6, LOW);
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D6 is Off");
    delay(1);
    
    checkD6Status();
  }
  
  if (request.indexOf("/d7on") > 0 ) {
    
    digitalWrite(pinD7, HIGH);
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D7 is On");
    delay(1);
    
    checkD7Status();
  }
  
  if (request.indexOf("/d7off") > 0) {
    
    digitalWrite(pinD7, LOW); 

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D7 is Off");
    delay(1);
    
    checkD7Status();
  }
  
  if (request.indexOf("/d8on") > 0 ) {
    
    digitalWrite(pinD8, HIGH);

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D8 is On");
    delay(1);
    
    checkD8Status();
  }
  
  if (request.indexOf("/d8off") > 0) {
    
    digitalWrite(pinD8, LOW);

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D8 is Off");
    delay(1);
    
    checkD8Status();
  }



  

  if (request.indexOf("/d0input") > 0) {
   
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D0 is set mode to input");
    delay(1);

    D0ModeInput();
    
    }

  if (request.indexOf("/d0output") > 0) {
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D0 is set mode to output");
    delay(1);

    D0ModeOutput();
   
    }

  if (request.indexOf("/d1input") > 0) {
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D1 is set mode to input");
    delay(1);

    D1ModeInput();
    
    }

  if (request.indexOf("/d1output") > 0) {

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D1 is set mode to output");
    delay(1);

    D1ModeOutput();
   
    }

  if (request.indexOf("/d2input") > 0) {

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D2 is set mode to input");
    delay(1);

    D2ModeInput();
    
    }

  if (request.indexOf("/d2output") > 0) {

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D2 is set mode to output");
    delay(1);

    D2ModeOutput();

    }        

  if (request.indexOf("/d3input") > 0) {

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D3 is set mode to input");
    delay(1);

    D3ModeInput();
    
    }

  if (request.indexOf("/d3output") > 0) {

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D3 is set mode to output");
    delay(1);

    D3ModeOutput();
 
    }

  if (request.indexOf("/d4input") > 0) {
        
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D4 is set mode to input");
    delay(1);

    D4ModeInput();
    
    }

  if (request.indexOf("/d4output") > 0) {

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D4 is set mode to output");
    delay(1);

    D4ModeOutput();
   
    }


  if (request.indexOf("/d5input") > 0) {
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D5 is set mode to input");
    delay(1);

    D5ModeInput();
    
    }

  if (request.indexOf("/d5output") > 0) {

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D5 is set mode to output");
    delay(1);

    D5ModeOutput();
  
    }

  if (request.indexOf("/d6input") > 0) {

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D6 is set mode to input");
    delay(1);

    D6ModeInput();
    
    }

   if (request.indexOf("/d6output") > 0) {

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D6 is set mode to output");
    delay(1);

    D6ModeOutput();
    
    }

   if (request.indexOf("/d7input") > 0) {
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D7 is set mode to input");
    delay(1);
    
    D7ModeInput();
    
    }

   if (request.indexOf("/d7output") > 0) {
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D7 is set mode to output");
    delay(1);

    D7ModeOutput();
  
    
    }

  if (request.indexOf("/d8input") > 0) {
  
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D8 is set mode to input");
    delay(1);

    D8ModeInput();
    
    }

   if (request.indexOf("/d8output") > 0) {

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");    
    client.println("");
    client.print("WioServer: D8 is set mode to output");
    delay(1);

    D8ModeOutput();

    }



  //delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}


void D0ModeInput(){
    
    pinMode(pinD0, INPUT);
    checkD0Status();
  }

void D0ModeOutput(){
    
    pinMode(pinD0, OUTPUT);
    checkD0Status();
  
}

void D1ModeInput(){
    
    pinMode(pinD1, INPUT);
    checkD1Status();
  }

void D1ModeOutput(){
    
    pinMode(pinD1, OUTPUT);
    checkD1Status();
  
}

void D2ModeInput(){
    
    pinMode(pinD2, INPUT);
    checkD2Status();
  }

void D2ModeOutput(){
    
    pinMode(pinD2, OUTPUT);
    checkD2Status();
  
}

void D3ModeInput(){
    
    pinMode(pinD3, INPUT);
    checkD3Status();
  }

void D3ModeOutput(){
    
    pinMode(pinD3, OUTPUT);
    checkD3Status();
  
}

void D4ModeInput(){
    
    pinMode(pinD4, INPUT);
    checkD4Status();
  }

void D4ModeOutput(){
    
    pinMode(pinD4, OUTPUT);
    checkD4Status();
  
}

void D5ModeInput(){
    
    pinMode(pinD5, INPUT);
    checkD5Status();
  }

void D5ModeOutput(){
    
    pinMode(pinD5, OUTPUT);
    checkD5Status();
  
}

void D6ModeInput(){
    
    pinMode(pinD6, INPUT);
    checkD6Status();
  }

void D6ModeOutput(){
    
    pinMode(pinD6, OUTPUT);
    checkD6Status();
  
}

void D7ModeInput(){
    
    pinMode(pinD7, INPUT);
    checkD7Status();
  }

void D7ModeOutput(){
    
    pinMode(pinD7, OUTPUT);
    checkD7Status();
  
}

void D8ModeInput(){
    
    pinMode(pinD8, INPUT);
    checkD8Status();
  }

void D8ModeOutput(){
    
    pinMode(pinD8, OUTPUT);
    checkD8Status();
  
}




void checkStatus()
{
  checkD0Status();
  checkD1Status();
  checkD2Status();
  checkD3Status();
  checkD4Status();
  checkD5Status();
  checkD6Status();
  checkD7Status();
  checkD8Status();  
}




void checkD0Status()
{
  if (digitalRead(pinD0) != HIGH ) {

    Serial.println("D0 is Off");
      
  }

  else {

    Serial.println("D0 is On"); 
      
  }

}

void checkD1Status()
{
  
  if (digitalRead(pinD1) != HIGH ) {

    Serial.println("D1 is Off");
      
  }

  else {

    Serial.println("D1 is On");
      
  }
  
}

void checkD2Status()
{
  if (digitalRead(pinD2) != HIGH ) {

    Serial.println("D2 is Off");
      
  }

  else {

    Serial.println("D2 is On");
      
  }
  
}

void checkD3Status()
{
  
  if (digitalRead(pinD3) != HIGH ) {

    Serial.println("D3 is Off");
      
  }

  else {

    Serial.println("D3 is On");
      
  }

}

void checkD4Status()
{
  if (digitalRead(pinD4) != HIGH ) {

    Serial.println("D4 is Off");
      
  }

  else {

    Serial.println("D4 is On");
      
  }
  
}

void checkD5Status()
{
  if (digitalRead(pinD5) != HIGH ) {

    Serial.println("D5 is Off");
      
  }

  else {

    Serial.println("D5 is On");
      
  }
  
}

void checkD6Status()
{
  if (digitalRead(pinD6) != HIGH ) {

    Serial.println("D6 is Off");
      
  }

  else {

    Serial.println("D6 is On");
      
  }
  
}

void checkD7Status()
{
  if (digitalRead(pinD7) != HIGH ) {

    Serial.println("D7 is Off");
      
  }

  else {

    Serial.println("D7 is On");
      
  }
  
}

void checkD8Status()
{
  if (digitalRead(pinD8) != HIGH ) {

    Serial.println("D8 is Off");
      
  }

  else {

    Serial.println("D8 is On");
      
  }
  
}


