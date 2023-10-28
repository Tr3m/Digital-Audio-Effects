#include "InterpolatedCombFilter.h"

template <typename SampleType>
InterpolatedCombFilter<SampleType>::InterpolatedCombFilter()
{

}

template <typename SampleType>
InterpolatedCombFilter<SampleType>::~InterpolatedCombFilter()
{

}

template <typename SampleType>
void InterpolatedCombFilter<SampleType>::prepare(SampleType sampleRate)
{
    this->sampleRate = sampleRate;
    circularBuffer.prepare(sampleRate);
    circularBuffer.setSize(2*sampleRate);
    circularBuffer.setDelayInSamples(delaySamples);
}

template <typename SampleType>
void InterpolatedCombFilter<SampleType>::setDelayMs(SampleType delayInMs)
{
    this->delaySamples = (delayInMs / 1000) * sampleRate;
    circularBuffer.setDelayInSamples(this->delaySamples);
}

template <typename SampleType>
void InterpolatedCombFilter<SampleType>::setDelaySamples(SampleType delayInSamples)
{
    this->delaySamples = delayInSamples;
    circularBuffer.setDelayInSamples(delaySamples);
}

template <typename SampleType>
void InterpolatedCombFilter<SampleType>::setFeedback(SampleType newFeedback)
{
    newFeedback >= FEEDBACK_LIMIT ? newFeedback = FEEDBACK_LIMIT : newFeedback = newFeedback;
    //newFeedback <= 0.0 ? newFeedback = 0.0 : newFeedback = newFeedback;

    this->feedback = newFeedback;
}

template <typename SampleType>
SampleType InterpolatedCombFilter<SampleType>::processSample(SampleType input)
{
    SampleType in = input + feedback*lastOutput;

    SampleType out = circularBuffer.popSample();
    circularBuffer.pushSample(in);

    lastOutput = out;

    return out;        
}

template <typename SampleType>
void InterpolatedCombFilter<SampleType>::process(SampleType* channelData, int startSample, int endSample)
{
    for(int sample = startSample; sample < endSample; ++sample)
        channelData[sample] = processSample(channelData[sample]);
}

template class InterpolatedCombFilter<float>;
template class InterpolatedCombFilter<double>;