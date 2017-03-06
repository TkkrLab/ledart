#include "fft.h"

Fft::Fft(rect_t rect, YAML::Node args):
Graphics(rect, args)
{
    // int err = snd_pcm_open(&this->capture_handle, "hw:0", SND_PCM_STREAM_CAPTURE, 0);
    // if(err < 0)
    // {
    //     fprintf(stderr, "cannot open audio device %s (%s)\n",
    //             "hw:0", snd_strerror(err));
    //     exit(1);
    // }

    // err = snd_pcm_hw_params_malloc(&this->hw_params);
    // if(err < 0)
    // {
    //     fprintf(stderr, "cannot allocate hardware parameter structure (%s)\n",
    //             snd_strerror(err));
    //     exit(1);
    // }

    // err = snd_pcm_hw_params_any(this->capture_handle, hw_params);
    // if(err < 0)
    // {
    //     fprintf(stderr, "cannot initialize hardware parameter structure (%s)\n",
    //             snd_strerror(err));
    //     exit(1);
    // }

    // err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    // if(err < 0)
    // {
    //     fprintf(stderr, "cannot set access type (%s)\n",
    //             snd_strerror(err));
    //     exit(1);
    // }

    // err = snd_pcm_hw_params_set_format(this->capture_handle, hw_params, format);
    // if(err < 0)
    // {
    //     fprintf(stderr, "cannot set sample format %s\n", snd_strerror(err));
    //     exit(1);
    // }

    // err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, 0);
    // if(err < 0)
    // {
    //     fprintf(stderr, "cannot set sample rate %s\n", snd_strerror(err));
    //     exit(1);
    // }

    // err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 2);
    // if(err < 0)
    // {
    //     fprintf(stderr, "cannot set channel count %s\n", snd_strerror(err));
    //     exit(1);
    // }

    // err = snd_pcm_hw_params(capture_handle, hw_params);
    // if(err < 0)
    // {
    //     fprintf(stderr, "cannot set parameters %s\n", snd_strerror(err));
    //     exit(1);
    // }

    // snd_pcm_hw_params_free(this->hw_params);

    // err = snd_pcm_prepare(capture_handle);
    // if(err < 0)
    // {
    //     fprintf(stderr, "cannot prepare audio interface for use %s\n", snd_strerror(err));
    //     exit(1);
    // }

    // this->buffer = new char[128 * snd_pcm_format_width(format) / 8 * 2];

}

void Fft::generate()
{
    this->draw_pixel(0, 0, BLUE);
}

Fft::~Fft()
{
    // delete this->buffer;
}
