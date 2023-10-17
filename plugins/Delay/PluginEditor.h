#pragma once

#include "PluginProcessor.h"
#include <GUIGraphics.h>


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

    std::unique_ptr<juce::Slider> delayLengthSlider, feedbackSlider, dryMixSlider, wetMixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayLengthSliderAtt, feedbackSliderAtt, dryMixSliderAtt, wetMixSliderAtt;
    
    GUIGraphics graphics{ GUIGraphics::EffectTypes::Delay };

    DelayPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayPluginAudioProcessorEditor)
};
