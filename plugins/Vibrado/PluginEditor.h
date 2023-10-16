/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include <GUIGraphics.h>

//==============================================================================
/**
*/
class VibradoPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                           public juce::Slider::Listener                                        
{
public:
    VibradoPluginAudioProcessorEditor (VibradoPluginAudioProcessor&);
    ~VibradoPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider);
    

private:
   
    juce::Slider rateSlider, depthSlider, levelSlider;
    juce::TextButton sineButton, triangleButton, sawButton;

    VibradoPluginAudioProcessor& audioProcessor;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Vibrado };

    juce::TooltipWindow tooltipWindow{ this, 200 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibradoPluginAudioProcessorEditor)
};
