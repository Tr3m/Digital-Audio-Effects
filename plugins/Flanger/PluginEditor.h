#pragma once

#include "PluginProcessor.h"
#include <GUIGraphics.h>

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

private:
    
    std::unique_ptr<juce::Slider> rateSlider, depthSlider, wetSlider, drySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAtt, depthSliderAtt, wetSliderAtt, drySliderAtt;
    
    GUIGraphics graphics{ GUIGraphics::EffectTypes::Flanger };

    FlangerPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerPluginAudioProcessorEditor)
};
