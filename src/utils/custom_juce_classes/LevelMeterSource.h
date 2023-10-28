#pragma once
#include <utils/extras/GainUtilities.h>

class LevelMeterSource
{
public:
    
    LevelMeterSource()
    {

    }

    void prepare(double sampleRate)
    {
        inputLevel.reset(sampleRate, 0.5);
        outputLevel.reset(sampleRate, 0.5);

        inputLevel.setCurrentAndTargetValue(-100.0f);
        outputLevel.setCurrentAndTargetValue(-100.0f);
    }

    void updateInputLevel(juce::AudioBuffer<float>& buffer)
    {
        inputLevel.skip(buffer.getNumSamples());

        const auto value = GainUtilities<float>::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples())); 
        if(value < inputLevel.getCurrentValue())
            inputLevel.setTargetValue(value);
        else
            inputLevel.setCurrentAndTargetValue(value);
    }

    void updateOutputLevel(juce::AudioBuffer<float>& buffer)
    {
        outputLevel.skip(buffer.getNumSamples());

        const auto value = GainUtilities<float>::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
        if(value < outputLevel.getCurrentValue())
            outputLevel.setTargetValue(value);
        else
            outputLevel.setCurrentAndTargetValue(value);
    }

    float getNextInput()
    {
        return inputLevel.getCurrentValue();
    }

    float getNextOutput()
    {
        return outputLevel.getCurrentValue();;
    }
    
private:

    juce::LinearSmoothedValue<float> inputLevel, outputLevel;

};
