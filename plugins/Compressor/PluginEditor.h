#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>

//==============================================================================
/**
*/
class CompressorPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CompressorPluginAudioProcessorEditor (CompressorPluginAudioProcessor&);
    ~CompressorPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    std::unique_ptr<juce::Slider> thresholdSlider, ratioSlider, attackSlider, releaseSilder, gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdSliderAtt, ratioSliderAtt, attackSliderAtt, releaseSilderAtt, gainSliderAtt;

    juce::TextButton hardKnee, softKnee;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Compressor };

    CompressorPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorPluginAudioProcessorEditor)
};
