# Disk91 - LoRaE5 library
This Arduino Library is making LoRa-E5 development much simpler for developper
LoRa-E5 is a LoRaWAN module make by Seeed studio.

## Installation
- Download the Zip file from the github **releases** menu
- In Arduino, go to sketch / include library / Add a library ZIP
- Load the downloaded Zip file
- Now you can import the library (Disk91 LoRaE5 library)
- Watch the examples in Arduino / Files / Examples / Disk91 LoRa-E5 library   

## Supported feature
- LoRaE5 module detection over different Serial ports on WIO
- LoRaWan configuration persistence
- Uplink / Downlink

## comming soon feature
- Synchronous and Asynchronous use
- Duty Cycle user management

## Suported zones for Helium and TTN
- EU868
- US915
- AS923_1/2/3/4
- KR920
- IN865

## Public API
```C
    Disk91_LoRaE5(
        bool       nothing = false       // if anyone can explain me why w/o param the constructer generate compilation error ?!?
    );

    Disk91_LoRaE5(
        uint16_t   atTimeoutMs,          // Default timeout in Ms for AT command execution
        Serial_  * logSerial = NULL      // When set, the library debug is enabled               
    );

    Disk91_LoRaE5(
        Serial_  * logSerial = NULL      // When set, the library debug is enabled               
    );

    ~Disk91_LoRaE5();

    bool begin(  
        uint8_t portType = DSKLORAE5_HWSEARCH,    // where to find the LoRa-E5 board  
        __HWSERIAL_T * hwSerial = NULL,           // for HWSERIAL_CUSTOM, link the associated Serial
        SoftwareSerial * swSerial = NULL,         // for SWSERIAL_CUTSOM, link the associated SoftwareSerial
        int16_t ssRxPort = -1,                    // for SWSERIAL_PINS, specify the RX & TX Pin, the SSerial will be initialized
        int16_t ssTxPort = -1
    );

    bool setup(                     // Setup the LoRaWAN stack with the stored credentials
        bool      selfDC = false,   // when true, the duty cycle management is not managed by the module but the user application
        bool      withADR = false   // when true, the ADR is turned ON
    );

    bool setup(                     // Setup the LoRaWAN stack
        uint8_t   zone,             // radio zone selection
        uint8_t   deveui[],         // deviceEUI in the normal order for the bytes
        uint8_t   appeui[],         // applicationEUI in the normal order for the bytes
        uint8_t   appkey[],         // applicationKEY in the normal order for the bytes
        bool      selfDC = false,   // when true, the duty cycle management is not managed by the module but the user application
        bool      withADR = false   // when true, the ADR is turned ON
    );

    bool persistConfig(             // Store the LoRaWan configuration into module EEPROM for restoring later 
                                    //   this allows to update WIO firmware without loosing the LoRaWan credentials
            uint8_t   zone,         // radio zone selection
            uint8_t   deveui[],     // deviceEUI in the normal order for the bytes
            uint8_t   appeui[],     // applicationEUI in the normal order for the bytes
            uint8_t   appkey[]      // applicationKEY in the normal order for the bytes
    );

    bool haveStoredConfig();    // Returns true when a configuration has already been stored in the E5 memory
    bool clearStoredConfig();   // Purge the stored configuration for E5

    bool sendReceive_sync(      // send a message on LoRaWan expert an ack at least, eventually a downlink, return true when sent is a success and expect a ack
        uint8_t     port,               // LoRaWan port
        uint8_t *   data,               // Data / payload to be transmitted
        uint8_t     sz,                 // Size of the data, when 0 Join only is proceeded
        uint8_t *   rxBuffer,           // Downlink buffer, make sure it will be large enought, no verification
        uint8_t *   rxSize,             // uint8_t containing the rxBuffer size and returning the downlink message size
        uint8_t *   rxPort,             // uint8_t pointer for returnin the downlink port
        uint8_t     sf = 9,             // Spread Factor , use DSKLORAE5_SF_UNCHANGED to keep the previous one
        uint8_t     pwr = 14,           // Transmission power, use DSKLORAE5_DW_UNCHANGED to keep the previous one
        uint8_t     retries = 0         // Number of retry, use DSKLORAE5_RT_UNCHANGED to keep the previous one. retry = 0 means 1 uplink, no retry
    );

    bool send_sync(    // send a message on LoRaWan, return true when sent is a success 
        uint8_t     port,               // LoRaWan port
        uint8_t *   data,               // Data / payload to be transmitted
        uint8_t     sz,                 // Size of the data, when 0 Join only is proceeded
        bool        acked = false,      // Ack / Downlink request
        uint8_t     sf = 9,             // Spread Factor , use DSKLORAE5_SF_UNCHANGED to keep the previous one
        uint8_t     pwr = 14,           // Transmission power, use DSKLORAE5_DW_UNCHANGED to keep the previous one
        uint8_t     retries = 0         // Number of retry, use DSKLORAE5_RT_UNCHANGED to keep the previous one. retry = 0 means 1 uplink, no retry
    );

    bool join_sync(    // Join only (join is automatically executed on send but you can decide to join sepratly)
        uint8_t     sf = 9,             // Spread Factor , use DSKLORAE5_SF_UNCHANGED to keep the previous one
        uint8_t     pwr = 14            // Transmission power, use DSKLORAE5_DW_UNCHANGED to keep the previous one
    );

    bool isJoined();                    // return true when the device has joined the network
    bool isAcked();                     // return true when the previous uplink has been confirmed as received
    bool isDownlinkPending();           // return true when the previous uplink got a downlink pending response
    bool isDownlinkReceived();          // return true when the previous uplink got a downlink response
    int16_t getRssi();                  // return last Ack RSSI when the previous uplink has been confirmed as received or DSKLORAE5_INVALID_RSSI
    int16_t getSnr();                   // return last Ack SNR when the previous uplink has been confirmed as received or DSKLORAE5_INVALID_SNR

```

## Changelog
### 2022-06-19 version 1.0.0
Initial version.