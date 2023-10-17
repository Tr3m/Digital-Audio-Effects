#include "CombFilter.h"

CombFilter::CombFilter()
{
    // set default values
    delayLength = 0.5;
    feedback = 0.35;
    delayBufferLength = 1;

    delayReadPosition = 0;
    delayWritePosition = 0;

    //m_SampleRate = sampleRate;
}

CombFilter::CombFilter(float _delayLength, float _feedback)
{
    //TODO: Add bounds check...

    delayLength = _delayLength;
    feedback = _feedback;
    delayBufferLength = 1;

    delayReadPosition = 0;
    delayWritePosition = 0;
}


void CombFilter::setDelayLength(float newValue)
{
    //TODO: Add bounds check
    delayLength = newValue;
    delayReadPosition = (int)(delayWritePosition - (delayLength * m_SampleRate) + delayBufferLength) % delayBufferLength;
}

float CombFilter::getDelayLength()
{
    return delayLength;
}

void CombFilter::setFeedback(float newValue)
{
    feedback = newValue;
}

float CombFilter::getFeedback()
{
    return feedback;
}

void CombFilter::prepare(double sampleRate, int samplesPerBlock)
{
    m_SampleRate = sampleRate;

    delayBufferLength = (int)2.0 * sampleRate;
    if (delayBufferLength < 1)
        delayBufferLength = 1;

    delayBuffer.setSize(2, delayBufferLength);
    delayBuffer.clear();

    delayReadPosition = (int)(delayWritePosition - (delayLength * sampleRate) + delayBufferLength) % delayBufferLength;
}

void CombFilter::process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels)
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


            out =  delayData[dpr];

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


//Need to create two instances of the class to use this function (One for each buffer channel).
float CombFilter::processSample(float sample, int channel)
{
    float* delayData = delayBuffer.getWritePointer(juce::jmin(channel, delayBuffer.getNumChannels() - 1));

    int dpr, dpw;

    dpr = delayReadPosition;
    dpw = delayWritePosition;

    const float in = sample;
    float out = 0.0;

    out = (in + delayData[dpr]);

    delayData[dpw] = in + (delayData[dpr] * feedback);

    if (++dpr >= delayBufferLength)
        dpr = 0;
    if (++dpw >= delayBufferLength)
        dpw = 0;

    delayReadPosition = dpr;
    delayWritePosition = dpw;

    return out;
}