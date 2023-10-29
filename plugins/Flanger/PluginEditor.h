#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>
#include <utils/custom_juce_classes/LevelMeter.h>

//==============================================================================
/**
*/
class FlangerPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FlangerPluginAudioProcessorEditor (FlangerPluginAudioProcessor&);
    ~FlangerPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void setMeters();

private:
    
    std::unique_ptr<juce::Slider> rateSlider, depthSlider, mixSlider, levelSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAtt, depthSliderAtt, mixSliderAtt, levelSliderAtt;
    
    GUIGraphics graphics{ GUIGraphics::EffectTypes::Flanger };
    LevelMeter inputMeter, outputMeter;

    FlangerPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerPluginAudioProcessorEditor)
};
