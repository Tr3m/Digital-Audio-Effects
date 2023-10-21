#include "IIRFilter.h"

template <typename SampleType>
IIRFilter<SampleType>::IIRFilter()
{

}

template <typename SampleType>
IIRFilter<SampleType>::~IIRFilter()
{
	
}

template <typename SampleType>
void IIRFilter<SampleType>::prepare(SampleType sampleRate)
{
	this->sampleRate = sampleRate;
	calculateCoeffs();		
}

template <typename SampleType>
SampleType IIRFilter<SampleType>::processSample(SampleType input)
{
	auto yn = d0*input + c0*(a0 * input + a1 * xn_1 + a2 * xn_2 - b1 * yn_1 - b2 * yn_2);

	xn_2 = xn_1;
	xn_1 = input;

	yn_2 = yn_1;
	yn_1 = yn;

	return yn;
}

template <typename SampleType>
void IIRFilter<SampleType>::process(SampleType* data, int startSample, int endSample)
{
	for(int sample = startSample; sample < endSample; ++sample)
		data[sample] = processSample(data[sample]);
}

template <typename SampleType>
void IIRFilter<SampleType>::setCutoff(SampleType newValue)
{
	if (newValue < 20.0f)
		fc = 20.0f;
	else if (newValue > 20000.0f)
		fc = 20000.0f;
	else
		fc = newValue;

	calculateCoeffs();
}

template <typename SampleType>
SampleType IIRFilter<SampleType>::getCutoff()
{
	return fc;
}

template <typename SampleType>
void IIRFilter<SampleType>::setFilterType(int type)
{
	if (type < 0)
		type = 0;
	else if (type > 4)
		type = 4;

	filterType = type;

	calculateCoeffs();
}

template <typename SampleType>
int IIRFilter<SampleType>::getFilterType()
{
	return filterType;
}

template <typename SampleType>
void IIRFilter<SampleType>::setQ(SampleType newValue)
{
	SampleType this_q = newValue;

	if (this_q > 20.0)
		this_q = 20.0;
	else if (this_q < 0.2)
		this_q = 0.2;

	Q = this_q;

	calculateCoeffs();
}

template <typename SampleType>
SampleType IIRFilter<SampleType>::getQ()
{
	return Q;
}

template <typename SampleType>
void IIRFilter<SampleType>::setGain(SampleType newValue)
{
	notchGain = newValue;
	calculateCoeffs();
}

template <typename SampleType>
SampleType IIRFilter<SampleType>::getGain()
{
	return notchGain;
}

template <typename SampleType>
void IIRFilter<SampleType>::calculateCoeffs()
{
	switch (filterType)
	{
		case FilterTypes::LPF : //2nd Order Butterworth LPF
			r = std::sqrt(2);
			C = SampleType(1.0f / tan(PI * fc / (SampleType)this->sampleRate));
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
			C = SampleType(tan(PI * fc / (SampleType)this->sampleRate));
			a0 = 1.0f / (1.0f + r * C + C * C);
			a1 = -2 * a0;
			a2 = a0;
			b1 = 2.0f * a0 * (C * C - 1.0f);
			b2 = a0 * (1.0f - r * C + C * C);
			c0 = 1.0f;
			d0 = 0.0;
			break;

		case FilterTypes::Parametric :
			
			K = tan(PI*fc/SampleType(this->sampleRate));
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

			/*theta_c = (2 * PI * fc) / SampleType(this->sampleRate);
			u = std::pow(10, notchGain / 20);
			zeta = 4.0 / (1.0 + u);
			beta = 0.5 * (1.0f - (zeta * tan(theta_c / (2.0 * Q)))) / (1.0f + (zeta * tan(theta_c / (2.0 * Q))));
			gamma = (0.5 + beta) * cos(theta_c);

			a0 = 0.5 - beta;
			a1 = 0.0;
			a2 = beta - 0.5;
			b1 = -2.0 * gamma;
			b2 = 2.0 * beta;
			c0 = u - 1.0f;
			d0 = 1.0f;*/
			break;
		
	}
}

template class IIRFilter<float>;
template class IIRFilter<double>;