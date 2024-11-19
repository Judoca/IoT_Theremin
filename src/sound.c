// sound.c

#include  "sound.h"

float get_frequency(float distance)
{
  const float min_distance = 3.0;
  const float max_distance = 50.0;
  const float min_frequency = 220;
  const float max_frequency = 880;

  // Linear mapping formula
  float frequency = min_frequency + (distance - min_distance) *
    (max_frequency - min_frequency) / (max_distance - min_distance);

  // Clamp frequency to the valid range
  if (frequency < min_frequency)
    frequency = min_frequency;
  if (frequency > max_frequency)
    frequency = max_frequency;

  return frequency;
}

void play_sound(float frequency, float duratio)
{
  snd_pcm_t *pcm_handle;
    int pcm;
    unsigned int rate = SAMPLE_RATE;
    int channels = 1; // Mono
    snd_pcm_uframes_t frames = 32;
    snd_pcm_hw_params_t *params;

    // Open the PCM device
    pcm = snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (pcm < 0) {
        fprintf(stderr, "ERROR: Cannot open PCM device: %s\n", snd_strerror(pcm));
        return;
    }

    // Set hardware parameters
    snd_pcm_hw_params_malloc(&params);
    snd_pcm_hw_params_any(pcm_handle, params);
    snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_FLOAT);
    snd_pcm_hw_params_set_channels(pcm_handle, params, channels);
    snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0);
    snd_pcm_hw_params(pcm_handle, params);
    snd_pcm_hw_params_free(params);
    snd_pcm_prepare(pcm_handle);

    // Generate and play the sin wave
    int num_samples = SAMPLE_RATE * duratio;
    float buffer[frames * channels];
    for (int i = 0; i < num_samples / frames; i++) {
        for (int j = 0; j < frames; j++) {
            buffer[j] = AMPLITUDE * sinf(2.0 * M_PI * frequency * (i * frames + j) / SAMPLE_RATE);
        }
        snd_pcm_writei(pcm_handle, buffer, frames);
    }

    // Clean up
    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);
}
