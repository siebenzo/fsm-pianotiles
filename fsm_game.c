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

/** I N C L U D E S *************************************************/
#include "config.h"
#include <stdlib.h>
#include <stdbool.h>
#include "func_audio.h"     
#include "func_adc.h"


/** D E F I N E S ***************************************************/
#define PUSHED 0

static unsigned int led_on_counter;
static unsigned int led_update_counter;   //is update state necessary?????
static unsigned int audio_on_counter;
static unsigned int led_cycle;
static unsigned char buttonIndex;
/** P R I V A T E   V A R I A B L E S *******************************/
static enum {FSM_IDLE,
            FSM_PLAY,
            FSM_MODE,
            FSM_START_EDGE,
            FSM_LED_ON,
            FSM_LED_UPDATE,
            FSM_CHECK,
            FSM_Success,
            FSM_MISS,
            FSM_FAIL
            } current_state;
            
/********************************************************************
 * Function:        void fsm_game_init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        This init sets the start state for this FSM and
 *                  may initialize some counters          
 ********************************************************************/
void fsm_game_init(void) {
	current_state = FSM_IDLE;
	led_on_counter=0;
    audio_on_counter=0;
    led_update_counter=0;
    lives=5;
    changed=0;
    cycleFinished=0;
    checkSuccess=0;
    mode=1;
    led_cycle=2000;
}

bool check(unsigned char button_pushed){
    if(Leds[7][button_pushed-1]==1){
        return false;
    }
    else{
       Leds[7][button_pushed-1]=1;
       return true;
    }
}

bool led_all_off(void){
    for(int i=0;i<8;i++){
       if(Leds[7][i]==0)   return false;
    }
    return true;
}

char pushed(void){
    if(BUTTON_1==PUSHED){
        return 1;
    }
    if(BUTTON_2==PUSHED){
        return 2;
    }
    if(BUTTON_3==PUSHED){
        return 3;
    }
    if(BUTTON_4==PUSHED){
        return 4;
    }
    if(BUTTON_5==PUSHED){
        return 5;
    }
    if(BUTTON_6==PUSHED){
        return 6;
    }
    if(BUTTON_7==PUSHED){
        return 7;
    }
    if(BUTTON_8==PUSHED){
        return 8;
    }
    return 0;
}

void fail(void){// turn on all the leds
    for(int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            Leds[i][j]=0;
        }
    }
}

void modeSelect(unsigned char modeWanted){
    if(modeWanted==1)  
    {mode=1;led_cycle = 10000;}
    if(modeWanted==2)  
    {mode=2;led_cycle = 8000;}
    if(modeWanted==3)  
    {mode=3;led_cycle = 6000;}
}
/********************************************************************
 * Function:        void fsm_game(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        An implementation for our game play
 ********************************************************************/
void fsm_game(void) {
    
    switch (current_state) { 
        case FSM_IDLE :
            startADC();
            if(pushed()>0){
              audio_on_counter=0;
              current_state=FSM_PLAY;
            }
            break;
        case FSM_PLAY:    
            AUDIO_play(C1);
            audio_on_counter++;
            if(audio_on_counter>500){ 
                AUDIO_stop();
                current_state=FSM_MODE;
            } 
            break;
        case FSM_MODE:
            if (ADC_value[0] < 328) {
                modeSelect(1);
            }
            if (ADC_value[0] >= 328 && ADC_value[0] <= 655) {
                modeSelect(2);                             
            }
            if (ADC_value[0] > 655) {
                modeSelect(3);               
            }
//            noteTime=led_cycle/10;
            current_state = FSM_START_EDGE;
            break;
        case FSM_START_EDGE :
            changed=0;
            cycleFinished=0;
            led_on_counter=0;
            led_update_counter=0;
            if(pushed()==0){
                current_state=FSM_LED_ON;
            }
            break;
        case FSM_LED_ON :
            led1_output=1;
            led_on_counter++;
            if(led_on_counter<=led_cycle&&pushed()>0){
                buttonIndex=pushed();
                current_state=FSM_CHECK;
            }
            if(led_on_counter<=led_cycle&&led_all_off()==TRUE){
            cycleFinished=1;    
            current_state=FSM_LED_UPDATE;
            }
            if(led_on_counter>led_cycle) {
                if(led_all_off()==FALSE) current_state=FSM_MISS;
                else{
                cycleFinished=1;
                current_state=FSM_LED_UPDATE;
            }
            }
            break;
        case FSM_LED_UPDATE:
            cycleFinished=0;
            led_update_counter++;
            if(led_update_counter>100) current_state=FSM_START_EDGE ;
            break;
        case FSM_CHECK:
            changed=0;
            if(check(buttonIndex)) {
                checkSuccess=1;
                current_state=FSM_Success;
            }
            else current_state=FSM_MISS;
            break;
        case FSM_Success:
            checkSuccess=0;
            if(pushed()==0) current_state=FSM_LED_ON;
            break;
        case FSM_MISS:
            lives--;
            changed=1;
            if(lives>0) 
            {cycleFinished=1; 
            current_state=FSM_LED_UPDATE;}
            else current_state=FSM_FAIL;
            break;
        case FSM_FAIL:
            changed=0;
            cycleFinished=0;
            fail();
            led1_output = 1;
            led2_output = 1;   
            break;
        default:
            current_state = FSM_IDLE;
            break;
    }
}
    

