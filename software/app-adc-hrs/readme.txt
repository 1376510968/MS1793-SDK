ADC demo
==========================

demo App: nRF ToolBox  
          HRM

ADC: 12bit, range 0 - 4095
HRM data: 0 - 511
Batt ind: 0 - 100

===========================
ADC: PA3



I2C demo(master)
===========================
I2C_SCL:PA9
I2C_SDA:PA10
��ѯ��ʽ��ʹ�ܺ궨��USE_I2C
�жϷ�ʽ��ʹ�ܺ궨��USE_I2C��USE_I2CIRQ

�������Ҫ�ں���IIC_Init()���޸�slave�豸��ַ


*�����ΪI2C slave, ��Ҫ����һ��io��֪ͨ���豸�������ݵĶ�ȡ



standby adv demo
===========================
�ϵ緢���һ�ι㲥�����standby,ʹ��IWDG������λ.
���ģʽ�㲥�������,���ݹ�������������IWDG��ʱ��.
ʹ�ñ��ݼĴ��������ֵ�һ���ϵ�


