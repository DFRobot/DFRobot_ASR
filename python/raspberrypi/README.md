# DFRobot_ASR
- [中文版](./README_CN.md)

Would you like to add voice to your projects? Connect up this Speech recognition module, add a few couples of lines of code, and your project will recognize what you said without requiring machine learning, specific human voice, and internet connection.
Combining with a speech synthesis module, you can easily have conversations with your projects! 
The module uses I2C communication mode, gravity interface, and is compatible with most main controllers on the market, making it ideal for educational scenarios.
It provides 3 speech recognition modes and 3 voice input methods.


![产品效果图片](../../resources/images/DFR0715.png)


## Product Link（https://www.dfrobot.com.cn/goods-3011.html）

    DFR0715：Gravity: I2C Speech Recognition Module

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)
## Summary

Speech Recognition Module

## Feature

  1. Add words to the speech recognition module, each phrase has a number.<br>
  2. When the module recognizes an added phrase, it returns the corresponding number.<br>

## Installation

To use this library, please download the library file first, and paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

```
$> python speech_recognition.py
```

## Methods

```python
  def begin(self ,mode,miMode):
  '''
    @fn begin
    @brief Init function
    @param mode Speech recognition mode
    @param miMode Mic mode
    @return Returning 0 indicates init succeeded, non-zero indicates init failed, return error code.
  '''

  def start(self):
  '''
    @fn start
    @brief The speech recognition module start to recognize.
  '''

  def addCommand(self,words,idNum):
  '''
    @fn addCommand
    @brief Add phrase to the module.
    @param words Character strings of the phrases
    @param idNum The id number of the phrase
    @return Boolean type, the setting result
    @retval Adding phrases succeeded
    @retval Adding phrases failed
  '''
    
  def read(self):
  '''
    @fn read
    @brief Read the recognized phrase
    @return Return the id number of the phrase
  '''

  def setI2CAddr(self ,addr):
  '''
    @fn setI2CAddr
    @brief Set module i2c address (take effect after powering on again)
    @param addr i2c address to be set (0-127)
  '''

```

## Compatibility

| MCU         | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :--: | :----: | :----: | :--: |
| RaspberryPi2 |      |        |   √    |      |
| RaspberryPi3 |      |        |   √    |      |
| RaspberryPi4 |  √   |        |        |      |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :--: | :----: | :----: | ---- |
| Python2 |  √   |        |        |      |
| Python3 |  √   |        |        |      |
## History

September 9, 2020 - Version 1.0 released.

## Credits

Written by fengli(li.feng@dfrobot.com), 2019.8.25 (Welcome to our [website](https://www.dfrobot.com/))
