//  kaimana.cpp
//
//  Copyright 2013 Paradise Arcade Shop, ParadiseArcadeShop.com
//  All rights reserved.  Use is subject to license terms.
//
//  Code is provided for entertainment purposes and use with the Kaimana controller.
//  Code may be copied, modified, resused with this Copyright notice.
//  No commercial use without written permission from Paradise Arcade Shop.
//
//  Paradise Arcade Shop Kaimana LED Driver Board
//  Initial Release October 15, 2013
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//  Kaimana animations based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//	Revised:  August 23, 2016		info // mightyjrmods.com

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "kaimana.h"
#include "kaimana_custom.h"
#include "animations.h"


void turnOn(int i,int iR,int iG, int iB)
{
	kaimana.setLED(i, iR,iG,iB);
	kaimana.updateALL();
	delay( FAST_COLOR_DELAY );
}
void blink(int i,int iR,int iG, int iB)
{
  kaimana.setLED(i,iR,iG,iB);
  kaimana.updateALL();
  delay( FAST_COLOR_DELAY );
  Serial.print(i);
  Serial.print("\n");
  kaimana.setALL(BLACK);
	
}
// blink LED to a color selected at random
void blinkMulti(int index)
{
	switch(random(1,9))    // pick a random color between 1 and 7
	{
		case 1:
		kaimana.setLED(index, COLOR_RANDOM_1);
		kaimana.updateALL();
		delay( FAST_COLOR_DELAY );
		kaimana.setLED(index, BLACK);
		break;
		case 2:
		kaimana.setLED(index, COLOR_RANDOM_2);  
		kaimana.updateALL();
		delay( FAST_COLOR_DELAY );
		kaimana.setLED(index, BLACK);
		break;
		case 3:
		kaimana.setLED(index, COLOR_RANDOM_3);    
		kaimana.updateALL();
		delay( FAST_COLOR_DELAY );
		kaimana.setLED(index, BLACK);
		break;
		case 4:
		kaimana.setLED(index, COLOR_RANDOM_4);    
		kaimana.updateALL();
		delay( FAST_COLOR_DELAY );
		kaimana.setLED(index, BLACK);
		break;
		case 5:
		kaimana.setLED(index, COLOR_RANDOM_5);    
		kaimana.updateALL();
		delay( FAST_COLOR_DELAY );
		kaimana.setLED(index, BLACK);
		break;
		case 6:
		kaimana.setLED(index, COLOR_RANDOM_6);    
		kaimana.updateALL();
		delay( FAST_COLOR_DELAY );
		kaimana.setLED(index, BLACK);
		break;
		case 7:
		kaimana.setLED(index, COLOR_RANDOM_7);    
		kaimana.updateALL();
		delay( FAST_COLOR_DELAY );
		kaimana.setLED(index, BLACK);
		break;
		case 8:
		kaimana.setLED(index, COLOR_RANDOM_8);    
		kaimana.updateALL();
		delay( FAST_COLOR_DELAY );
		kaimana.setLED(index, BLACK);
		break;
		case 9:
		kaimana.setLED(index, COLOR_RANDOM_9);    
		kaimana.updateALL();
		delay( FAST_COLOR_DELAY );
		kaimana.setLED(index, BLACK);
		break;
		default:   // any undefined value so discard data and set led to BLACK
		kaimana.setLED(index, BLACK);    
		break;
	} 
}	
void blinkMultiExperimental(int index)
{
	int iR = random(1,256);
	int iG = random(1,256);
	int iB = random(1,256);
	
	int variance = abs(iR-iG-iB);
	if(variance <100)
	{
		kaimana.setLED(index, iR,iG,iB);
		delay( FAST_COLOR_DELAY );
		kaimana.updateALL();
		kaimana.setLED(index, BLACK);		
	}
}
// set LED to one of 8 predefined colors selected at random
//
void setLEDRandomColor(int index)
{
  switch(random(1,7))    // pick a random color between 1 and 7
  {
    case 1:
      kaimana.setLED(index, COLOR_RANDOM_1);
      break;
    case 2:
      kaimana.setLED(index, COLOR_RANDOM_2);
      break;
    case 3:
      kaimana.setLED(index, COLOR_RANDOM_3);
      break;
    case 4:
      kaimana.setLED(index, COLOR_RANDOM_4);
      break;
    case 5:
      kaimana.setLED(index, COLOR_RANDOM_5);
      break;
    case 6:
      kaimana.setLED(index, COLOR_RANDOM_6);
      break;
    case 7:
      kaimana.setLED(index, COLOR_RANDOM_7);
      break;
   
    default:   // any undefined value so discard data and set led to BLACK
      kaimana.setLED(index, BLACK);    
      break;
  }  
}
// Color Fade Animation when Idle
int animation_idle(void)
{
  int  index;
  int  i;

  // set initial color to BLACK
  kaimana.setALL(BLACK);
  
  while(true)
  {
    for(index=0;index<IDLE_SIZE;++index)
    {
      // update strip with new color2
      for(i=0;i<LED_COUNT;++i)
      {
        kaimana.setLED(
          i,
          pgm_read_byte_near(&colorCycleData[((index+IDLE_OFFSET_2+((LED_COUNT-i)*IDLE_OFFSET))%IDLE_SIZE)]),
          pgm_read_byte_near(&colorCycleData[((index+IDLE_OFFSET_1+((LED_COUNT-i)*IDLE_OFFSET))%IDLE_SIZE)]),
          pgm_read_byte_near(&colorCycleData[((index+IDLE_OFFSET_0+((LED_COUNT-i)*IDLE_OFFSET))%IDLE_SIZE)])
        );
      }

      // update the leds with new/current colors in the array
      kaimana.updateALL();

      // test all switches and exit idle animation if active switch found
      for(i=0;i<SWITCH_COUNT;++i)
      {
        if( !digitalRead(switchPins[i]) )
          return(false);
      }

      // place test for switches here and use calculated timer not delay
      //
      delay( IDLE_ANIMATION_DELAY );
    }
  }
}
//light walks thru all 8 buttons
void walkyStartup(int iR,int iG, int iB)	
{
  	for (int i = 0; i < LED_COUNT; i++) 
	{
		blink(i, iR,iG,iB);
	}
}
void defaultStartup(void)
{
  kaimana.setALL( BLACK );
  delay( FAST_COLOR_DELAY );
  kaimana.setALL( RED );
  delay( FAST_COLOR_DELAY );
  kaimana.setALL( BLACK );
  delay( FAST_COLOR_DELAY );
  kaimana.setALL( GREEN );
  delay( FAST_COLOR_DELAY );
  kaimana.setALL( BLACK );
  delay( FAST_COLOR_DELAY );
  kaimana.setALL( BLUE );
  delay( FAST_COLOR_DELAY );
  kaimana.setALL( BLACK );
  delay( BOOT_COMPLETE_DELAY );  
} 
int breatheSine(int iR, int iG, int iB)
{
	int index;
	int i;
	
	while(true)
	{
	int breatheSpeed= 1;
	float factor = millis()/1000.0;

		int alpha = 129.0 + 127 * sin((factor*.50)* PI );
		//STROOOBE int alpha = 127.0 + 127 * sin((factor*3)* PI );
		// set all leds in the array to the RGB color passed to this function
		if (alpha != 0 ){
		for(index=0;index<LED_COUNT;++index)
		{
			kaimana.setLEDBrightness( index, iR, iG, iB,alpha );
		}
		
		// update the leds with new/current colors in the array
		kaimana.updateALL();
		// test all switches and exit idle animation if active switch found
		for(i=0;i<SWITCH_COUNT;++i)
		{
			if( !digitalRead(switchPins[i]) )
			return(false);
        }

		// place test for switches here and use calculated timer not delay
		delay( IDLE_ANIMATION_DELAY );
		Serial.print(alpha);
		Serial.print("\n");}
		//delay(100);
		
	}
  } 
int breatheApple(int iR, int iG, int iB)
{
	int index;
	int i;
	
	while(true)
	{
	int breatheSpeed= 1;
	float factor = millis()/1000.0;

		//int alpha = 127.0 + 127 * sin((factor*.50)* PI );
		int alpha = (exp(sin(factor*PI)) - 0.36787944)*108.0;
		// set all leds in the array to the RGB color passed to this function
		
		if (alpha != 0 ){
			for(index=0;index<LED_COUNT;++index)
		{
			kaimana.setLEDBrightness( index, iR, iG, iB,alpha );
		}
		// update the leds with new/current colors in the array
		kaimana.updateALL();
		if (alpha != 0 ){
		// test all switches and exit idle animation if active switch found
		for(i=0;i<SWITCH_COUNT;++i)
		{
			if( !digitalRead(switchPins[i]) )
			return(false);
        }
		// place test for switches here and use calculated timer not delay
		delay( IDLE_ANIMATION_DELAY );
		Serial.print(alpha);
		Serial.print("\n");}}
		//delay(100);
		
	}
  }  
// LEDS blink on randomly
void starryStartup(int iR,int iG, int iB)	
{
	static int i;
	static int trackled[]= {1,2,3,4,5,6,7,8};
	int delay_val;
	
	kaimana.setALL( BLACK ); //set everything to OFF | this is for when you are calling from a button combination the buttons pressed do not remain on
	for (i = 0; i < 8; ++i) //randomizing the array
    {     
      int rand = random(1,8);
	  int temp = trackled[i];
	  trackled[i] = trackled[rand];
	  trackled[rand] = temp;
    }	
	delay_val = FAST_COLOR_DELAY;
	for (i = 0; i < 8; ++i) 
    {      
		switch(trackled[i])
		{
			case 1:
			kaimana.setLED(LED_P4, iR,iG,iB);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 2:
			kaimana.setLED(LED_P3, iR,iG,iB);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 3:
			kaimana.setLED(LED_P2, iR,iG,iB);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 4:
			kaimana.setLED(LED_P1, iR,iG,iB);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 5:
			kaimana.setLED(LED_K1, iR,iG,iB);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 6:
			kaimana.setLED(LED_K2, iR,iG,iB);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 7:
			kaimana.setLED(LED_K3, iR,iG,iB);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 8:
			kaimana.setLED(LED_K4, iR,iG,iB);
			kaimana.updateALL();
			delay( delay_val );
			break;
			default:   // any undefined value so discard data and set led to BLACK
			kaimana.setALL( BLACK );    
			kaimana.updateALL();
			delay( delay_val );
			break;
		};		
	}
}
// LEDS blink on/off randomly
void starryIdle(int iR,int iG, int iB)	
{
	static int i;
	static int trackled[]= {1,2,3,4,5,6,7,8};
	int delay_val;
	
	kaimana.setALL( BLACK ); //set everything to OFF | this is for when you are calling from a button combination the buttons pressed do not remain on
	for (i = 0; i < 8; ++i) //randomizing the array
    {     
      int rand = random(1,8);
	  int temp = trackled[i];
	  trackled[i] = trackled[rand];
	  trackled[rand] = temp;
    }	
	delay_val = FAST_COLOR_DELAY;
	for (i = 0; i < 8; ++i) 
    {      
		switch(trackled[i])
		{
			case 1:
			blink(LED_P4, iR,iG,iB);
			break;
			case 2:
			blink(LED_P3, iR,iG,iB);
			break;
			case 3:
			blink(LED_P2, iR,iG,iB);
			break;
			case 4:
			blink(LED_P1, iR,iG,iB);
			break;
			case 5:
			blink(LED_K1, iR,iG,iB);
			break;
			case 6:
			blink(LED_K2, iR,iG,iB);
			break;
			case 7:
			blink(LED_K3, iR,iG,iB);
			break;
			case 8:
			blink(LED_K4, iR,iG,iB);			
			break;
			default:   // any undefined value so discard data and set led to BLACK
			kaimana.setALL( BLACK );    
			kaimana.updateALL();
			delay( delay_val );
			break;
		};		
	}
}
// LEDS blink on/off randomly with multiple colors
void starryIdleMulti()	
{
	static int i;
	static int trackled[]= {1,2,3,4,5,6,7,8};
	int delay_val;
	
	kaimana.setALL( BLACK ); //set everything to OFF | this is for when you are calling from a button combination the buttons pressed do not remain on
	for (i = 0; i < 8; ++i) //randomizing the array
    {     
      int rand = random(1,8);
	  int temp = trackled[i];
	  trackled[i] = trackled[rand];
	  trackled[rand] = temp;
    }	
	delay_val = FAST_COLOR_DELAY;
	for (i = 0; i < 8; ++i) 
    {      
		switch(trackled[i])
		{
			case 1:
			blinkMulti(LED_P4);
			break;
			case 2:
			blinkMulti(LED_P3);
			break;
			case 3:
			blinkMulti(LED_P2);
			break;
			case 4:
			blinkMulti(LED_P1);
			break;
			case 5:
			blinkMulti(LED_K1);
			break;
			case 6:
			blinkMulti(LED_K2);
			break;
			case 7:
			blinkMulti(LED_K3);
			break;
			case 8:
			blinkMulti(LED_K4);			
			break;
			default:   // any undefined value so discard data and set led to BLACK
			kaimana.setALL( BLACK );    
			kaimana.updateALL();
			delay( delay_val );
			break;
		};		
	}
}
//Tournament mode animations
void tourneyModeActivate(void)
{
	
	kaimana.setALL(RED);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K4, BLACK);
	kaimana.setLED(LED_P4, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );	
	
	kaimana.setLED(LED_K3, BLACK);
	kaimana.setLED(LED_P3, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K2, BLACK);
	kaimana.setLED(LED_P2, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K1, BLACK);
	kaimana.setLED(LED_P1, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
}
void tourneyModeDeactivate(void)
{
	
	kaimana.setALL(BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K1, RED);
	kaimana.setLED(LED_P1, RED);
	kaimana.updateALL();
	delay( T_DELAY );
		
	kaimana.setLED(LED_K2, RED);
	kaimana.setLED(LED_P2, RED);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K3, RED);
	kaimana.setLED(LED_P3, RED);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K4, RED );
	kaimana.setLED(LED_P4, RED);
	kaimana.updateALL();
	delay( T_DELAY );	

	kaimana.setALL(BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setALL(RED);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setALL(BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
}

