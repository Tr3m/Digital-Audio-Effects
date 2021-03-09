#include "IIRFilter.h"


IIRFilter::IIRFilter(double sampleRate)
{
	setCutoff(400.0f);
	last_SampleRate = sampleRate;
	filterType = 0;	//Initialize as LPF
	Q = 0.707;

	calculateCoeffs(fc, sampleRate);
}

IIRFilter::IIRFilter(double sampleRate, int type)
{
	setCutoff(400.0f);
	last_SampleRate = sampleRate;
	setFilterType(type);
	Q = 0.707;

	calculateCoeffs(fc, sampleRate);
}

IIRFilter::IIRFilter(double sampleRate, int type, float freq)
{
	setCutoff(freq);
	last_SampleRate = sampleRate;
	setFilterType(type);
	Q = 0.707;

	calculateCoeffs(fc, sampleRate);
}

void IIRFilter::calculateCoeffs(float freq, double sampleRate)
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
			a2 = a0;
			b1 = 2.0f * a0 * (C * C - 1.0f);
			b2 = a0 * (1.0f - r * C + C * C);
			c0 = 1.0f;
			d0 = 0.0;
			break;

		case FilterTypes::Parametric :
			K = tan(m_pi*freq/float(sampleRate));
			V0 = std::pow(10, notchGain / 20);
			D0 = 1 + (K/Q)+K*K;
			e0 = 1 + (K/(V0*Q)) + K*K;
			alpha = 1 + ((V0*K) / Q) + K*K;
			beta = 2*(K*K - 1);
			gamma = 1 - ((V0*K) / Q) + K*K;
			delta = 1 - (K / Q) + K*K;
			heta = 1 - (K / V0*Q) + K*K;

			if(notchGain >= 0)
			{
				//Calcualte boost coefficients

				a0 = alpha/D0;
				a1 = beta/D0;
				a2 = gamma/D0;
				b1 = beta/D0;
				b2 = delta/D0;
				c0 = 1.0f;
				d0 = 0.0f;

			}else
			{
				//Calculate cut coefficients

				a0 = D0/e0;
				a1 = beta/e0;
				a2 = delta/e0;
				b1 = beta/e0;
				b2 = heta/e0;
				c0 = 1.0f;
				d0 = 0.0f;

			}
			break;
	}
		

	
	//std::string log = "a0 = " + std::to_string(a0) + "\na1 = " + std::to_string(a1) + "\na1 = " + std::to_string(a2) + "\na2 = " + std::to_string(a2)
		//+ "\nb1 = " + std::to_string(b1) + "\nb2 = " + std::to_string(b2) + "\nSample Rate = " + std::to_string(m_SampleRate) + "\nC = " + std::to_string(C);

	//DBG(log);
}

void IIRFilter::prepare(double sampleRate, int samplesPerBlock)
{
	calculateCoeffs(fc, sampleRate);	
	last_SampleRate = sampleRate;	
}

void IIRFilter::process(juce::AudioBuffer<float>& buffer, int channel, double sampleRate)
{
	last_SampleRate = sampleRate;

	calculateCoeffs(fc, sampleRate);

	
	
	auto* channelData = buffer.getWritePointer(channel);

		

	for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
	{
			

		auto yn = a0 * channelData[sample] + a1 * xn_1 + a2 * xn_2 - b1 * yn_1 - b2 * yn_2;
			

		xn_2 = xn_1;
		xn_1 = channelData[sample];

		yn_2 = yn_1;
		yn_1 = yn;

		channelData[sample] = yn;
	}
	
}

void IIRFilter::setCutoff(float newValue)
{
	if (newValue < 20.0f)
		fc = 20.0f;
	else if (newValue > 20000.0f)
		fc = 20000.0f;
	else
		fc = newValue;

	calculateCoeffs(fc, last_SampleRate);
}

float IIRFilter::getCutoff()
{
	return fc;
}

void IIRFilter::setFilterType(int type)
{
	if (type < 0)
		type = 0;
	else if (type > 3)
		type = 3;

	filterType = type;

	calculateCoeffs(fc, last_SampleRate);
}

void IIRFilter::setQ(float newValue)
{
	float this_q = newValue;

	if (this_q > 20.0)
		this_q = 20.0;
	else if (this_q < 0.2)
		this_q = 0.2;

	Q = this_q;

	calculateCoeffs(fc, last_SampleRate);
}

float IIRFilter::getQ()
{
	return Q;
}

void IIRFilter::setGain(float newValue)
{
	notchGain = newValue;
}

float IIRFilter::getGain()
{
	return notchGain;
}

int IIRFilter::getFilterType()
{
	return filterType;
}