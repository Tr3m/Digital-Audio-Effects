#include "Delay.h"

template <typename SampleType>        
Delay<SampleType>::Delay()
{

}

template <typename SampleType>
Delay<SampleType>::~Delay()
{

}

template <typename SampleType>
void Delay<SampleType>::prepare(SampleType sampleRate)
{
    this->sampleRate = sampleRate;  
    combFilter.prepare(sampleRate);
    combFilter.setDelayMs(delayTime);
    combFilter.setFeedback(feedback);
    smoother.prepare(850.0, sampleRate);
}

template <typename SampleType>
void Delay<SampleType>::setDelayTime(SampleType delayInMs)
{
    this->delayTime = delayInMs;
}

template <typename SampleType>
void Delay<SampleType>::setFeedback(SampleType newFeedback)
{
    combFilter.setFeedback(newFeedback);
}

template <typename SampleType>
void Delay<SampleType>::setMix(SampleType newMix)
{
    if(newMix >= 1.0)
        newMix = 1.0;
    if(newMix <= 0.0)
        newMix = 0.0;

    this->mix = newMix;
}

template <typename SampleType>
void Delay<SampleType>::process(SampleType* channelData, int startSample, int endSample)
{
    for(int sample = startSample; sample < endSample; ++sample)
    {
        combFilter.setDelayMs(smoother.process(delayTime));
        SampleType processed = combFilter.processSample(channelData[sample]);
        SampleType output = (1.0 - mix)*channelData[sample] + mix*processed;
        channelData[sample] = output;
    }
}


template class Delay<float>;
template class Delay<double>;
