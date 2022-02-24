/*!
 * @file DFRobot_ASR.h
 * @brief Basic struct of DFRobot_ASR class
 * @details The speech recognition module can recognize the phrases pre-written to the sensor and return the corresponding number.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT license (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-08-17
 * @https://github.com/DFRobot/DFRobot_ASR
*/

#ifndef DFROBOT_ASR_H
#define DFROBOT_ASR_H
#include "Arduino.h"
#include <Wire.h>
//#define ENABLE_DBG
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif


/*
 * Only Chinese characters can be recognized, convert the Chinese characters to be recognized into pinyin with spaces between each one, e.g.: 开始 --> kai shi
 * Add up to 50 phrases, each phrase is up to 72 characters and up to 10 Chinese characters
 * Each phrase corresponds to an id number (set within 1-255), different voice phrases can correspond to the same id number.
 */
#define I2C_ADDR               0x4F

#define ASR_BEGIN              0xA1  //module init command 
//The recognition result storage, determine whether the voice is recognized by constantly reading the address value, different values correspond to different voices.
#define ASR_ADDCOMMAND         0xA2  //command to start writing phrases
#define ASR_ADDCOMMAND_END     0xA3  //command to end writing phrases
#define ASR_START              0xA4  //command to start recognition

#define ASR_LOOP               0xA5  //Loop mode command
#define ASR_BUTTON             0xA7  //Button mode command
#define ASR_PASSWORD           0xA6  //Password mode command

#define ASR_IDLE               0xA8  //Idle mode command

#define ASR_MIC_MODE           0xA9  //mic mode command
#define ASR_MONO_MODE          0xAA  //mono mode command
#define ASR_SET_IIC_ADDR       0xAB  //set address command



class DFRobot_ASR {
public:
  #define ERR_OK             0      //No error
  #define ERR_DATA_BUS      -1      //Data bus error
  #define ERR_IC_VERSION    -2      //Chip version does not match
  /**
   * @struct eMode_t
   * @brief 3 recognition modes
   */
  typedef enum {
    LOOP, /**<loop mode>**/
    PASSWORD, /**<password mode>**/
    BUTTON,/**<button mode>**/
  }eMode_t;
  
  /**
   * @enum eMicrophoneMode_t
   * @brief Mic mode select
   */
  typedef enum {
    MIC,
    MONO,
  }eMicrophoneMode_t;
  
  
public:
  /**
   * @fn DFRobot_ASR
   * @brief Constructor
   * @param pWire I2C bus pointer object, construct device, choose to pass into the parameter or not, default to be Wire
   * @param address 7-bit I2C address, the address value is determined by the first three bits, default to be 0x4F
  */
  DFRobot_ASR(TwoWire *pWire = &Wire, uint8_t address = 0x4f);
  
  /**
   * @fn begin
   * @brief Init function
   * @param mode Speech recognition mode
   * @param miMode Mic mode
   * @return Returning 0 indicates init succeeded, non-zero indicates init failed, return error code.
  */
  int begin(eMode_t mode = LOOP,eMicrophoneMode_t miMode = MIC);
  
  /**
   * @fn start
   * @brief The speech recognition module start to recognize.
   */
  void start();
   
  /**
   * @fn addCommand
   * @brief Add phrases to the module
   * @param words Character strings of the phrases
   * @param idNum The id number of the phrase
   * @return Boolean type, the setting result
   * @retval Adding phrases succeeded
   * @retval Adding phrases failed
   */
  bool addCommand( char *words, char idNum);
  
  /**
   * @fn setI2CAddr
   * @brief Set module i2c address (take effect after powering on again)
   * @param addr i2c address to be set (0-127)
  */
  void setI2CAddr(uint8_t addr);
   
  /**
   * @fn read
   * @brief Read the recognized phrase
   * @return Return the id number of the phrase
  */
  int read();
private:
  uint16_t  idle = 0;
  uint8_t _deviceAddr;
  TwoWire *_pWire;
  eMode_t _mode;
  
  /**
   * @brief Write register value through SPI bus
   * @param reg  Register address 8bits
   * @param data Data to be written
   */
  void writeReg(uint8_t reg, uint8_t data);
  /**
   * @brief Read register value through SPI bus
   * @param reg  Register address 8bits
   * @param pBuf Storage and buffer for data to be written
   * @param size Length of data to be written
   * @return Return the read length, returning 0 means length reading failed
   */
  uint8_t readReg(uint8_t reg, void* pBuf, size_t size);
  
  uint8_t writeReg(uint8_t reg);

};

#endif
