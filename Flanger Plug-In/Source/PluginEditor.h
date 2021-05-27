/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FlangerPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                           public juce::Slider::Listener
{
public:
    FlangerPluginAudioProcessorEditor (FlangerPluginAudioProcessor&);
    ~FlangerPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider);

private:
    
    juce::Slider rateSlider, depthSlider, wetSlider, drySlider;
    juce::Label rateLabel, depthLabel, wetLabel, dryLabel;

    FlangerPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerPluginAudioProcessorEditor)
};
