#pragma once

#include "PluginProcessor.h"
#include <GUIGraphics.h>

//==============================================================================
/**
*/
class DistortionPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor&);
    ~DistortionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    std::unique_ptr<juce::Slider> gainSlider, levelSlider, filterSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAtt, levelSliderAtt, filterSliderAtt;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Distortion };

    DistortionPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPluginAudioProcessorEditor)
};
