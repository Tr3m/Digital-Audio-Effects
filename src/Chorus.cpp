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

	delayLine.prepare(sampleRate);
	delayLine.setSize(int(sampleRate / 2));
	
	lfo.prepare(sampleRate);
	lfo.setWaveformType(0);
}

template <typename SampleType>
SampleType Chorus<SampleType>::processSample(SampleType input)
{
	SampleType modMin = minDelay;
	SampleType modMax = minDelay + maxDelay;
	
	SampleType in = input;
	SampleType out = in;                

	SampleType newDelTime = (doUnipolarModulationFromMin(bipolarToUnipolar(depth * lfo.getNextOutputSample(LFO::LFOPhase::Normal)), modMin, modMax));

	delayLine.pushSample(out);        
	delayLine.setDelayInSamples(newDelTime * sampleRate / 1000.0);
	out = delayLine.popSample();

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
	lfo.setFrequency(this->rate);
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

template <typename SampleType>
SampleType Chorus<SampleType>::doUnipolarModulationFromMin(SampleType unipolarModulatorValue, SampleType minValue, SampleType maxValue)
{
	// --- UNIPOLAR bound
	unipolarModulatorValue = fmin(unipolarModulatorValue, 1.0f);
	unipolarModulatorValue = fmax(unipolarModulatorValue, 0.0f);

	// --- modulate from minimum value upwards
	return unipolarModulatorValue * (maxValue - minValue) + minValue;
}

template <typename SampleType>
SampleType Chorus<SampleType>::bipolarToUnipolar(SampleType value)
{
	return 0.5 * value + 0.5;
}

template class Chorus<float>;
template class Chorus<double>;