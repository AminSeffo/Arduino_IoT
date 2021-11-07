
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */

#ifndef MATLAB_MEX_FILE
#include <Arduino.h>                                                         
volatile bool adc = LOW;
#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */

#ifndef MATLAB_MEX_FILE
void pwm_setup() {
  
  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(1) |          // Divide the 48MHz clock source by divisor 1: 48MHz/1=48MHz
                    GCLK_GENDIV_ID(3);            // Select Generic Clock (GCLK) 4
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |           // Set the duty cycle to 50/50 HIGH/LOW
                     GCLK_GENCTRL_GENEN |         // Enable GCLK4
                     GCLK_GENCTRL_SRC_DFLL48M |   // Set the 48MHz clock source
                     GCLK_GENCTRL_ID(3);          // Select GCLK4
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  // Enable the port multiplexer for the digital pin D5
  (*PORT).Group[g_APinDescription[5].ulPort].PINCFG[g_APinDescription[5].ulPin].bit.PMUXEN = 1;

  // Connect the TCC0 timer to the port output D5 - port pins are paired odd PMUXO and even PMUXE
  // F & E specify the timers: TCC0, TCC1 and TCC2
  (*PORT).Group[g_APinDescription[5].ulPort].PMUX[g_APinDescription[5].ulPin >> 1].reg = PORT_PMUX_PMUXO_E | PORT_PMUX_PMUXE_E;

  // Feed GCLK4 to TCC0 and TCC1
  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // Enable GCLK4 to TCC0 and TCC1
                     GCLK_CLKCTRL_GEN_GCLK3 |     // Select GCLK4
                     GCLK_CLKCTRL_ID_TCC0_TCC1;   // Feed GCLK4 to TCC0 and TCC1
  while ((*GCLK).STATUS.bit.SYNCBUSY);            // Wait for synchronization

  // Double Slope PWM setup
  REG_TCC0_WAVE |= TCC_WAVE_POL(0xF) |            // Reverse the output polarity on all TCC0 outputs
                   TCC_WAVE_WAVEGEN_DSTOP;        // Setup dual slope PWM on TCC0
  while (TCC0->SYNCBUSY.bit.WAVE);                // Wait for synchronization

  // Each timer counts up to a maximum or TOP value set by the PER register,
  // this determines the frequency of the PWM operation:
  // 20000 = 50Hz, 10000 = 100Hz, 2500  = 400Hz
  REG_TCC0_PER = 480;                               // Set the frequency of the PWM on TCC0/TCC1 to 50kHz
  while (TCC0->SYNCBUSY.bit.PER);                   // Wait for synchronization

  // Set the output matrix so that D5 is set to output CC3
  REG_TCC0_WEXCTRL = TCC_WEXCTRL_OTMX(0x2);  

  // Divide the 48MHz signal by 4 giving 48MHz (20.83ns) TCC0 timer tick and enable the outputs
  REG_TCC0_CTRLA |= TCC_CTRLA_PRESCALER_DIV1 |      // Divide GCLK4 by 1
                    TCC_CTRLA_ENABLE;               // Enable the TCC0 output
  while ((*TCC0).SYNCBUSY.bit.ENABLE);              // Wait for synchronization
  /* Wait for bus synchronization. */
}

void adc_setup() {
  /* Enable GCLK0 for the ADC */
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN |
                      GCLK_CLKCTRL_GEN_GCLK0 |
                      GCLK_CLKCTRL_ID_ADC;

  while (GCLK->STATUS.bit.SYNCBUSY) {};    /* Wait for bus synchronization. */
  
  while (ADC->STATUS.bit.SYNCBUSY);                  // Wait for synchronization
    
  ADC->SAMPCTRL.bit.SAMPLEN = 0x8;                  // Set max Sampling Time Length to half divided ADC clock pulse (2.66us)
  ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_16 | ADC_AVGCTRL_ADJRES(4);
  ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV16 |     // Divide Clock ADC GCLK by 512 (48MHz/512 = 93.7kHz)
                   ADC_CTRLB_RESSEL_16BIT |          // Set the ADC resolution to 16 bits --> enable averaging mode
                   ADC_CTRLB_FREERUN;                // Set the ADC to free run
  while (ADC->STATUS.bit.SYNCBUSY);                  // Wait for synchronization
}
#endif
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void customPWM_Start_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */

#ifndef MATLAB_MEX_FILE 

//   pinMode(2, INPUT_PULLUP);    // program pin 2 as a INPUT PULLUP pin to be used for the Disable Button
  //pinMode(7, OUTPUT);          // pin 7 is used to enable/disable the gate driver
  adc_setup();                 // call the adc setup method   
  pwm_setup();                 // call the PWM setup method
    
#endif
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void customPWM_Outputs_wrapper(const real32_T *duty)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */

#ifndef MATLAB_MEX_FILE 
   digitalWrite(12,!adc);                // write a digital value 1/0 in pin 12 for Sample Rate measuring
   adc = !adc;                            // invert the state of the pin (to be updated next itteration)
    (*TCC0).CCB[0].reg = 450 * duty[0];    // set the controll register with the actual duty cycle to change dhe PWM
    
  #endif
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


