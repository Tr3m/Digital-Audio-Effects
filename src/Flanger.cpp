#include "Flanger.h"

template <typename SampleType>
Flanger<SampleType>::Flanger()
{

}

template <typename SampleType>
Flanger<SampleType>::~Flanger()
{

}

template <typename SampleType>
void Flanger<SampleType>::prepare(SampleType sampleRate)
{
	this->sampleRate = sampleRate;

	delayLine.prepare(sampleRate);
	delayLine.setSize(int(sampleRate / 2));
	
	lfo.prepare(sampleRate);
	lfo.setWaveformType(0);
}

template <typename SampleType>
SampleType Flanger<SampleType>::processSample(SampleType input)
{
	SampleType modMin = minDelay;
	SampleType modMax = minDelay + maxDelay;
	
	SampleType in = input;
	SampleType out = in;                

	SampleType newDelTime = (doUnipolarModulationFromMin(bipolarToUnipolar(depth * lfo.getNextOutputSample(LFO::LFOPhase::Normal)), modMin, modMax));

	delayLine.pushSample(out);        
	delayLine.setDelayInSamples(newDelTime);
	out = delayLine.popSample();

	return (1.0 - mix) * in + mix * out;
}

template <typename SampleType>
void Flanger<SampleType>::process(SampleType* data, int startSample, int endSample)
{
	for(int sample = startSample; sample < endSample; ++sample)
		data[sample] = processSample(data[sample]);
}

template <typename SampleType>
void Flanger<SampleType>::setRate(SampleType newRate)
{
	this->rate = newRate;
	lfo.setFrequency(this->rate);
}

template <typename SampleType>
void Flanger<SampleType>::setDepth(SampleType newDepth)
{
	this->depth = newDepth;
}

template <typename SampleType>
void Flanger<SampleType>::setMix(SampleType newMix)
{
	this->mix = newMix;
}

template <typename SampleType>
SampleType Flanger<SampleType>::doUnipolarModulationFromMin(SampleType unipolarModulatorValue, SampleType minValue, SampleType maxValue)
{
	// --- UNIPOLAR bound
	unipolarModulatorValue = fmin(unipolarModulatorValue, 1.0f);
	unipolarModulatorValue = fmax(unipolarModulatorValue, 0.0f);

	// --- modulate from minimum value upwards
	return unipolarModulatorValue * (maxValue - minValue) + minValue;
}

template <typename SampleType>
SampleType Flanger<SampleType>::bipolarToUnipolar(SampleType value)
{
	return 0.5 * value + 0.5;
}

template class Flanger<float>;
template class Flanger<double>;