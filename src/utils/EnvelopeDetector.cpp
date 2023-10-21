#include "EnvelopeDetector.h"

template <typename SampleType>
EnvelopeDetector<SampleType>::EnvelopeDetector()
{
}

template <typename SampleType>
void EnvelopeDetector<SampleType>::prepare(SampleType sampleRate)
{
	setSampleRate(sampleRate);
	previousValue = 0.0;
}

template <typename SampleType>
SampleType EnvelopeDetector<SampleType>::processSample(SampleType input)
{
	SampleType xn = std::fabs(input);
	SampleType currentValue = 0.0; //Envelope value for the current sample

	if(detectionMode == DetectionModes::MS || detectionMode == DetectionModes::RMS)
		xn = xn*xn;

	if(xn > previousValue)
		currentValue = attackTimeCoeff * (previousValue - xn) + xn;
	else
		currentValue = releaseTimeCoeff * (previousValue  - xn) + xn;

	if (currentValue > 0.0 && currentValue < 1.175494351e-38)
	{
		currentValue = 0;
		
	}
	else if (currentValue < 0.0 && currentValue > -1.175494351e-38)
	{
		currentValue = 0;
		
	}

	currentValue = std::fmax(currentValue, 0.0);
	previousValue = currentValue;

	//Check if RMS Mode is selected
	if(getDetectionMode() == DetectionModes::RMS)
		currentValue = std::pow(currentValue, 0.5);

	//Check if output is linear
	if(!output_In_dB)
		return currentValue;

	if (currentValue <= 0)
		return -96.0;

	//If output is in dB...
	return 20*(std::log10(currentValue));
}

template <typename SampleType>
void EnvelopeDetector<SampleType>::setAttackTime(SampleType newValue)
{
	attackTimeCoeff = std::exp(rc_atc / (newValue * sampleRate * 0.001));
}

template <typename SampleType>
SampleType EnvelopeDetector<SampleType>::getAttackTime()
{
	return attackTime;
}

template <typename SampleType>
void EnvelopeDetector<SampleType>::setReleaseTime(SampleType newValue)
{
	releaseTimeCoeff = std::exp(rc_atc / (newValue * sampleRate * 0.001));
}

template <typename SampleType>
SampleType EnvelopeDetector<SampleType>::getReleaseTime()
{
	return releaseTimeCoeff;
}

template <typename SampleType>
void EnvelopeDetector<SampleType>::setDetectionMode(int index)
{
	switch(index)
	{
		case DetectionModes::Peak:
			detectionMode = DetectionModes::Peak;
			break;
		case DetectionModes::MS:
			detectionMode = DetectionModes::MS;
			break;
		case DetectionModes::RMS:
			detectionMode = DetectionModes::RMS;
			break;
		default:
			detectionMode = DetectionModes::Peak;
	}
}

template <typename SampleType>
int EnvelopeDetector<SampleType>::getDetectionMode()
{
	return detectionMode;
}

template <typename SampleType>
void EnvelopeDetector<SampleType>::setOutputIndB(bool outputIndB)
{
	output_In_dB = outputIndB;
}

template <typename SampleType>
bool EnvelopeDetector<SampleType>::isOutputIndB()
{
	return output_In_dB;
}

template <typename SampleType>
void EnvelopeDetector<SampleType>::setSampleRate(SampleType sampleRate)
{
	this->sampleRate = sampleRate;
	setAttackTime(attackTime);
	setReleaseTime(releaseTime);
}

template class EnvelopeDetector<float>;
template class EnvelopeDetector<double>;