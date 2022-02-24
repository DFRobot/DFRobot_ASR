"""
   @file set_addr.ino
   @brief Set i2c slave address, up to 127, default to be 0x4F
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
     @brief Init function
     @param Speech recognition mode: LOOP; PASSWORD; BUTTON
     @return Returning 0 indicates init succeeded, non-zero indicates init failed, return error code
"""
asr.begin(asr.ASR_LOOP,asr.MIC)
time.sleep(0.1)
#Set I2C address
asr = asr.setI2CAddr(0x4E)
print("The new address needs to be powered off and reconnected to take effect")
