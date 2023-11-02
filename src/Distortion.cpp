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
	filter.setCutoff(this->filterCutoff);
}

template <typename SampleType>
SampleType Distortion<SampleType>::processSample(SampleType input)
{
	SampleType in = input;
	SampleType out = 0.0;

	switch(algorithm)
	{
	case Algorithms::Tube:
		in *= GainUtilities<SampleType>::decibelsToGain(this->gain);
		out = VaccumTube<SampleType>::processSample(in);
		break;
	case Algorithms::Shockley_Diode:
		in *= GainUtilities<SampleType>::decibelsToGain(50.0);
		in *= GainUtilities<SampleType>::decibelsToGain(this->gain);
		out = Diode<SampleType>::processSample(in);
		out *= GainUtilities<SampleType>::decibelsToGain(23.0);
		break;
	case Algorithms::Soft:
		out = SoftClipper<SampleType>::processSample(in, GainUtilities<SampleType>::decibelsToGain(this->gain));
		break;
	case Algorithms::Hard:
		in *= GainUtilities<SampleType>::decibelsToGain(this->gain);
		out = HardClipper<SampleType>::processSample(in);
		break;
	case Algorithms::Asymetric:
		in *= GainUtilities<SampleType>::decibelsToGain(40.0);
		in *= GainUtilities<SampleType>::decibelsToGain(this->gain);
		out = AsymetricClipper<SampleType>::processSample(in);
		out *= GainUtilities<SampleType>::decibelsToGain(-30.0);
		break;
	default:
		out = in;
		break;
	}

	out = filter.processSample(out);

	return out * GainUtilities<SampleType>::decibelsToGain(this->level);
}

template <typename SampleType>
void Distortion<SampleType>::process(SampleType* data, int startSample, int endSample)
{
	for(int sample = startSample; sample < endSample; ++sample)
		data[sample] = processSample(data[sample]);
}

template <typename SampleType>
void Distortion<SampleType>::setAlgorithm(int algorithmIndex)
{
	if (algorithmIndex < 0 || algorithmIndex >= NUM_ALGORITHMS)
		throw std::invalid_argument("Algorithm index out of range");

	this->algorithm = algorithmIndex;
}

template <typename SampleType>
int Distortion<SampleType>::getAlgorithm()
{
	return this->algorithm;
}

template <typename SampleType>
void Distortion<SampleType>::setGain(SampleType newGain)
{
	this->gain = newGain;
}

template <typename SampleType>
void Distortion<SampleType>::setLevel(SampleType newLevel)
{
	this->level = newLevel;
}

template <typename SampleType>
void Distortion<SampleType>::setFilterFreq(SampleType newFilterFreq)
{
	filterCutoff = newFilterFreq;
	filter.setCutoff(filterCutoff);
}

template class Distortion<float>;
template class Distortion<double>;