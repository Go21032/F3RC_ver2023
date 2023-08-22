# F3RC2022_Proto
まだ何もないです。

## 設定済み
HSI 8MHz -> SYSCLK 180MHz

Debug:Serial Wire

TimeBase Sourse:SysTick

- オドメトリX軸用エンコーダ TIM1
  - A:PA8,B:PA9
- オドメトリY軸用エンコーダ TIM8
  - A:PC6,B:PC7
- 拡張用エンコーダ TIM2
  - A:PA15,B:PB9
- 通信用I2C 1個
  - SDA:PB7,SCL:PB8
- ◯サーボ用PWM 1個
  - TIM10:PA7
- ◯モタドラ DIR用 6個
  - PC0,PC1,PC2,PC3,PB2,PB10
- ◯モタドラ PWM用 6個
  - TIM3:PA6,TIM3:PB5,TIM3:PB0,TIM3:PB1,TIM12:PB14,TIM12:PB15
- センサ用GPIO_Input 1個 5VTolerant
  - PB12
- ◯ESP32通信用 USART1 1個 
  - TX:PB6,RX:PA10
- ◯ユーザLED
  - PA5
- ◯ユーザボタン
  - PC13
- ◯ソレノイドスイッチング用 2個
  - PC4, PC5
## 未設定
- アナログ用 2個
  - PA0,PA1

# 無線のコントローラについて
ESP32とDualShock3をBlueToothによって通信し、ESP32とNUCLEO-F446REをUARTによって通信してコントローラのデータを扱います。

ESP32のプログラムはこちら

[ESP_BT_DualShock3](https://github.com/KogakuinRobotProject/ESP_BT_DualShock3)
