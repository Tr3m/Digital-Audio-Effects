#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>
#include <utils/custom_juce_classes/LevelMeter.h>

//==============================================================================
/**
*/
class ChorusPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ChorusPluginAudioProcessorEditor (ChorusPluginAudioProcessor&);
    ~ChorusPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void setMeters();


private:

    std::unique_ptr<juce::Slider> rateSlider, depthSlider, mixSlider, levelSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAtt, depthSliderAtt, mixSliderAtt, levelSliderAtt;  

    ChorusPluginAudioProcessor& audioProcessor;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Chorus };
    LevelMeter inputMeter, outputMeter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusPluginAudioProcessorEditor)
};
