#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set PB0-PB3 as input (buttons)
    DDRB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3));
    PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3); // enable pull-ups

    // Set PD2-PD5 as output (to 7447)
    DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);

    while (1) {
        // Read buttons (active low)
        uint8_t inputBCD = PINB & 0x0F;   // Read PB0-PB3
        inputBCD = ~inputBCD & 0x0F;      // Invert since pull-up

        // Output to PD2-PD5 (shift bits to match wiring)
        PORTD = (PORTD & 0xC3) | (inputBCD << 2);

        _delay_ms(500); // debounce delay
    }
}
