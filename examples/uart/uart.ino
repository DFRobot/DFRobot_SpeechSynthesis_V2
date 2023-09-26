/*!
 * @file uart.ino
 * @brief Control speech synthesis sensor via UART, and synthetise speech
 * @details phenomena£ºthe speaker of the module plays English on a loop
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-11-6
 * @url https://github.com/DFRobot/DFRobot_SpeechSynthesis_V2
 */
#include "DFRobot_SpeechSynthesis_V2.h"
#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))   // Using a soft serial port
#include <SoftwareSerial.h>
SoftwareSerial FPSerial(2, 3);  //RX, TX
#else
#define FPSerial Serial1
#endif

DFRobot_SpeechSynthesis_UART ss;

void setup() {
  Serial.begin(115200);
#if (defined ESP32)
  FPSerial.begin(115200, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
#else
  FPSerial.begin(115200);
#endif
  //Init speech synthesis sensor
  ss.begin(FPSerial);
  
  //Set voice volume to 5
  //ss.setVolume(5);
  //Set playback speed to 5
  //ss.setSpeed(5);
  //Set tone to 5
  //ss.setTone(5);
  //For English, speak word 
  //ss.setEnglishPron(ss.WORD);
}

void loop() {
  ss.speak(F("She sells seashells by the seashore"));
  ss.speak(F("Hello, I'm Speech Synthesis module"));
  ss.speak(F("a b c d e f g"));
  ss.speak(F("a b c d e f g"));

  /*Use text control identifier*/
  //Voice volume identifier 
  //ss.speak(F("[v3]Hello [v8]world"));
  //Word Pronounce mode identifier
  //ss.speak(F("[h1]Hello [h2]world"));
}
