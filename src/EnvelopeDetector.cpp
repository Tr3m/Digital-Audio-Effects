#include "EnvelopeDetector.h"

EnvelopeDetector::EnvelopeDetector()
{
}

void EnvelopeDetector::prepare(double _sampleRate)
{
	setSampleRate(_sampleRate);
	previousValue = 0.0;
}

double EnvelopeDetector::processSample(double input)
{
	double xn = std::fabs(input);
	double currentValue = 0.0; //Envelope value for the current sample

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

void EnvelopeDetector::setAttackTime(double newValue)
{
	attackTimeCoeff = std::exp(rc_atc / (newValue * sampleRate * 0.001));
}

double EnvelopeDetector::getAttackTime()
{
	return attackTime;
}

void EnvelopeDetector::setReleaseTime(double newValue)
{
	releaseTimeCoeff = std::exp(rc_atc / (newValue * sampleRate * 0.001));
}

double EnvelopeDetector::getReleaseTime()
{
	return releaseTimeCoeff;
}

void EnvelopeDetector::setDetectionMode(int index)
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

int EnvelopeDetector::getDetectionMode()
{
	return detectionMode;
}

void EnvelopeDetector::setOutputIndB(bool _output_In_dB)
{
	output_In_dB = _output_In_dB;
}

bool EnvelopeDetector::isOutputIndB()
{
	return output_In_dB;
}

void EnvelopeDetector::setSampleRate(double m_SampleRate)
{
	sampleRate = m_SampleRate;
	setAttackTime(attackTime);
	setReleaseTime(releaseTime);
}