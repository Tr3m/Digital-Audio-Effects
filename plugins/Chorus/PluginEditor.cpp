#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChorusPluginAudioProcessorEditor::ChorusPluginAudioProcessorEditor (ChorusPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{ 
    setSize(370, 470);

    //Rate Slider
    rateSlider.reset(new juce::Slider("RateSlider"));
    rateSlider->setSliderStyle(juce::Slider::Rotary);
    rateSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    rateSlider->setTextValueSuffix(" Hz");
    rateSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(rateSlider.get());    

    rateSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "RATE_ID", *rateSlider);

    //Depth Slider
    depthSlider.reset(new juce::Slider("DepthSlider"));
    depthSlider->setSliderStyle(juce::Slider::Rotary);
    depthSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    depthSlider->setTextValueSuffix(" %");
    depthSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(depthSlider.get());

    depthSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "DEPTH_ID", *depthSlider);

    //Wet Slider
    wetSlider.reset(new juce::Slider("WetSlider"));
    wetSlider->setSliderStyle(juce::Slider::Rotary);
    wetSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    wetSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(wetSlider.get()); 
    
    wetSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "WET_ID", *wetSlider);

    //Dry Slider
    drySlider.reset(new juce::Slider("DrySlider"));
    drySlider->setSliderStyle(juce::Slider::Rotary);
    drySlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    drySlider->setLookAndFeel(&graphics);
    addAndMakeVisible(drySlider.get());     

    drySliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "DRY_ID", *drySlider);

    rateSlider->setBounds(44, 91, 124, 124);
    depthSlider->setBounds(198, 91, 124, 124);
    wetSlider->setBounds(44, 252, 124, 124);
    drySlider->setBounds(198, 252, 124, 124);
}

ChorusPluginAudioProcessorEditor::~ChorusPluginAudioProcessorEditor()
{
    rateSliderAtt = nullptr;
    depthSliderAtt = nullptr;
    wetSliderAtt = nullptr;
    drySliderAtt = nullptr;
}

//==============================================================================
void ChorusPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
  
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void ChorusPluginAudioProcessorEditor::resized()
{
    
}
