Overview

This project implements a simple reaction timer game on the MSP430G2553 using the EduKit BoosterPack, which includes an LCD display, buttons, LEDs, and a buzzer.

The goal of the game is to react as quickly as possible when the LED lights up. The player must press the button only after the LED turns on. Reaction time is measured in milliseconds and displayed on the LCD.

If the player presses the button too early, a “Too Soon!” message is shown and a buzzer sounds. If the player reacts correctly, their time is displayed and the buzzer also plays a tone.

Game Flow
	1.	The LCD displays: Wait for LED...
	2.	After a random delay (1–4 seconds), the LED turns on.
	3.	The LCD updates to: Press now!
	4.	The player must press the button:
	•	If too early → “Too Soon!” and buzzer
	•	If correct → Reaction time is displayed and buzzer plays
	5.	Game resets after 2 seconds.

Controls
	•	Button (P1.3): Press to respond to the LED.
	•	LED (P1.0): Lights up to signal the player to react.
	•	LCD: Displays instructions and reaction time.
	•	Buzzer (P2.1): Plays tone on result.

Makefile Usage
make         # Build ELF
make hex     # Convert to .hex
make flash   # Flash to MSP430 via USB
make clean   # Clean build files