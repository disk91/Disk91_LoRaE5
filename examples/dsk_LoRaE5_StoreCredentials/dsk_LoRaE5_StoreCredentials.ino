#include <Arduino.h>
#include "disk91_LoRaE5.h"

Disk91_LoRaE5 lorae5(false); // true or false whatever

AT+ID=DevEui,"2CF7FXXXXXX0A49F"
AT+ID=AppEui," 80000XXXXXX00009"
AT+KEY=APPKEY,"2B7E151628XXXXXXXXXX158809CF4F3C"

void setup() {

  Serial.begin(9600);
  uint32_t start = millis();
  while ( !Serial && (millis() - start) < 1500 );  // Open the Serial Monitor to get started or wait for 1.5"

  // init the library, search the LORAE5 over the different WIO port available
  if ( ! lorae5.begin(DSKLORAE5_SEARCH_WIO) ) {
    Serial.println("LoRa E5 Init Failed");
    while(1); 
  }
  
  //lorae5.clearStoredConfig();

  // This is just an example, usually the setup is made in a specific part of the code, 
  // like a serial console reading or a UI. then is is stored into the E5 memory
  // that way the credential are not staticly defined as it is in this example.
  //
  // That way, the configuration will be backup and the WioTerminal can be upgraded w/o loosing the credentials
  if ( !lorae5.haveStoredConfig() ) {

    // By executing this, the credentials will be stored 
    if ( ! lorae5.persistConfig(
            DSKLORAE5_ZONE_EU868,
            deveui,
            appeui,
            appkey
         ) ) {
          Serial.println("LoRa E5 Persist failed");
          while(1);         
    } else {
      Serial.println("LoRaWan config saved in LoRa E5"); 
    }
    
  } else {
    Serial.println("LoRaWan configuration is stored in LoRa E5");
  }

  // Setup the LoRaWan Credentials
  if ( ! lorae5.setup(
          DSKLORAE5_ZONE_EU868,     // LoRaWan Radio Zone EU868 here
          deveui,
          appeui,
          appkey
       ) ){
    Serial.println("LoRa E5 Setup Failed");
    while(1);         
  }

}

void loop() {
  static uint8_t data[] = { 0x01, 0x02, 0x03, 0x04 }; 

  if ( lorae5.send_sync(
        1,              // LoRaWan Port
        data,           // data array
        sizeof(data),   // size of the data
        false,          // we are not expecting a ack
        7,              // Spread Factor
        14              // Tx Power in dBm
       ) 
  ) {
      Serial.println("Uplink done");
      if ( lorae5.isDownlinkReceived() ) {
        Serial.println("A downlink has been received");
        if ( lorae5.isDownlinkPending() ) {
          Serial.println("More downlink are pending");
        }
      }
  }
  delay(30000);
    
}