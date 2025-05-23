#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "incrementing.h"

char switch_state_changed = 0;

static char 
switch_update_interrupt_sense()
{
  char p1val = P1IN;
  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void 
switch_init()			/* setup switch */
{  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  //buzzer_Update();
  // led_update();
}
void switch_sense(){
  P2IES |= EXP_SWITCH;
}
void
switch_init_2(){
  P2REN |= EXP_SWITCH;
  P2IE |= EXP_SWITCH;
  P2DIR &= ~(EXP_SWITCH);
  P2OUT |= EXP_SWITCH;
}
void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();
  switch_state_down = (p1val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  switch_state_changed = 1;
}

char switch_state_down() {
  char result = 0;
  char p2val = P2IN;
  for (char i = 0; i < 4; i++) {
    if (~p2val & (1 << i)) result = 1;
  }
  return result;
}

