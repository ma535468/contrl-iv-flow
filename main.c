#include <msp430.h>
#include <math.h>

#define LED1 BIT0

double velocity(double height);
void resetVelocity(double velocityArray[]);

double gravity = 9.81;
double step = 0.5;
unsigned int i;

int main(void)
{
    double testHeight;
    double velocityArray[10];

    P1DIR |= LED1;

    TA0CCTL0 = CCIE;
    TA0CTL = TASSEL_1 | ID_1 | MC_1 | TACLR;
    TA0CCR0 = 0x8000;
    TA0R = 0;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    __bis_SR_register(GIE);     // Enable global interrupts.

    while(1)
    {
        testHeight = 5.0;
        resetVelocity(velocityArray);

        for(i=0; i<10; i++)
        {
            testHeight -= step;

            if(testHeight > 2.5)
                velocityArray[i] = 0;
            else
                velocityArray[i] = velocity(testHeight);
        }
    }
}

//Velocity of water flow from IV.
double velocity(double height)
{
    return sqrt(2*gravity*height);
}

//Simple function that resets velocity memory.
void resetVelocity(double velocityArray[])
{
    for(i = 0; i<10; i++)
        velocityArray[i] = 0;
}

#pragma vector = TIMER0_A0_VECTOR;
__interrupt void Timer(void)
  {
    P1OUT ^= LED1;
  }
