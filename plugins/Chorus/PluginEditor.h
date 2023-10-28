#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>

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

private:

    std::unique_ptr<juce::Slider> rateSlider, depthSlider, wetSlider, drySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAtt, depthSliderAtt, wetSliderAtt, drySliderAtt;  

    ChorusPluginAudioProcessor& audioProcessor;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Chorus };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusPluginAudioProcessorEditor)
};
