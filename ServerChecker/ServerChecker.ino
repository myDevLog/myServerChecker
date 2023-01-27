#include <ESP8266WiFi.h>
#include <PubSubClient.h>

extern "C" {
  #include "user_interface.h"
  #include "wpa2_enterprise.h"
  #include "c_types.h"
}

#include "wifiSetup.h"
#include "mqttSetup.h"



// GPIO-2 = 2
#define GREEN 2
// GPIO-0 = 0
#define RED 0



const char* ssid = wifi_ssid;
const char* identity = wifi_identity;
const char* username = wifi_username;
const char* password = wifi_password;

IPAddress mqttServer = server;
const uint16_t mqttPort = serverPort;
const char* clientId = mqttClientId;
const char* clientUser = mqttClientUsername;
const char* clientPass = mqttClientPassword;





void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}


WiFiClient espClient;
PubSubClient client(serverStr, mqttPort, callback, espClient);





void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);

  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);

  client.setKeepAlive(180);

  setupWifi();
}



void loop() {
  if(WiFi.status() == WL_CONNECTED){
    if(!client.connected()){
      reconnect();
    }
    
    client.loop();
  } else {
    setupWifi();
  }
}





void setupWifi() {
  delay(10);
  
  // Print where we're connecting to
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  verifyWPA2Enterprise();
  //WiFi.begin(hotspot_ssid, hotspot_password);
  
  retry();

  while (WiFi.status() != WL_CONNECTED) {
    toggleRetry();

    delay(500);
    Serial.print(".");
  }

  success();

  //clearRessources();

  delay(200);

  Serial.println("");
  Serial.println("WiFi connected - IP address: ");
  Serial.println(WiFi.localIP());
}



void verifyWPA2Enterprise(){
  WiFi.disconnect(true);
  wifi_set_opmode(STATION_MODE);

  Serial.setDebugOutput(true);
  WiFi.printDiag(Serial);

  // set the config to connect like to a normal wpa-network 
  struct station_config wifiConfig;
  memset(&wifiConfig, 0, sizeof(wifiConfig));
  strcpy((char*)wifiConfig.ssid, ssid);
  strcpy((char*)wifiConfig.password, password);
  
  
  wifi_station_set_config(&wifiConfig);

  // enable wpa2 enterprise authentication
  wifi_station_set_wpa2_enterprise_auth(1);

  clearRessources();

  // set the necessary wpa2 enterpise parameters
  wifi_station_set_enterprise_identity((uint8*)username, strlen(username));
  wifi_station_set_enterprise_username((uint8*)username, strlen(username));
  wifi_station_set_enterprise_password((uint8*)password, strlen((char*)password));

  Serial.println(WiFi.macAddress());

  wifi_station_connect();
}



void reconnect(){
  retry();
  delay(200);
  
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");    
    
    // Attempt to connect
    if (client.connect(clientId, clientUser, clientPass)) {
      Serial.println(" MQTT - connected");
      
      success();
      
      delay(200);

    } else {
      Serial.print(" MQTT - failed, rc=");
      Serial.print(client.state());
      Serial.println("");
      
      failure();

      // Wait 200 milli-seconds before retrying
      delay(200);
    }
  }
}

void clearRessources(){
  // Throw away old data, so no artifacts develop
  //wifi_station_clear_cert_key();
  //wifi_station_clear_enterprise_ca_cert();
  wifi_station_clear_enterprise_identity();
  wifi_station_clear_enterprise_username();
  wifi_station_clear_enterprise_password();
  //wifi_station_clear_enterprise_new_password();
}

void success(){
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
}

void failure(){
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
}

void retry(){
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
}

void toggleRetry(){
  digitalWrite(RED, !digitalRead(RED));
  digitalWrite(GREEN, !digitalRead(GREEN));
}
