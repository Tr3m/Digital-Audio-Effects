#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbPluginAudioProcessorEditor::ReverbPluginAudioProcessorEditor (ReverbPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    inputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextInput();}),
    outputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextOutput();})
{    
    setSize (370, 470);

    graphics.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));

    setMeters();

    roomSizeSlider.reset(new juce::Slider("RoomSizeSlider"));
    roomSizeSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    roomSizeSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(roomSizeSlider.get());
    roomSizeSlider->setLookAndFeel(&graphics);

    roomSizeSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "ROOM_SIZE_ID", *roomSizeSlider);  

    decaySlider.reset(new juce::Slider("decaySlider"));
    decaySlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    decaySlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(decaySlider.get());
    decaySlider->setLookAndFeel(&graphics);
    
    decaySliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "DECAY_ID", *decaySlider);  

    mixSlider.reset(new juce::Slider("mixSlider"));
    mixSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mixSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    mixSlider->setTextValueSuffix(" %");
    addAndMakeVisible(mixSlider.get());
    mixSlider->setLookAndFeel(&graphics);  

    mixSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "MIX_ID", *mixSlider);  

    filterSlider.reset(new juce::Slider("filterSlider"));
    filterSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    filterSlider->setTextValueSuffix(" Hz");
    addAndMakeVisible(filterSlider.get());
    filterSlider->setLookAndFeel(&graphics);

    filterSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "FILTER_ID", *filterSlider);

    levelSlider.reset(new juce::Slider("LevelSlider"));
    levelSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    levelSlider->setTextValueSuffix(" dB");
    addAndMakeVisible(levelSlider.get());
    levelSlider->setLookAndFeel(&graphics);

    filterSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "LEVEL_ID", *levelSlider);


    int knobSize = 133;
    int knobSizeSmall = 111;

    roomSizeSlider->setBounds(40, 107, knobSize, knobSize);
    decaySlider->setBounds(198, 63, knobSize, knobSize);
    
    mixSlider->setBounds(19, 328, knobSizeSmall, knobSizeSmall);
    filterSlider->setBounds(132, 291, knobSizeSmall, knobSizeSmall);
    levelSlider->setBounds(247, 250, knobSizeSmall, knobSizeSmall);
   
}

ReverbPluginAudioProcessorEditor::~ReverbPluginAudioProcessorEditor()
{
    roomSizeSliderAtt = nullptr;
    decaySliderAtt = nullptr;
    mixSliderAtt = nullptr;
    filterSliderAtt = nullptr;
    levelSliderAtt = nullptr;
}

//==============================================================================
void ReverbPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void ReverbPluginAudioProcessorEditor::resized()
{
    
}

void ReverbPluginAudioProcessorEditor::setMeters()
{
    addAndMakeVisible(&inputMeter);
    addAndMakeVisible(&outputMeter);

    inputMeter.setMeterColour(juce::Colours::ivory);
    outputMeter.setMeterColour(juce::Colours::ivory);
    inputMeter.setBackgroundColour(juce::Colours::transparentBlack);
    outputMeter.setBackgroundColour(juce::Colours::transparentBlack);

    inputMeter.setBounds(13, getHeight() / 2 + 13, 6, 195);
    outputMeter.setBounds(getWidth() - 17, 24, 6, 195);
}