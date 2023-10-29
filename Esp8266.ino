#include <ESP8266WiFi.h>

#include <Servo.h>

Servo servo;
Servo servo_2;

 

const char* ssid = "bot_test";  //YOUR SSID

const char* password = "bot_test";  //YOUR WIFI PSSWORD


WiFiServer server(80);

 

void setup() {

  Serial.begin(115200);

  delay(10);

  servo.attach(5); //D1 of nodemcu with pwm pin of servo motor
  servo_2.attach(0);

  // Connect to WiFi network

  Serial.println();

  Serial.println();

  Serial.print("Connecting to ");

  Serial.println(ssid);

 

  WiFi.begin(ssid, password);

 

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi connected");

 

  // Start the server

  server.begin();

  Serial.println("Server started");

 

  // Print the IP address on serial monitor

  Serial.print("Use this URL to connect: ");

  Serial.print("http://");    //URL IP to be typed in mobile/desktop browser

  Serial.print(WiFi.localIP());

  Serial.println("/");

 

}

 

void loop() {

  // Check if a client has connected

  WiFiClient client = server.available();

  if (!client) {

    return;

  }

 

  // Wait until the client sends some data

  Serial.println("new client");

  while(!client.available()){

    delay(1);

  }

 

  // Read the first line of the request

  String request = client.readStringUntil('\r');

  Serial.println(request);

  client.flush();


 int value = 0;

 // Match the request


if (request.indexOf("/Req=0") != -1)  {

  servo.write(0); //Moving servo to 0 degree

  value=0;

}

if (request.indexOf("/Req=90") != -1)  {  

  servo.write(90); //Moving servo to 90 degree

  value=90;

}

if (request.indexOf("/Req=180") != -1)  { 

  servo.write(180); //Moving servo to 180 degree

  value=180;

}  

if (request.indexOf("/Req_2=0") != -1)  {

  servo_2.write(0); //Moving servo to 0 degree

  value=0;

}

if (request.indexOf("/Req_2=90") != -1)  {  

  servo_2.write(90); //Moving servo to 90 degree

  value=90;

}

if (request.indexOf("/Req_2=180") != -1)  { 

  servo_2.write(180); //Moving servo to 180 degree

  value=180;

}  

  Serial.print("Servo Angle:");


  

  // Return the response

  client.println("HTTP/1.1 200 OK");

  client.println("Content-Type: text/html");

  client.println(""); //  

  client.println("<!DOCTYPE HTML>");

  client.println("<html>");

  client.println("<h1 align=center>Drug Dispenser Beta Testing</h1><br><br>");

  client.print("~ Aditya");


  client.println("<br><br>");

  client.println("<h2>Pack 1 </h1><br>");
  client.println("<a href=\"/Req=180\"\"><button  text-align: left; style='font-size: 100px;'>Drop 1</button></a><br><br>");
  client.println("<a href=\"/Req=0\"\"><button text-align: right; style='font-size: 100px;'>Reset 1</button></a>");
  client.println("<hr>");
  client.println("<h2>Pack 2 </h1><br>");
  client.println("<a href=\"/Req_2=180\"\"><button text-align: left; style='font-size: 100px;' >Drop 2</button></a><br><br>");
  client.println("<a href=\"/Req_2=0\"\"><button text-align: right; style='font-size: 100px;' >Reset 2</button></a>");


  client.println("<br><br>");


  client.println("</html>");

  delay(15);

  Serial.println("Client disonnected");

  Serial.println("");

 

}
