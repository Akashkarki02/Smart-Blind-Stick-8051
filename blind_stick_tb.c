#include <reg51.h>

sbit BUZZER = P2^2;
sbit LED = P2^3;

void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}

void beep(unsigned int time)
{
    BUZZER = 1;
    LED = 1;

    delay_ms(time);

    BUZZER = 0;
    LED = 0;

    delay_ms(time);
}

void test_distance(unsigned int distance)
{
    if(distance < 30)
    {
        beep(50);
    }
    else if(distance < 60)
    {
        beep(150);
    }
    else if(distance < 100)
    {
        beep(300);
    }
    else
    {
        BUZZER = 0;
        LED = 0;
        delay_ms(200);
    }
}

void main()
{
    // Test 1: Very close obstacle
    test_distance(20);

    // Test 2: Close obstacle
    test_distance(50);

    // Test 3: Medium distance obstacle
    test_distance(80);

    // Test 4: No nearby obstacle
    test_distance(150);

    while(1);
}
