#include "ModulatedAllPassFilter.h"

template <typename SampleType>
ModulatedAllPassFilter<SampleType>::ModulatedAllPassFilter()
{

}

template <typename SampleType>
ModulatedAllPassFilter<SampleType>::~ModulatedAllPassFilter()
{

}

template <typename SampleType>
void ModulatedAllPassFilter<SampleType>::prepare(SampleType sampleRate)
{
    this->sampleRate = sampleRate;
    allPassFilter.prepare(sampleRate);
    allPassFilter.setDelayMs(delayTime);
    allPassFilter.setFeedback(feedback);

    lfo.prepare(sampleRate);
    lfo.setWaveformType(LFO::Waveforms::Sine);
}

template <typename SampleType>
void ModulatedAllPassFilter<SampleType>::setDelayMs(SampleType delayInMs)
{
    this->delayTime = delayInMs;
}

template <typename SampleType>
void ModulatedAllPassFilter<SampleType>::setDelayInSamples(SampleType delayInSamples)
{
    this->delayTime = (delayInSamples / sampleRate) * 1000.0;
}

template <typename SampleType>
void ModulatedAllPassFilter<SampleType>::setFeedback(SampleType newFeedback)
{
    this->feedback = newFeedback;
    allPassFilter.setFeedback(this->feedback);
}

template <typename SampleType>
void ModulatedAllPassFilter<SampleType>::setRate(SampleType newRate)
{
    this->rate = newRate;
    lfo.setFrequency(this->rate);
}

template <typename SampleType>
void ModulatedAllPassFilter<SampleType>::setDepth(SampleType newDepth)
{
    this->depth = newDepth;
}

template <typename SampleType>
void ModulatedAllPassFilter<SampleType>::setWidth(SampleType newWidth)
{
    this->width = newWidth;
}

template <typename SampleType>
SampleType ModulatedAllPassFilter<SampleType>::processSample(SampleType input)
{
    SampleType minDelay = ((this->delayTime / 1000) * sampleRate) - width;
    SampleType maxDelay = ((this->delayTime / 1000) * sampleRate) + width;
    SampleType modMin = minDelay;
    SampleType modMax = maxDelay;

    SampleType newDelTime = (doUnipolarModulationFromMin(bipolarToUnipolar(depth * lfo.getNextOutputSample(LFO::LFOPhase::Normal)), modMin, modMax));

    allPassFilter.setDelaySamples(newDelTime);                

    SampleType output = allPassFilter.processSample(input);

    return output;  
}

template <typename SampleType>
void ModulatedAllPassFilter<SampleType>::process(SampleType* data, int startSample, int endSample)
{
    for(int sample = startSample; sample < endSample; ++sample)
        data[sample] = processSample(data[sample]);
}

template <typename SampleType>
SampleType ModulatedAllPassFilter<SampleType>::doUnipolarModulationFromMin(SampleType unipolarModulatorValue, SampleType minValue, SampleType maxValue)
{
    // --- UNIPOLAR bound
    unipolarModulatorValue = fmin(unipolarModulatorValue, 1.0f);
    unipolarModulatorValue = fmax(unipolarModulatorValue, 0.0f);

    // --- modulate from minimum value upwards
    return unipolarModulatorValue * (maxValue - minValue) + minValue;
}

template <typename SampleType>
SampleType ModulatedAllPassFilter<SampleType>::bipolarToUnipolar(SampleType value)
{
    return 0.5 * value + 0.5;
}

template class ModulatedAllPassFilter<float>;
template class ModulatedAllPassFilter<double>;