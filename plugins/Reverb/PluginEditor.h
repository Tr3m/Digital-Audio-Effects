#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>
#include <utils/custom_juce_classes/LevelMeter.h>

//==============================================================================
/**
*/
class ReverbPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ReverbPluginAudioProcessorEditor (ReverbPluginAudioProcessor&);
    ~ReverbPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void setMeters();

private:
    std::unique_ptr<juce::Slider> roomSizeSlider, decaySlider, mixSlider, filterSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeSliderAtt, decaySliderAtt, mixSliderAtt, filterSliderAtt;

    juce::Label lengthLabel, feedbackLabel, wetLabel, dryLabel, filterLabel;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Reverb };
    LevelMeter inputMeter, outputMeter;

    ReverbPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbPluginAudioProcessorEditor)
};
