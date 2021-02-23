#include "iirFilter.h"


iirFilter::iirFilter(double sampleRate)
{
	fc = 400.0f;
	last_SampleRate = sampleRate;
	filterType = 0;	//Initialize as LPF
	Q = 0.707;

	calculateCoeffs(fc, sampleRate);
}

iirFilter::iirFilter(double sampleRate, int type)
{
	fc = 400.0f;
	last_SampleRate = sampleRate;
	filterType = type;
	Q = 0.707;

	calculateCoeffs(fc, sampleRate);
}

void iirFilter::calculateCoeffs(float freq, double sampleRate)
{
	switch (filterType)
	{
		case FilterTypes::LPF : //2nd Order Butterworth LPF
			r = std::sqrt(2);
			C = float(1.0f / tan(m_pi * freq / (float)sampleRate));
			a0 = 1.0f / (1.0f + r * C + C * C);
			a1 = 2 * a0;
			a2 = a0;
			b1 = 2.0f * a0 * (1.0f - C * C);
			b2 = a0 * (1.0f - r * C + C * C);
			c0 = 1.0f;
			d0 = 0.0;
			break;

		case FilterTypes::HPF : //2nd Order Butterworth HPF
			r = std::sqrt(2);
			C = float(tan(m_pi * freq / (float)sampleRate));
			a0 = 1.0f / (1.0f + r * C + C * C);
			a1 = -2 * a0;
			a2 = a1;
			b1 = 2.0f * a0 * (C * C - 1.0f);
			b2 = a0 * (1.0f - r * C + C * C);
			c0 = 1.0f;
			d0 = 0.0;
			break;
	}
		

	
	//std::string log = "a0 = " + std::to_string(a0) + "\na1 = " + std::to_string(a1) + "\na1 = " + std::to_string(a2) + "\na2 = " + std::to_string(a2)
		//+ "\nb1 = " + std::to_string(b1) + "\nb2 = " + std::to_string(b2) + "\nSample Rate = " + std::to_string(m_SampleRate) + "\nC = " + std::to_string(C);

	//DBG(log);
}

void iirFilter::prepare(double sampleRate, int samplesPerBlock)
{
	calculateCoeffs(fc, sampleRate);	
	last_SampleRate = sampleRate;	
}

void iirFilter::process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels, double sampleRate)
{
	last_SampleRate = sampleRate;

	calculateCoeffs(fc, sampleRate);

	
	for(int channel = 0; channel < numOutputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);

		

		for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			

			float yn = a0 * channelData[sample] + a1 * xn_1 + a2 * xn_2 - b1 * yn_1 - b2 * yn_2;
			

			xn_2 = xn_1;
			xn_1 = channelData[sample];

			yn_2 = yn_1;
			yn_1 = yn;

			channelData[sample] = yn;
		}
	}
}

void iirFilter::setCutoff(float newValue)
{
	fc = newValue;

	calculateCoeffs(fc, last_SampleRate);
}

float iirFilter::getCutoff()
{
	return fc;
}

void iirFilter::setFilterType(int type)
{
	if (type < 0)
		type = 0;
	else if (type > 3)
		type = 3;

	filterType = type;

	calculateCoeffs(fc, last_SampleRate);
}

void iirFilter::setQ(float newValue)
{
	float this_q = newValue;

	if (this_q > 20.0)
		this_q = 20.0;
	else if (this_q < 0.2)
		this_q = 0.2;

	Q = this_q;

	calculateCoeffs(fc, last_SampleRate);
}

float iirFilter::getQ()
{
	return Q;
}