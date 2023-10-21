#include "Distortion.h"

template <typename SampleType>
Distortion<SampleType>::Distortion()
{

}

template <typename SampleType>
Distortion<SampleType>::~Distortion()
{
	
}

template <typename SampleType>
void Distortion<SampleType>::prepare(SampleType sampleRate)
{
	this->sampleRate = sampleRate;

	filter.prepare(sampleRate);
	filter.setFilterType(IIRFilter<SampleType>::FilterTypes::LPF);
	filter.setCutoff(filterCutoff);
}

template <typename SampleType>
SampleType Distortion<SampleType>::processSample(SampleType input)
{
	SampleType in = input;
	SampleType out = in;

	// Gain
	out = out * GainUtilities<SampleType>::decibelsToGain(gain);
	
	// Clipping
	out = out * GainUtilities<SampleType>::decibelsToGain(40.0);

	// Distortion Transfer Function (Waveshaping)	
	if (out >= 0) 
	{
		out = (SampleType)(atan(k * out) / atan(k));
	}
	else 
	{
		out = (SampleType)(0.5 * (atan((k / g) * out) / atan(k / g)));
	}		

	// Filter
	out = filter.processSample(out);

	// Level
	out = out * GainUtilities<SampleType>::decibelsToGain(level);

	return out;
}

template <typename SampleType>
void Distortion<SampleType>::process(SampleType* data, int startSample, int endSample)
{
	for(int sample = startSample; sample < endSample; ++sample)
		data[sample] = processSample(data[sample]);
}

template <typename SampleType>
void Distortion<SampleType>::setGain(SampleType newGain)
{
	gain = newGain;
}

template <typename SampleType>
void Distortion<SampleType>::setLevel(SampleType newLevel)
{
	level = newLevel;
}

template <typename SampleType>
void Distortion<SampleType>::setFilterFreq(SampleType newFilterFreq)
{
	filterCutoff = newFilterFreq;
	filter.setCutoff(filterCutoff);
}

template class Distortion<float>;
template class Distortion<double>;