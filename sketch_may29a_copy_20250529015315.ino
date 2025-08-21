#include <WiFi.h>
#include <WebServer.h>
#include "index_html.h"
#include "styles_css.h"
#include <FirebaseESP32.h>

// Wi-Fi credentials
const char* ssid = "DESKTOP";
const char* password = "ansh1234";

// Firebase credentials
#define API_KEY "your-api-key"
#define FIREBASE_HOST "lock2003-2d392-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "iflwXUmLG42oslRT7JVHHPeQzDsfjBqf6x2Yspy9"

// Firebase object
FirebaseData fbdo;

// Relay pin
const int relayPin = 23;
WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", INDEX_HTML);
}

void handleCSS() {
  server.send(200, "text/css", STYLES_CSS);
}

void handleRelay() {
  String state = server.arg("state");
  if (state == "on") {
    digitalWrite(relayPin, LOW);  // Turn ON relay
    Firebase.setString(fbdo, "/relayState", "ON");
    server.send(200, "text/plain", "Relay is ON");
  } else if (state == "off") {
    digitalWrite(relayPin, HIGH); // Turn OFF relay
    Firebase.setString(fbdo, "/relayState", "OFF");
    server.send(200, "text/plain", "Relay is OFF");
  } else {
    server.send(400, "text/plain", "Invalid Request");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Relay OFF initially

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nConnected to WiFi: " + WiFi.localIP().toString());

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Set up web server routes
  server.on("/", handleRoot);
  server.on("/style.css", handleCSS);
  server.on("/relay", handleRelay);
  server.begin();

  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}

