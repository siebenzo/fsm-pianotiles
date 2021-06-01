/*********************************************************************
 *
 *                  EE 4 Project - C7
 *
 *********************************************************************
 * Processor:       PIC18F25K50
 * Compiler:        XC8 1.35+
 * Author:          Peier Wu
 * Updated:         14/05/2021
 ********************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

/** D E F I N E S ***************************************************/
#define TRUE 1
#define FALSE 0

/*** ADC Configuration *******************/
/* Uncomment the line below if you want to use the ADC */
#define ENABLE_ADC TRUE

/* If you are using the ADC specify how many channels you are using
 * for every channel you can read the ADC value from ADC_value[] */
#define ADC_CHANNELS    1

/*** IO expander configuration *********** 
 * BE AWARE: When using the IO expander RC7 and RB1 are used for communication
 * RB0 can only be used as output, in this example we use it as CS */
#define ENABLE_IOEXP TRUE

#define IOEXP_DATA          LATCbits.LATC7
#define IOEXP_CLK           LATBbits.LATB1
#define IOEXP_CS            LATBbits.LATB0


/*** Audio Configuration *****************/
 #define ENABLE_AUDIO TRUE

/* Specify the pin for your audio output, every digital output can be used */
#define AUDIO_OUT           LATBbits.LATB2

/* Define all out- and inputs with readable names */
#define PRG_BUTTON      PORTCbits.RC0
#define LED1_OUT        LATCbits.LATC1
#define LED2_OUT        LATCbits.LATC2
#define POTENTIOMETER   PORTAbits.RA0 
#define BUTTON_6        PORTAbits.RA1
#define BUTTON_7        PORTAbits.RA2
#define BUTTON_8        PORTAbits.RA3
#define PWM_OUT         LATAbits.LATA4 
#define BUTTON_1        PORTBbits.RB3
#define BUTTON_2        PORTBbits.RB4
#define BUTTON_3        PORTBbits.RB5
#define BUTTON_4        PORTBbits.RB6
#define BUTTON_5        PORTBbits.RB7

/** I N C L U D E S *************************************************/
#include <xc.h>
#include "func_adc.h"
#include "func_pwm.h"
#include "func_ioexp.h"
#include "func_audio.h"
#include "func_servo.h"

/** G L O B A L   P U B L I C   V A R I A B L E S *******************/
extern unsigned char PWM_duty[1];
extern unsigned char led1_output;
extern unsigned char led2_output;
extern unsigned char lives;
extern unsigned char changed;
extern unsigned char checkSuccess;
extern unsigned char cycleFinished;
extern unsigned char Leds[8][8];
extern unsigned int noteTime;
extern unsigned char mode;

/** P U B L I C   P R O T O T Y P E S *******************************/

/** F S M   R O U T I N E S *****************************************/
void fsm_io_init(void);
void fsm_io(void);

void fsm_game_init(void);
void fsm_game(void);

void fsm_ioexp_init(void);
void fsm_ioexp(void);

#endif
//EOF----------------------------------------------------------------

