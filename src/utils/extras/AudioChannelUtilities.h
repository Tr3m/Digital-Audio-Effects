#pragma once

/**
 * Struct wrapping inline functions for manipulating Audio Buffer channels.
 */
template <typename SampleType>
struct AudioChannelUtilities
{
    /**
     * @brief Copies the data from one stereo audio buffer's channel to the other.
     * 
     * @param sourceChannelData Source audio buffer memory block start pointer
     * @param destinationChannelData Deistination audio buffer memory block start pointer
     * @param startSample Sample index to start copying from
     * @param numSamples Number of samples to copy
     */
    static inline void doDualMono(SampleType* sourceChannelData, SampleType* destinationChannelData, int startSample, int numSamples)
    {
        for(int sample = 0; sample < numSamples; ++sample)
            destinationChannelData[sample] = sourceChannelData[sample];
    };
};