/*!
 * @file DFRobot_ASR.h
 * @brief DFRobot_ASR 类的基础结构
 * @details 语音识别模块可以识别到,预先被写入到传感器的词条,并返回对应编号
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
 * 只能识别汉字，将要识别的汉字转换成拼音字母，每个汉字之间空格隔开，比如：开始 --> kai shi
 * 最多添加50个词条，每个词条最长为72个字符，每个词条最多10个汉字
 * 每个词条都对应一个识别号（1~255随意设置）不同的语音词条可以对应同一个识别号，
 */
#define I2C_ADDR               0x4F

#define ASR_BEGIN              0xA1  //模块初始化指令 
//识别结果存放处，通过不断读取此地址的值判断是否识别到语音，不同的值对应不同的语音，
#define ASR_ADDCOMMAND         0xA2  //开始写入词条指令
#define ASR_ADDCOMMAND_END     0xA3  //结束写入词条指令
#define ASR_START              0xA4  //识别开始指令

#define ASR_LOOP               0xA5  //循环模式指令
#define ASR_BUTTON             0xA7  //按钮模式指令
#define ASR_PASSWORD           0xA6  //指令模式指令

#define ASR_IDLE               0xA8  //空闲模式指令

#define ASR_MIC_MODE           0xA9  //mic模式指令
#define ASR_MONO_MODE          0xAA  //mono模式指令
#define ASR_SET_IIC_ADDR       0xAB  //设置地址指令



class DFRobot_ASR {
public:
  #define ERR_OK             0      //No error
  #define ERR_DATA_BUS      -1      //Data bus error
  #define ERR_IC_VERSION    -2      //Chip version does not match
  /**
   * @struct eMode_t
   * @brief 三种识别模式
   */
  typedef enum {
    LOOP, /**<循环模式，>**/
    PASSWORD, /**<指令模式，>**/
    BUTTON,/**<按钮模式，>**/
  }eMode_t;
  
  /**
   * @enum eMicrophoneMode_t
   * @brief 麦克风模式选择
   */
  typedef enum {
    MIC,
    MONO,
  }eMicrophoneMode_t;
  
  
public:
  /**
   * @fn DFRobot_ASR
   * @brief 构造函数
   * @param pWire I2C总线指针对象，构造设备，可传参数也可不传参数，默认Wire
   * @param address 7位I2C地址,由前三位决定地址的值，默认0x4F
  */
  DFRobot_ASR(TwoWire *pWire = &Wire, uint8_t address = 0x4f);
  
  /**
   * @fn begin
   * @brief 初始化函数
   * @param mode 语音识别模式
   * @param miMode 麦克风模式
   * @return 返回0表示初始化成功，返回其他值表示初始化失败，返回错误码
  */
  int begin(eMode_t mode = LOOP,eMicrophoneMode_t miMode = MIC);
  
  /**
   * @fn start
   * @brief 语音模块开始识别.
   */
  void start();
   
  /**
   * @fn addCommand
   * @brief 向模块添加词条
   * @param words 代表词条的字符串
   * @param idNum 词条的识别号
   * @return Boolean type, the result of seted
   * @retval 添加词条成功
   * @retval 添加词条失败
   */
  bool addCommand( char *words, char idNum);
  
  /**
   * @fn setI2CAddr
   * @brief 设置模块的i2c地址(从新上电后生效)
   * @param addr 需要设置的i2c地址(0~127)
  */
  void setI2CAddr(uint8_t addr);
   
  /**
   * @fn read
   * @brief 读取识别到的词条.
   * @return 返回代表词条的识别号
  */
  int read();
private:
  uint16_t  idle = 0;
  uint8_t _deviceAddr;
  TwoWire *_pWire;
  eMode_t _mode;
  
  /**
   * @brief 通过SPI总线写入寄存器值
   * @param reg  寄存器地址 8bits
   * @param data 要写入数据
   */
  void writeReg(uint8_t reg, uint8_t data);
  /**
   * @brief 通过SPI总线读取寄存器值
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return 返回实际读取的长度，返回0表示读取失败
   */
  uint8_t readReg(uint8_t reg, void* pBuf, size_t size);
  
  uint8_t writeReg(uint8_t reg);

};

#endif
