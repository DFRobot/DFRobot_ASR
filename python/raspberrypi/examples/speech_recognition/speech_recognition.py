# -*- coding:utf-8 -*-
"""
   @file speech_recognition.ino
   @brief Speech recognition, there are 3 modes.
   @n 1. Loop mode: the target phrase will be identified in a loop until it is successfully identified
   @n 2. Button mode: press the button to start recognition, and then press it again to end recognition
   @n 3. Password mode: the first phrase is a command, the sensor will start to work normally only when the first phrase is recognized.
   @n             If nothing is input, the sensor will enter idle mode within 10 seconds, input the command again to wake up it.

   @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @License     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2020-08-17
   @https://github.com/DFRobot/DFRobot_ASR
"""
import sys
import time
sys.path.append("../..")
from DFRobot_ASR import *

IIC_MODE         = 0x01            # default use IIC1
IIC_ADDRESS      = 0x4F           # default i2c device address
'''
   # The first  parameter is to select iic0 or iic1
   # The second parameter is the iic device address
'''
asr = DFRobot_ASR(IIC_MODE ,IIC_ADDRESS)
"""
     @brief Init function
     @param Speech recognition mode: LOOP; PASSWORD; BUTTON
     @return Returning 0 indicates init succeeded, non-zero indicates init failed, return error code.
"""

asr.begin(asr.LOOP,asr.MIC)
"""
   * Only Chinese characters can be recognized, convert the Chinese characters to be recognized into pinyin with spaces between each one, e.g.: 开始 --> kai shi
   * Add up to 50 phrases, each phrase is up to 72 characters and up to 10 Chinese characters
   * Each phrase corresponds to an id number (set within 1-255), different voice phrases can correspond to the same id number.
"""
asr.addCommand("kai deng",0)     #开灯

asr.addCommand("guan deng",1)             #关灯
'''In password mode, the first phrase is the start password'''
asr.addCommand("bei jing",2)              #北京
asr.addCommand("shang hai",3)       #上海
asr.addCommand("xiang gang",4)             #香港
#Start recognition
asr.start()
print("start\r\n")


while(1):
    result = asr.read()
    if result != -1 :
           print("ASR result is:%d"%result)
           #print(result);
          # print("\r\n");
