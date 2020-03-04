#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework3.h"
#include "myGPIO.h"
#include "myTimer.h"

int main(void)
{
    // Count variables to control the LEDs.
    unsigned int count0 = 0;
    unsigned int count1 = 0;

    // TODO: Declare the variables that main uses to interact with your state machine.
    unsigned char buttonhistory = UNPRESSED;
    bool debouncedPress = false;

    // Stops the Watchdog timer.
    initBoard();
    // Initialize the GPIO.
    // YOU MUST WRITE THIS FUNCTION IN myGPIO.c
    initGPIO();
    // Initialize Timer0 to provide a one second count interval for updating LED2.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_0_BASE, TIMER0_PRESCALER, TIMER0_COUNT);
    // Initialize Timer1 to provide a one millisecond count interval for updating the button history.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_1_BASE, TIMER1_PRESCALER, TIMER1_COUNT);

    while(1)
    {
        // Update the color of LED2 using count0 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeLaunchpadLED2(count0);
        // Update the color of the Boosterpack LED using count1 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeBoosterpackLED(count1);

        // TODO: If Timer0 has expired, increment count0.
        // YOU MUST WRITE timer0expired IN myTimer.c
        if (timer0Expired()) {
            count0++;
            if (count0 == 8) {
                count0 = 0;
            }
        }


        // TODO: If Timer1 has expired, update the button history from the pushbutton value.
        // YOU MUST WRITE timer1expired IN myTimer.c
        if (timer1Expired()) {
            buttonhistory = buttonhistory << 1;
            buttonhistory = buttonhistory + checkStatus_BoosterpackS1();
        }


        // TODO: Call the button state machine function to check for a completed, debounced button press.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        debouncedPress = fsmBoosterpackButtonS1(buttonhistory);



        // TODO: If a completed, debounced button press has occurred, increment count1.
        if (debouncedPress) {
            count1++;
            if (count1 == 8) {
                count1 = 0;
            }
        }


    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// TODO: Map the value of a count variable to a color for LED2.
// Since count is an unsigned integer, you can mask the value in some way.
void changeLaunchpadLED2(unsigned int count)
{
    switch (count) {
        case OFF:
            turnOff_LaunchpadLED2Red();
            turnOff_LaunchpadLED2Green();
            turnOff_LaunchpadLED2Blue();
            break;
        case RED:
            turnOn_LaunchpadLED2Red();
            turnOff_LaunchpadLED2Green();
            turnOff_LaunchpadLED2Blue();
            break;
        case GREEN:
            turnOff_LaunchpadLED2Red();
            turnOn_LaunchpadLED2Green();
            turnOff_LaunchpadLED2Blue();
            break;
        case YELLOW:
            turnOn_LaunchpadLED2Red();
            turnOn_LaunchpadLED2Green();
            turnOff_LaunchpadLED2Blue();
            break;
        case BLUE:
            turnOff_LaunchpadLED2Red();
            turnOff_LaunchpadLED2Green();
            turnOn_LaunchpadLED2Blue();
            break;
        case PURPLE:
            turnOn_LaunchpadLED2Red();
            turnOff_LaunchpadLED2Green();
            turnOn_LaunchpadLED2Blue();
            break;
        case CYAN:
            turnOff_LaunchpadLED2Red();
            turnOn_LaunchpadLED2Green();
            turnOn_LaunchpadLED2Blue();
            break;
        case WHITE:
            turnOn_LaunchpadLED2Red();
            turnOn_LaunchpadLED2Green();
            turnOn_LaunchpadLED2Blue();
            break;
        default: // Do nothing
            break;
    }
}

// TODO: Maybe the value of a count variable to a color for the Boosterpack LED
// This is essentially a copy of the previous function, using a different LED
void changeBoosterpackLED(unsigned int count)
{
    switch (count) {
        case OFF:
            turnOff_BoosterpackLEDRed();
            turnOff_BoosterpackLEDGreen();
            turnOff_BoosterpackLEDBlue();
            break;
        case RED:
            turnOn_BoosterpackLEDRed();
            turnOff_BoosterpackLEDGreen();
            turnOff_BoosterpackLEDBlue();
            break;
        case GREEN:
            turnOff_BoosterpackLEDRed();
            turnOn_BoosterpackLEDGreen();
            turnOff_BoosterpackLEDBlue();
            break;
        case YELLOW:
            turnOn_BoosterpackLEDRed();
            turnOn_BoosterpackLEDGreen();
            turnOff_BoosterpackLEDBlue();
            break;
        case BLUE:
            turnOff_BoosterpackLEDRed();
            turnOff_BoosterpackLEDGreen();
            turnOn_BoosterpackLEDBlue();
            break;
        case PURPLE:
            turnOn_BoosterpackLEDRed();
            turnOff_BoosterpackLEDGreen();
            turnOn_BoosterpackLEDBlue();
            break;
        case CYAN:
            turnOff_BoosterpackLEDRed();
            turnOn_BoosterpackLEDGreen();
            turnOn_BoosterpackLEDBlue();
            break;
        case WHITE:
            turnOn_BoosterpackLEDRed();
            turnOn_BoosterpackLEDGreen();
            turnOn_BoosterpackLEDBlue();
            break;
        default: // Do nothing
            break;
    }
}

// TODO: Create a button state machine.
// The button state machine should return true or false to indicate a completed, debounced button press.
bool fsmBoosterpackButtonS1(unsigned char buttonhistory)
{
    static unsigned char state = UNPRESSED;
    if ((state == PRESSED) && (buttonhistory == UNPRESSED)) {
        state = UNPRESSED;
        return false;
    } else if ((state == UNPRESSED) && (buttonhistory == PRESSED)) {
        state = PRESSED;
        return true;
    } else {
        return false;
    }
}
