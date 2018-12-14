#include <msp430.h> 
#include <math.h>

double velocity(double height);
void resetVelocity(void)

double gravity = 9.81;
double step = 0.5;
unsigned int i;

int main(void)
{
    double testHeight = 5.0;
    double velocityArray[10];

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	while(1)
	{
	    resetVelocity();

        for(i=0; i<10; i++)
        {
            testHeight -= step;

            if(testHeight > 2.5)
                velocityArray[i] = 0;
            else
                velocityArray[i] = velocity(testHeight);

            if(i == 9)
            {
                resetVelocity();
                i = 0;
            }
        }
	}
}

//Velocity of water flow from IV.
double velocity(double height)
{
    return sqrt(2*gravity*height);
}

//Simple function that resets velocity memory.
void resetVelocity(void)
{
    for(i = 0; i<10; i++)
        velocityArray[i] = 0;
}
