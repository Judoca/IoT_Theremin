// sensor.c - sensor setup and distance measurement code

#include    <wiringPi.h>
#include    "sensor.h"
#include    <stdio.h>

void setup_sensor()
{
    wiringPiSetupGpio();            // Use BCM GPIO numbering
    pinMode(TRIG_PIN, OUTPUT);      // Set Trigger pin as output
    pinMode(TRIG_PIN_2, OUTPUT);    // Set Trigger pin 2 as output

    pinMode(ECHO_PIN, INPUT);       // Set Echo pin as input
    pinMode(ECHO_PIN, INPUT);       // Set Echo pin 2 as input

    digitalWrite(TRIG_PIN, LOW);    // Initialize Trigger pin to low
    digitalWrite(TRIG_PIN_2, LOW);  // Initialize Trigger pin 2 to low

    delay(30);
}

// Function to trigger the ultrasonic sensor and measure the distance

float get_distance_p ()
{
    // Send a pulse to trigger the ultrasonic sensor
    printf("Trigger pin 1 high.\n");
    digitalWrite(TRIG_PIN, HIGH);

    delayMicroseconds(10);          // Pulse width of 10 microseconds
    
    printf("Trigger pin 1 low.\n");
    digitalWrite(TRIG_PIN, LOW);

    // Wait for the echo pin to go HIGH and measure the pulse duration
    printf("digitalRead low.\n");
    while (digitalRead(ECHO_PIN)  == LOW) {
        // Waiting for the Echo pins to go HIGH
    }

    long start_time = micros();     // Record the start time
    
    printf("digitalRead high.\n");
    while (digitalRead(ECHO_PIN) == HIGH) {
        // Waiting for Echo pin to go low
    }

    long end_time = micros();       // Record the end time

    // Calculate the pulse duration
    long duration = end_time - start_time;

    // Calculate the distance in cm
    float distance = (duration / 2.0 ) * 0.0343;

    printf("Ending get_distance_p\n");

    return distance;    // Return distance in cms
}

float remove_outliers(float distance)
{
    if (distance < 5) {     // To set the minimum distance possible  
        return 5;
    } else if (distance > 400) {    // To set the max distance possible
        return 400;
    } else {
        return distance;
    }
}


