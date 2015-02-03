
/*
*------------------------------------------------------------------------------
* device.c
*
* Board specipic drivers module(BSP)
*
*
* The copyright notice above does not evidence any
* actual or intended publication of such source code.
*
*------------------------------------------------------------------------------
*/


/*
*------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------
*/


#include "board.h"
#include "config.h"
#include "typedefs.h"




/*
*------------------------------------------------------------------------------
* Private Defines
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Macros
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Data Types
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Variables
*------------------------------------------------------------------------------
*/
UINT16 tickPeriod = 0;
/*
*------------------------------------------------------------------------------
* Private Variables (static)
*------------------------------------------------------------------------------
*/

static BOOL ledState;

/*
*------------------------------------------------------------------------------
* Public Constants
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Constants (static)
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Function Prototypes (static)
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Functions
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* void InitializeBoard(void)

* Summary	: This function configures all i/o pin directions
*
* Input		: None
*
* Output	: None
*
*------------------------------------------------------------------------------
*/
void BRD_init(void)
{
	unsigned long clock, temp;

	//Store sytem clock
	clock = SYSTEM_CLOCK;

	switch(clock)
	{

		case MHz_32:
		default:
				OSCCON = 0X60; 		//internal oscillator 32MHz
				OSCTUNEbits.PLLEN = 1;	//PLL Enable
		break;
		
		case MHz_16:
				OSCCON = 0X70; 		//internal oscillator 16MHz
				OSCTUNEbits.PLLEN = 0;	//PLL Enable
		break;

		case MHz_40:
		break;
	}

	//calculating tick period for timer-0
	temp = clock >> 2;	
	temp *= (TIMER0_TIMEOUT_DURATION/1000);
	temp /= 1000;		

	tickPeriod = (FULLSCALE_16BIT - (UINT16)temp);



	// set all anolog channels as Digital I/O
	ADCON0 = 0x00;	
	ADCON0 = 0x0F;



	HEART_BEAT_DIRECTION = PORT_OUT;

    // Enable internal PORTB pull-ups
    //INTCON2bits.RBPU = 0;

	TX_EN_DIR = PORT_OUT;		// Rs485 Direction Control
	TX_EN = 0;					//initialized for RX 

	
	SER_TX_DIR  = PORT_OUT;		//USART Tx 
	SER_RX_DIR	= PORT_IN;		//USART Rx


	// MMD Configuration
	DISPLAY_CONTROL_DIRECTION = PORT_OUT;
	DISPLAY_CONTROL			  = DISPLAY_DISABLE;


	DATA_PORT_DIR = 0x00;
	DIGIT_PORT_DIR = 0x00;
	DIGIT_PORT = 0x00;
	

	ROW_SEL_A_DIR = PORT_OUT;
	ROW_SEL_A = SWITCH_OFF;
	ROW_SEL_B_DIR = PORT_OUT;
	ROW_SEL_B = SWITCH_OFF;
	ROW_SEL_C_DIR = PORT_OUT;
	ROW_SEL_C = SWITCH_OFF;
	ROW_SEL_D_DIR = PORT_OUT;
	ROW_SEL_D = SWITCH_OFF;
	ROW_SEL_E_DIR = PORT_OUT;
	ROW_SEL_E = SWITCH_OFF;
	ROW_SEL_F_DIR = PORT_OUT;
	ROW_SEL_F = SWITCH_OFF;
	ROW_SEL_G_DIR = PORT_OUT;
	ROW_SEL_G = SWITCH_OFF;
}



/*
*------------------------------------------------------------------------------
* Private Functions
*------------------------------------------------------------------------------
*/

/*
*  End of device.c
*/
