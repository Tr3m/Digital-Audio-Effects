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
class VibradoPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                           public juce::Slider::Listener,
                                           public juce::ComboBox::Listener
{
public:
    VibradoPluginAudioProcessorEditor (VibradoPluginAudioProcessor&);
    ~VibradoPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider);
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

private:
   
    juce::Slider rateSlider, depthSlider, levelSlider;
    juce::Label rateLabel, depthLabel, levelLabel, lfoLabel;
    juce::ComboBox lfoType;

    VibradoPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibradoPluginAudioProcessorEditor)
};
