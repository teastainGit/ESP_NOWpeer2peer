//with thanks to RandomNerdTutorials to teach me this!
#include <esp_now.h>
#include <WiFi.h>
#define LED 10     // or whatever you have
#define Button 37  // or whatever you have
//MAC Address of the OTHER board below:
uint8_t broadcastAddress[] = { 0x94, 0xB9, 0x7E, 0x8C, 0xB9, 0x7C };

String success;

typedef struct struct_message {
  bool State;
} struct_message;

// Create a struct_message to hold outgoing button
struct_message TxButton;
// Create a struct_message to hold incoming button (to turn on this LED)
struct_message RxButton;  //I.E. = incomingReadings

// Register peer
esp_now_peer_info_t peerInfo;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  pinMode(Button, INPUT);
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("A- Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
  delay(1000);
}

void loop() {
  TxButton.State = digitalRead(Button);  //***this is where you tramsmit this units button state
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&TxButton, sizeof(TxButton));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
  delay(500);
}

// OnDataRecv when data is received, LED is controlled here
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&RxButton, incomingData, sizeof(RxButton));
  Serial.print("Bytes received: ");
  Serial.println(len);
  digitalWrite(LED, RxButton.State);  //***this is where you receive the state of the other unit's button
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
