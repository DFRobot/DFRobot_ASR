/*!
   @file speechRecognition.ino
   @brief 设置iic从机地址，最大为127，默认为0x50
   @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2020-08-17
   @get from https://www.dfrobot.com
   @https://github.com/DFRobot/DFRobot_ASR
*/

#include "DFRobot_ASR.h"

/**
   @brief 构造函数
   @param pWire I2C总线指针对象，构造设备，可传参数也可不传参数，默认Wire
   @param address 7位I2C地址,由前三位决定地址的值，默认0x4F
*/
DFRobot_ASR  asr;

void setup()
{
  Serial.begin(9600);

  
  /**
     @brief 初始化函数
     @param 语音识别模式1.LOOP(循环模式)2.PASSWORD(指令模式)3.BUTTON(按钮模式)
     @return 返回0表示初始化成功，返回其他值表示初始化失败，返回错误码
  */
  asr.begin(BUTTON);
  Serial.println("set iic ADDR");
  //需要再次断电后生效,
  asr.setI2CAddr(0x50);
}

void loop()
{

}