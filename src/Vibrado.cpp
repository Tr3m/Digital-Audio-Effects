#include "Vibrado.h"

template <typename SampleType>
Vibrado<SampleType>::Vibrado()
{

}

template <typename SampleType>
Vibrado<SampleType>::~Vibrado()
{

}

template <typename SampleType>
void Vibrado<SampleType>::prepare(SampleType sampleRate)
{
	this->sampleRate = sampleRate;

	this->delayLine.prepare(sampleRate);
	this->delayLine.setSize(int(sampleRate / 2));

	this->lfo.prepare(sampleRate);
	this->lfo.setWaveformType(this->lfoType);
}

template <typename SampleType>
SampleType Vibrado<SampleType>::processSample(SampleType input)
{
	SampleType modMin = minDelay;
	SampleType modMax = minDelay + maxDelay;

	SampleType out = input;                

	SampleType newDelTime = (this->doUnipolarModulationFromMin(this->bipolarToUnipolar(depth * this->lfo.getNextOutputSample(LFO::LFOPhase::Normal)), modMin, modMax));

	this->delayLine.pushSample(out);        
	this->delayLine.setDelayInSamples(newDelTime * this->sampleRate / 1000.0);
	out = this->delayLine.popSample();

	return out * GainUtilities<SampleType>::decibelsToGain(this->level);
}

template <typename SampleType>
void Vibrado<SampleType>::process(SampleType* data, int startSample, int endSample)
{
	for(int sample = startSample; sample < endSample; ++sample)
		data[sample] = processSample(data[sample]);
}

template <typename SampleType>
void Vibrado<SampleType>::setRate(SampleType newRate)
{
	this->rate = newRate;
	this->lfo.setFrequency(this->rate);
}

template <typename SampleType>
void Vibrado<SampleType>::setDepth(SampleType newDepth)
{
	this->depth = newDepth;
}

template <typename SampleType>
void Vibrado<SampleType>::setLevel(SampleType level_dB)
{
	this->level = level_dB;
}

template <typename SampleType>
void Vibrado<SampleType>::setLFOType(int type)
{
	switch (type)
	{
	case LFO_Types::Triangle:
		this->lfoType = LFO_Types::Triangle;
		this->lfo.setWaveformType(LFO::Waveforms::Triangle);
		break;
	case LFO_Types::Sine:
		this->lfoType = LFO_Types::Sine;
		this->lfo.setWaveformType(LFO::Waveforms::Sine);
		break;
	case LFO_Types::Saw:
		this->lfoType = LFO_Types::Saw;
		this->lfo.setWaveformType(LFO::Waveforms::Saw);
		break;
	}
}

template <typename SampleType>
int Vibrado<SampleType>::getLFOType()
{
	return this->lfoType;
}

template class Vibrado<float>;
template class Vibrado<double>;