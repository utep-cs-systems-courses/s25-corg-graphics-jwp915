#include <msp430.h>
#include "switches.h"

// Removed duplicate definition to avoid linker error
// void switch_interrupt_handler() {
//   // This was a duplicate and has been commented out.
// }

void __interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {   // check if switch caused the interrupt
    P1IFG &= ~SWITCHES;     // clear pending switch interrupts
    switch_interrupt_handler();  // delegate to the actual handler (in switches.c)
  }
}
