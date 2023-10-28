#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>
#include <utils/custom_juce_classes/LevelMeter.h>


//==============================================================================
/**
*/
class DelayPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DelayPluginAudioProcessorEditor (DelayPluginAudioProcessor&);
    ~DelayPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    std::unique_ptr<juce::Slider> delayLengthSlider, feedbackSlider, mixSlider, levelSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayLengthSliderAtt, feedbackSliderAtt, mixSliderAtt, levelSliderAtt;
    
    GUIGraphics graphics{ GUIGraphics::EffectTypes::Delay };
    LevelMeter inputMeter, outputMeter;

    DelayPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayPluginAudioProcessorEditor)
};
