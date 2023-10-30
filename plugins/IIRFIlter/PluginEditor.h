#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>
#include <utils/custom_juce_classes/LevelMeter.h>
#include <utils/custom_juce_classes/AssetManager.h>

//==============================================================================
/**
*/
class IirfilterPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    IirfilterPluginAudioProcessorEditor (IirfilterPluginAudioProcessor&);
    ~IirfilterPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void setMeters();
    void updateButtons();
    void setGainKnob();

    enum FilterTypes
	{
		LPF = 0,	// Low Pass Fitler
		HPF,		// High Pass Filter
		Parametric,
	};

private:
    
    std::unique_ptr<juce::Slider> freqSlider, levelSlider, gainSlider, filterTypeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqSliderAtt, levelSliderAtt, gainSliderAtt, filterTypeSliderAtt;

    std::unique_ptr<juce::ImageButton> lpButton, hpButton, parButton;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Filter };
    AssetManager assetManager;

    LevelMeter inputMeter, outputMeter;

    juce::TooltipWindow tooltipWindow{ this, 200 };

    IirfilterPluginAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IirfilterPluginAudioProcessorEditor)
};
