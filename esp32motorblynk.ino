// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL37alQSknW"
#define BLYNK_TEMPLATE_NAME "wifi  motor test"
#define BLYNK_AUTH_TOKEN "0nwbG8qrGMPL2yFuZ0wzpIgAXeYaOaj7"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
const char* server = "blynk.cloud";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "realme C30s";
char pass[] = "Shreeshcr7!!";

int IN1 = 4;
int IN2 = 5;
int motorspeed=18;
//int IN3 = 12;
//int IN4 = 13;


BLYNK_WRITE(V1) { //anti-cw  
  digitalWrite(IN2, param.asInt());
  //digitalWrite(IN4, param.asInt());
}

BLYNK_WRITE(V2) { //cw
  digitalWrite(IN1, param.asInt());
  //digitalWrite(IN3, param.asInt());
}

BLYNK_WRITE(V3) { //speed control
  int speed = param.asInt(); // Read the slider value (0-255)
  analogWrite(motorspeed, speed); // Control motor speed using PWM
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Making HTTP request...");

  WiFiClient client;

  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    client.println("GET / HTTP/1.1");
    client.println("Host: example.com");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Connection failed");
  }
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  //pinMode(IN3, OUTPUT);
  //pinMode(IN4, OUTPUT);
  pinMode(motorspeed,OUTPUT);

  //Blynk.begin(auth, ssid, pass);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();

}
