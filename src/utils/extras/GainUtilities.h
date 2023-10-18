#pragma once
#include <cmath>

/**
 * Struct wrapping inline functions for manipulating Audio Buffer sample levels.
 */
template <typename SampleType>
struct GainUtilities
{
    /**
     * @brief Converts linear gain values to decibels
     * 
     * @param gainValue Linear gain value
     */
    static inline SampleType gainToDecibels(SampleType gainValue)
    {
        return 20.0 * log10(gainValue);
    };

    /**
     * @brief Converts decibel values to linear gain
     * 
     * @param dbValue Decibel value
     */
    static inline SampleType decibelsToGain(SampleType dbValue)
    {
        return pow(10.0, dbValue / 20.0);
    };
};