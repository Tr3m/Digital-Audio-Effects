#include "Delay.h"

Delay::Delay()
{
	// set default values
    delayLength = 0.5;
    dryMix = 1.0;
    wetMix = 0.5;
    feedback = 0.35;
    delayBufferLength = 1;

    delayReadPosition = 0;
    delayWritePosition = 0;

    //m_SampleRate = sampleRate;
}

Delay::Delay(float _delayLength, float _feedback, float _wet, float _dry)
{
    //TODO: Add bounds check...
    
    delayLength = _delayLength;
    dryMix = _dry;
    wetMix = _wet;
    feedback = _feedback;
    delayBufferLength = 1;

    delayReadPosition = 0;
    delayWritePosition = 0;
}


float Delay::getParameter(int index)
{
    switch (index) {
    case dryMixParam:
        return dryMix;
    case wetMixParam:
        return wetMix;
    case feedbackParam:
        return feedback;
    case delayLengthParam:
        return delayLength;
    default:
        return 0.0f;
    }
}

void Delay::setParameter(int index, float newValue)
{
    switch (index) {
    case dryMixParam:
        dryMix = newValue;
        break;
    case wetMixParam:
        wetMix = newValue;
        break;
    case feedbackParam:
        feedback = newValue;
        break;
    case delayLengthParam:
        delayLength = newValue;
        delayReadPosition = (int)(delayWritePosition - (delayLength * m_SampleRate) + delayBufferLength) % delayBufferLength;
        break;
    default:
        break;;
    }
}



void Delay::prepare(double sampleRate, int samplesPerBlock)
{
    m_SampleRate = sampleRate;

	delayBufferLength = (int)2.0 * sampleRate;
    if (delayBufferLength < 1)
        delayBufferLength = 1;

    delayBuffer.setSize(2, delayBufferLength);
    delayBuffer.clear();

    delayReadPosition = (int)(delayWritePosition - (delayLength * sampleRate) + delayBufferLength) % delayBufferLength;
}

void Delay::process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels)
{
    const int numSamples = buffer.getNumSamples();

    int dpr, dpw;

    for (int channel = 0; channel < numInputChannels; ++channel) {
        float* channelData = buffer.getWritePointer(channel);
        float* delayData = delayBuffer.getWritePointer(juce::jmin(channel, delayBuffer.getNumChannels() - 1));

        dpr = delayReadPosition;
        dpw = delayWritePosition;

        for (int i = 0; i < numSamples; ++i) {
            const float in = channelData[i];
            float out = 0.0;

            out = (dryMix * in + wetMix * delayData[dpr]);

            delayData[dpw] = in + (delayData[dpr] * feedback);

            if (++dpr >= delayBufferLength)
                dpr = 0;
            if (++dpw >= delayBufferLength)
                dpw = 0;

            channelData[i] = out;
        }
    }

    delayReadPosition = dpr;
    delayWritePosition = dpw;

}