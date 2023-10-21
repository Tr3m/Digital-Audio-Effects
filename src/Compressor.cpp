#include "Compressor.h" 

template <typename SampleType>
Compressor<SampleType>::Compressor()
{

}

template <typename SampleType>
Compressor<SampleType>::~Compressor()
{

}

template <typename SampleType>
void Compressor<SampleType>::prepare(SampleType sampleRate)
{
	detector.prepare(sampleRate);
	detector.setOutputIndB(true);
}

template <typename SampleType>
SampleType Compressor<SampleType>::processSample(SampleType sample)
{
	SampleType xn = sample;
	SampleType detect_input = 0.0;

	detect_input = detector.processSample(xn);

	//Gain Reduction Calculation
	SampleType gainReduction = calaculateGain(detect_input);

	//Make-up Gain
	SampleType muGain = GainUtilities<SampleType>::decibelsToGain(makeupGain);

	return xn * gainReduction * muGain;
}

template <typename SampleType>
void Compressor<SampleType>::process(SampleType* data, int startSample, int endSample)
{
	for(int sample = startSample; sample < endSample; ++sample)
		data[sample] = processSample(data[sample]);
}

template <typename SampleType>
void Compressor<SampleType>::setThreshold(SampleType newThreshold)
{
	threshold = newThreshold;

	//Bounds Check
	if (threshold > 0.0)
		threshold = 0.0;
	if (threshold < -80.0)
		threshold = -80.0;
}

template <typename SampleType>
void Compressor<SampleType>::setRatio(SampleType newRatio)
{
	ratio = newRatio;

	//Bounds Check
	if (ratio > 100.0)
		ratio = 100.0;
	if (ratio < 1.0)
		ratio = 1.0;
}

template <typename SampleType>
void Compressor<SampleType>::setAttack(SampleType newAttack)
{
	attack = newAttack;

	//Bounds Check
	if (attack > 100.0)
		attack = 100.0;
	if (attack < 1.0)
		attack = 1.0;
	
	detector.setAttackTime(attack);
}

template <typename SampleType>
void Compressor<SampleType>::setRelease(SampleType newRelease)
{
	release = newRelease;

	//Bounds Check
	if (release > 1000.0)
		release = 1000.0;
	if (release < 10.0)
		release = 10.0;

	detector.setReleaseTime(release);
}

template <typename SampleType>
void Compressor<SampleType>::setGain(SampleType newGain)
{
	makeupGain = newGain;
}

template <typename SampleType>
void Compressor<SampleType>::setParameter(int index, SampleType newValue)
{
	switch (index)
	{
	case Parameters::Threshold:
		setThreshold(newValue);
		break;
	case Parameters::Ratio:
		setRatio(newValue);
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
SampleType Compressor<SampleType>::getParameter(int index)
{
	switch (index)
	{
	case Parameters::Threshold:
		return threshold;
		break;
	case Parameters::Ratio:
		return ratio;
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
void Compressor<SampleType>::setKneeType(int index)
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
int Compressor<SampleType>::getKneeType()
{
	return kneeType;
}

template <typename SampleType>
SampleType Compressor<SampleType>::calaculateGain(SampleType input)
{
	SampleType output = 0.0;

	switch (kneeType)
	{
	case KneeTypes::Soft:

		if (2.0 * (input - threshold) < -(kneeWidth))
			output = input;
		else if (2.0 * (std::fabs(input - threshold)) <= kneeWidth)
			output = input + (((1.0 / ratio) - 1.0) * std::pow((input - threshold + (kneeWidth/ 2.0)), 2.0)) / (2.0 * kneeWidth);
		else if (2.0 * (input - threshold) > kneeWidth)
			output = threshold + (input - threshold) / ratio;

		break;
	case KneeTypes::Hard:

		if (input <= threshold)
			output = input;
		else
			output = threshold + (input - threshold) / ratio;

		break;
	}

	SampleType gainReduction_dB = output - input;
	SampleType gainReduction_Linear = std::pow(10.0, (gainReduction_dB) / 20.0);

	return gainReduction_Linear;
}

template class Compressor<float>;
template class Compressor<double>;