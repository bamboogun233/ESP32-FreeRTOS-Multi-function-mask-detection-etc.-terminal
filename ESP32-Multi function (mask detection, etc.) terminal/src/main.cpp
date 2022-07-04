/*
基于深度学习与FreeRTOS的AI多功能终端
AI multifunction terminal based on deep learning and FreeRTOS
@ Author : BAMBOO(251905126郭世荣)
@ Time : 2022-06-16
@ Environment : vscode--platformio--Arduino framework
这是一个综合设计二的作品，第一次部署FreeRTOS设计作品。
设计了一个多级菜单，基础功能是调用K210、OpenMv或者PC端的深度学习模型，拓展加入WIFI配网功能，考勤打卡功能。
*/
#include <Arduino.h>//ESP32的Arduino框架自带了FreeRTOS，调用一个头文件即可
#include <U8g2lib.h>
#include <Wire.h>
#include <WiFi.h>
#include <config_display.h>
#include <SoftwareSerial.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
int MASK = 14;
int FACE = 12;
int LED = 13;
int A_EN=5;
int Acode2=19;
int Acode1=23;
int Acode0=18;
#define UP_KEY      25 //gpio25
#define M_KEY       32 //gpio32
#define DOWN_KEY    33 //gpio33
#define BACK_KEY    35 //gpio35
//读取键值
#define keyup     digitalRead(UP_KEY)
#define keyenter  digitalRead(M_KEY)
#define keydown   digitalRead(DOWN_KEY)
#define keyback   digitalRead(BACK_KEY)
uint32_t func_index=1;//显示任务的索引
uint8_t event_index=0;//其他任务的索引
int people_index=0;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/27, /* data=*/26);
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
char BLEbuf[32] = {0};
uint32_t cnt = 0;
// 定义UART service UUID
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" 
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
 
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};
//SoftwareSerial mySerial(4,15);// RX, TX
//oled屏幕显示任务
void oledTask(void * pvParam) {
  u8g2.begin();
  u8g2.enableUTF8Print();
  for (;;) {
    //一级菜单，有光标
        if(func_index==1)
    {
      fun1();
    }
        if(func_index==2)
    {
      fun2();
    }
        if(func_index==3)
    {
      fun3();
    }
        if(func_index==4)
    {
      fun4();
    }
      //二级菜单，第一页，有光标
        if(func_index==10)
        {
          fun11();
          digitalWrite(A_EN,0);
        }
        if(func_index==11)
        {
          fun12();
          digitalWrite(A_EN,0);
        }
        if(func_index==12)
        {
          fun13();
          digitalWrite(A_EN,0);
        }
        if(func_index==13)
        {
          fun14();
          digitalWrite(A_EN,0);
        }
        //二级菜单，无光标
        if(func_index==20)
        {
          page20();
          digitalWrite(A_EN,0);
        }
        if(func_index==30)
        {
          page30();
          digitalWrite(A_EN,0);
        }
        if(func_index==40)
        {
          page40();
          digitalWrite(A_EN,0);
        }
        //功能界面
        if(func_index==110)//110-->口罩检测
        {
          display_mask();

        }
        if(func_index==130)//130-->我的音乐
        {
          display_hutao();
          digitalWrite(A_EN,1);
          digitalWrite(Acode0,1);
          digitalWrite(Acode1,1);
          digitalWrite(Acode2,0);
        }
        if(func_index==400)//400-->EIElogo
        {
          display_EIE_logo();
        }
  }
}

//按键状态判断任务
void keyTask(void * pvParam) {
  for (;;) {
      if((keyup==0)||(keydown==0)||(keyenter==0)||(keyback==0))
      {
        vTaskDelay(120);//消抖
        if(keyup==0)
        {
          if(func_index>=20){
            if(func_index==40)
            {
              func_index=func_index*10;
            }
            else{
              func_index=func_index/10;//返回上级菜单
            }
          }
          else
          {
            func_index++;    //光标向上翻
            if((func_index==5)||(func_index==14))
            {
              func_index=func_index-4;
            }
          }
        }
        if(keydown==0)
        {
          if(func_index>=20){
            if(func_index==40)
            {
              func_index=func_index*10;
            }
            else{
              func_index=func_index/10;//返回上级菜单
            }
          }
          else
          {
            func_index--;    //光标向下翻
            if((func_index==0)||(func_index==9))
            {
              func_index=func_index+4;
            }
          }
        }
        if(keyenter==0)                     
        {                
          if(func_index<10)
          {
            func_index=func_index*10;//进入下级菜单
          }
          if(func_index==13)
          {
            func_index=func_index*10;
          }
          if(func_index==11)
          {
            func_index=func_index*10;
          }
        }
        if(keyback==0)                     
        {                
          if(func_index>=10)
          {
            func_index=func_index/10;//返回上级菜单
          }
        }
      }
  }
}
void pintask(void * pvParam) {
  for (;;) {
    int MASKState = digitalRead(MASK);//读取MASK引脚电平
    int FACEState = digitalRead(FACE);//读取FACE引脚电平
    if (func_index==110)
    {
      if(MASKState==1){
        digitalWrite(A_EN,1);
        digitalWrite(Acode0,1);
        digitalWrite(Acode1,0);
        digitalWrite(Acode2,0);//识别通过
        people_index++;
        memset(BLEbuf, 0, 32);  
        memcpy(BLEbuf, (char*)"MASK OK! People pass +1!", 32);
        pCharacteristic->setValue(BLEbuf);
        vTaskDelay(100);
        pCharacteristic->notify(); // 将待发送的值发出
        digitalWrite(LED, 1);
        vTaskDelay(500);
        digitalWrite(LED, 0);
        vTaskDelay(500);
        digitalWrite(LED, 1);
        vTaskDelay(500);
        digitalWrite(LED, 0);
        vTaskDelay(500);
        digitalWrite(LED, 1);
        vTaskDelay(500);
        digitalWrite(LED, 0);
      }
      else if (FACEState==1)
      {
        digitalWrite(A_EN,1);
        digitalWrite(Acode0,0);
        digitalWrite(Acode1,1);
        digitalWrite(Acode2,0);
        memset(BLEbuf, 0, 32);  
        memcpy(BLEbuf, (char*)"FACE OK!", 32);
        pCharacteristic->setValue(BLEbuf);
        vTaskDelay(100);
        pCharacteristic->notify(); // 将待发送的值发出
        digitalWrite(LED, 1);
        vTaskDelay(3000);
        digitalWrite(LED, 0);
      }
      else
      {
        digitalWrite(A_EN,1);
        digitalWrite(Acode0,0);
        digitalWrite(Acode1,1);
        digitalWrite(Acode2,1);//识别失败
      }
    }
}
}
 //蓝牙回传函数
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
 
      if (rxValue.length() > 0) {
        Serial.print("------>Received Value: ");
 
        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }
        Serial.println();
       
        if (rxValue.find("open") != -1) { 
          Serial.print("open the door!");
          digitalWrite(A_EN,1);
          digitalWrite(Acode0,1);
          digitalWrite(Acode1,0);
          digitalWrite(Acode2,0);
          digitalWrite(LED,1);
          delay(500);
          digitalWrite(LED,0);
          delay(500);
          digitalWrite(LED,1);
          delay(500);
          digitalWrite(LED,0);
          delay(500);
          digitalWrite(LED,1);
          delay(500);
          digitalWrite(LED,0);
          delay(500);
        }
        else if (rxValue.find("B") != -1) {
          Serial.print("Rx B!");
        }
        Serial.println();
      }
    }
};
void setup(void) { //loopBack , Priority 1, Core 1
  pinMode(MASK, INPUT);// 把MASK引脚设置为输入
  pinMode(FACE, INPUT);// 把MASK引脚设置为输入
  pinMode(LED, OUTPUT);// 把FACE引脚设置为输出
  pinMode(A_EN,OUTPUT);
  pinMode(Acode0,OUTPUT);
  pinMode(Acode1,OUTPUT);
  pinMode(Acode2,OUTPUT);
  digitalWrite(A_EN,0);
  digitalWrite(Acode0,1);
  digitalWrite(Acode1,1);
  digitalWrite(Acode2,1);
  pinMode(UP_KEY,INPUT);
  pinMode(M_KEY,INPUT);
  pinMode(DOWN_KEY,INPUT);
  pinMode(BACK_KEY,INPUT);
  //mySerial.begin(115200);
  Serial.begin(9600);
  Serial.print("ESP32 Tick Period - ");
  Serial.print(portTICK_PERIOD_MS);
  Serial.println("ms   ");
  xTaskCreatePinnedToCore(oledTask, "OLED Task", 1024 * 20, NULL, 3, NULL, 1);//笔记：合理分配优先级可以大大加快任务的运行速度
  xTaskCreatePinnedToCore(keyTask, "KEY Task", 1024 * 6, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(pintask, "PIN Task", 1024 * 6 , NULL, 1, NULL, 1);
  	// 所创建蓝牙设备名称
	BLEDevice::init("BAMBOO'S ESP32"); 
	// 创建这个蓝牙服务
	BLEServer *pServer = BLEDevice::createServer();
	pServer->setCallbacks(new MyServerCallbacks());
	
	BLEService *pService = pServer->createService(SERVICE_UUID);
	// 创造出一个可改变的特征
	pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
	pCharacteristic->addDescriptor(new BLE2902());
	BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new MyCallbacks());
	// 启动服务
	pService->start();
	// 开始广播
	pServer->getAdvertising()->start();
	Serial.println("Waiting a client connection to notify...");
}

void loop() {
  Serial.print(func_index);
  Serial.print("   ");
  vTaskDelay(1000);
}

