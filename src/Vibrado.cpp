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

	delayLine.prepare(sampleRate);
	delayLine.setSize(int(sampleRate / 2));

	lfo.prepare(sampleRate);
	lfo.setWaveformType(lfoType);
}

template <typename SampleType>
SampleType Vibrado<SampleType>::processSample(SampleType input)
{
	SampleType modMin = minDelay;
	SampleType modMax = minDelay + maxDelay;

	SampleType out = input;                

	SampleType newDelTime = (doUnipolarModulationFromMin(bipolarToUnipolar(depth * lfo.getNextOutputSample(LFO::LFOPhase::Normal)), modMin, modMax));

	delayLine.pushSample(out);        
	delayLine.setDelayInSamples(newDelTime * sampleRate / 1000.0);
	out = delayLine.popSample();

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
	lfo.setFrequency(this->rate);
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
		lfoType = LFO_Types::Triangle;
		lfo.setWaveformType(LFO::Waveforms::Triangle);
		break;
	case LFO_Types::Sine:
		lfoType = LFO_Types::Sine;
		lfo.setWaveformType(LFO::Waveforms::Sine);
		break;
	case LFO_Types::Saw:
		lfoType = LFO_Types::Saw;
		lfo.setWaveformType(LFO::Waveforms::Saw);
		break;
	}
}

template <typename SampleType>
int Vibrado<SampleType>::getLFOType()
{
	return lfoType;
}

template <typename SampleType>
SampleType Vibrado<SampleType>::doUnipolarModulationFromMin(SampleType unipolarModulatorValue, SampleType minValue, SampleType maxValue)
{
	// --- UNIPOLAR bound
	unipolarModulatorValue = fmin(unipolarModulatorValue, 1.0f);
	unipolarModulatorValue = fmax(unipolarModulatorValue, 0.0f);

	// --- modulate from minimum value upwards
	return unipolarModulatorValue * (maxValue - minValue) + minValue;
}

template <typename SampleType>
SampleType Vibrado<SampleType>::bipolarToUnipolar(SampleType value)
{
	return 0.5 * value + 0.5;
}

template class Vibrado<float>;
template class Vibrado<double>;