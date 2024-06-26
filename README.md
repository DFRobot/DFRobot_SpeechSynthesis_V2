# DFRobot_SpeechSynthesis_V2
- [中文版](./README_CN.md)

Would you like to add voice to your projects? Connect up this Speech Synthesis module, add few couples of lines of code, then here goes, your project starts speaking. Both Chinese and English are "so easy" for this speech synthesis module. It also can broadcast the current time and environment data. Combining with a speech recognition module, you can easily have conversations with your projects! The module uses I2C and UART two communication modes, gravity interface, and is compatible with most main-controllers on the market. Besides, the module already comes with a speaker, so you don't need to buy one.


![Product Image](./resources/images/dfr0760.png)

## Product Link (https://www.dfrobot.com/product-2234.html)
  DFR0760:Speech Synthesis Module(Support English and Chinese)
	
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

   1. Speech Synthesis <br>


## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
    
  /**
   * @fn speak
   * @brief Speech synthesis function 
   * @param word Content to be synthesized, could be Chinese, English, Number, etc. 
   */
  void speak(String word);
  
  /**
   * @fn speak
   * @brief Speech synthesis function,the data to be converted is put into Flash
   * @param word Content to be synthesized, could be Chinese, English, Number, etc. 
   */
  void speak(const __FlashStringHelper *data);
  
  /**
   * @fn setVolume
   * @brief Set voice volume
   * @param voc  Volume value(0-9)
   */
  void setVolume(uint8_t voc);

  /**
   * @fn setSpeed
   * @brief Set playback speed 
   * @param speed Speed value (0-9)
   */
  void setSpeed(uint8_t speed);

  /**
   * @fn setSoundType
   * @brief Set voice type 
   * @param eFemale1,<Female 1, recommended>
   *        eMale1,<Male 1, recommended>
   *        eMale2,<Male 2>
   *        eFemale2,<Female 2>
   *        eDonaldDuck,<Donald Duck>
   *        eFemale3,<Female 3>
   */
  void setSoundType(eSoundType_t type);

  /**
   * @fn setTone
   * @brief Set the tone 
   * @param tone Tone value (0-9)
   */
  void setTone(uint8_t tone);

  /**
   * @fn setEnglishPron
   * @brief Set how to read English 
   * @param pron(eAlphabet: letter, eWord: word)
   */
  void setEnglishPron(eENpron_t pron);

  /**
   * @fn reset
   * @brief Reset settings to default 
   */
  void reset();
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
micro:bit        |      √       |              |             | 


## History


- 2020/12/06 - Version 1.0.0 released.
- 2024/05/20 - Version 1.0.1 released.


## Credits

Written by fengli(li.feng@dfrobot.com), 2020.11.6 (Welcome to our [website](https://www.dfrobot.com/))





