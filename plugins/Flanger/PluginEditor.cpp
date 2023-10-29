#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FlangerPluginAudioProcessorEditor::FlangerPluginAudioProcessorEditor (FlangerPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    inputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextInput();}),
    outputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextOutput();})
{
    setSize (370, 470);

    graphics.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));

    setMeters();

    //Rate Slider
    rateSlider.reset(new juce::Slider("RateSlider"));
    rateSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    rateSlider->setTextValueSuffix(" Hz");
    rateSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(rateSlider.get());    

    rateSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "RATE_ID", *rateSlider);

    //Depth Slider
    depthSlider.reset(new juce::Slider("DepthSlider"));
    depthSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    depthSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(depthSlider.get());

    depthSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "DEPTH_ID", *depthSlider);

    //Wet Slider
    mixSlider.reset(new juce::Slider("MixSlider"));
    mixSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mixSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    mixSlider->setTextValueSuffix(" %");
    mixSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(mixSlider.get()); 
    
    mixSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "MIX_ID", *mixSlider);

    //Level Slider
    levelSlider.reset(new juce::Slider("LevelSlider"));
    levelSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    levelSlider->setTextValueSuffix(" dB");
    levelSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(levelSlider.get());     

    levelSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "LEVEL_ID", *levelSlider);


    int knobSize = 133;

    rateSlider->setBounds(40, 107, knobSize, knobSize);
    depthSlider->setBounds(198, 63, knobSize, knobSize);
    mixSlider->setBounds(40, 283, knobSize, knobSize);
    levelSlider->setBounds(198, 234, knobSize, knobSize);

}

FlangerPluginAudioProcessorEditor::~FlangerPluginAudioProcessorEditor()
{
    rateSliderAtt = nullptr;
    depthSliderAtt = nullptr;
    mixSliderAtt = nullptr;
    levelSliderAtt = nullptr;
}

//==============================================================================
void FlangerPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void FlangerPluginAudioProcessorEditor::resized()
{
    
}

void FlangerPluginAudioProcessorEditor::setMeters()
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