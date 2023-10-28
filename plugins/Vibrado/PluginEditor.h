#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>

//==============================================================================
/**
*/
class VibradoPluginAudioProcessorEditor  : public juce::AudioProcessorEditor                                      
{
public:
    VibradoPluginAudioProcessorEditor (VibradoPluginAudioProcessor&);
    ~VibradoPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;    

private:
   
    std::unique_ptr<juce::Slider> rateSlider, depthSlider, levelSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAtt, depthSliderAtt, levelSliderAtt;

    juce::TextButton sineButton, triangleButton, sawButton;

    VibradoPluginAudioProcessor& audioProcessor;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Vibrado };

    juce::TooltipWindow tooltipWindow{ this, 200 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibradoPluginAudioProcessorEditor)
};
