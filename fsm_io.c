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
#include "func_audio.h"
#include "func_ioexp.h"

/** P R I V A T E   V A R I A B L E S *******************************/

static unsigned char noteIndex;
static unsigned char pwm_counter;
static unsigned char audio_on_counter;

static unsigned int song3[56] = {C1, B1, E1, C1, E1, C1, E1, D1, E1, F1, F1, E1, 
D1, F1, E1, F1, G1, E1, G1, E1, G1,F1, G1, A1, A1, G1, F1, G1, G1, C1, D1, E1, 
F1,G1, A1, A1, D1, E1, F1, G1, A1, B1, B1, E1, F1, G1, A1, B1, C2, C2, B1, A1, 
F1, B1, G1, C2 };

static unsigned int song2[38] = {B1, E2, FS2, G2, E2, B1, E2, FS2, G2, E2, B1, 
E2, FS2, G2, FS2, E2, G2, FS2, E2, B2, B2, B2, A2, B2, C3, C3, E3, D3, C3, E3, 
D3, A2, G2, FS2, B2, FS2, G2, E2 };

static unsigned int song1[8] = {B1, E2, G2, FS2, E2, B2, A2, FS2};

static enum {FSM_SETIO,
             FSM_UPDATE_VU,
             FSM_PLAY_AUDIO
            } current_state;
            
            
/********************************************************************
 * Function:        void fsm_io_init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        This init sets the start state for this FSM and
 *                  may initialize some counters          
 ********************************************************************/
void fsm_io_init(void) {
	current_state = FSM_SETIO;
    led1_output = 0;
    led2_output = 0;
    pwm_counter = 0;
    changed=0;
    PWM_duty[0]=6;
    lives=5;
    noteIndex=0;
    noteTime=200;
}

/********************************************************************
 * Function:        fsm_io(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        Will give PWM output to our VU and update the PWM duty cycle when changed is 1 
 *                  A buzz will also be played when lives change         
 ********************************************************************/
void fsm_io(void) {
    
    switch (current_state) {                
        case FSM_SETIO :
            audio_on_counter=0;
            LED1_OUT = led1_output;
            pwm_counter = (pwm_counter + 1u) % 10;
            // generating a PWM signal on one (or more) of the outputs
            PWM_OUT = (unsigned)(PWM_duty[0] > pwm_counter);
//            LED2_OUT = (unsigned)(PWM_duty[0] > pwm_counter);//the lightness will decrease
        // *** transitions ***
            if (changed==1) {
                current_state = FSM_UPDATE_VU;
            }
            if(checkSuccess==1){
                noteIndex++;
                current_state = FSM_PLAY_AUDIO;
             }
            break;
        
        case FSM_UPDATE_VU :
            changed=0;
            switch(lives){
                case 5:PWM_duty[0]=6;
                break;
                case 4:PWM_duty[0]=5;
                break;
                case 3:PWM_duty[0]=3;
                break;
                case 2:PWM_duty[0]=2;
                break;
                case 1:PWM_duty[0]=1;
                break;
                case 0:PWM_duty[0]=0;
                break;
                
            }  
            current_state = FSM_SETIO;
            break;
            
        case  FSM_PLAY_AUDIO:
            pwm_counter = (pwm_counter + 1u) % 10;
            // generating a PWM signal on one (or more) of the outputs
            PWM_OUT = (unsigned)(PWM_duty[0] > pwm_counter);
//            LED2_OUT = (unsigned)(PWM_duty[0] > pwm_counter);
            if(mode==1){
            noteIndex=noteIndex%8;
            AUDIO_play(song1[noteIndex]);
            }
            if(mode==2){
            noteIndex=noteIndex%38;
            AUDIO_play(song2[noteIndex]);
            }    
            if(mode==3){
            noteIndex=noteIndex%56;
            AUDIO_play(song3[noteIndex]);
            }
            audio_on_counter++;
            if(audio_on_counter>noteTime){
            checkSuccess=0;    
            AUDIO_stop();
            current_state = FSM_SETIO;
            }
            if (changed==1) {
                changed=0;
                current_state = FSM_UPDATE_VU;}
            break;
            
        default:
            current_state = FSM_SETIO;
            break;
    }
    
}
