#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>
#include <utils/custom_juce_classes/LevelMeter.h>
#include <utils/custom_juce_classes/AssetManager.h>

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

    void setMeters();
    void updateButtons();

private:
    
    std::unique_ptr<juce::Slider> thresholdSlider, ratioSlider, attackSlider, releaseSilder, gainSlider, kneeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdSliderAtt, ratioSliderAtt, attackSliderAtt, releaseSilderAtt, gainSliderAtt, kneeSliderAtt;

    std::unique_ptr<juce::ImageButton> hardKnee, softKnee;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Compressor };
    GUIGraphics graphicsSmalll{ GUIGraphics::EffectTypes::Compressor, true };
    AssetManager assetManager;

    LevelMeter inputMeter, outputMeter;

    juce::TooltipWindow tooltipWindow{ this, 200 };

    CompressorPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorPluginAudioProcessorEditor)
};
