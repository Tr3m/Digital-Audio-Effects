#pragma once

#include "PluginProcessor.h"
#include <GUIGraphics.h>

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

private:
    std::unique_ptr<juce::Slider> roomSizeSlider, decaySlider, mixSlider, filterSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeSliderAtt, decaySliderAtt, mixSliderAtt, filterSliderAtt;

    juce::Label lengthLabel, feedbackLabel, wetLabel, dryLabel, filterLabel;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Reverb };

    ReverbPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbPluginAudioProcessorEditor)
};
