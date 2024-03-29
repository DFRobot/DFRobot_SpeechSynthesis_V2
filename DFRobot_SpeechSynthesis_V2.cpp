#include "DFRobot_SpeechSynthesis_V2.h"
/*!
   @file DFRobot_SpeechSynthesis_V2.cpp
   @brief Implementation of DFRobot_SpeechSynthesis class
   @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @License     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2020-08-17
   @https://github.com/DFRobot/DFRobot_SpeechSynthesis_V2
*/

DFRobot_SpeechSynthesis::DFRobot_SpeechSynthesis()
{

}

void DFRobot_SpeechSynthesis::speakElish(String word)
{
  uint16_t point = 0;
  _len = word.length();DBG(_len);
  _unicode = (uint8_t*)malloc(_len + 1);
  while (_index < _len) {
    _unicode[point++] = (word[_index] & 0x7f);
    _index++;
  }
  sendPack(START_SYNTHESIS1, _unicode, _len);

  wait();

  _index = 0;
  _len = 0;

  if (_unicode != NULL) {
    free(_unicode);
    _unicode = NULL;
  }
}
void DFRobot_SpeechSynthesis::setVolume(uint8_t voc)
{
  String str = "[v3]";
  if (voc > 9) voc = 9;
  str[2] = 48 + voc;
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setSpeed(uint8_t speed)
{
  String str = "[s5]";
  if (speed > 9) speed = 9;
  str[2] = 48 + speed;
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setTone(uint8_t tone)
{
  String str = "[t5]";
  if (tone > 9) tone = 9;
  str[2] = 48 + tone;
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setSoundType(eSoundType_t type)
{
  String str;
  if (type == eFemale1) {
    str = "[m3]";
  } else if (type == eMale1) {
    str = "[m51]";
  } else if (type == eMale2) {
    str = "[m52]";
  } else if (type == eFemale2) {
    str = "[m53]";
  } else if (type == eDonaldDuck) {
    str = "[m54]";
  } else if (type == eFemale3) {
    str = "[m55]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setEnglishPron(eENpron_t pron)
{
  String str;
  if (pron == eAlphabet) {
    str = "[h1]";
  } else if (pron == eWord) {
    str = "[h2]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setDigitalPron(eDigitalPron_t pron)
{
  String str;
  if (pron == eNumber) {
    str = "[n1]";
  } else if (pron == eNumeric) {
    str = "[n2]";
  } else if (pron == eAutoJudged) {
    str = "[n0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setSpeechStyle(eSpeechStyle_t style)
{
  String str;
  if (style == eCaton) {
    str = "[f0]";
  } else if (style == eSmooth) {
    str = "[f1]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::enablePINYIN(bool enable)
{
  String str;
  if (enable == true) {
    str = "[i1]";
  } else if (enable == false) {
    str = "[i0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setLanguage(eLanguage_t style)
{
  String str;
  if (style == eChinesel) {
    str = "[g1]";
  } else if (style == eEnglishl) {
    str = "[g2]";
  } else if (style == eAutoJudgel) {
    str = "[g0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setZeroPron(eZeroPron_t pron)
{
  String str;
  if (pron == eZreo) {
    str = "[o0]";
  } else if (pron == eOu) {
    str = "[o1]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setOnePron(eOnePron_t pron)
{
  String str;
  if (pron == eYao) {
    str = "[y0]";
  } else if (pron == eChone) {
    str = "[y1]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setNamePron(eNamePron_t pron)
{
  String str;
  if (pron == eName) {
    str = "[r1]";
  } else if (pron == eAutoJudgedn) {
    str = "[r0]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::enableRhythm(bool enable)
{
  String str;
  if (enable == true) {
    str = "[z1]";
  } else if (enable == false) {
    str = "[z0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::reset()
{

  speakElish("[d]");

}

void DFRobot_SpeechSynthesis::speak(String word)
{
  //DBG("String");
  uint32_t uni = 0;
  uint8_t utf8State = 0;
  DBG("\n");
  uint16_t point = 0;
  if (_utf8 != NULL) {
    free(_utf8);
    _utf8 = NULL;
  }DBG("\n");
  _len = word.length(); //总长度
  _utf8 = (uint8_t*)malloc(_len + 1);
  if (_utf8 == NULL) {
    DBG("no memory");
    return;
  }
  DBG("_len=");DBG(_len);

  for (uint32_t i = 0;i <= _len;i++) {
    _utf8[i] = word[i]; //总的utf8码
    //DBG(_utf8[i]);
  }
  DBG("\n");
  word = "";
  uint16_t len1 = getWordLen();
  DBG("len1=");DBG(len1);
  _unicode = (uint8_t*)malloc(len1 + 1);
  while (_index < _len) {
    if (_utf8[_index] >= 0xfc) {
      utf8State = 5;
      uni = _utf8[_index] & 1;
      _index++;
      for (uint8_t i = 1;i <= 5;i++) {
        uni <<= 6;
        uni |= (_utf8[_index] & 0x3f);
        utf8State--;
        _index++;
      }

    } else if (_utf8[_index] >= 0xf8) {
      utf8State = 4;
      uni = _utf8[_index] & 3;
      _index++;
      for (uint8_t i = 1;i <= 4;i++) {
        uni <<= 6;
        uni |= (_utf8[_index] & 0x03f);
        utf8State--;
        _index++;
      }

    } else if (_utf8[_index] >= 0xf0) {
      utf8State = 3;
      uni = _utf8[_index] & 7;
      _index++;
      for (uint8_t i = 1;i <= 3;i++) {
        uni <<= 6;
        uni |= (_utf8[_index] & 0x03f);
        utf8State--;
        _index++;
      }
      DBG(_index);DBG(uni);

    } else if (_utf8[_index] >= 0xe0) {
      curState = eChinese;
      if ((curState != lastState) && (lastState != eNone)) {
        lanChange = true;
      } else {
        utf8State = 2;
        DBG("index=");DBG(_index);
        uni = _utf8[_index] & 15;
        _index++;
        DBG("uni=");DBG(uni);
        for (uint8_t i = 1;i <= 2;i++) {
          uni <<= 6;
          uni |= (_utf8[_index] & 0x03f);
          utf8State--;
          _index++;
        }
        if (_utf8[_index] == 239) {
          //DBG("aaaa");
          lanChange = true;
        }
        lastState = eChinese;
        DBG(_index);DBG(uni);
        _unicode[point++] = uni & 0xff;
        _unicode[point++] = uni >> 8;
        //if(point ==  24) lanChange = true;
      }
    } else if (_utf8[_index] >= 0xc0) {
      curState = eChinese;
      if ((curState != lastState) && (lastState != eNone)) {
        lanChange = true;

      } else {
        utf8State = 1;
        uni = _utf8[_index] & 0x1f;
        _index++;
        for (uint8_t i = 1;i <= 1;i++) {
          uni <<= 6;
          uni |= (_utf8[_index] & 0x03f);
          utf8State--;
          _index++;
        }
        lastState = eChinese;
        _unicode[point++] = uni & 0xff;
        _unicode[point++] = uni >> 8;
        //if(point ==  24) lanChange = true;
      }
    } else if (_utf8[_index] <= 0x80) {
      curState = eEnglish;
      if ((curState != lastState) && (lastState != eNone)) {
        lanChange = true;

      } else {
        _unicode[point++] = (_utf8[_index] & 0x7f);
        _index++;
        lastState = eEnglish;
        if (/*(point ==  24) || */(_utf8[_index] == 0x20) || (_utf8[_index] == 0x2c)) lanChange = true;
      }
    }
    if (lanChange == true) {
      if (lastState == eChinese) {
        sendPack(START_SYNTHESIS, _unicode, point);
        wait();
      } else if (lastState == eEnglish) {
        sendPack(START_SYNTHESIS1, _unicode, point);
        wait();
      }
      lastState = eNone;
      curState = eNone;
      point = 0;
      lanChange = false;
    }
  }
  if (lastState == eChinese) {
    sendPack(START_SYNTHESIS, _unicode, point);
    wait();
  } else if (lastState == eEnglish) {
    sendPack(START_SYNTHESIS1, _unicode, point);
    wait();
  }
  lastState = eNone;
  curState = eNone;
  point = 0;
  lanChange = false;

  _index = 0;
  _len = 0;

  if (_unicode != NULL) {
    free(_unicode);
    _unicode = NULL;
  }
  return;

}
void DFRobot_SpeechSynthesis::wait()
{
  while (readACK() != 0x41)//等待语音合成完成
  {
    //if(readACK() == 0) break;
#if (defined ESP8266)
    yield();
#endif
  }
  //DBG("NEXT--------------------------------0X41")
  delay(100);

  while (1)//等待语音播放完成
  {
    //delay(20);
    uint8_t check[4] = { 0xFD,0x00,0x01,0x21 };
    sendCommand(check, 4);
#if (defined ESP8266)
    yield();
#endif
    if (readACK() == 0x4f) break;
    delay(20);
  }

  /*
readACK();
readACK();
readACK();
readACK();

*/

}
uint16_t DFRobot_SpeechSynthesis::getWordLen()
{
  uint16_t index = 0;
  uint32_t uni = 0;
  uint16_t length = 0;DBG("\n");
  DBG("len=");DBG(_len);
  while (index < _len) {
    DBG("index=");DBG(index);
    if (_utf8[index] >= 0xfc) {
      index++;
      for (uint8_t i = 1;i <= 5;i++) {
        index++;
      }
      length += 4;
    } else if (_utf8[index] >= 0xf8) {
      index++;
      for (uint8_t i = 1;i <= 4;i++) {
        index++;
      }
      length += 3;
    } else if (_utf8[index] >= 0xf0) {
      index++;
      for (uint8_t i = 1;i <= 3;i++) {
        index++;
      }
      length += 3;
    } else if (_utf8[index] >= 0xe0) {
      index++;
      for (uint8_t i = 1;i <= 2;i++) {
        index++;
      }
      length += 2;
    } else if (_utf8[index] >= 0xc0) {

      index++;
      for (uint8_t i = 1;i <= 1;i++) {
        index++;
      }
      length += 2;
    } else if (_utf8[index] <= 0x80) {
      index++;
      length++;
    }
  }
  return length;
}
void DFRobot_SpeechSynthesis::speak(const __FlashStringHelper* data)
{

  sSubMess_t mess;
  mess.index = 0;
  uint16_t uni = 0;
  __index = 0;
  uint8_t* _data = (uint8_t*)data;
  while (pgm_read_byte(_data + _len) != 0) {
    _len++;
  }
  while (__index < _len) {
    _isFlash = true;
    mess = getSubMess(_data);
    if (mess.ischar == 2) {
      uint8_t sendData[5] = { 0xfd,(mess.length + 2) >> 8,(mess.length + 2) & 0xff,0x01,0x03 };
      sendCommand(sendData, 5);
      for (uint16_t i = 0; i < mess.index;) {
        uint8_t utf8 = pgm_read_byte(_data + __index + i);
        if (utf8 >= 0xe0) {
          uni = utf8 & 15;
          i++;
          utf8 = pgm_read_byte(_data + __index + i);
          uni <<= 6;
          uni |= (utf8 & 0x03f);
          i++;
          utf8 = pgm_read_byte(_data + __index + i);
          uni <<= 6;
          uni |= (utf8 & 0x03f);

          sendData[0] = uni & 0xff;
          sendData[1] = uni >> 8;
          sendCommand(sendData, 2);
          i++;
        } else if (utf8 >= 0xc0) {
          uni = utf8 & 0x1f;
          i++;
          utf8 = pgm_read_byte(_data + __index + i);
          uni <<= 6;
          uni |= (utf8 & 0x03f);
          i++;
          sendData[0] = uni & 0xff;
          sendData[1] = uni >> 8;
          sendCommand(sendData, 2);
        }

      }
    }

    if (mess.ischar == 1) {
      uint8_t sendData[5] = { 0xfd,(mess.length + 2) >> 8,(mess.length + 2) & 0xff,0x01,0x00 };
      sendCommand(sendData, 5);
      for (uint16_t i = 0; i < mess.index;) {
        uint8_t utf8 = pgm_read_byte(_data + __index + i);
        sendData[0] = utf8 & 0x7f;
        sendCommand(sendData, 1);
        i++;
      }
    }
    if (mess.length == 0) break;
    wait();

    __index += mess.index;
  }


}

DFRobot_SpeechSynthesis::sSubMess_t DFRobot_SpeechSynthesis::getSubMess(const void* data)
{

  uint16_t index = 0;
  sSubMess_t mess;
  uint16_t length = 0;
  uint8_t* _data = (uint8_t*)data;
  if (_isFlash == true) {
    while (pgm_read_byte(_data + _len) != 0) {
      _len++;
    }
  } else {
    _len = strlen((char*)_data);
  }
  bool frist = false;
  uint8_t ischar = 0;
  while (index < _len) {
    uint8_t utf8;
    if (_isFlash == true) {
      utf8 = pgm_read_byte(_data + index + __index);
    } else {
      utf8 = _data[index + __index];
    }
    if (utf8 >= 0xfc) {
      index += 6;
      length += 4;
    } else if (utf8 >= 0xf8) {
      index += 5;
      length += 3;
    } else if (utf8 >= 0xf0) {
      index += 4;
      length += 3;
    } else if (utf8 >= 0xe0) {
      if (ischar == 1) {
        break;
      }
      index += 3;
      length += 2;
      if (frist == false) {
        ischar = 2;
        frist = true;
      }
    } else if (utf8 >= 0xc0) {
      if (ischar == 1) {
        break;
      }
      index += 2;
      length += 2;
      if (frist == false) {
        ischar = 2;
        frist = true;
      }
    } else  if (utf8 <= 0x80) {
      if (utf8 == 0) break;
      if (ischar == 2) {
        break;
      }

      index += 1;
      length++;

      if (frist == false) {
        ischar = 1;
        frist = true;
      }
    }
  }
  mess.ischar = ischar;
  mess.length = length;
  mess.index = index;
  return mess;
}

void DFRobot_SpeechSynthesis::speak(const void* data)
{
  sSubMess_t mess;
  mess.index = 0;
  uint16_t uni = 0;
  __index = 0;
  uint8_t* _data = (uint8_t*)data;
  uint16_t _len = strlen((char*)_data);
  while (__index < _len) {
    _isFlash = false;
    mess = getSubMess(_data);
    if (mess.ischar == 2) {
      uint8_t sendData[5] = { 0xfd,(mess.length + 2) >> 8,(mess.length + 2) & 0xff,0x01,0x03 };
      sendCommand(sendData, 5);
      for (uint16_t i = 0; i < mess.index;) {
        uint8_t utf8 = _data[__index + i];
        if (utf8 >= 0xe0) {
          uni = utf8 & 15;
          i++;
          utf8 = _data[__index + i];
          uni <<= 6;
          uni |= (utf8 & 0x03f);
          i++;
          utf8 = _data[__index + i];
          uni <<= 6;
          uni |= (utf8 & 0x03f);

          sendData[0] = uni & 0xff;
          sendData[1] = uni >> 8;
          sendCommand(sendData, 2);
          //
        //DBG(uni & 0xff,HEX);
          //DBG(uni >> 8,HEX);
          i++;
        } else if (utf8 >= 0xc0) {
          uni = utf8 & 0x1f;
          i++;
          utf8 = _data[__index + i];
          uni <<= 6;
          uni |= (utf8 & 0x03f);
          i++;
          sendData[0] = uni & 0xff;
          sendData[1] = uni >> 8;
          sendCommand(sendData, 2);
        }

      }
      //Wire.endTransmission();    // stop transmitting
    }

    if (mess.ischar == 1) {
      uint8_t sendData[5] = { 0xfd,(mess.length + 2) >> 8,(mess.length + 2) & 0xff,0x01,0x00 };
      sendCommand(sendData, 5);
      for (uint16_t i = 0; i < mess.index;) {
        uint8_t utf8 = _data[__index + i];
        sendData[0] = utf8 & 0x7f;
        sendCommand(sendData, 1);
        i++;
      }
    }
    if (mess.length == 0) break;
    wait();

    __index += mess.index;
  }
}
void DFRobot_SpeechSynthesis::stopSynthesis()
{
  sendPack(STOP_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::pauseSynthesis()
{
  sendPack(PAUSE_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::recoverSynthesis()
{
  sendPack(RECOVER_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::sleep()
{
  sendPack(ENTERSAVEELETRI);
}
void DFRobot_SpeechSynthesis::wakeup()
{
  sendPack(WAKEUP);
}
void DFRobot_SpeechSynthesis::sendPack(uint8_t cmd, uint8_t* data, uint16_t len)
{

  uint16_t length = 0;
  uint8_t head[5] = { 0 };
  head[0] = 0xfd;
  switch (cmd) {
  case START_SYNTHESIS: {
    length = 2 + len;
    head[1] = length >> 8;
    head[2] = length & 0xff;
    head[3] = START_SYNTHESIS;
    head[4] = 0x03;
    sendCommand(head, data, len);
  } break;
  case START_SYNTHESIS1: {
    length = 2 + len;
    head[1] = length >> 8;
    head[2] = length & 0xff;
    head[3] = START_SYNTHESIS;
    head[4] = 0x04;
    sendCommand(head, data, len);
  }
                       break;
  default: {
    length = 1;
    head[1] = length >> 8;
    head[2] = length & 0xff;
    head[3] = cmd;
    sendCommand(head, 4);
  }
         break;
  }
}
DFRobot_SpeechSynthesis_I2C::DFRobot_SpeechSynthesis_I2C(TwoWire* pWire, uint8_t address)
{
  _pWire = pWire;
  _deviceAddr = address;
}
DFRobot_SpeechSynthesis_I2C::~DFRobot_SpeechSynthesis_I2C()
{
  //_pWire->setClock(100000);
}

void DFRobot_SpeechSynthesis_I2C::begin()
{
  uint8_t ack = 0;

  _pWire->begin();

  uint8_t init = 0xAA;
  for (uint8_t i = 0;i < 40;i++) {
    sendCommand(&init, 1);
    delay(50);
    uint8_t check[4] = { 0xFD,0x00,0x01,0x21 };
    sendCommand(check, 4);
    if (readACK() == 0x4f) break;

  }



  //delay(5000);

    //delay(50);
    //speakElish("[n1]");
  setVolume(1);
  //setSpeed(5); 
 // setTone(5);  

 // setEnglishPron(WORD);
}
uint8_t DFRobot_SpeechSynthesis_I2C::sendCommand(uint8_t* head, uint8_t* data, uint16_t length)
{
  DBG();
  uint16_t lenTemp = 0;
  _pWire->beginTransmission(_deviceAddr);
  for (uint8_t i = 0;i < 5;i++) {
    _pWire->write(head[i]);
    // Serial.print(head[i], HEX);
  }
  _pWire->endTransmission();


  while (length) {
    if (length > 28) {
      lenTemp = 28;
    } else {
      lenTemp = length;
    }

    _pWire->beginTransmission(_deviceAddr);
    for (uint8_t i = 0;i < lenTemp;i++) {
      _pWire->write(data[i]);
      // Serial.print(data[i], HEX);
    }
    if (_pWire->endTransmission() != 0) {
      DBG("ERR_DATA_BUS");
      return ERR_DATA_BUS;
    }
    length -= lenTemp;
    data += lenTemp;
  }
#ifdef ENABLE_DBG
  DBG();
  for (uint8_t i = 0;i < 5;i++) {
    Serial.print(head[i], HEX);
    Serial.print(" ");
  }
  for (uint8_t i = 0;i < length;i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  DBG();
#endif
  // if( _pWire->endTransmission() != 0 ) {
      // DBG("ERR_DATA_BUS");
      // return ERR_DATA_BUS;
  // }


  return ERR_OK;
}

uint8_t DFRobot_SpeechSynthesis_I2C::sendCommand(uint8_t* data, uint8_t length)
{
  _pWire->beginTransmission(_deviceAddr);
  for (uint8_t i = 0;i < length;i++) {
    _pWire->write(data[i]);
    // if (4 != length) {
    //   Serial.print(data[i], HEX);
    //   Serial.print(" ");
    // }
  }
  if (_pWire->endTransmission() != 0) {
    DBG("ERR_DATA_BUS");
    return ERR_DATA_BUS;
  }


  return ERR_OK;
}
uint8_t DFRobot_SpeechSynthesis_I2C::readACK()
{

  uint8_t data = 0;
  _pWire->requestFrom(_deviceAddr, 1);
  //delay(1);
  if (_pWire->available()) {
    data = _pWire->read();
  }
  // DBG(data, HEX);
  return data;
}

DFRobot_SpeechSynthesis_UART::DFRobot_SpeechSynthesis_UART()
{


}

bool DFRobot_SpeechSynthesis_UART::begin(Stream& s)
{
  _s = &s;
  if (_s == NULL) {
    return false;
  } else {
    // speakElish("[n1]");
    setVolume(5);
    //setSpeed(5); 
   // setTone(5);  
   // setSoundType(eFemale1);
   // setEnglishPron(eWord);
    return true;
  }

}
uint8_t DFRobot_SpeechSynthesis_UART::sendCommand(uint8_t* head, uint8_t* data, uint16_t length)
{
  while (_s->available()) {
    _s->read();
  }


  for (uint8_t i = 0;i < 5;i++) {
    _s->write(head[i]);
  }
  for (uint8_t i = 0;i < length;i++) {
    _s->write(data[i]);
  }
#ifdef ENABLE_DBG
  DBG();
  for (uint8_t i = 0;i < 5;i++) {
    Serial.print(head[i], HEX);
    Serial.print(" ");
  }
  for (uint8_t i = 0;i < length;i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  DBG();
#endif
  return ERR_OK;
}

uint8_t DFRobot_SpeechSynthesis_UART::sendCommand(uint8_t* data, uint8_t length)
{
  for (uint8_t i = 0;i < length;i++) {
    _s->write(data[i]);
  }
  return ERR_OK;
}
uint8_t DFRobot_SpeechSynthesis_UART::readACK()
{

  uint8_t data = 0;
  delay(10);
  //DBG(data,HEX);
  if (_s->available()) {
    data = _s->read();
    DBG(data, HEX);
  }
  DBG(data, HEX);
  return data;

}
