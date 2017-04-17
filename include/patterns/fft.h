#ifndef __FFT_H__
#define __FFT_H__

#include <colors.h>
#include <graphics/graphics.h>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <fftw3.h>
#include <math.h>

class Fft: public Graphics
{
public:
    Fft(rect_t rect, YAML::Node args):
    Graphics(rect, args)
    {
        int error;
        this->s = pa_simple_new(NULL,
                                "ledart-fft",
                                PA_STREAM_RECORD,
                                NULL,
                                "fft",
                                &(this->ss),
                                NULL,
                                NULL,
                                &error);

        if(!(this->s))
        {
            fprintf(stderr, "pa_simple_new failed: %s\n", pa_strerror(error));
            exit(-1);
        }
    }

    float windowFunction(int n, int N)
    {
        return 0.5f * (1.0f - cosf(2.0f * M_PI * n / (N - 1.0f)));
    }

    void calculateBars(fftw_complex *fft, int fft_size, int *bars, int num_bars)
    {
        double width = this->upper_freq / (this->fps * this->get_rect().width);
        int bar_width = (int)ceil(width);

        double scale = 2.0 / fft_size * this->gain;

        int i = 0;
        for(int bar = 0; bar < num_bars; bar++)
        {
            double power = 0.0;
            for(int j = 0; j < bar_width && i < fft_size; i++, j++)
            {
                double re = fft[i][0] * scale;
                double im = fft[i][1] * scale;
                power += re * re + im * im;
            }
            power *= (1.0 / bar_width);
            if(power < 1e-15) power = 1e-15;

            int dB = this->get_rect().height + (int)(10.0 * log10(power));
            if(dB > this->get_rect().height) dB = this->get_rect().height;
            if(dB < 0) dB = 0;

            bars[bar] = dB;
        }
    }

    void generate(){};

    pa_simple *s;
    pa_sample_spec ss =
    {
        PA_SAMPLE_FLOAT32LE,
        44100,
        2
    };
    double gain = 1.0;
    double upper_freq = 3520.0;
    int fps = 30;
};

#endif
