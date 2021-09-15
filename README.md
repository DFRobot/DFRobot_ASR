# DFRobot_ASR
 语音识别模块

   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary
  1.向语音识别模块添加词条,每一个词条会附带一个编号<br>
  2.当模块识别到添加的词条时,会返回对应的编号<br>
## Installation
To use this library, please download the library file first, and paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++

  /**
     @brief 初始化函数
     @param 语音识别模式
     @return 返回0表示初始化成功，返回其他值表示初始化失败，返回错误码
  */
  int begin(eMode_t mode = LOOP,eMicrophoneMode_t miMode = MIC);
  
  /**
     @brief 语音模块开始识别.
  */
  void start();
   
  /**
     @brief 向模块添加词条
     @param 代表词条的字符串
     @param 词条的识别号
     @return bool值 成功返回 1.
  */
  bool addCommand( char *words, char idNum);
  
  /**
     @brief 设置模块的i2c地址(从新上电后生效)
     @param addr 需要设置的i2c地址(0~127)
  */
  void setI2CAddr(uint8_t addr);
   
  /**
     @brief 读取识别到的词条.
     @return 返回代表词条的识别号
  */
  int read();

```

## Compatibility
MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
Arduino MEGA2560        |      √       |              |             | 
Arduino Leonardo|      √       |              |             | 
Micro:bit        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 
Raspberry Pi      |      √       |              |             | 

## History

- data 2019-8-25
- version V0.1


## Credits

Written by fengli(li.feng@dfrobot.com), 2019.8.25 (Welcome to our [website](https://www.dfrobot.com/))





