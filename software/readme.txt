****MS1793 IO resources****

========SPI========
CSN: GPB8
MOSI:GPB5
MISO:GPB4
SCK: GPB3

IRQ: GPA12

-----module led indicator-----
GPA8

======ADC=========
GPA3
GPA4
PGA7

======PWM=========
GPA9
GPA10
PGA11
GPA4
PGA7





****sample application****

1====UART����͸��Ӧ��==============
TX:GPA9  
RX:GPA10
RTS:GPA11
CTS:GPD2


2====LED-V2BJF======================
GPA11  LED_G
GPA4   LED_R 
GPA7   LED_B


3====ARGUN==================================
2���������ӽ�������״̬
PA0 wakeup mcu from standby with rising edge


4====HID ������==============================
2���������ӽ�������״̬
ʹ���ֻ�ԭ��������������,����Ҫapp
PA0 ��������


5===ADC demo==================================
2���������ӽ�������״̬
���nRF toolbox app�����HRM demo
���Ӻ����PA3�ڶ�Ӧ�Ŀɱ������


6===OTA demo==========================

7====LED-V2BJF-WS28111=====================
GPA8  OUT to WS2811(1.7us)

==============================================
