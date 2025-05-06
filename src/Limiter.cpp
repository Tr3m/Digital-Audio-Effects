#include "Limiter.h"

template <typename SampleType>
Limiter<SampleType>::Limiter()
{

}

template <typename SampleType>
Limiter<SampleType>::~Limiter()
{

}

template <typename SampleType>
void Limiter<SampleType>::prepare(SampleType sampleRate)
{
	this->sampleRate = sampleRate;
	this->detector.prepare(sampleRate);
	this->detector.setOutputIndB(true);
}

template <typename SampleType>
SampleType Limiter<SampleType>::processSample(SampleType sample)
{
	SampleType xn = sample;
	SampleType detect_input = 0.0;

	detect_input = this->detector.processSample(xn);

	//Gain Reduction Calculation
	SampleType gainReduction = calaculateGain(detect_input);

	//MakeupGain
	SampleType muGain = GainUtilities<SampleType>::decibelsToGain(makeupGain);

	return xn * gainReduction * muGain;
}

template <typename SampleType>
void Limiter<SampleType>::process(SampleType* data, int startSample, int endSample)
{
	for(int sample = startSample; sample < endSample; ++sample)
		data[sample] = processSample(data[sample]);
}

template <typename SampleType>
void Limiter<SampleType>::setThreshold(SampleType newThreshold)
{
	threshold = newThreshold;

	//Bounds Check
	if (threshold > 0.0)
		threshold = 0.0;
	if (threshold < -80.0)
		threshold = -80.0;
}

template <typename SampleType>
void Limiter<SampleType>::setAttack(SampleType newAttack)
{
	attack = newAttack;

	//Bounds Check
	if (attack > 100.0)
		attack = 100.0;
	if (attack < 1.0)
		attack = 1.0;
	
	this->detector.setAttackTime(attack);
}

template <typename SampleType>
void Limiter<SampleType>::setRelease(SampleType newRelease)
{
	release = newRelease;

	//Bounds Check
	if (release > 1000.0)
		release = 1000.0;
	if (release < 10.0)
		release = 10.0;

	this->detector.setReleaseTime(release);
}

template <typename SampleType>
void Limiter<SampleType>::setGain(SampleType newGain)
{
	makeupGain = newGain;
}

template <typename SampleType>
void Limiter<SampleType>::setParameter(int index, SampleType newValue)
{
	switch (index)
	{
	case Parameters::Threshold:
		setThreshold(newValue);
		break;

	case Parameters::Attack:
		setAttack(newValue);
		break;
	case Parameters::Release:
		setRelease(newValue);
		break;
	case Parameters::MakeupGain:
		setGain(newValue);
		break;
	}
}

template <typename SampleType>
SampleType Limiter<SampleType>::getParameter(int index)
{
	switch (index)
	{
	case Parameters::Threshold:
		return threshold;
		break;
	case Parameters::Attack:
		return attack;
		break;
	case Parameters::Release:
		return release;
		break;
	case Parameters::MakeupGain:
		return makeupGain;
		break;
	}
}

template <typename SampleType>
void Limiter<SampleType>::setKneeType(int index)
{
	switch (index)
	{
	case KneeTypes::Soft:
		kneeType = KneeTypes::Soft;
		break;
	case KneeTypes::Hard:
		kneeType = KneeTypes::Hard;
		break;
	}
}

template <typename SampleType>
int Limiter<SampleType>::getKneeType()
{
	return kneeType;
}

template <typename SampleType>
SampleType Limiter<SampleType>::calaculateGain(SampleType input)
{
	SampleType output = 0.0;

	switch (kneeType)
	{
	case KneeTypes::Soft:

		if (2.0 * (input - threshold) < -kneeWidth)
			output = input;
		else if (2.0 * (std::fabs(input - threshold)) <= kneeWidth)
			output = input - std::pow((input - threshold + (kneeWidth / 2.0)), 2.0) / (2.0 * kneeWidth);
		else if (2.0 * (input - threshold) > kneeWidth)
			output = threshold;
		break;

	case KneeTypes::Hard:

		if (input <= threshold)
			output = input;
		else
			output = threshold;
		break;
	}

	SampleType gainReduction_dB = output - input;
	SampleType gainReduction_Linear = std::pow(10.0, (gainReduction_dB) / 20.0);

	return gainReduction_Linear;
}

template class Limiter<float>;
template class Limiter<double>;