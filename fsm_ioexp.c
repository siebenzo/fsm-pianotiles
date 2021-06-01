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

static unsigned int IOEXP_OUTPUT_COL;

static enum {
    FSM_IOEXP_OUTPUT0,
    FSM_IOEXP_OUTPUT1,
    FSM_IOEXP_OUTPUT2,
    FSM_IOEXP_OUTPUT3,
    FSM_IOEXP_OUTPUT4,
    FSM_IOEXP_OUTPUT5,
    FSM_IOEXP_OUTPUT6,
    FSM_IOEXP_OUTPUT7, 
    FSM_UPDATE_ROW01,
    FSM_UPDATE_ROW02,
    FSM_UPDATE_ROW03,
    FSM_UPDATE_ROW04,   
    FSM_UPDATE_ROW1,
    FSM_UPDATE_ROW2,
    FSM_UPDATE_ROW3,
    FSM_UPDATE_ROW4,
    FSM_UPDATE_ROW5,
    FSM_UPDATE_ROW6,
    FSM_UPDATE_ROW7        
            } current_state;
            
/********************************************************************
 * Function:        void fsm_ioexp_init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        This init sets the start state for this FSM and
 *                  may initialize some counters          
 ********************************************************************/
void fsm_ioexp_init(void) {
	current_state = FSM_IOEXP_OUTPUT0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
        {
            Leds[i][j]=1;
        }
    }
}
/********************************************************************
 * Function:        fsm_ioexp(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        Will constantly light up every row according to Leds matrix
 *                  And when a cycle is finished, leds will be updated
 ********************************************************************/
void fsm_ioexp(void) {    
    switch (current_state) {                
        case FSM_IOEXP_OUTPUT0:
            IOEXP_send(0x80, 1);
            IOEXP_OUTPUT_COL=0x00;
            for (int j = 8; j>0; j--) {
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL << 1;
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL | Leds[0][j-1];
            }
            IOEXP_send(IOEXP_OUTPUT_COL, 0);
            if (cycleFinished==1) current_state = FSM_UPDATE_ROW7;
            else  current_state = FSM_IOEXP_OUTPUT1;  
            break;
        case FSM_IOEXP_OUTPUT1:
            IOEXP_send(0x40, 1);
            IOEXP_OUTPUT_COL=0x00;
            for (int j=8;j>0;j--) {
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL << 1;
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL | Leds[1][j-1];            
            }            
            IOEXP_send(IOEXP_OUTPUT_COL, 0);
            if (cycleFinished==1) current_state = FSM_UPDATE_ROW7;
            else current_state = FSM_IOEXP_OUTPUT2;
            break;
        case FSM_IOEXP_OUTPUT2:
            IOEXP_send(0x20, 1);
            IOEXP_OUTPUT_COL=0x00;
            for (int j = 8; j>0; j--) {
                 IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL << 1;
                 IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL | Leds[2][j-1];             
            }
            IOEXP_send(IOEXP_OUTPUT_COL, 0);            
            if (cycleFinished==1) current_state = FSM_UPDATE_ROW7;
            else  current_state = FSM_IOEXP_OUTPUT3;  
            break;
        case FSM_IOEXP_OUTPUT3:
            IOEXP_send(0x10, 1);
            IOEXP_OUTPUT_COL=0x00;
            for (int j = 8; j >0; j--) {
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL << 1;
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL | Leds[3][j-1];
            }
            IOEXP_send(IOEXP_OUTPUT_COL, 0);
            if (cycleFinished==1) current_state = FSM_UPDATE_ROW7;
            else  current_state = FSM_IOEXP_OUTPUT4;  
            break;    
        case FSM_IOEXP_OUTPUT4:
            IOEXP_send(0x08, 1);
            IOEXP_OUTPUT_COL=0x00;
            for (int j = 8; j >0; j--) {
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL << 1;                
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL | Leds[4][j-1];
            }
            IOEXP_send(IOEXP_OUTPUT_COL, 0);
            if (cycleFinished==1) current_state = FSM_UPDATE_ROW7;
            else  current_state = FSM_IOEXP_OUTPUT5;  
            break;
        case FSM_IOEXP_OUTPUT5:
            IOEXP_send(0x04, 1);
            IOEXP_OUTPUT_COL=0x00;
            for (int j = 8; j >0; j--) {
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL << 1;
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL | Leds[5][j-1];
            }
            IOEXP_send(IOEXP_OUTPUT_COL, 0);            
            if (cycleFinished==1) current_state = FSM_UPDATE_ROW7;
            else  current_state = FSM_IOEXP_OUTPUT6;  
            break;
        case FSM_IOEXP_OUTPUT6:
            IOEXP_send(0x02, 1);
            IOEXP_OUTPUT_COL=0x00;
            for (int j = 8; j >0; j--) {
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL << 1;                
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL | Leds[6][j-1];               
            }
            IOEXP_send(IOEXP_OUTPUT_COL, 0);
            if (cycleFinished==1) current_state = FSM_UPDATE_ROW7;
            else  current_state = FSM_IOEXP_OUTPUT7;  
            break;
        case FSM_IOEXP_OUTPUT7:
            IOEXP_send(0x01, 1);
            IOEXP_OUTPUT_COL=0x00;
            for (int j = 8; j >0; j--) {
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL << 1;
                IOEXP_OUTPUT_COL = IOEXP_OUTPUT_COL | Leds[7][j-1];
            }
            IOEXP_send(IOEXP_OUTPUT_COL, 0);
            if (cycleFinished==1) current_state = FSM_UPDATE_ROW7;
            else  current_state = FSM_IOEXP_OUTPUT0;  
            break;    
        case FSM_UPDATE_ROW7:
           for(int j=0;j<8;j++){
            Leds[7][j]=Leds[6][j];//move row 6 to row 7
           }
            current_state = FSM_UPDATE_ROW6;
            break;
        case FSM_UPDATE_ROW6 :
           for(int j=0;j<8;j++){
            Leds[6][j]=Leds[5][j];//move row 5 to row 6
           }
            current_state =FSM_UPDATE_ROW5;
            break;  
        case FSM_UPDATE_ROW5 :
           for(int j=0;j<8;j++){
            Leds[5][j]=Leds[4][j];//move row 4 to row 5
           }
            current_state = FSM_UPDATE_ROW4;
            break;
        case FSM_UPDATE_ROW4 :
           for(int j=0;j<8;j++){
            Leds[4][j]=Leds[3][j];//move row 3 to row 4
           }
            current_state =FSM_UPDATE_ROW3;
            break;  
        case FSM_UPDATE_ROW3 :
           for(int j=0;j<8;j++){
            Leds[3][j]=Leds[2][j];//move row 2 to row 3
           }
            current_state = FSM_UPDATE_ROW2;
            break;
        case FSM_UPDATE_ROW2 :
           for(int j=0;j<8;j++){
            Leds[2][j]=Leds[1][j];//move row 1 to row 2
           }
            current_state =FSM_UPDATE_ROW1;
            break;  
        case FSM_UPDATE_ROW1 :
           for(int j=0;j<8;j++){
            Leds[1][j]=Leds[0][j];//move row 0 to row 1
           }
            current_state = FSM_UPDATE_ROW01;
            break;
        case FSM_UPDATE_ROW01 :
            Leds[0][0]=(char)rand()%2;
            if(Leds[0][0]==1) Leds[0][1]=0;
            else Leds[0][1]=1;
            current_state = FSM_UPDATE_ROW02;
            break;
        case FSM_UPDATE_ROW02:
            Leds[0][2]=(char)rand()%2;
            if(Leds[0][2]==1) {Leds[0][3]=0;}
            else {Leds[0][3]=1;}
            current_state = FSM_UPDATE_ROW03;
            break;
        case FSM_UPDATE_ROW03:
            Leds[0][4]=(char)rand()%2;
            if(Leds[0][4]==1) {Leds[0][5]=0;}
            else {Leds[0][5]=1;}
            current_state = FSM_UPDATE_ROW04;
            break;
        case FSM_UPDATE_ROW04:
            Leds[0][6]=(char)rand()%2;
            if(Leds[0][6]==1) {Leds[0][7]=0;}
            else {Leds[0][7]=1;}
            current_state =FSM_IOEXP_OUTPUT0;
            break;            
        default:
            current_state = FSM_IOEXP_OUTPUT0;
            break;
    }   
}