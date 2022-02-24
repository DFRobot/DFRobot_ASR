# -*- coding: utf-8 -*
'''!
  @file DFRobot_ASR.py
  @brief The speech recognition module can recognize the phrases pre-written to the sensor and return the corresponding number.
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT license (MIT)
  @author [fengli](li.feng@dfrobot.com)
  @version  V1.0
  @date  2020-08-17
  @https://github.com/DFRobot/DFRobot_ASR
'''
import serial
import time
import smbus
               
class DFRobot_ASR(object):
  ''' register configuration '''
  I2C_ADDR                = 0x50
  ASR_BEGIN               = 0xA1  #module init command
  ASR_ADDCOMMAND          = 0xA2  #command to start writing command
  ASR_ADDCOMMAND_END      = 0xA3  #command to end writing command
  ASR_START               = 0xA4  #command to start recognition
  ASR_LOOP                = 0xA5  #Loop mode command
  ASR_BUTTON              = 0xA7  #Button mode command
  ASR_PASSWORD            = 0xA6  #Password mode command
  ASR_IDLE                = 0xA8  #Idle mode command
  ASR_MIC_MODE            = 0xA9  #mic mode command
  ASR_MONO_MODE           = 0xAA  #mono mode command
  ASR_SET_IIC_ADDR        = 0xAB  #Set address command
  LOOP                    = 0x01  #Loop mode
  PASSWORD                = 0x02  #Password mode
  BUTTON                  = 0x03  #Button mode
  MIC                     = 0x04
  MONO                    = 0x05
  
  ''' Conversion data '''
  #txbuf      = [0]
  #_addr      =  0x50
  #_mode      =  0
  #   idle =    0
  def __init__(self ,bus,address):
    self.i2cbus = smbus.SMBus(bus)
    self._addr = address
    self.idle =    0

  def begin(self ,mode,miMode):
  '''
    @fn begin
    @brief Init function
    @param mode Speech recognition mode
    @param miMode Mic mode
    @return Returning 0 indicates init succeeded, non-zero indicates init failed, return error code.
  '''
    self._mode = mode
    self.write_data(self.ASR_BEGIN)
    if miMode == self.MIC:
       self.write_data(self.ASR_MIC_MODE)
    else:
       self.write_data(self.ASR_MONO_MODE)
    time.sleep(0.05)

  def start(self):
  '''
    @fn start
    @brief The speech recognition module start to recognize.
  '''
    self.write_data(self.ASR_START)
    time.sleep(0.05)

  def addCommand(self,words,idNum):
  '''
    @fn addCommand
    @brief Add phrases to the module
    @param words Character strings of the phrase
    @param idNum The id number of the phrase
    @return Boolean type, the result of seted
    @retval Adding phrases succeeded
    @retval Adding phrases failed
  '''
    #word = str(chr(idNum))+words+str(chr(self.ASR_ADDCOMMAND_END))
    #print(word[0])
    self.write_data(self.ASR_ADDCOMMAND)
    self.write_data(idNum)
    
    word = list(words)
    self.write_data(len(word))
    #print(len(word))
    for i in range(0,len(word)):
      self.write_data(ord(word[i]))
      #print(word[i])
    #self.i2cbus.write_i2c_block_data(self._addr ,idNum ,word)
    self.write_data(self.ASR_ADDCOMMAND_END)
    
  def read(self):
  '''
    @fn read
    @brief Read the recognized phrase
    @return Return the id number of the phrase
  '''
    rslt = -1
    #print(self._mode)
    if self._mode == self.BUTTON:
        rslt = self.read_reg(self.ASR_BUTTON,1)
    elif self._mode == self.LOOP:
        rslt = self.read_reg(self.ASR_LOOP,1)
    elif self._mode == self.PASSWORD:
        rslt = self.read_reg(self.ASR_PASSWORD,1)
    if self._mode == self.PASSWORD:
        self.idle = self.idle + 1
        if self.idle >= 500:
           self.write_data(self.ASR_IDLE)
           self.idle = 0
    if rslt == 0xff:
       return -1
    else:
       self.idle=0
       return rslt


  def setI2CAddr(self ,addr):
  '''
    @fn setI2CAddr
    @brief Set module i2c address (take effect after powering on again)
    @param addr i2c address to be set (0-127)
  '''
    if addr > 127:
        addr = 127
    self.i2cbus.write_byte_data(self._addr,self.ASR_SET_IIC_ADDR ,addr)
    #print(self._addr)
    #print(self.ASR_SET_IIC_ADDR)
    #print(addr)

  def write_data(self, data):
    self.i2cbus.write_byte(self._addr ,data)
    
  def write_reg(self, reg, data):
    self.i2cbus.write_byte(self._addr ,reg)
    self.i2cbus.write_byte(self._addr ,data)

  def read_reg(self, reg ,len):
    self.i2cbus.write_byte(self._addr,reg)
    time.sleep(0.02)
    rslt = self.i2cbus.read_byte(self._addr)
    return rslt
