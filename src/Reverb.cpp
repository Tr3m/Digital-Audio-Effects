#include "Reverb.h"

template <typename SampleType>
Reverb<SampleType>::Reverb()
{

}

template <typename SampleType>
Reverb<SampleType>::~Reverb()
{

}

template <typename SampleType>
void Reverb<SampleType>::prepare(SampleType sampleRate)
{
    this->sampleRate = sampleRate;

    for(int comb = 0; comb < NUM_COMBS; ++comb)
    {
        combFilters[comb].prepare(sampleRate);
        combFilters[comb].setDelayMs(combDelayTimeValues[comb]);
        combFilters[comb].setFeedback(combFeedbackValues[comb]);
        combFilters[comb].setWidth(8);
        combFilters[comb].setRate(combModRates[comb]);
        combFilters[comb].setDepth(1.0);

        valueSmoothers[comb].prepare(450.0, sampleRate);
    }

    for(int allpass = 0; allpass < NUM_ALLPASS; ++allpass)
    {
        allPassFilters[allpass].prepare(sampleRate);
        allPassFilters[allpass].setDelayMs(allPassDelayTimeValues[allpass]);
        allPassFilters[allpass].setFeedback(allPassFeedbackValues[allpass]);
        allPassFilters[allpass].setWidth(8);
        allPassFilters[allpass].setRate(allPassModRates[allpass]);
        allPassFilters[allpass].setDepth(0.4);
    }

    filter.prepare(sampleRate);
    filter.setFilterType(IIRFilter<SampleType>::FilterTypes::LPF);
    filter.setCutoff(this->filterCutoff);
}

template <typename SampleType>
SampleType Reverb<SampleType>::processSample(SampleType input)
{
    SampleType combOutput = 0.0;
    SampleType output = 0.0;

    // Comb Filters
    for(int comb = 0; comb < NUM_COMBS; ++comb)
    {
        combFilters[comb].setDelayMs(valueSmoothers[comb].process(roomSize) * combDelayTimeValues[comb]);
        combOutput += combFilters[comb].processSample(input);
    }

    combOutput = combOutput / NUM_COMBS;

    // All-Pass Filters
    output = allPassFilters[0].processSample(combOutput);
    output = allPassFilters[1].processSample(output);

    // Low-Pass Filter
    output = filter.processSample(output);

    return (mix * output) + ((1.0 - mix) * input);
}

template <typename SampleType>
void Reverb<SampleType>::process(SampleType* data, int startSample, int endSample)
{
    for(int sample = startSample; sample < endSample; ++sample)
        data[sample] = processSample(data[sample]);
}

template <typename SampleType>
void Reverb<SampleType>::setRoomSize(SampleType newRoomSize)
{
    this->roomSize = newRoomSize;        
}

template <typename SampleType>
void Reverb<SampleType>::setDecay(SampleType newDecay)
{
    this->decay = newDecay;

    for(int comb = 0; comb < NUM_COMBS; ++comb)
        combFilters[comb].setFeedback(decay * combFeedbackValues[comb]);
}

template <typename SampleType>
void Reverb<SampleType>::setCutoff(SampleType newCutoff)
{
    this->filterCutoff = newCutoff;
    filter.setCutoff(this->filterCutoff);
}

template <typename SampleType>
void Reverb<SampleType>::setMix(SampleType newMix)
{
    this->mix = newMix;
}

template class Reverb<float>;
template class Reverb<double>;