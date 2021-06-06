/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "../../Effect_Classes/GUIGraphics.h"

//==============================================================================
/**
*/
class CompressorPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              public juce::Slider::Listener
{
public:
    CompressorPluginAudioProcessorEditor (CompressorPluginAudioProcessor&);
    ~CompressorPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void initializeSlider(juce::Slider&);
    void sliderValueChanged(juce::Slider* slider);

private:
    
    juce::Slider thresholdSlider, ratioSlider, attackSlider, releaseSilder, gainSlider;
    juce::TextButton hardKnee, softKnee;
    GUIGraphics graphics{ GUIGraphics::EffectTypes::Compressor };

    CompressorPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorPluginAudioProcessorEditor)
};
