#include "AllPassFilter.h"

template <typename SampleType>
AllPassFilter<SampleType>::AllPassFilter()
{

}

template <typename SampleType>
AllPassFilter<SampleType>::~AllPassFilter()
{

}

template <typename SampleType>
void AllPassFilter<SampleType>::prepare(SampleType sampleRate)
{
    this->sampleRate = sampleRate;
    circularBuffer.prepare(sampleRate);
    circularBuffer.setSize(2*sampleRate);
    circularBuffer.setDelayInMs(delayTime);

}

template <typename SampleType>
void AllPassFilter<SampleType>::setDelayMs(SampleType delayInMs)
{
    circularBuffer.setDelayInMs(delayInMs);
}

template <typename SampleType>
void AllPassFilter<SampleType>::setDelaySamples(SampleType delayInSamples)
{
    circularBuffer.setDelayInSamples(delayInSamples);
}

template <typename SampleType>
void AllPassFilter<SampleType>::setFeedback(SampleType newFeedback)
{
    newFeedback >= FEEDBACK_LIMIT ? newFeedback = FEEDBACK_LIMIT : newFeedback = newFeedback;
    newFeedback <= 0.0 ? newFeedback = 0.0 : newFeedback = newFeedback;

    this->feedback = newFeedback;
}

template <typename SampleType>
SampleType AllPassFilter<SampleType>::processSample(SampleType input)
{
    lastOutput = circularBuffer.popSample();
    circularBuffer.pushSample(input + (feedback * lastOutput));
    lastInput = input * -feedback;

    return (lastOutput + lastInput);
}

template <typename SampleType>
void AllPassFilter<SampleType>::process(SampleType* channelData, int startSample, int endSample)
{
    for(int sample = startSample; sample < endSample; ++sample)
        channelData[sample] = processSample(channelData[sample]);
}

template class AllPassFilter<float>;
template class AllPassFilter<double>;