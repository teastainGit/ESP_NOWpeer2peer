//with thanks to RandomNerdTutorials to teach me this!
/*
This demonstrates esp_now communication between two esp32, incl S3
This is peer to peer mode where both esp can send and receive in duplex mode
This is one sketch to be copied into two esp32...and the MAC address of one 
is copied over to the others 'broadcastAddress[] '
For testing: type a number from 0 to 9 in the serial monitor input field
You should see the ASCII number equiv showing up in the other boards serial monitor
i.e. type '0' into the serial window the other board will display ASCII 48 decimal 
in its serial stream...and vice versa
contact teastain@me.com for assistance
*/

// MAC of the this 'board A':  34:b7:da:56:60:3c
#include <esp_now.h>
#include <WiFi.h>
//MAC Address of the other board  'board B' below:
uint8_t broadcastAddress[] = { 0x34, 0xB7, 0xDA, 0x56, 0x1B, 0x88 };

String success;

typedef struct struct_message {
  int State;
} struct_message;

// Create a struct_message to hold outgoing button
struct_message Txmsg;
// Create a struct_message to hold incoming button (to turn on this LED)
struct_message Rxmsg;  //I.E. = incomingReadings

// Register peer
esp_now_peer_info_t peerInfo;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("A- Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  delay(1000);
}

void loop() {
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&Txmsg, sizeof(Txmsg));
  Serial.println("   ");
  Serial.println("              BOARD A serial stream ");
  Serial.print(" Rxmsg.State ");
  Serial.println(Rxmsg.State);
  delay(1000);
  if (Serial.available() > 0) {  //Read Serial.monitor
    Txmsg.State = Serial.read();
    Serial.print("Send out on esp_now: ");
    Serial.print("outgoing msg = ");
    Serial.println(Txmsg.State);  // to BOARD B
  }
}

// OnDataRecv when data is received, LED is controlled here
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&Rxmsg, incomingData, sizeof(Rxmsg));
  //Serial.print("Bytes received: ");
  //Serial.println(len);
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nA- Last Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0) {
    success = "Delivery Success :)";
  } else {
    success = "Delivery Fail :(";
  }
}
