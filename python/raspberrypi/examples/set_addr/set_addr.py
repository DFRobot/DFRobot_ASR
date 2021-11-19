"""
   @file set_addr.ino
   @brief 设置iic从机地址，最大为127，默认为0x4F
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
IIC_ADDRESS      = 0x4F            # default iic device address
'''
   # The first  parameter is to select iic0 or iic1
   # The second parameter is the iic device address
'''
asr = DFRobot_ASR(IIC_MODE ,IIC_ADDRESS)
''' Change the device number of i2c, value range 1 to 127 '''
"""
     @brief 初始化函数
     @param 语音识别模式1.LOOP(循环模式)2.PASSWORD(指令模式)3.BUTTON(按钮模式)
     @return 返回0表示初始化成功，返回其他值表示初始化失败，返回错误码
"""
asr.begin(asr.ASR_LOOP,asr.MIC)
time.sleep(0.1)
#设置I2C地址
asr = asr.setI2CAddr(0x4E)
print("The new address needs to be powered off and reconnected to take effect")
