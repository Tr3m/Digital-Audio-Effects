#include "CombFilter.h"

template <typename SampleType>
CombFilter<SampleType>::CombFilter()
{

}

template <typename SampleType>
CombFilter<SampleType>::~CombFilter()
{

}

template <typename SampleType>
void CombFilter<SampleType>::prepare(SampleType sampleRate)
{
    this->sampleRate = sampleRate;
    circularBuffer.prepare(sampleRate);
    circularBuffer.setSize(2*sampleRate);
    circularBuffer.setDelayInMs(delayTime);

}

template <typename SampleType>
void CombFilter<SampleType>::setDelayMs(SampleType delayInMs)
{
    circularBuffer.setDelayInMs(delayInMs);
}

template <typename SampleType>
void CombFilter<SampleType>::setDelaySamples(SampleType delayInSamples)
{
    circularBuffer.setDelayInSamples(delayInSamples);
}

template <typename SampleType>
void CombFilter<SampleType>::setFeedback(SampleType newFeedback)
{
    newFeedback >= FEEDBACK_LIMIT ? newFeedback = FEEDBACK_LIMIT : newFeedback = newFeedback;
    newFeedback <= 0.0 ? newFeedback = 0.0 : newFeedback = newFeedback;

    this->feedback = newFeedback;
}

template <typename SampleType>
SampleType CombFilter<SampleType>::processSample(SampleType input)
{
    SampleType in = input + feedback*lastOutput;
    SampleType out = circularBuffer.processSample(in);
    lastOutput = out;

    return out;        
}

template <typename SampleType>
void CombFilter<SampleType>::process(SampleType* channelData, int startSample, int endSample)
{
    for(int sample = startSample; sample < endSample; ++sample)
        channelData[sample] = processSample(channelData[sample]);
}

template class CombFilter<float>;
template class CombFilter<double>;