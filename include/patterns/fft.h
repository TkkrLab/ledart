#ifndef __FFT_H__
#define __FFT_H__

#include <colors.h>
#include <graphics/graphics.h>

#include <alsa/asoundlib.h>

class Fft: public Graphics
{
public:
    Fft(rect_t, YAML::Node);
    ~Fft();
    void generate();

    // char *buffer;
    // int buffer_frames = 128;
    // unsigned int rate = 44100;
    // snd_pcm_t *capture_handle;
    // snd_pcm_hw_params_t *hw_params;
    // snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;
};

#endif
