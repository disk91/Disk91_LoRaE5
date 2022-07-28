#include <Arduino.h>
#include "disk91_LoRaE5.h"

Disk91_LoRaE5 lorae5(false); // true or false, whatever

AT+ID=DevEui,"2CF7FXXXXXX0A49F"
AT+ID=AppEui," 80000XXXXXX00009"
AT+KEY=APPKEY,"2B7E151628XXXXXXXXXX158809CF4F3C"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  uint32_t start = millis();
  while ( !Serial && (millis() - start) < 1500 );  // Open the Serial Monitor to get started or wait for 1.5"
  
  if ( ! lorae5.begin(DSKLORAE5_SEARCH_WIO) ) {
    Serial.println("LoRa E5 Init Failed");
    while(1); 
  }

  if ( ! lorae5.setup(
          DSKLORAE5_ZONE_EU868,
          deveui,
          appeui,
          appkey
       ) ){
    Serial.println("LoRa E5 Setup Failed");
    while(1);         
  }

  if ( ! lorae5.join_sync(9,14) ) {
    Serial.println("LoRa E5 Failed to join");
    while(1);         
  }

}

uint8_t data[] = { 0x01, 0x02, 0x03, 0x04 }; 

void loop() {
  // send a simple uplink sf7, 14dBm
  if ( lorae5.send_sync(1,data,sizeof(data),false,7,14) ) {
    Serial.println("Uplink done");
    if ( lorae5.isDownlinkReceived() ) {
      Serial.println("A downlink has been received");
      if ( lorae5.isDownlinkPending() ) {
        Serial.println("More downlink are pending");
      }
    }
  }
  delay(2000);
  if ( lorae5.send_sync(1,data,sizeof(data),true,7,14,2) ) {
    Serial.println("Uplink with ack done");
    if ( lorae5.isAcked() ) {
      Serial.printf("With Rssi %d and Snr %d\r\n",lorae5.getRssi(), lorae5.getSnr()); 
    }
    if ( lorae5.isDownlinkReceived() ) {
      Serial.println("A downlink has been received");
      if ( lorae5.isDownlinkPending() ) {
        Serial.println("More downlink are pending");
      }
    }
  }
  delay(2000);
  uint8_t rxBuff[16];
  uint8_t rxSize = 16;
  uint8_t rxPort;
  if ( lorae5.sendReceive_sync(1,data,sizeof(data),rxBuff,&rxSize,&rxPort,7,14,0) ) {
    Serial.println("Uplink with downlink expectation done");
    if ( lorae5.isAcked() ) {
      Serial.printf("With Rssi %d and Snr %d\r\n",lorae5.getRssi(), lorae5.getSnr()); 
    }
    if ( lorae5.isDownlinkReceived() ) {
      Serial.println("A downlink has been received");
      for ( int i = 0 ; i < rxSize ; i++ ) {
        Serial.printf("0x%02X,",rxBuff[i]);
      }
      Serial.printf(" On port %d\r\n",rxPort);
      if ( lorae5.isDownlinkPending() ) {
        Serial.println("More downlink are pending");
      }
    }
  }
  delay(60000);

}