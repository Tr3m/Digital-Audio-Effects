#pragma once

template <typename SampleType>
struct AudioChannelUtilities
{
    static inline void doDualMono(SampleType* sourceChannelData, SampleType* destinationChannelData, int startSample, int numSamples)
    {
        for(int sample = 0; sample < numSamples; ++sample)
            destinationChannelData[sample] = sourceChannelData[sample];
    };
};