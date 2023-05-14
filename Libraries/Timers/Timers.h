#include <avr/io.h>

/// @brief Function to initialize a timer
/// @param timer value of 0 to 2
/// @param mode 0 = CSC Mode, 1 = Fast PWM Mode
/// @param interrupts 0 = OCRxA interrupt, 1 = Top Value interrupt, 2 = both
void initTimer(uint8_t timer, uint8_t mode, uint8_t interrupts);

/// @brief Start a timer with the defined factor
/// @param timer Value of 0 to 2
/// @param factor Can be either 1, 8, 64, 128, 256 or 1024
void startTimer(uint8_t timer, int factor);

/// @brief Stop a timer
/// @param timer value of 0 to 2
void stopTimer(uint8_t timer);

/// @brief Set the OCRxA interrupt value
/// @param timer value of 0 to 2
/// @param value value for the interrupt
void setOCRXA(uint8_t timer, long value);