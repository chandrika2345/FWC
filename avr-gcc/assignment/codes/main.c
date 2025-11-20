#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // A -> PD3, B -> PD4, F -> PD2

    DDRD &= ~((1 << PD3) | (1 << PD4)); // PD3, PD4 as inputs
    DDRD |= (1 << PD2);                 // PD2 as output for F

    while (1) {
        uint8_t A = (PIND & (1 << PD3)) ? 1 : 0;
        uint8_t B = (PIND & (1 << PD4)) ? 1 : 0;

        // XNOR logic: F = 1 if A == B, else 0
        uint8_t F = (A == B) ? 1 : 0;

        if (F) {
            PORTD |= (1 << PD2);   // Output HIGH
        } else {
            PORTD &= ~(1 << PD2);  // Output LOW
        }

        _delay_ms(10); // Small debounce delay
    }
}
