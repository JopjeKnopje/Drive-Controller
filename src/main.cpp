#include <Arduino.h>

#define SPEED_UP       A0
#define SPEED_DOWN     A1
#define PWM_MAX_DUTY   255
#define PWM_MIN_DUTY   50
#define PWM_START_DUTY 100

void bemf_a_rising()
{
    ADCSRB = (0 << ACME); // Select AIN1 as comparator negative input
    ACSR |= 0x03;         // Set interrupt on rising edge
}
void bemf_a_falling()
{
    ADCSRB = (0 << ACME); // Select AIN1 as comparator negative input
    ACSR &= ~0x01;        // Set interrupt on falling edge
}
void bemf_b_rising()
{
    ADCSRA = (0 << ADEN); // Disable the ADC module
    ADCSRB = (1 << ACME);
    ADMUX = 2; // Select analog channel 2 as comparator negative input
    ACSR |= 0x03;
}
void bemf_b_falling()
{
    ADCSRA = (0 << ADEN); // Disable the ADC module
    ADCSRB = (1 << ACME);
    ADMUX = 2; // Select analog channel 2 as comparator negative input
    ACSR &= ~0x01;
}
void bemf_c_rising()
{
    ADCSRA = (0 << ADEN); // Disable the ADC module
    ADCSRB = (1 << ACME);
    ADMUX = 3; // Select analog channel 3 as comparator negative input
    ACSR |= 0x03;
}
void bemf_c_falling()
{
    ADCSRA = (0 << ADEN); // Disable the ADC module
    ADCSRB = (1 << ACME);
    ADMUX = 3; // Select analog channel 3 as comparator negative input
    ACSR &= ~0x01;
}

void a_high_b_low()
{
    PORTB = 0x04;
    PORTD &= ~0x18;
    PORTD |= 0x20;
    TCCR1A = 0;    // Turn pin 11 (OC2A) PWM ON (pin 9 & pin 10 OFF)
    TCCR2A = 0x81; //
}
void a_high_c_low()
{
    PORTB = 0x02;
    PORTD &= ~0x18;
    PORTD |= 0x20;
    TCCR1A = 0;    // Turn pin 11 (OC2A) PWM ON (pin 9 & pin 10 OFF)
    TCCR2A = 0x81; //
}
void b_high_c_low()
{
    PORTB = 0x02;
    PORTD &= ~0x28;
    PORTD |= 0x10;
    TCCR2A = 0;    // Turn pin 10 (OC1B) PWM ON (pin 9 & pin 11 OFF)
    TCCR1A = 0x21; //
}
void b_high_a_low()
{
    PORTB = 0x08;
    PORTD &= ~0x28;
    PORTD |= 0x10;
    TCCR2A = 0;    // Turn pin 10 (OC1B) PWM ON (pin 9 & pin 11 OFF)
    TCCR1A = 0x21; //
}
void c_high_a_low()
{
    PORTB = 0x08;
    PORTD &= ~0x30;
    PORTD |= 0x08;
    TCCR2A = 0;    // Turn pin 9 (OC1A) PWM ON (pin 10 & pin 11 OFF)
    TCCR1A = 0x81; //
}
void c_high_b_low()
{
    PORTB = 0x04;
    PORTD &= ~0x30;
    PORTD |= 0x08;
    TCCR2A = 0;    // Turn pin 9 (OC1A) PWM ON (pin 10 & pin 11 OFF)
    TCCR1A = 0x81; //
}

void set_pwm_duty(byte duty)
{
    duty = constrain(duty, PWM_MIN_DUTY, PWM_MAX_DUTY);
    OCR1A = duty; // Set pin 9  PWM duty cycle
    OCR1B = duty; // Set pin 10 PWM duty cycle
    OCR2A = duty; // Set pin 11 PWM duty cycle
}

uint8_t bldc_step = 0, motor_speed;
unsigned int i;

void bldc_move()
{
    switch (bldc_step)
    {
    case 0:
        a_high_b_low();
        bemf_c_rising();
        break;
    case 1:
        a_high_c_low();
        bemf_b_falling();
        break;
    case 2:
        b_high_c_low();
        bemf_a_rising();
        break;
    case 3:
        b_high_a_low();
        bemf_c_falling();
        break;
    case 4:
        c_high_a_low();
        bemf_b_rising();
        break;
    case 5:
        c_high_b_low();
        bemf_a_falling();
        break;
    }
}

void setup()
{
    // `LIN` on the IR2021
    DDRD |= 0x38; // Configure pins 3, 4 and 5 as outputs
    PORTD = 0x00;
    // `HIN` on the IR2021
    // TODO: Get rid of `HIN` side.
    DDRB |= 0x0E; // Configure pins 9, 10 and 11 as outputs
    PORTB = 0x31;
    // Timer1 module setting: set clock source to clkI/O / 1 (no prescaling)
    TCCR1A = 0;
    TCCR1B = 0x01;
    // Timer2 module setting: set clock source to clkI/O / 1 (no prescaling)
    TCCR2A = 0;
    TCCR2B = 0x01;
    // Analog comparator setting
    ACSR = 0x10; // Disable and clear (flag bit) analog comparator interrupt

    pinMode(SPEED_UP, INPUT_PULLUP);
    pinMode(SPEED_DOWN, INPUT_PULLUP);
}

// Analog comparator ISR
ISR(ANALOG_COMP_vect)
{
    // BEMF debounce
    for (i = 0; i < 10; i++)
    {
        // Check if the bit:0 is set
        // essentially we check if bldc_step is either 1, 3 or 5
        if (bldc_step & 1)
        {
            // read the `ACO` bit, which is the ouput of the comparator
            if (!(ACSR & 0x20))
                i -= 1; // 0b00100000
        }
        else
        {
            if ((ACSR & 0x20))
                i -= 1; // 0b00100000
        }
    }
    bldc_move();
    bldc_step++;
    bldc_step %= 6;
}

void loop()
{
    set_pwm_duty(PWM_START_DUTY);
    i = 5000;
    Serial.begin(115200);
    // Motor start
    while (i > 100)
    {
        delayMicroseconds(100);
        bldc_move();
        bldc_step++;
        bldc_step %= 6;
        // Not sure about this `- 20` stuff
        i = i - 20;
        Serial.println(i);
    }
    motor_speed = PWM_START_DUTY;
    ACSR |= 0x08; // Enable analog comparator interrupt
    while (1)
    {
        while (!(digitalRead(SPEED_UP)) && motor_speed < PWM_MAX_DUTY)
        {
            motor_speed++;
            set_pwm_duty(motor_speed);
            delay(100);
        }
        while (!(digitalRead(SPEED_DOWN)) && motor_speed > PWM_MIN_DUTY)
        {
            motor_speed--;
            set_pwm_duty(motor_speed);
            delay(100);
        }
    }
}
