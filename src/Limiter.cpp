#include "Limiter.h"

Limiter::Limiter()
{

}

void Limiter::prepare(double _sampleRate)
{
	detector.prepare(_sampleRate);
	detector.setOutputIndB(true);
}

double Limiter::processSample(double sample)
{
	double xn = sample;
	double detect_input = 0.0;

	detect_input = detector.processSample(xn);

	//Gain Reduction Calculation
	double gainReduction = calaculateGain(detect_input);

	//MakeupGain
	double muGain = decibelToLinear(makeupGain);

	return xn * gainReduction * muGain;

}

double Limiter::calaculateGain(double input)
{
	double output = 0.0;

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

	double gainReduction_dB = output - input;
	double gainReduction_Linear = std::pow(10.0, (gainReduction_dB) / 20.0);

	return gainReduction_Linear;
}

void Limiter::setParameter(int index, double newValue)
{
	switch (index)
	{
	case Parameters::Threshold:

		threshold = newValue;

		//Bounds Check
		if (threshold > 0.0)
			threshold = 0.0;
		if (threshold < -80.0)
			threshold = -80.0;
		break;

	case Parameters::Attack:

		attack = newValue;

		//Bounds Check
		if (attack > 100.0)
			attack = 100.0;
		if (attack < 1.0)
			attack = 1.0;

		detector.setAttackTime(attack);

		break;
	case Parameters::Release:

		release = newValue;

		//Bounds Check
		if (release > 1000.0)
			release = 1000.0;
		if (release < 10.0)
			release = 10.0;

		detector.setReleaseTime(release);

		break;
	case Parameters::MakeupGain:

		makeupGain = newValue;
		break;
	}
}

double Limiter::getParameter(int index)
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

void Limiter::setKneeType(int index)
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

int Limiter::getKneeType()
{
	return kneeType;
}

double Limiter::decibelToLinear(double dbValue)
{
	return powf(10.0, dbValue / 20.0);
}