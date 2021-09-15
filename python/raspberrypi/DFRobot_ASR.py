# -*- coding: utf-8 -*
import serial
import time
import smbus
                

class DFRobot_ASR(object):


  
  ''' register configuration '''
  I2C_ADDR                = 0x50
  ASR_BEGIN               = 0xA1
  ASR_ADDCOMMAND          = 0xA2
  ASR_ADDCOMMAND_END      = 0xA3
  ASR_START               = 0xA4
  ASR_LOOP                = 0xA5
  ASR_BUTTON              = 0xA7
  ASR_PASSWORD            = 0xA6
  ASR_IDLE                = 0xA8
  ASR_MIC_MODE            = 0xA9
  ASR_MONO_MODE           = 0xAA
  ASR_SET_IIC_ADDR        = 0xAB
  LOOP                    = 0x01
  PASSWORD                = 0x02
  BUTTON                  = 0x03
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
    self._mode = mode
    self.write_data(self.ASR_BEGIN)
    if miMode == self.MIC:
       self.write_data(self.ASR_MIC_MODE)
    else:
       self.write_data(self.ASR_MONO_MODE)
    time.sleep(0.05)

  def start(self):
    self.write_data(self.ASR_START)
    time.sleep(0.05)

  def addCommand(self,words,idNum):
    
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
    
   
  ''' Read the result data of the register '''
  def read(self):
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
  ''' Modify i2c device number '''
  def setI2CAddr(self ,addr):
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