#include "Chorus.h"

template <typename SampleType>
Chorus<SampleType>::Chorus()
{

}

template <typename SampleType>
Chorus<SampleType>::~Chorus()
{

}

template <typename SampleType>
void Chorus<SampleType>::prepare(SampleType sampleRate)
{
	this->sampleRate = sampleRate;

	this->delayLine.prepare(sampleRate);
	this->delayLine.setSize(int(sampleRate / 2));
	
	this->lfo.prepare(sampleRate);
	this->lfo.setWaveformType(0);
}

template <typename SampleType>
SampleType Chorus<SampleType>::processSample(SampleType input)
{
	SampleType modMin = minDelay;
	SampleType modMax = minDelay + maxDelay;
	
	SampleType in = input;
	SampleType out = in;                

	SampleType newDelTime = (this->doUnipolarModulationFromMin(this->bipolarToUnipolar(depth * this->lfo.getNextOutputSample(LFO::LFOPhase::Normal)), modMin, modMax));

	this->delayLine.pushSample(out);        
	this->delayLine.setDelayInSamples(newDelTime * this->sampleRate / 1000.0);
	out = this->delayLine.popSample();

	return (1.0 - mix) * in + mix * out;
}

template <typename SampleType>
void Chorus<SampleType>::process(SampleType* data, int startSample, int endSample)
{
	for(int sample = startSample; sample < endSample; ++sample)
		data[sample] = processSample(data[sample]);
}

template <typename SampleType>
void Chorus<SampleType>::setRate(SampleType newRate)
{
	this->rate = newRate;
	this->lfo.setFrequency(this->rate);
}

template <typename SampleType>
void Chorus<SampleType>::setDepth(SampleType newDepth)
{
	this->depth = newDepth;
}

template <typename SampleType>
void Chorus<SampleType>::setMix(SampleType newMix)
{
	this->mix = newMix;
}

template class Chorus<float>;
template class Chorus<double>;