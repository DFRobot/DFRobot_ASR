/*!
 * @file speechRecognition.ino
 * @brief Speech recognition
 * @details Speech recognition, there are 3 modes.
 * @n 1. Loop mode: the target phrase will be identified in a loop until it is successfully identified
 * @n 2. Button mode: press the button to start recognition, and then press it again to end recognition
 * @n 3. Password mode: the first phrase is a command, the sensor will start to work normally only when the first phrase is recognized.
 * @n             If nothing is input, the sensor will enter idle mode within 10 seconds, input the command again to wake up it.
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
  /*!
   * Only Chinese characters can be recognized, convert the Chinese characters to be recognized into pinyin with spaces between each one, e.g.: 开始 -> kai shi.
   * Add up to 50 phrases, each phrase is up to 72 characters and up to 10 Chinese characters.
   * Each phrase corresponds to an id number (set within 1-255), different voice phrases can correspond to the same id number.
   */
  asr.addCommand("kai deng",0);   //In password mode, the first phrase is the start command
  asr.addCommand("guan deng",1);             //Start
  asr.addCommand("bei jing",2);              //Beijing
  asr.addCommand("shang hai",3);             //Shanghai
  asr.addCommand("xiang gang",4);            //Hong Kong

  //Start to recognize
  asr.start();
  Serial.println("Start");
}

void loop()
{
  int result = 0;
  //Read the recognized phrase
  result = asr.read();

  if(result != -1)
  {
    Serial.print("ASR result is:");
    Serial.println(result);//Return recognition result, i.e., number of the recognized phrase.
    }

}
