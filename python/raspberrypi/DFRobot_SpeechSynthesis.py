# coding=gbk

""" 
  @file DFRobot_SpeechSynthesis.py
  @brief DFRobot_SpeechSynthesis Class infrastructure, implementation of underlying methods
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author      [fengli](li.feng@dfrobot.com)
  version  V1.0
  @url https://github.com/DFRobot/DFRobot_SpeechSynthesis_V2
"""
import serial
import time
from smbus2 import SMBus, i2c_msg
import array
import numpy as np
from sys import version_info

I2C_ADDR = 0x40  # i2c address
INQUIRYSTATUS = 0x21  # Check status
ENTERSAVEELETRI = 0x88  #
WAKEUP = 0xFF  # Wake-up command

START_SYNTHESIS = 0x01  # start synthesis command 0
START_SYNTHESIS1 = 0x05  # Start synthesis command 1
STOP_SYNTHESIS = 0x02  # End speech synthesis
PAUSE_SYNTHESIS = 0x03  # pause speech synthesis command
RECOVER_SYNTHESIS = 0x04  # Resume speech synthesis commands
I2C_MODE = 0x01
UART_MODE = 0x02

MEAL = 0x04  # Male voice
FEMEAL = 0x03  # female voice
DONALDDUCK = 0x05  # Voice of Donald Duck

ALPHABET = 0x06  # Spell
WORD = 0x07  # word


CHINESE = 0xA0  # Chinese
ENGLISH = 0xA1  # English
NONE = 0xA2  #
CATON = 0xA3  # Word by word
SMOOTH = 0xA4  # Fluently
PINYIN_ENABLE = 0xA5  # Use Pinyin to read
PINYIN_DISABLE = 0xA6  # don't use pinyin pronunciation
CHINESEL = 0xA7  #
ENGLISHL = 0xA8  #
AUTOJUDGEL = 0xA9  # Auto Judge
NUMBER = 0xAA  # Telephone number
NUMERIC = 0xAB  #
AUTOJUDGED = 0xAC  # Auto Judge
ZREO = 0xAD  # Read as 'zero'
OU = 0xAE  # Read as'ou'
YAO = 0xAF  # Read as 'yao'
CHONE = 0xB0  # Read as 'yi'
NAME = 0xB1  #
AUTOJUDGEDN = 0xB2  #
ERROR = -1


class DFRobot_SpeechSynthesis(object):

    __txbuf = [0]  # i2c send buffer
    __alcoholdata = [0] * 101  # alcohol data

    def __init__(self, bus, Baud):
        if bus != 0:
            self._i2c = SMBus(bus)
            for i in range(0, 40):
                self._i2c.write_byte(self._addr, 0xAA)
                time.sleep(0.05)
                check = [0xFD, 0x00, 0x01, 0x21]
                time.sleep(0.1)
                self.write_cmd(check)
                result = self.read_ack(1)
                if result == 0x4F:
                    break
        else:
            self.ser = serial.Serial(
                "/dev/ttyAMA0",
                baudrate=Baud,
                bytesize=8,
                parity="N",
                stopbits=1,
                timeout=0.5,
            )
            if self.ser.isOpen == False:
                self.ser.open()

        self.set_voice(1)  # Set volume(0-9)

    def speak(self, string):
        """
        @fn speak
        @brief Speech synthesis function
        @param string word Content to be synthesized, could be Chinese, English, Number, etc.
        """
        str = string.encode("gb2312")
        head = [0xFD, 0x00, 0x00, 0x01, 0x00]
        if version_info.major == 2 and version_info.minor == 7:
            data = array.array("B", str)
        else:
            data = list(str)
        data2 = list(data)
        lenght = len(data2) + 2
        head[1] = lenght >> 8
        head[2] = lenght & 0xFF
        data1 = head + data2
        self.read_ack(1)
        self.read_ack(1)
        self.write_cmd(data1)
        self.wait()
        return

    def wait(self):
        """
        @brief Wait for speech synthesis to complete
        """
        while 1:
            result = self.read_ack(1)
            if result == 0x41:
                break
        # time.sleep(1)
        time.sleep(0.1)
        while 1:
            check = [0xFD, 0x00, 0x01, 0x21]
            self.write_cmd(check)
            time.sleep(0.02)
            result = self.read_ack(1)
            if result == 0x4F:
                break

    def set_voice(self, voc):
        """
        @brief Set voice volume
        @param voc Volume value(0-9)
        """
        list1 = [0xFD, 0x00, 0x06, 0x01, 0x00, 91, 118, 49, 93]
        if voc > 9 or voc < 0:
            return
        list1[7] = voc + 48
        self.write_cmd(list1)
        self.wait()

    def set_speed(self, speed):
        """
        @brief Set playback speed
        @param speed  Speed(0-9)
        """
        list1 = [0xFD, 0x00, 0x06, 0x01, 0x00, 91, 115, 54, 93]

        if speed > 9 or speed < 0:
            return
        list1[7] = speed + 48
        self.write_cmd(list1)
        self.wait()

    def set_soundType(self, type):
        """
        @brief Set voice type
        @param type(MALE:male, FEMALE:famale, DONALDDUCK:Donaldduck)
        """
        if type == MEAL:
            self.speak("[m51]")
        elif type == FEMEAL:
            self.speak("[m3]")
        elif type == DONALDDUCK:
            self.speak("[m54]")
        else:
            print("no that type")

    def set_tone(self, tone):
        """
        @brief Set tone
        @param tone Tone(0-9)
        """
        list1 = [0xFD, 0x00, 0x06, 0x01, 0x00, 91, 116, 54, 93]
        if tone > 9 or tone < 0:
            return
        list1[7] = tone + 48
        self.write_cmd(list1)
        self.wait()

    def set_english_pron(self, pron):
        """
        @brief Set how to read English
        @param pron(ALPHABET: letter, WORD: word)
        """
        if pron == ALPHABET:
            self.speak("[h1]")
        elif pron == WORD:
            self.speak("[h2]")

    def enable_rhythm(self, enable):
        """
        @brief This function is only used for reading Chinese
        @param enable(true;alse)
        """
        if enable == True:
            str1 = "[z1]"
        elif enable == False:
            str1 = "[z0]"
        self.speak(str1)

    def set_digitalPron(self, pron):
        """
        @brief Set how to read long numbers
        @param pron(NUMBER: phone number, NUMERIC: number, AUTOJUDGED: auto judge)
        """
        if pron == NUMBER:
            str1 = "[n1]"
        elif pron == NUMERIC:
            str1 = "[n2]"
        elif pron == AUTOJUDGED:
            str1 = "[n0]"
        self.speak(str1)

    def enable_PINYIN(self, enable):
        """
        @brief Enable PinYin synthesis
        @param enable(true: enable, false:disable)
        """
        if enable == True:
            str1 = "[i1]"
        elif enable == False:
            str1 = "[i0]"
        self.speak(str1)

    def set_speech_style(self, style):
        """
        @brief Set synthesis style
        @param enable(CATON: word by word; SMOOTH: fluently)
        """
        if style == CATON:
            str1 = "[f0]"
        elif style == SMOOTH:
            str1 = "[f1]"
        self.speak(str1)

    def set_language(self, style):
        """
        @brief Synthesize Arabic number, unit, special characters into Chinese or English
        @param style(CHINESEL:Chinese, ENGLISHL: English, AUTOJUDGEL: Auto judge)
        """
        if style == CHINESEL:
            str1 = "[g1]"
        elif style == ENGLISHL:
            str1 = "[g2]"
        elif style == AUTOJUDGEL:
            str1 = "[g0]"
        self.speak(str1)

    def set_zero_pron(self, pron):
        """
        @brief Set how to read "0" in phone number
        @param pron(ZREO: read as "zero"; OU: read as "ou")
        """
        if pron == ZREO:
            str1 = "[o0]"
        elif pron == OU:
            str1 = "[o1]"
        self.speak(str1)

    def set_one_pron(self, pron):
        """
        @brief Set how to read "1" in phone number
        @param pron(YAO: read as "yao"; CHONE: read as "yi")
        """
        if pron == YAO:
            str1 = "[y0]"
        elif pron == CHONE:
            str1 = "[y1]"
        self.speak(str1)

    def set_name_pron(self, pron):
        """
        @brief Set whether to use surname reading principle mandatorily
        @param pron(NAME: mandatory; AUTOJUDGEDN: auto judge)
        """
        if pron == NAME:
            str1 = "[r1]"
        elif pron == AUTOJUDGEDN:
            str1 = "[r0]"
        self.speak(str1)

    def test(self):
        """
        @brief Test function
        """
        data = [0xFD, 0x00, 0x0C, 0x01, 0x00, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75]
        self.write_cmd(data)
        self.wait()

    def reset(self):
        """
        @brief Reset settings to default
        """
        self.speak("[d]")


class DFRobot_SpeechSynthesis_I2C(DFRobot_SpeechSynthesis):
    def __init__(self, bus, addr=I2C_ADDR):
        self._addr = addr
        super(DFRobot_SpeechSynthesis_I2C, self).__init__(bus, 0)

    def write_cmd(self, data):
        """
        @brief writes data to a register
        @param data written data
        """
        max_block_size = 32
        for i in range(0, len(data), max_block_size):
            end_index = min(i + max_block_size, len(data))
            write_msg = i2c_msg.write(self._addr, data[i:end_index])
            self._i2c.i2c_rdwr(write_msg)

    def read_ack(self, len):
        """
        @brief read the data from the register
        """
        try:
            rslt = self._i2c.read_byte(self._addr)
        except:
            rslt = -1
        return rslt


class DFRobot_SpeechSynthesis_UART(DFRobot_SpeechSynthesis):

    def __init__(self, Baud):
        self.__Baud = Baud
        super(DFRobot_SpeechSynthesis_UART, self).__init__(0, Baud)

    def write_cmd(self, data):
        """
        @brief writes data to a register
        @param data written data
        """
        self.ser.write(data)
        time.sleep(0.1)
        return

    def read_ack(self, len):
        """
        @brief read the data from the register
        """
        a = [0]
        a[0] = self.ser.read(1)
        if a[0] == b"A":
            return 0x41
        if a[0] == b"O":
            return 0x4F
        return a[0]
