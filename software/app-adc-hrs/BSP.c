#include "BSP.h"
#include "adc.h"



/********************************************************************************************************
**������Ϣ ��SPIM_TXEn(SPI_TypeDef* SPIx)                     
**�������� :�ر� SPI ��˫��ģʽ�µ����ݴ��䷽�� 
**������� ��SPI_TypeDef* SPIx,��ѡ��SPI1,SPI2
**������� ����
********************************************************************************************************/
void SPIM_TXEn(SPI_TypeDef* SPIx)
{
    //Transmit Enable bit TXEN
    SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Tx);
}

/********************************************************************************************************
**������Ϣ ��SPIM_TXDisable(SPI_TypeDef* SPIx)                     
**�������� :�ر� SPI ��˫��ģʽ�µ����ݴ��䷽�� 
**������� ��SPI_TypeDef* SPIx,��ѡ��SPI1,SPI2
**������� ����
********************************************************************************************************/
void SPIM_TXDisable(SPI_TypeDef* SPIx)
{
    //disable TXEN
    SPI_BiDirectionalLineConfig(SPIx, SPI_Disable_Tx);
}

/********************************************************************************************************
**������Ϣ ��SPIM_RXEn(SPI_TypeDef* SPIx)                     
**�������� :�ر� SPI ��˫��ģʽ�µ����ݴ��䷽�� 
**������� ��SPI_TypeDef* SPIx,��ѡ��SPI1,SPI2
**������� ����
********************************************************************************************************/
void SPIM_RXEn(SPI_TypeDef* SPIx)
{
    //enable RXEN
    SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Rx);
}

/********************************************************************************************************
**������Ϣ ��SPIM_RXDisable(SPI_TypeDef* SPIx)                     
**�������� :�ر� SPI ��˫��ģʽ�µ����ݴ��䷽�� 
**������� ��SPI_TypeDef* SPIx,��ѡ��SPI1,SPI2
**������� ����
********************************************************************************************************/
void SPIM_RXDisable(SPI_TypeDef* SPIx)
{
    //disable RXEN
    SPI_BiDirectionalLineConfig(SPIx, SPI_Disable_Rx);
}

/********************************************************************************************************
**������Ϣ ��SPIM_Init(SPI_TypeDef* SPIx, unsigned short spi_baud_div)            
**�������� :���޸Ĳ�����ʼ��SPI
**������� ��SPI_TypeDef* SPIx,��ѡ��SPI1,SPI2  ;spi_baud_div
**������� ����
********************************************************************************************************/
void SPIM_Init(SPI_TypeDef* SPIx,unsigned short spi_baud_div)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    if(SPIx==SPI1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);  //SPI1 clk enable
        SPI_CS_Disable;

        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_0);
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_0);
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_0);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;   //spi1_cs  pb8
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        
        GPIO_SetBits(GPIOB, GPIO_Pin_8); //csn=H
        

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;   //spi1_sck  pb3
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // ���⸴�����
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;   //spi1_mosi  pb5
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // ���⸴�����
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;  //spi1_miso  pb4
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������   
        GPIO_Init(GPIOB, &GPIO_InitStructure);

    }


    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_DataWidth = SPI_DataWidth_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;    // mode0 SPI_CPOL_Low, SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;  // mode3 SPI_CPOL_High,SPI_CPHA_2Edge
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    //SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_BaudRatePrescaler = spi_baud_div;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPIx, &SPI_InitStructure);
    
    SPI_Cmd(SPIx, ENABLE); //Enables the specified SPI peripheral SPIʹ�ܡ�����ģʽ 8λ����ģʽ SPI �Ĳ�����

    SPIM_TXEn(SPIx);
    SPIM_RXEn(SPIx);
}

/********************************************************************************************************
**������Ϣ ��SystemClk_HSEInit (void)                        
**�������� ��ϵͳʱ�ӳ�ʼ����������ʼ��֮ǰ�ȸ�λ����ʱ��
**������� ����
**������� ����
********************************************************************************************************/
void SetSysClock_HSI(u8 PLL)
{
  unsigned char temp=0;   
  
  RCC->CR|=RCC_CR_HSION;  
  while(!(RCC->CR&RCC_CR_HSIRDY));
  RCC->CFGR=RCC_CFGR_PPRE1_2; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
  
  RCC->CFGR&=~RCC_CFGR_PLLSRC;	  //PLLSRC ON 
  
  RCC->CR &=~(RCC_CR_PLLON);		//clear PLL//	RCC->CR &=~(7<<20);		//clear PLL
  
  RCC->CR &=~(0x1f<<26);	
  RCC->CR|=(PLL - 1) << 26;   //setting PLL value 2~16
  
  FLASH->ACR=FLASH_ACR_LATENCY_1|FLASH_ACR_PRFTBE;	  //FLASH 2 delay clk cycles
  
  RCC->CR|=RCC_CR_PLLON;  //PLLON
  while(!(RCC->CR&RCC_CR_PLLRDY));//waiting for PLL locked
  RCC->CFGR&=~RCC_CFGR_SW;
  RCC->CFGR|=RCC_CFGR_SW_PLL;//PLL to be the sys clock
  while(temp!=0x02)     //waiting PLL become the sys clock
  {    
    temp=RCC->CFGR>>2;
    temp&=0x03;
  } 
}

void SystemClk_HSEInit(void)
{
    SetSysClock_HSI(4);//HSI:12*4=48M

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//selecting PLL clock as sys clock
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
}

void SysTick_Configuration(void)
{
    SysTick_Config(48000);
}

void LED_ONOFF(unsigned char onFlag)//module indicator,GPA8
{
    if(onFlag){
        GPIOA->BRR = GPIO_Pin_8;  //low, on
    }else{
        GPIOA->BSRR = GPIO_Pin_8; //high, off
    }
}

void Sys_Standby(void)
{  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//ʹ��PWR����ʱ��
    //RCC->APB2RSTR|=0X01FC;//��λ����IO��
    PWR_WakeUpPinCmd(ENABLE);  //ʹ�ܻ��ѹܽŹ���
   PWR_EnterSTANDBYMode();	  //���������STANDBY��ģʽ 

}

#ifdef USE_I2C
void IIC_Init(I2C_TypeDef* I2Cx)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
#ifdef USE_I2CIRQ
    NVIC_InitTypeDef NVIC_InitStructure;

    //I2C NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
#endif

    if(I2Cx==I2C1)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);  //i2c1 clk enable
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9 | GPIO_Pin_10;   //i2c1_scl  pa9  i2c1_sda  pa10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // ���ÿ�©���
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_4);
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_4);
    }

    I2Cx->IC_ENABLE = 0x0;
    I2Cx->IC_CON = 0x163;
    I2Cx->IC_TAR = 0xAA>>1;//Address
    //I2Cx->IC_SAR = 0xAA>>1;//Address
    I2Cx->IC_SS_SCL_HCNT = 0x77;
    I2Cx->IC_SS_SCL_LCNT = 0x55;
    I2Cx->IC_RX_TL=0x0;//set Rx FIFO threshold level 
    I2Cx->IC_TX_TL=0x0;//set Tx FIFO threschold level 
    I2Cx->IC_INTR_MASK=0X00;//disable all inttrupt
    I2Cx->IC_ENABLE=0x1;
}

static u8 *DataPt;
static u8 DataLen=0, DataCnt=0;
void I2C_Send(u8 *pdat, u8 len)
{
    DataPt = pdat;
    DataLen = len;

    DataCnt = 0;
#ifdef USE_I2CIRQ
    I2C1->IC_DATA_CMD = DataPt[DataCnt++];
    I2C1->IC_INTR_MASK = I2C_IT_TX_EMPTY;
#else
    do
    {
        if (DataLen - DataCnt == 1)
        {
            I2C1->IC_DATA_CMD = DataPt[DataCnt++] | 0x200;
        }
        else
        {
            I2C1->IC_DATA_CMD = DataPt[DataCnt++];
        }
        
        while(!(I2C1->IC_STATUS & I2C_STATUS_FLAG_TFE));
    }
    while(DataCnt < DataLen);
    
#endif
}

#ifdef USE_I2CIRQ
void I2C1_IRQHandler(void)
{
    if(I2C1->IC_INTR_STAT & I2C_IT_TX_EMPTY)
    {
        I2C_ClearFlag(I2C1,I2C_IT_TX_EMPTY);
        if (DataCnt < DataLen)
        {
            if (DataLen - DataCnt == 1)
            {
               I2C1->IC_DATA_CMD = DataPt[DataCnt++] | 0x200;
            }
            else
            {
                I2C1->IC_DATA_CMD = DataPt[DataCnt++];
            }
        }
        else//over
        {
            I2C1->IC_INTR_MASK=0x0000;//disable all inttrupt
        }
    }
}
#endif
#endif

void BSP_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    SystemClk_HSEInit();
    SysTick_Configuration();
    
    SPIM_Init(SPI1,0x08); //6Mhz
    //SPIM_Init(SPI1,0x06); //8Mhz


    //IRQ - pa12
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0; //PA.0
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��IO
    
    //module led indicator PA8
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_5);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    
    GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /*��PA3����Ϊģ������*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    ADC1_SingleChannel(ADC_Channel_3);
    

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    SYSCFG_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);
    EXTI_InitStructure.EXTI_Line = EXTI_Line12;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    PWR->CR = PWR->CR & 0xfffd; //PDDS = 0;enter stop mode
    SCB->SCR |= 0x4;

}




/////////////////////Following functions are porting functions/////////////////////////////////

unsigned char SPI_WriteRead(unsigned char SendData,unsigned char WriteFlag) //porting api
{
    SPI1->TXREG = SendData;
    while(!(SPI1->CSTAT & SPI_FLAG_TXEPT));
    while(!(SPI1->CSTAT & SPI_FLAG_RXAVL));
    return SPI1->RXREG;
}

void SPI_CS_Enable_(void) //porting api
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);
}

void SPI_CS_Disable_(void) //porting api
{
    GPIO_SetBits(GPIOB, GPIO_Pin_8);
}

char IsIrqEnabled(void) //porting api
{
    return (!(GPIO_ReadInputData(GPIOA) & 0x1000)); //GPA12
}


#define TOUT_ARGUN 600 //1000/200*60*2 = 2 min
extern unsigned int StandbyTimeout; 
void McuGotoSleepAndWakeup(void) // auto goto sleep AND wakeup, porting api
{
    if (TOUT_ARGUN < StandbyTimeout)
    {
        RCC_LSICmd(DISABLE);  //in STANDBY iwdg will cause reset
        
        radio_standby();
        
        Sys_Standby();
    }
    else
    { //enter SLEEP/STOP to save power
#ifdef USE_I2C
        if (0 == (I2C1->IC_STATUS & 0x20))
#endif
        {
#if 0 //SLEEP
        SysClk48to8();
        SCB->SCR &= 0xFB;
        __WFE();
        
        SysClk8to48();
#else //STOP
        SysClk48to8();
        SCB->SCR |= 0x4;
        __WFI();
        
        RCC->CR|=RCC_CR_HSION;
        RCC->CR |= RCC_CR_PLLON;
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
        SysTick_Config(48000);
#endif
        }
    }
}

//////DO NOT REMOVE, used in ble lib///////
void SysClk8to48(void)
{
    SystemClk_HSEInit();
    SysTick_Config(48000);
}
void SysClk48to8(void)
{
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);//selecting PLL clock as sys clock
    
    while (RCC_GetSYSCLKSource() != 0x0)
    {}
    
    RCC->CR &=~(RCC_CR_PLLON); //clear PLL
    SysTick_Config(8000);
}

static char dis_int_count = 0;
void DisableEnvINT(void)
{ 
    //to disable int
    __ASM volatile("cpsid i");
    
    dis_int_count ++;
}

void EnableEnvINT(void)
{
    //to enable/recover int
    dis_int_count --;    
    if(dis_int_count<=0) //protection purpose
    {
        dis_int_count = 0; //reset
        __ASM volatile("cpsie i");
    }
}

//api provide in blelib
//    EnableLED_Flag; Led_R; Led_G; Led_B; Led_Y; Led_W; Led_Lum_percent; 
void UpdateLEDValueAll(void) //porting function
{
    
}

