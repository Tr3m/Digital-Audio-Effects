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
class LimiterPluginAudioProcessorEditor  : public juce::AudioProcessorEditor, 
                                           public juce::Slider::Listener
{
public:
    LimiterPluginAudioProcessorEditor (LimiterPluginAudioProcessor&);
    ~LimiterPluginAudioProcessorEditor() override;
    void sliderValueChanged(juce::Slider* slider);

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider thresholdSlider, attackSlider, releaseSilder, gainSlider;
    juce::TextButton hardKnee, softKnee;
    GUIGraphics graphics{ GUIGraphics::EffectTypes::Limiter };


    LimiterPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LimiterPluginAudioProcessorEditor)
};
