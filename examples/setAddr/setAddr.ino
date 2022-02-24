/*!
 * @file setAddr.ino
 * @brief Set i2c slave address, up to 127, default to be 0x50
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-08-17
 * @https://github.com/DFRobot/DFRobot_ASR
*/

#include "DFRobot_ASR.h"

/**
 * @brief Constructor
 * @param pWire I2C bus pointer object, construct device, choose to pass into the parameter or not, default to be Wire
 * @param address 7-bit I2C address, the address value is determined by the first three bits, default to be 0x4F
 */
//DFRobot_ASR  asr(&Wire,0x4f);
DFRobot_ASR  asr;

void setup()
{
  Serial.begin(9600);

  
  //Init function
  //Speech recognition mode: LOOP; PASSWORD; BUTTON
  asr.begin(asr.BUTTON);
  Serial.println("set iic ADDR");
  //Take effect after restarting
  asr.setI2CAddr(0x50);
}

void loop()
{

}
