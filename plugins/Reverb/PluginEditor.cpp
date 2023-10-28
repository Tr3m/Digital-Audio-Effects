#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbPluginAudioProcessorEditor::ReverbPluginAudioProcessorEditor (ReverbPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{    
    setSize (370, 470);

    roomSizeSlider.reset(new juce::Slider("RoomSizeSlider"));
    roomSizeSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    roomSizeSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    addAndMakeVisible(roomSizeSlider.get());
    //roomSizeSlider->setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::length));
    roomSizeSlider->setLookAndFeel(&graphics);

    roomSizeSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "ROOM_SIZE_ID", *roomSizeSlider);  

    decaySlider.reset(new juce::Slider("decaySlider"));
    decaySlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    decaySlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    addAndMakeVisible(decaySlider.get());
    //decaySlider->setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::feedback));
    decaySlider->setLookAndFeel(&graphics);
    
    decaySliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "DECAY_ID", *decaySlider);  

    mixSlider.reset(new juce::Slider("mixSlider"));
    mixSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mixSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    addAndMakeVisible(mixSlider.get());
    //mixSlider->setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::wetMix));
    mixSlider->setLookAndFeel(&graphics);  

    mixSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "MIX_ID", *mixSlider);  

    filterSlider.reset(new juce::Slider("filterSlider"));
    filterSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    addAndMakeVisible(filterSlider.get());
    //filterSlider->setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::Filter));
    filterSlider->setLookAndFeel(&graphics);

    filterSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "FILTER_ID", *filterSlider);

    int smallSlider = 100;

    roomSizeSlider->setBounds(44, 91, 124, 124);
    decaySlider->setBounds(198, 91, 124, 124);
    mixSlider->setBounds(20, 266, smallSlider, smallSlider);
    filterSlider->setBounds(243, 266, smallSlider, smallSlider);
   
}

ReverbPluginAudioProcessorEditor::~ReverbPluginAudioProcessorEditor()
{
    roomSizeSliderAtt = nullptr;
    decaySliderAtt = nullptr;
    mixSliderAtt = nullptr;
    filterSliderAtt = nullptr;
}

//==============================================================================
void ReverbPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void ReverbPluginAudioProcessorEditor::resized()
{
    
}