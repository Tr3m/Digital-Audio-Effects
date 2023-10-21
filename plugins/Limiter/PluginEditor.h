#pragma once

#include "PluginProcessor.h"
#include <GUIGraphics.h>
//==============================================================================
/**
*/
class LimiterPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LimiterPluginAudioProcessorEditor (LimiterPluginAudioProcessor&);
    ~LimiterPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    std::unique_ptr<juce::Slider> thresholdSlider, attackSlider, releaseSilder, gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdSliderAtt, attackSliderAtt, releaseSilderAtt, gainSliderAtt;

    juce::TextButton hardKnee, softKnee;
    
    GUIGraphics graphics{ GUIGraphics::EffectTypes::Limiter };

    LimiterPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LimiterPluginAudioProcessorEditor)
};
