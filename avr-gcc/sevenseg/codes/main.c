//Prints a decimal number 
//on the display
/*#include <avr/io.h>
 
int main (void)
{
	
	
 //set PD2-PD7 as output pins 0xFC=0b11111100 (binary)
  DDRD   |= 0xFC;
  //set PB0 as output pin
  DDRB    |= ((1 << DDB0));
 
  while (1) {
//turn PB0 off
    PORTB = ((1 <<  PB0));
//turn PD2-PD7 on    
    PORTD = 0b11100100; 
  }

  return 0;

}*/




#include <avr/io.h>
#include <util/delay.h>

// Lookup table for digits 0-9
// Each entry: {PORTD_value, PORTB_value}
// PORTD bits: PD7..PD2 control a–f (except g)
// PB0 controls g
const uint8_t digitPD[10] = {
    0b00000000, // 0  -> a,b,c,d,e,f ON, g OFF
    0b11100100, // 1  -> b,c ON, g OFF
    0b10010000, // 2  -> a,b,d,e,g ON
    0b11000000, // 3  -> a,b,c,d,g ON
    0b01100100, // 4  -> b,c,f,g ON
    0b01001000, // 5  -> a,c,d,f,g ON
    0b00001000, // 6  -> a,c,d,e,f,g ON
    0b11100000, // 7  -> a,b,c ON
    0b00000000, // 8  -> all ON
    0b01000000  // 9  -> a,b,c,d,f,g ON
};

const uint8_t digitPB[10] = {
    0b00000001, // g OFF for 0
    0b00000001, // g OFF for 1
    0b00000000, // g ON for 2
    0b00000000, // g ON for 3
    0b00000000, // g ON for 4
    0b00000000, // g ON for 5
    0b00000000, // g ON for 6
    0b00000001, // g OFF for 7
    0b00000000, // g ON for 8
    0b00000000  // g ON for 9
};

int main(void) {
    DDRD |= 0xFC;  // PD2–PD7 as output
    DDRB |= (1 << PB0); // PB0 as output

    while (1) {
        for (uint8_t i = 0; i < 10; i++) {
            PORTD = digitPD[i];
            PORTB = digitPB[i];
            _delay_ms(500); // half second delay between numbers
        }
    }
}
