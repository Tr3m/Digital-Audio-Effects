#pragma once
#include <cmath>

/**
 * First order filter for smoothing parameter changes
 * 
 */
class FirstOrderSmoother
{
public:
    FirstOrderSmoother()
    {
        
    }

    ~FirstOrderSmoother()
    {

    }

    /**
     * @brief Prepares filter for playback
     * 
     * @param smoothingTimeInMs Amount of time to reach target value in milliseconds
     * @param samplingRate Current sampling rate
     */
    void prepare(float smoothingTimeInMs, float samplingRate)
    {
        const float c_twoPi = 6.283185307179586476925286766559f;

        a = exp(-c_twoPi / (smoothingTimeInMs * 0.001f * samplingRate));
        b = 1.0f - a;
        z = 0.0f;
    };

    /**
     * @brief Processes a single sample
     * 
     * @param in Target value to reach
     */
    inline float process(float in)
    {
        z = (in * b) + (z * a);
        return z;
    }

private:
    float a;
    float b;
    float z;
};