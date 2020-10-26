/******************************************************************************
 * @file  StepMotor.c
 * @author  Huins Embbeded Team  by HyunKH
 * @version V1.0.0
 * @date    2015. 02. 13
 * @brief   StepMotor Control (4 Step)
 ******************************************************************************/

/* Include ---------------------------------------------------------*/
#include "LPC1768_fnd.h"
#include "LPC1768_motor.h"
#include "LPC1768_utility.h"
#include "LPC17xx.h"  // Device header
#include "lpc17xx_adc.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_timer.h"
#include "Keypad.H"

#define _ADC_INT ADC_ADINTEN2
#define _ADC_CHANNEL ADC_CHANNEL_2
/* Private variable ---------------------------------------------------------*/
uint32_t motor_cnt = 0;
uint32_t ADC = 0;
__IO uint32_t adc_value = 300;
uint8_t status = 0;

int time_10h = 0;
int time_1h = 0;
int time_10m = 0;
int time_1m = 0;

uint8_t last_joystick = 0;
uint8_t ventilation = 0;
uint8_t compressor = 0;
uint8_t air_direction_up = 0;
uint8_t air_direction_down = 0;
uint8_t air_direction = 0;
uint8_t defrost_front = 0;
uint8_t defrost_back = 0;
uint8_t defrost = 0;
uint8_t before_input = 16;
uint8_t temperature = 0;
uint8_t cooling_mode = 0; // 0 - cooling 1 heating
uint8_t stop_flag = 0;

/* Private struct ---------------------------------------------------------*/
TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct;

/* custom driver ---------------------------------------------------------*/
// custom keypad
void custom_EXTI_Init(void) {
  LPC_SC->EXTINT = 0x0;
  LPC_SC->EXTMODE = 0x0;
  LPC_SC->EXTPOLAR = 0x0;
}
void custom_Keypad_DIR_Output() {
  /* PORT0 defined as Output    */
  LPC_GPIO0->FIODIR |= (1 << 5);
  LPC_GPIO0->FIODIR |= (1 << 10);
  /* PORT2 defined as output    */
  LPC_GPIO2->FIODIR |= (1 << 12);
  LPC_GPIO2->FIODIR |= (1 << 13);
}

void custom_Keypad_Output_Row_1() {
  custom_Keypad_DIR_Output();
  /* PORT0 defined as Output    */
  LPC_GPIO0->FIOPIN &= ~(1 << 5);
  LPC_GPIO0->FIOPIN |= (1 << 10);
  /* PORT2 defined as output    */
  LPC_GPIO2->FIOPIN |= (1 << 12);
  LPC_GPIO2->FIOPIN |= (1 << 13);

  LPC_GPIO2->FIOPIN |= (1 << 11);  // CS Clock High Edge
  LPC_GPIO2->FIOPIN &= ~(1 << 11);
}
void custom_Keypad_Output_Row_2() {
  custom_Keypad_DIR_Output();
  /* PORT0 defined as Output    */
  LPC_GPIO0->FIOPIN |= (1 << 5);
  LPC_GPIO0->FIOPIN &= ~(1 << 10);
  /* PORT2 defined as output    */
  LPC_GPIO2->FIOPIN |= (1 << 12);
  LPC_GPIO2->FIOPIN |= (1 << 13);

  LPC_GPIO2->FIOPIN |= (1 << 11);  // CS Clock High Edge
  LPC_GPIO2->FIOPIN &= ~(1 << 11);
}

void custom_Keypad_Output_Row_3() {
  custom_Keypad_DIR_Output();
  /* PORT0 defined as Output    */
  LPC_GPIO0->FIOPIN |= (1 << 5);
  LPC_GPIO0->FIOPIN |= (1 << 10);
  /* PORT2 defined as output    */
  LPC_GPIO2->FIOPIN &= ~(1 << 12);
  LPC_GPIO2->FIOPIN |= (1 << 13);

  LPC_GPIO2->FIOPIN |= (1 << 11);  // CS Clock High Edge
  LPC_GPIO2->FIOPIN &= ~(1 << 11);
}

void custom_Keypad_Output_Row_4() {
  custom_Keypad_DIR_Output();
  /* PORT0 defined as Output    */
  LPC_GPIO0->FIOPIN |= (1 << 5);
  LPC_GPIO0->FIOPIN |= (1 << 10);
  /* PORT2 defined as output    */
  LPC_GPIO2->FIOPIN |= (1 << 12);
  LPC_GPIO2->FIOPIN &= ~(1 << 13);

  LPC_GPIO2->FIOPIN |= (1 << 11);  // CS Clock High Edge
  LPC_GPIO2->FIOPIN &= ~(1 << 11);
}

uint8_t custom_Keypad_Input(uint8_t Low_Num) {
  uint32_t Key_val = 0;
  LPC_GPIO1->FIOPIN &= ~(1 << 21);  // Keypad Input CS On

  if (Low_Num == 1) {
    if ((LPC_GPIO0->FIOPIN >> 23) & 0x01)
      Key_val = 0;
    else
      Key_val = 1;
  }
  if (Low_Num == 2) {
    if ((LPC_GPIO0->FIOPIN >> 24) & 0x01)
      Key_val = 0;
    else
      Key_val = 1;
  }
  if (Low_Num == 3) {
    if ((LPC_GPIO3->FIOPIN >> 25) & 0x01)
      Key_val = 0;
    else
      Key_val = 1;
  }
  if (Low_Num == 4) {
    if ((LPC_GPIO3->FIOPIN >> 26) & 0x01)
      Key_val = 0;
    else
      Key_val = 1;
  }

  LPC_GPIO1->FIOPIN |= (1 << 21);  // Keypad Input CS Off

  return Key_val;
}

uint8_t custom_keypad(int8_t EXT_IO_DIR) {
  uint8_t Key_Temp, Key_Value = 16;

  LPC_GPIO_TypeDef bc_gp0;
  LPC_GPIO_TypeDef bc_gp2;
  LPC_GPIO_TypeDef bc_gp3;

  bc_gp0.FIOPIN = LPC_GPIO0->FIOPIN;
  bc_gp2.FIOPIN = LPC_GPIO2->FIOPIN;
  bc_gp3.FIOPIN = LPC_GPIO3->FIOPIN;
  bc_gp0.FIODIR = LPC_GPIO0->FIODIR;
  bc_gp2.FIODIR = LPC_GPIO2->FIODIR;
  bc_gp3.FIODIR = LPC_GPIO3->FIODIR;

  LPC_GPIO0->FIOPIN |= (1 << 4);  // DIR A->B
                                  /* PORT0 defined as Input    */
  LPC_GPIO0->FIODIR &= ~(1 << 23);
  LPC_GPIO0->FIODIR &= ~(1 << 24);
  /* PORT3 defined as input    */
  LPC_GPIO3->FIODIR &= ~(1 << 25);
  LPC_GPIO3->FIODIR &= ~(1 << 26);

  custom_Keypad_DIR_Output();

  if (EXT_IO_DIR == 'A')
    EXT_IO_A_CS();
  else if (EXT_IO_DIR == 'B')
    EXT_IO_B_CS();
  else
    EXT_IO_C_CS();

  custom_Keypad_Output_Row_1();
  Key_Temp = custom_Keypad_Input(1);
  if (Key_Temp == 1) Key_Value = 3;
  Key_Temp = custom_Keypad_Input(2);
  if (Key_Temp == 1) Key_Value = 2;
  Key_Temp = custom_Keypad_Input(3);
  if (Key_Temp == 1) Key_Value = 1;
  Key_Temp = custom_Keypad_Input(4);
  if (Key_Temp == 1) Key_Value = 0;

  custom_Keypad_Output_Row_2();
  Key_Temp = custom_Keypad_Input(1);
  if (Key_Temp == 1) Key_Value = 7;
  Key_Temp = custom_Keypad_Input(2);
  if (Key_Temp == 1) Key_Value = 6;
  Key_Temp = custom_Keypad_Input(3);
  if (Key_Temp == 1) Key_Value = 5;
  Key_Temp = custom_Keypad_Input(4);
  if (Key_Temp == 1) Key_Value = 4;

  custom_Keypad_Output_Row_3();
  Key_Temp = custom_Keypad_Input(1);
  if (Key_Temp == 1) Key_Value = 11;
  Key_Temp = custom_Keypad_Input(2);
  if (Key_Temp == 1) Key_Value = 10;
  Key_Temp = custom_Keypad_Input(3);
  if (Key_Temp == 1) Key_Value = 9;
  Key_Temp = custom_Keypad_Input(4);
  if (Key_Temp == 1) Key_Value = 8;

  custom_Keypad_Output_Row_4();
  Key_Temp = custom_Keypad_Input(1);
  if (Key_Temp == 1) Key_Value = 15;
  Key_Temp = custom_Keypad_Input(2);
  if (Key_Temp == 1) Key_Value = 14;
  Key_Temp = custom_Keypad_Input(3);
  if (Key_Temp == 1) Key_Value = 13;
  Key_Temp = custom_Keypad_Input(4);
  if (Key_Temp == 1) Key_Value = 12;

  LPC_GPIO0->FIOPIN = bc_gp0.FIOPIN;
  LPC_GPIO2->FIOPIN = bc_gp2.FIOPIN;
  LPC_GPIO3->FIOPIN = bc_gp3.FIOPIN;
  LPC_GPIO0->FIODIR = bc_gp0.FIODIR;
  LPC_GPIO2->FIODIR = bc_gp2.FIODIR;
  LPC_GPIO3->FIODIR = bc_gp3.FIODIR;

  return Key_Value;
}

uint8_t custom_Hvac(uint8_t before_input) {
  uint8_t keypad_value;
  keypad_value = custom_keypad('C');

  // SAME KEY
  if (keypad_value == before_input) return keypad_value;

  // MODE
  else if (keypad_value == 0) {
    ventilation++;
    if (ventilation == 3) ventilation = 0;
  } else if (keypad_value == 1) {
    compressor ^= 0x01;
  } else if (keypad_value == 4 || keypad_value == 5) {
    if (keypad_value == 4) air_direction_down ^= 0x01;
    if (keypad_value == 5) air_direction_up ^= 0x01;

    if (air_direction_down == 1 && air_direction_up == 0)
      air_direction = 1;
    else if (air_direction_down == 0 && air_direction_up == 1)
      air_direction = 2;
    else
      air_direction = 0;
  } else if (keypad_value == 8 || keypad_value == 9) {
    if (keypad_value == 8) defrost_front ^= 0x01;
    if (keypad_value == 9) defrost_back ^= 0x01;

    if (defrost_front == 1 && defrost_back == 1)
      defrost = 3;
    else if (defrost_front == 1 && defrost_back == 0)
      defrost = 1;
    else if (defrost_front == 0 && defrost_back == 1)
      defrost = 2;
    else
      defrost = 0;
  }

  // TEMPERATE
  else if (keypad_value == 13){
      temperature = 0;
      cooling_mode ^= 0x01;
   }  
  else if (keypad_value != 16){
      temperature = (keypad_value / 4) * 2 + keypad_value % 4 - 1;
   }
    

  return keypad_value;
}

// custom joystick
void timeCheck() {
  //+
  if (time_1h >= 10) {
    time_1h = 0;
    time_10h++;
  }
  if (time_10h >= 2) {
    if (time_1h >= 4) {
      time_10h = 0;
      time_1h = 0;
    }
  }
  if (time_1m >= 10) {
    time_1m = 0;
    time_10m++;
  }
  if (time_10m >= 6) {
    time_10m = 0;
    time_1m = 0;
  }
  //-
  if (time_1h < 0) {
    if (time_10h == 0) {
      time_10h = 2;
      time_1h = 3;
    } else {
      time_10h--;
      time_1h = 9;
    }
  }
  if (time_1m < 0) {
    if (time_10m == 0) {
      time_10m = 5;
      time_1m = 9;
    } else {
      time_1m = 9;
      time_10m--;
    }
  }
}

void custom_Joystick_Init(void) {
  LPC_GPIO4->FIODIR |= (1 << 28);  //output

  LPC_GPIO1->FIODIR &= ~(1 << 20);  //input
  LPC_GPIO1->FIODIR &= ~(1 << 23);
  LPC_GPIO1->FIODIR &= ~(1 << 24);
  LPC_GPIO1->FIODIR &= ~(1 << 25);
  LPC_GPIO1->FIODIR &= ~(1 << 26);
}

void custom_Joystick_read() {
  uint8_t temp = 0;
  uint8_t temp_time = 0;
  LPC_GPIO_TypeDef bc_gp0;
  LPC_GPIO_TypeDef bc_gp2;
  LPC_GPIO_TypeDef bc_gp3;
  LPC_GPIO_TypeDef bc_gp4;

  bc_gp0.FIOPIN = LPC_GPIO0->FIOPIN;
  bc_gp2.FIOPIN = LPC_GPIO2->FIOPIN;
  bc_gp3.FIOPIN = LPC_GPIO3->FIOPIN;
  bc_gp4.FIOPIN = LPC_GPIO4->FIOPIN;
  bc_gp0.FIODIR = LPC_GPIO0->FIODIR;
  bc_gp2.FIODIR = LPC_GPIO2->FIODIR;
  bc_gp3.FIODIR = LPC_GPIO3->FIODIR;
  bc_gp4.FIODIR = LPC_GPIO4->FIODIR;

  custom_Joystick_Init();

  //TODO: make your own Joystick Driver!
  if (((LPC_GPIO1->FIOPIN >> 23) & 0x01) == 0) {
    if (last_joystick != 1) {
      time_1h--;
      last_joystick = 1;
    }
  } else if (((LPC_GPIO1->FIOPIN >> 24) & 0x01) == 0) {
    if (last_joystick != 2) {
      time_1m++;
      last_joystick = 2;
    }
  } else if (((LPC_GPIO1->FIOPIN >> 25) & 0x01) == 0) {
    if (last_joystick != 3) {
      time_1h++;
      last_joystick = 3;
    }
  } else if (((LPC_GPIO1->FIOPIN >> 26) & 0x01) == 0) {
    if (last_joystick != 4) {
      time_1m--;
      last_joystick = 4;
    }
  } else if (((LPC_GPIO1->FIOPIN >> 20) & 0x01) == 0) {
    if (last_joystick != 5) {
      time_10h = 0;
      time_1h = 0;
      time_10m = 0;
      time_1m = 0;
      last_joystick = 5;
    }
  } else
    last_joystick = 0;

  LPC_GPIO0->FIOPIN = bc_gp0.FIOPIN;
  LPC_GPIO2->FIOPIN = bc_gp2.FIOPIN;
  LPC_GPIO3->FIOPIN = bc_gp3.FIOPIN;
  LPC_GPIO4->FIOPIN = bc_gp4.FIOPIN;
  LPC_GPIO0->FIODIR = bc_gp0.FIODIR;
  LPC_GPIO2->FIODIR = bc_gp2.FIODIR;
  LPC_GPIO3->FIODIR = bc_gp3.FIODIR;
  LPC_GPIO4->FIODIR = bc_gp4.FIODIR;
}

// time interrupter
void TIMER0_IRQHandler(void) {
  TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);  //TIM0 interrupt clear

  // ? : 1? ?? , 10? ?? / ? : 1? ??, 10? ??
  time_1m++;
  if (time_1m == 10) {
    time_10m++;
    time_1m = 0;
  }
  if (time_10m == 6) {
    time_1h++;
    time_10m = 0;
  }
  if (time_1h == 10) {
    time_10h++;
    time_1h = 0;
  }
  if (time_10h == 2) {
    if (time_1h == 4) {
      time_10h = 0;
      time_1h = 0;
      time_10m = 0;
      time_1m = 0;
    }
  }
}

void TIMER0_Config(void) {
  TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;             //   us(microsecond) ???? Prescale ??
  TIM_ConfigStruct.PrescaleValue = 100;                             //   100us
  TIM_MatchConfigStruct.MatchChannel = 0;                           //   0? ?? ??
  TIM_MatchConfigStruct.IntOnMatch = ENABLE;                        //   Timer? ??? ?  Interrupt ?? Enable
  TIM_MatchConfigStruct.ResetOnMatch = ENABLE;                      //   Timer? ??? ?  Reset Enable
  TIM_MatchConfigStruct.StopOnMatch = DISABLE;                      //   Timer? ??? ? Timer Stop Disable
  TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;  //   Timer ???? ??? ?? ?? ?? ?? (??? ???? ?? ??? GPIO? ???? ??? ?.)
  TIM_MatchConfigStruct.MatchValue = 600000;                        // Timer ?? ? ?? 100us * 10000? = 1?
}

// potentio
void ADC_IRQHandler(void) {
  adc_value = 0;
  if (ADC_ChannelGetStatus(LPC_ADC, _ADC_CHANNEL, ADC_DATA_DONE)) {
    adc_value = ADC_ChannelGetData(LPC_ADC, _ADC_CHANNEL) / 400;
    if (adc_value == 0)
      stop_flag = 1;
    else
      stop_flag = 0;
    NVIC_DisableIRQ(ADC_IRQn);
  }
}

// step motor
void custom_Motor_Init(void) {
  GPIO_SetDir(GPIO_PORT_0, (1 << 4) | (1 << 5) | (1 << 10) | (1 << 11) | (1 << 19) | (1 << 20) | (1 << 21) | (1 << 23) | (1 << 24), OUTPUT);
  GPIO_SetDir(GPIO_PORT_1, (1 << 21), OUTPUT);
  GPIO_SetDir(GPIO_PORT_2, (1 << 11) | (1 << 12) | (1 << 13), OUTPUT);
  GPIO_SetDir(GPIO_PORT_3, (1 << 25) | (1 << 26), OUTPUT);
}
void custom_StepMotor_Cycle(uint8_t cycle) {
  uint32_t count = 0;

  for (count = 0; count < cycle * 4; count++) {
    GPIO_SetValue(GPIO_PORT_0, GPIO_PIN_5);
    GPIO_ClearValue(GPIO_PORT_0, GPIO_PIN_10);
    GPIO_SetValue(GPIO_PORT_0, GPIO_PIN_23);
    GPIO_ClearValue(GPIO_PORT_0, GPIO_PIN_24);
    Delay(SEC_1 / (10 + adc_value * 16));

    GPIO_ClearValue(GPIO_PORT_0, GPIO_PIN_5);
    GPIO_SetValue(GPIO_PORT_0, GPIO_PIN_10);
    GPIO_SetValue(GPIO_PORT_0, GPIO_PIN_23);
    GPIO_ClearValue(GPIO_PORT_0, GPIO_PIN_24);
    Delay(SEC_1 / (10 + adc_value * 16));

    GPIO_ClearValue(GPIO_PORT_0, GPIO_PIN_5);
    GPIO_SetValue(GPIO_PORT_0, GPIO_PIN_10);
    GPIO_ClearValue(GPIO_PORT_0, GPIO_PIN_23);
    GPIO_SetValue(GPIO_PORT_0, GPIO_PIN_24);
    Delay(SEC_1 / (10 + adc_value * 16));

    GPIO_SetValue(GPIO_PORT_0, GPIO_PIN_5);
    GPIO_ClearValue(GPIO_PORT_0, GPIO_PIN_10);
    GPIO_ClearValue(GPIO_PORT_0, GPIO_PIN_23);
    GPIO_SetValue(GPIO_PORT_0, GPIO_PIN_24);
    Delay(SEC_1 / (10 + adc_value * 16));
  }
}

// FND
void custom_FND_Init(void) {
  GPIO_SetDir(GPIO_PORT_0, (1 << 4) | (1 << 5) | (1 << 10) | (1 << 11) | (1 << 19) | (1 << 20) | (1 << 21) | (1 << 23) | (1 << 24), OUTPUT);
  GPIO_SetDir(GPIO_PORT_1, (1 << 21), OUTPUT);
  GPIO_SetDir(GPIO_PORT_2, (1 << 11) | (1 << 12) | (1 << 13), OUTPUT);
  GPIO_SetDir(GPIO_PORT_3, (1 << 25) | (1 << 26), OUTPUT);
}

void custom_FND_Segment(uint8_t comNum, uint8_t dataNum) {
  // init
  GPIO_ClearValue(GPIO_PORT_0, (1 << 23));  //   COM1
  GPIO_ClearValue(GPIO_PORT_0, (1 << 24));  //   COM2
  GPIO_ClearValue(GPIO_PORT_1, (1 << 21));  //   COM3
  GPIO_ClearValue(GPIO_PORT_2, (1 << 11));  //   COM4
  GPIO_ClearValue(GPIO_PORT_2, (1 << 12));  //   COM5
  GPIO_ClearValue(GPIO_PORT_2, (1 << 13));  //   COM6
  GPIO_ClearValue(GPIO_PORT_3, (1 << 25));  //   COM7
  GPIO_ClearValue(GPIO_PORT_3, (1 << 26));  //   COM8

  // select
  switch (comNum) {
    case 1:
      GPIO_SetValue(GPIO_PORT_0, (1 << 23));  //   DIC
      break;

    case 2:
      GPIO_SetValue(GPIO_PORT_0, (1 << 24));  //   DIC 2
      break;

    case 3:
      GPIO_SetValue(GPIO_PORT_1, (1 << 21));  //   DIC 3
      break;

    case 4:
      GPIO_SetValue(GPIO_PORT_2, (1 << 11));  //   DIC 4
      break;

    case 5:
      GPIO_SetValue(GPIO_PORT_2, (1 << 12));  //   DIC 5
      break;

    case 6:
      GPIO_SetValue(GPIO_PORT_2, (1 << 13));  //   DIC 6
      break;

    case 7:
      GPIO_SetValue(GPIO_PORT_3, (1 << 25));  //   DIC 7
      break;

    case 8:
      GPIO_SetValue(GPIO_PORT_3, (1 << 26));  //   DIC 8
      break;
  }

  LPC_GPIO0->FIOPIN |= (1 << 10);
  LPC_GPIO0->FIOPIN &= ~(1 << 10);

  /* FND Data setting */
  GPIO_SetValue(GPIO_PORT_0, (1 << 23));  //   FND A
  GPIO_SetValue(GPIO_PORT_0, (1 << 24));  //   FND B
  GPIO_SetValue(GPIO_PORT_1, (1 << 21));  //   FND C
  GPIO_SetValue(GPIO_PORT_2, (1 << 11));  //   FND D
  GPIO_SetValue(GPIO_PORT_2, (1 << 12));  //   FND E
  GPIO_SetValue(GPIO_PORT_2, (1 << 13));  //   FND F
  GPIO_SetValue(GPIO_PORT_3, (1 << 25));  //   FND G
  GPIO_SetValue(GPIO_PORT_3, (1 << 26));  //   FND DP

  // clock init
  GPIO_SetValue(GPIO_PORT_0, (1 << 5));
  GPIO_ClearValue(GPIO_PORT_0, (1 << 5));

  switch (dataNum) {
    case 0:
      GPIO_ClearValue(GPIO_PORT_0, FND_A | FND_B);
      GPIO_ClearValue(GPIO_PORT_1, FND_C);
      GPIO_ClearValue(GPIO_PORT_2, FND_D | FND_E | FND_F);
      break;

    case 1:
      GPIO_ClearValue(GPIO_PORT_0, FND_B);
      GPIO_ClearValue(GPIO_PORT_1, FND_C);
      break;

    case 2:
      GPIO_ClearValue(GPIO_PORT_0, FND_A | FND_B);
      GPIO_ClearValue(GPIO_PORT_2, FND_D | FND_E);
      GPIO_ClearValue(GPIO_PORT_3, FND_G);
      break;

    case 3:
      GPIO_ClearValue(GPIO_PORT_0, FND_A | FND_B);
      GPIO_ClearValue(GPIO_PORT_1, FND_C);
      GPIO_ClearValue(GPIO_PORT_2, FND_D);
      GPIO_ClearValue(GPIO_PORT_3, FND_G);
      break;

    case 4:
      GPIO_ClearValue(GPIO_PORT_0, FND_B);
      GPIO_ClearValue(GPIO_PORT_1, FND_C);
      GPIO_ClearValue(GPIO_PORT_2, FND_F);
      GPIO_ClearValue(GPIO_PORT_3, FND_G);
      break;

    case 5:
      GPIO_ClearValue(GPIO_PORT_0, FND_A);
      GPIO_ClearValue(GPIO_PORT_1, FND_C);
      GPIO_ClearValue(GPIO_PORT_2, FND_D | FND_F);
      GPIO_ClearValue(GPIO_PORT_3, FND_G);
      break;

    case 6:
      GPIO_ClearValue(GPIO_PORT_0, FND_A);
      GPIO_ClearValue(GPIO_PORT_1, FND_C);
      GPIO_ClearValue(GPIO_PORT_2, FND_D | FND_E | FND_F);
      GPIO_ClearValue(GPIO_PORT_3, FND_G);
      break;

    case 7:
      GPIO_ClearValue(GPIO_PORT_0, FND_A | FND_B);
      GPIO_ClearValue(GPIO_PORT_1, FND_C);
      break;

    case 8:
      GPIO_ClearValue(GPIO_PORT_0, FND_A | FND_B);
      GPIO_ClearValue(GPIO_PORT_1, FND_C);
      GPIO_ClearValue(GPIO_PORT_2, FND_D | FND_E | FND_F);
      GPIO_ClearValue(GPIO_PORT_3, FND_G);
      break;

    case 9:
      GPIO_ClearValue(GPIO_PORT_0, FND_A | FND_B);
      GPIO_ClearValue(GPIO_PORT_1, FND_C);
      GPIO_ClearValue(GPIO_PORT_2, FND_F);
      GPIO_ClearValue(GPIO_PORT_3, FND_G);
      break;
  }

  GPIO_SetValue(GPIO_PORT_0, (1 << 5));
  GPIO_ClearValue(GPIO_PORT_0, (1 << 5));
}

void custom_FND_Present() {
  custom_FND_Segment(8, time_1m);  // 8??(??? ? ?) ????? time_1s ? ??
  Delay(5000);
  custom_FND_Segment(7, time_10m);
  Delay(5000);
  custom_FND_Segment(6, time_1h);
  Delay(5000);
  custom_FND_Segment(5, time_10h);
  Delay(5000);

  // Mode
  custom_FND_Segment(1, ventilation);
  Delay(5000);
  custom_FND_Segment(2, compressor);
  Delay(5000);
  custom_FND_Segment(3, air_direction);
  Delay(5000);
  custom_FND_Segment(4, defrost);
  Delay(5000);
}
// LED
void custom_Led_Init() {
  GPIO_SetDir(GPIO_PORT_1, (1 << 28) | (1 << 29) | (1 << 31), OUTPUT);
  GPIO_SetDir(GPIO_PORT_2, (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6), OUTPUT);
}
void custom_Led_Present1(uint8_t Led) {
  // LED On
  if (Led >= 1)
    GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_28);

  if (Led >= 2)
    GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_29);

  if (Led >= 3)
    GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_31);

  if (Led >= 4)
    GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_2);

  if (Led >= 5)
    GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_3);

  if (Led >= 6)
    GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_4);

  if (Led >= 7)
    GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_5);

  if (Led >= 8)
    GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_6);

  // LED Off
  if (Led < 1)
    GPIO_ClearValue(GPIO_PORT_1, GPIO_PIN_28);

  if (Led < 2)
    GPIO_ClearValue(GPIO_PORT_1, GPIO_PIN_29);

  if (Led < 3)
    GPIO_ClearValue(GPIO_PORT_1, GPIO_PIN_31);

  if (Led < 4)
    GPIO_ClearValue(GPIO_PORT_2, GPIO_PIN_2);

  if (Led < 5)
    GPIO_ClearValue(GPIO_PORT_2, GPIO_PIN_3);

  if (Led < 6)
    GPIO_ClearValue(GPIO_PORT_2, GPIO_PIN_4);

  if (Led < 7)
    GPIO_ClearValue(GPIO_PORT_2, GPIO_PIN_5);

  if (Led < 8)
    GPIO_ClearValue(GPIO_PORT_2, GPIO_PIN_6);
}

void custom_Led_Present2(uint8_t Led) {
  // LED On
  if (Led >= 1)
      GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_6);
    
  if (Led >= 2)
      GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_5);
    
  if (Led >= 3)
      GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_4);

  if (Led >= 4)
      GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_3);
 
  if (Led >= 5)
    GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_2);

  if (Led >= 6)
    GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_31);

  if (Led >= 7)
    GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_29);

  if (Led >= 8)
    GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_28);

  // LED Off
  if (Led < 1)
      GPIO_ClearValue(GPIO_PORT_2, GPIO_PIN_6);

  if (Led < 2)
    GPIO_ClearValue(GPIO_PORT_2, GPIO_PIN_5);

  if (Led < 3)
    GPIO_ClearValue(GPIO_PORT_2, GPIO_PIN_4);

  if (Led < 4)
      GPIO_ClearValue(GPIO_PORT_2, GPIO_PIN_3);
   
  if (Led < 5)
    GPIO_ClearValue(GPIO_PORT_2, GPIO_PIN_2);

  if (Led < 6)
      GPIO_ClearValue(GPIO_PORT_1, GPIO_PIN_31);

  if (Led < 7)
      GPIO_ClearValue(GPIO_PORT_1, GPIO_PIN_29);
    
  if (Led < 8)
      GPIO_ClearValue(GPIO_PORT_1, GPIO_PIN_28);
    
}


// int interrupter
void EINT0_IRQHandler(void) {
  EXTI_ClearEXTIFlag(EXTI_EINT0);  // Interrupt        U      ?   ?         ·   ?? .
  status = status == 0 ? 1 : 0;
}

int main(void) {
  // initialize
  uint8_t i;
  PINSEL_CFG_Type PinCfg;
  custom_Motor_Init();
  custom_FND_Init();
  custom_Joystick_Init();
  custom_Led_Init();
  custom_EXTI_Init();

  // configuration for pin port
  AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_10, PINSEL_FUNC_1);

  // configuration for external interrupter
  EXTI_ConfigPin(EXTI_EINT0);
  NVIC_EnableIRQ(EINT0_IRQn);

  // configuration for timer interrupter
  TIMER0_Config();
  TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TIM_ConfigStruct);  //  TIM_ConfigStruct ?? ??
  TIM_ConfigMatch(LPC_TIM0, &TIM_MatchConfigStruct);      // TIM_MatchConfigStruct ?? ??
  NVIC_EnableIRQ(TIMER0_IRQn);                            //   TIMER0 Interrupt ???
  TIM_Cmd(LPC_TIM0, ENABLE);                              //   Timer Start

  // configuration for potentio (ADC)
  PinCfg.Funcnum = 1;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Pinnum = 25;
  PinCfg.Portnum = 0;
  PINSEL_ConfigPin(&PinCfg);
  ADC_Init(LPC_ADC, 200000);
  ADC_IntConfig(LPC_ADC, _ADC_INT, ENABLE);
  ADC_ChannelCmd(LPC_ADC, _ADC_CHANNEL, ENABLE);
  NVIC_SetPriority(ADC_IRQn, ((0x01 << 3) | 0x01));

  while (1) {
    if (status == 0) {
      // Time & Mode
      custom_Joystick_read();
      timeCheck();
      before_input = custom_Hvac(before_input);
      custom_FND_Present();

      // Temperature
         if(compressor){
            if(cooling_mode) custom_Led_Present1(temperature);
            else custom_Led_Present2(temperature);
         } else custom_Led_Present1(0);
         
         
         
    } else {
      ADC_StartCmd(LPC_ADC, ADC_START_NOW);
      NVIC_EnableIRQ(ADC_IRQn);
      if (stop_flag == 1) {
      } else
        custom_StepMotor_Cycle(1);
    }
  }
}