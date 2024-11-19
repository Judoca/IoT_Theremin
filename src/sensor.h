// sensor.h

#ifndef SENSOR_H
#define SENSOR_H

#define TRIG_PIN 17     // GPIO 17 for Trigger
#define ECHO_PIN 4      // GPIO 4 for Echo

#define TRIG_PIN_2 26   // GPIO 26 for Trigger 2
#define ECHO_PIN_2 16   // GPIO 16 for Echo 2

void    setup_sensor();
float   get_distance_p();   // To receive the distance from the ultrsonic
                            // sound sensor 1

float   get_distance_v();   // To receive the distance from the ultrasonic
                            // sound sensor 2

float   remove_outliers(float distance);    // To remove outliers in the 
                                            // data




#endif  // SENSOR_H
