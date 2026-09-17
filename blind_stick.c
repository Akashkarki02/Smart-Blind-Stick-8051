#include <reg51.h>

// HC-SR04 pins
sbit TRIG = P2^0;
sbit ECHO = P2^1;

// Alert devices
sbit BUZZER = P2^2;
sbit LED = P2^3;

// Delay function
void delay_us(unsigned int us)
{
    while(us--)
    {
        ;
    }
}

// Millisecond delay
void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}

// Generate ultrasonic pulse
void send_trigger()
{
    TRIG = 0;
    delay_us(2);

    TRIG = 1;
    delay_us(10);

    TRIG = 0;
}

// Measure distance
unsigned int get_distance()
{
    unsigned int time;
    unsigned int distance;

    TMOD = 0x01;       // Timer 0, Mode 1
    TH0 = 0;
    TL0 = 0;

    send_trigger();

    while(ECHO == 0);

    TR0 = 1;

    while(ECHO == 1);

    TR0 = 0;

    time = (TH0 << 8) | TL0;

    // Approximate distance calculation for 12 MHz crystal
    distance = time / 58;

    return distance;
}

// Beep function
void beep(unsigned int delay_time)
{
    BUZZER = 1;
    LED = 1;

    delay_ms(delay_time);

    BUZZER = 0;
    LED = 0;

    delay_ms(delay_time);
}

void main()
{
    unsigned int distance;

    TRIG = 0;
    BUZZER = 0;
    LED = 0;

    while(1)
    {
        distance = get_distance();

        // Very close obstacle
        if(distance < 30)
        {
            beep(50);
        }

        // Close obstacle
        else if(distance < 60)
        {
            beep(150);
        }

        // Medium distance
        else if(distance < 100)
        {
            beep(300);
        }

        // No nearby obstacle
        else
        {
            BUZZER = 0;
            LED = 0;
            delay_ms(200);
        }
    }
}
