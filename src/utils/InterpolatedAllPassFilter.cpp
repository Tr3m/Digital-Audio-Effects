#include "InterpolatedAllPassFilter.h"

template <typename SampleType>
InterpolatedAllPassFilter<SampleType>::InterpolatedAllPassFilter()
{

}

template <typename SampleType>
InterpolatedAllPassFilter<SampleType>::~InterpolatedAllPassFilter()
{

}

template <typename SampleType>
void InterpolatedAllPassFilter<SampleType>::prepare(SampleType sampleRate)
{
    this->sampleRate = sampleRate;
    circularBuffer.prepare(sampleRate);
    circularBuffer.setSize(2*sampleRate);
    circularBuffer.setDelayInMs(delayTime);

}

template <typename SampleType>
void InterpolatedAllPassFilter<SampleType>::setDelayMs(SampleType delayInMs)
{
    circularBuffer.setDelayInMs(delayInMs);
}

template <typename SampleType>
void InterpolatedAllPassFilter<SampleType>::setDelaySamples(SampleType delayInSamples)
{
    circularBuffer.setDelayInSamples(delayInSamples);
}

template <typename SampleType>
void InterpolatedAllPassFilter<SampleType>::setFeedback(SampleType newFeedback)
{
    newFeedback >= FEEDBACK_LIMIT ? newFeedback = FEEDBACK_LIMIT : newFeedback = newFeedback;
    newFeedback <= 0.0 ? newFeedback = 0.0 : newFeedback = newFeedback;

    this->feedback = newFeedback;
}

template <typename SampleType>
SampleType InterpolatedAllPassFilter<SampleType>::processSample(SampleType input)
{
    lastOutput = circularBuffer.popSample();
    circularBuffer.pushSample(input + (feedback * lastOutput));
    lastInput = input * -feedback;

    return (lastOutput + lastInput);
}

template <typename SampleType>
void InterpolatedAllPassFilter<SampleType>::process(SampleType* channelData, int startSample, int endSample)
{
    for(int sample = startSample; sample < endSample; ++sample)
        channelData[sample] = processSample(channelData[sample]);
}

template class InterpolatedAllPassFilter<float>;
template class InterpolatedAllPassFilter<double>;