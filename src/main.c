// main.c

#include    <stdio.h>
#include    "sensor.h"
#include    <wiringPi.h>
#include    "sound.h"
#include    <stdlib.h>
#include    <string.h>
#include    <curl/curl.h>

int main (void)
{
  
  // Initialize WiringPi and check for errors
  if (wiringPiSetup () == -1) {
      printf ("WiringPi setup failed!\n");
      return 1;			// Exit with error
    }

  printf ("WiringPI initialized!\n");

  setup_sensor ();
  printf ("Sensor initialized!\n");

  float distance, distance_p;
  float frequency;

  // Main loop
  while (1) {
      printf ("Getting distance...\n");
      distance = get_distance_p ();
      printf ("Pitch Distance: %.2f cm\n", distance);

      // Pre-processing to remove outliers:
 
      distance_p = remove_outliers(distance);
      printf("Pre-processed Pitch Distance: %.2f cm\n", distance_p);
      
      printf("Phase 2: sound.\n");

      printf("Get frequency.\n");
      frequency = get_frequency(distance_p);
      printf("Frequency: %.2f\n", frequency);

      printf("Playing sound.\n");
      play_sound(frequency, 0.2);

      CURL *curl;
      CURLcode res;

      // ThingSpeak Write API key
      const char *write_api_key = "5V0G0Q6PWNDSFSVD";

      // URL for ThingSpeak API
      char url[200];
      snprintf(url, sizeof(url), "https://api.thingspeak.com/update?api_key=%s", write_api_key);

      // Data to send
      float cloud_distance = distance_p;
      float cloud_frequency = frequency;

      // Prepare data to send
      char data[200];
      snprintf(data, sizeof(data), "&field1=%.2f&field2=%.2f", cloud_distance, cloud_frequency);

      // Initialie CURL
      curl_global_init(CURL_GLOBAL_DEFAULT);
      curl = curl_easy_init();

      if(curl) {
        // set the url for post request
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // set the data to be sent as part of the request
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        // send the HTTP post request
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
          fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
          printf("Data sent to ThingSpeak successfully.\n");
        }

        // Clean CURL
        curl_global_cleanup();
      }

      

      delay(50);
  }
}
