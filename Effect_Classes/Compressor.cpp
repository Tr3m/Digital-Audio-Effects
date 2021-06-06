#include "Compressor.h" 

Compressor::Compressor()
{

}

void Compressor::prepare(double _sampleRate)
{
	detector.prepare(_sampleRate);
	detector.setOutputIndB(true);
}

double Compressor::processSample(double sample)
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

double Compressor::calaculateGain(double input)
{
	double output = 0.0;

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

	double gainReduction_dB = output - input;
	double gainReduction_Linear = std::pow(10.0, (gainReduction_dB) / 20.0);

	return gainReduction_Linear;
}

void Compressor::setParameter(int index, double newValue)
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
	case Parameters::Ratio:

		ratio = newValue;

		//Bounds Check
		if (ratio > 100.0)
			ratio = 100.0;
		if (ratio < 1.0)
			ratio = 1.0;
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

double Compressor::getParameter(int index)
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

void Compressor::setKneeType(int index)
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

int Compressor::getKneeType()
{
	return kneeType;
}

double Compressor::decibelToLinear(double dbValue)
{
	return powf(10.0, dbValue / 20.0);
}