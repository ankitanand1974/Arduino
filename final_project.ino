#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

#define _SSID "project" // Your WiFi SSID
#define _PASSWORD "Cucek12." // Your WiFi Password
#define REFERENCE_URL "https://toycar-8266e-default-rtdb.asia-southeast1.firebasedatabase.app" // Your Firebase project reference URL

// LED pin assignments for NodeMCU v3 (ESP8266)
const int redPin1 = 16;   // Red LED 1 (GPIO5)
const int greenPin1 = 5; // Green LED 1 (GPIO4)
const int bluePin1 = 4;  // Blue LED 1 (GPIO0)

const int redPin2 = D5;   // Red LED 2 (GPIO2)
const int greenPin2 = D7; // Green LED 2 (GPIO14)
const int bluePin2 = D8;  // Blue LED 2 (GPIO12)

Firebase firebase(REFERENCE_URL);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Set LED pins as outputs
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // Fetch data from Firebase
  String leftSignal = firebase.getString("traffic/left_signal");
  String rightSignal = firebase.getString("traffic/right_signal");

  Serial.print("Left Signal: ");
  Serial.println(leftSignal);
  Serial.print("Right Signal: ");
  Serial.println(rightSignal);

  // Control LED 1 based on left_signal value
  if (leftSignal == "GREEN") {
    digitalWrite(redPin1, LOW);
    digitalWrite(greenPin1, HIGH);
    digitalWrite(bluePin1, LOW);
    Serial.println("led.....");
  } else if (leftSignal == "RED") {
    digitalWrite(redPin1, HIGH);
    digitalWrite(greenPin1, LOW);
    digitalWrite(bluePin1, LOW);
  } else if (leftSignal == "YELLOW") {
    digitalWrite(redPin1, HIGH);
    digitalWrite(greenPin1, HIGH);
    digitalWrite(bluePin1, LOW);
  }

  // Control LED 2 based on right_signal value
  if (rightSignal == "GREEN") {
    digitalWrite(redPin2, LOW);
    digitalWrite(greenPin2, HIGH);
    digitalWrite(bluePin2, LOW);
  } else if (rightSignal == "RED") {
    digitalWrite(redPin2, HIGH);
    digitalWrite(greenPin2, LOW);
    digitalWrite(bluePin2, LOW);
  } else if (rightSignal == "YELLOW") {
    digitalWrite(redPin2, HIGH);
    digitalWrite(greenPin2, HIGH);
    digitalWrite(bluePin2, LOW);
  }

  delay(500); // Wait for 500ms before checking again
}