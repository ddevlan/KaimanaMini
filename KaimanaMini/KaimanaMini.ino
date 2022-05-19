//  KaimanaMini.ino

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "kaimana.h"
#include "kaimana_custom.h"
#include "animations.h"


// local function declarations
int  pollSwitches(void);
void showStartup(void);
void setLEDRandomColor(int index);
int tourneypollSwitches(void);
boolean tournamentMode = false;
int holdTimeout = 0;
int selection = 0;

// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;


// the setup routine runs first and once each time power is applied to the Kaimana board
void setup() 
{                
  // light up all leds at boot to demonstrate everything is functional
  defaultStartup();
  walkyStartup(GREEN);
  starryStartup(BLUE);
  walkyStartup(RED);
  starryStartup(MAGENTA); 
  starryIdleMulti();
  starryIdle(CYAN);
}

// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop() 
{
  unsigned long  ulTimeout;
  
    
  // initialize timeout value to now + some seconds
  ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
  
 // infinite loop of read switches, update LEDs and idle animation when necessary
  while( true)
  {
    // active -- poll switches and update leds
	
	if (tournamentMode != true)
	{
		if( pollSwitches() != 0 )	
		{
			// some switches were active so reset idle timeout to now + some seconds
			ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
		}
		else
		{
			// no switches active so test for start of idle timeout  
			if( millis() > ulTimeout )
			{				
				switch(selection) 
				{
					case 0:
						animation_idle();
						break;
					case 1:
						breatheSine(RED);
						break;
					case 2:
						breatheApple(YELLOW);
						break;
					case 3:
						starryStartup(MAGENTA);
						break;
					case 4:
						walkyStartup(ORANGE);
						break;
					case 5:
						starryIdle(CYAN);
						break;
					case 6:
						starryIdleMulti();
						break;
					default:
						selection = 0;
						break;
				}
			}  
		}
	}
	else
	{
		if( tourneypollSwitches() != 0 )	
		{
			// some switches were active so reset idle timeout to now + some seconds
			ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
		}
		
	}
  }
    // delay a little to avoid flickering (yea, updates happens really, really fast!)
    delay( MAIN_LOOP_DELAY );
 
}


// ==============================================================
//
//  local functions start here
//
// ==============================================================





int pollSwitches(void)
{
  static int  iLED[LED_COUNT];
  static int  iActiveSwitchCount;
  static int  i;  
  static int  j;  
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;

  // reset LED status
  if (firsttime == 1)
  {
    for(i=0;i<LED_COUNT;++i)
    {
      iLED[i] = false;
      firsttime = 0;
    }
  }

  // read arduino pins and save results in the mapped LED if button is pressed (pin grounded)

  // complex special case for joystick but it's worth the effort
  joystickDirection = ATTACK_NONE;

  // clear results for switch activity
  switchActivity = ATTACK_NONE;

  // test switch and set LED based on result
  if(!digitalRead(PIN_P1))
  {
    switchActivity |= ATTACK_P1;
    // switch is active
    if(iLED[LED_P1] == true)
    {
    blink(LED_P1, PINK);
		//maintain color while switch is active
		iLED[LED_P1] = true;
		
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P1,WHITE);
	  selection++;
	  ///setLEDRandomColor(LED_P1);
      iLED[LED_P1] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P1, BLACK);    
      
	  iLED[LED_P1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P2))
  {
    switchActivity |= ATTACK_P2;
    
    // switch is active
    if(iLED[LED_P2] == true)
    {
      kaimana.setLED(LED_P2,GREEN);
      //maintain color while switch is active
      iLED[LED_P2] = true;
    }
    else
    {
      kaimana.setLED(LED_P2,WHITE);
	  iLED[LED_P2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P2, BLACK);    
      iLED[LED_P2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P3))
  {
    switchActivity |= ATTACK_P3;
    
    // switch is active
    if(iLED[LED_P3] == true)
    {
      kaimana.setLED(LED_P3, ORANGE);
      //maintain color while switch is active
      iLED[LED_P3] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P3, WHITE);  
      iLED[LED_P3] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P3, BLACK);    
      iLED[LED_P3] = false;
  }
  

  // test switch and set LED based on result
  if(!digitalRead(PIN_P4))
  {
    switchActivity |= ATTACK_P4;
    
    // switch is active
    if(iLED[LED_P4] == true)
    {
      kaimana.setLED(LED_P4, WHITE); 
      //maintain color while switch is active
      iLED[LED_P4] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P4, BLUE); 
	  
      iLED[LED_P4] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P4, BLACK);    
      iLED[LED_P4] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K1))
  {
    switchActivity |= ATTACK_K1;
    
    // switch is active
    if(iLED[LED_K1] == true)
    {
      blink(LED_K1, PINK);
      blink(LED2_K1, PINK);
      //maintain color while switch is active
      iLED[LED_K1] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K1] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K1, BLACK);
      kaimana.setLED(LED2_K1, BLACK);   
      iLED[LED_K1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K2))
  {
    switchActivity |= ATTACK_K2;
    
    // switch is active
    if(iLED[LED_K2] == true)
    {
      kaimana.setLED(LED_K2, RED);
      kaimana.setLED(LED2_K2, RED);
      //maintain color while switch is active
      iLED[LED_K2] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K2, BLACK);    
      kaimana.setLED(LED2_K2, BLACK);
      iLED[LED_K2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K3))
  {
    switchActivity |= ATTACK_K3;
    
    // switch is active
    if(iLED[LED_K3] == true)
    {
      kaimana.setLED(LED_K3, YELLOW);
      kaimana.setLED(LED2_K3, YELLOW);
      //maintain color while switch is active
      iLED[LED_K3] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K3] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K3, BLACK); 
      kaimana.setLED(LED2_K3, BLACK);    
      iLED[LED_K3] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K4))
  {
    switchActivity |= ATTACK_K4;
    
    // switch is active
    if(iLED[LED_K4] == true)
    {
      kaimana.setLED(LED_K4, BLACK);
      //maintain color while switch is active
      iLED[LED_K4] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K4, BLUE); 
      iLED[LED_K4] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K4, BLACK);    
      iLED[LED_K4] = false;
  }
	
/*   if( kaimana.switchHistoryTest( TOURNAMENT_MODE ) )
  {
	  if (tournamentMode != true)
	  {
		  tournamentMode = true;
		  tourneyMode
	  }
	  else
	  {
		  
		  tournamentMode = false;
	  }
  } */

  // zero active switch counter (note: 4 way joystick counts as 1)
  iActiveSwitchCount = 0;
  
  // set LED color based on switch
  for(i=0;i<LED_COUNT;++i)
  {
    if(iLED[i] == true)
      ++iActiveSwitchCount;
  }  

  // update the leds with new/current colors in the array
  kaimana.updateALL();
  
  // return number of active switches
  return(iActiveSwitchCount);
}  

int tourneypollSwitches(void)
{
  static int  iLED[LED_COUNT];
  static int  iActiveSwitchCount;
  static int  i;  
  static int  j;  
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;

  // reset LED status
  if (firsttime == 1)
  {
    for(i=0;i<LED_COUNT;++i)
    {
      iLED[i] = false;
      firsttime = 0;
    }
  }

  // read arduino pins and save results in the mapped LED if button is pressed (pin grounded)
  // clear results for switch activity
  switchActivity = ATTACK_NONE;

  // test switch and set LED based on result
  if(!digitalRead(PIN_P1))
  {
    switchActivity |= ATTACK_P1;
    
    // switch is active
    if(iLED[LED_P1] == true)
    {		
		
	  iLED[LED_P1] = true;
    }
    else
    {    
	iLED[LED_P1] = true;
    
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_P1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P2))
  {
    switchActivity |= ATTACK_P2;
    
    // switch is active
    if(iLED[LED_P2] == true)
    {
      //maintain color while switch is active
      iLED[LED_P2] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_P2] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_P2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P3))
  {
    switchActivity |= ATTACK_P3;
    
    // switch is active
    if(iLED[LED_P3] == true)
    {
      //maintain color while switch is active
      iLED[LED_P3] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_P3] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_P3] = false;
  }
  

  // test switch and set LED based on result
  if(!digitalRead(PIN_P4))
  {
    switchActivity |= ATTACK_P4;
    
    // switch is active
    if(iLED[LED_P4] == true)
    {
      //maintain color while switch is active
      iLED[LED_P4] = true;
    }
    else
    {
      // select new color when switch is first activated
	  
      iLED[LED_P4] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_P4] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K1))
  {
    switchActivity |= ATTACK_K1;
    
    // switch is active
    if(iLED[LED_K1] == true)
    {
      //maintain color while switch is active
      iLED[LED_K1] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K1] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_K1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K2))
  {
    switchActivity |= ATTACK_K2;
    
    // switch is active
    if(iLED[LED_K2] == true)
    {
      //maintain color while switch is active
      iLED[LED_K2] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K2] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_K2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K3))
  {
    switchActivity |= ATTACK_K3;
    
    // switch is active
    if(iLED[LED_K3] == true)
    {
      //maintain color while switch is active
      iLED[LED_K3] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K3] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_K3] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K4))
  {
    switchActivity |= ATTACK_K4;
    
    // switch is active
    if(iLED[LED_K4] == true)
    {
      //maintain color while switch is active
      iLED[LED_K4] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K4] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_K4] = false;
  }

  // convert joystick, P1-P4, K1-K4 into a single unsigned int
  switchActivity = joystickDirection + switchActivity;
  kaimana.switchHistorySet(switchActivity);

  // zero active switch counter (note: 4 way joystick counts as 1)
  iActiveSwitchCount = 0;
  
  // set LED color based on switch
  for(i=0;i<LED_COUNT;++i)
  {
    if(iLED[i] == true)
      ++iActiveSwitchCount;
  }  

  // update the leds with new/current colors in the array
  kaimana.updateALL();
  
  // return number of active switches
  return(iActiveSwitchCount);
}  
