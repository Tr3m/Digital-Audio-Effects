#include "Vibrado.h"

Vibrado::Vibrado()
{
	delayLine_L.setParameter(Delay::Parameters::wetMixParam, 1.0);
	delayLine_L.setParameter(Delay::Parameters::dryMixParam, 0.0);
	delayLine_L.setParameter(Delay::Parameters::feedbackParam, 0.0f);
	delayLine_L.setParameter(Delay::Parameters::delayLengthParam, 0.007);

	delayLine_R.setParameter(Delay::Parameters::wetMixParam, 1.0);
	delayLine_R.setParameter(Delay::Parameters::dryMixParam, 0.0);
	delayLine_R.setParameter(Delay::Parameters::feedbackParam, 0.0f);
	delayLine_R.setParameter(Delay::Parameters::delayLengthParam, 0.007);

	lfo.setWaveformType(lfoType);
	lfo.setFrequency(rate);
}

void Vibrado::prepare(double sampleRate, int samplesPerBlock)
{
	delayLine_L.prepare(sampleRate, samplesPerBlock);
	delayLine_R.prepare(sampleRate, samplesPerBlock);
	lfo.prepare(sampleRate);
}

void Vibrado::process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels)
{
	double modDepth = depth / 100.0f;
	double modMin = minDelay;
	double modMax = minDelay + maxDelay;



	auto* channelDataLeft = buffer.getWritePointer(0);
	auto* channelDataRight = buffer.getWritePointer(1);

	for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
	{
		lfo.generateOutputSample();

		double newDelayTime = doUnipolarModulationFromMin(bipolarToUnipolar(modDepth * lfo.getOutputSample(LFO::PhaseTypes::Normal)), modMin, modMax);


		channelDataLeft[sample] = delayLine_L.processSample(channelDataLeft[sample], 0) * decibelToLinear(level_dB);
		delayLine_L.setParameter(Delay::Parameters::delayLengthParam, newDelayTime);

		channelDataRight[sample] = delayLine_R.processSample(channelDataRight[sample], 0) * decibelToLinear(level_dB);
		delayLine_R.setParameter(Delay::Parameters::delayLengthParam, newDelayTime);
	}

	
}

void Vibrado::setParameter(int index, float newValue)
{
	switch (index)
	{
	case Parameters::Rate:
		rate = newValue;

		//Bounds Check
		if (rate < 0.1)
			rate = 0.1;
		if (rate > 10.0)
			rate = 10.0;

		lfo.setFrequency(rate);

		break;

	case Parameters::Depth:
		depth = newValue;

		//Bounds Check
		if (depth > 100.0)
			depth = 100.0;
		if (depth < 0.0)
			depth = 0.0;

		break;

	case Parameters::Level:
		level_dB = newValue;
		
		float level_dBBounds = 12.0;

		//Bounds Check
		if (level_dB > level_dBBounds)
			level_dB = level_dBBounds;
		if (level_dB < -level_dBBounds)
			level_dB = -level_dBBounds;

		break;

	}
}

float Vibrado::getParameter(int index)
{
	switch (index)
	{
	case Parameters::Rate:
		return rate;
		break;
	case Parameters::Depth:
		return depth;
		break;
	case Parameters::Level:
		return level_dB;
		break;
	}
}

void Vibrado::setLFOType(int type)
{
	switch (type)
	{
	case LFO_Types::Triangle:
		lfoType = LFO_Types::Triangle;
		lfo.setWaveformType(LFO::WaveformTypes::Triangle);
		break;
	case LFO_Types::Sine:
		lfoType = LFO_Types::Sine;
		lfo.setWaveformType(LFO::WaveformTypes::Sine);
		break;
	case LFO_Types::Saw:
		lfoType = LFO_Types::Saw;
		lfo.setWaveformType(LFO::WaveformTypes::Saw);
		break;
	}

}

int Vibrado::getLFOType()
{
	return lfoType;
}

double Vibrado::doUnipolarModulationFromMin(double unipolarModulatorValue, double minValue, double maxValue)
{
	// --- UNIPOLAR bound
	unipolarModulatorValue = fmin(unipolarModulatorValue, 1.0f);
	unipolarModulatorValue = fmax(unipolarModulatorValue, 0.0f);

	// --- modulate from minimum value upwards
	return unipolarModulatorValue * (maxValue - minValue) + minValue;
}

double Vibrado::bipolarToUnipolar(double value)
{
	return 0.5 * value + 0.5;
}

float Vibrado::decibelToLinear(float dbValue)
{
	return powf(10.0, dbValue / 20.0);
}

