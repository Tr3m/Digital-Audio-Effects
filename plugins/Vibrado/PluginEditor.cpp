#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibradoPluginAudioProcessorEditor::VibradoPluginAudioProcessorEditor (VibradoPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    inputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextInput();}),
    outputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextOutput();})
{
    
    setSize(370, 470);

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

    //Level Slider
    levelSlider.reset(new juce::Slider("LevelSlider"));
    levelSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    levelSlider->setTextValueSuffix(" dB");
    levelSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(levelSlider.get()); 
    
    levelSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "LEVEL_ID", *levelSlider);

    lfoTypeSlider.reset(new juce::Slider("LfoType"));
    lfoTypeSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "LFO_TYPE_ID", *lfoTypeSlider);

    int knobSize = 133;
    rateSlider->setBounds(40, 107, knobSize, knobSize);
    depthSlider->setBounds(198, 63, knobSize, knobSize);
    levelSlider->setBounds(198, 234, knobSize, knobSize);

    sineButton.reset(new juce::ImageButton("SineButton"));
    addAndMakeVisible(sineButton.get());
    sineButton->setBounds(71, 283, 70, 40);
    sineButton->setTooltip("Sine");
    sineButton->onClick = [this] {
        lfoTypeSlider->setValue(Vibrado<float>::LFO_Types::Sine, juce::NotificationType::sendNotificationSync);
        audioProcessor.setLfoType(Vibrado<float>::LFO_Types::Sine);
        updateButtons();
    };

    triangleButton.reset(new juce::ImageButton("TriangleButton"));
    addAndMakeVisible(triangleButton.get());
    triangleButton->setBounds(71, 323, 70, 40);
    triangleButton->setTooltip("Triangle");
    triangleButton->onClick = [this] {
        lfoTypeSlider->setValue(Vibrado<float>::LFO_Types::Triangle, juce::NotificationType::sendNotificationSync);
        audioProcessor.setLfoType(Vibrado<float>::LFO_Types::Triangle);
        updateButtons();
    };

    sawButton.reset(new juce::ImageButton("SawButton"));
    addAndMakeVisible(sawButton.get());
    sawButton->setBounds(71, 363, 70, 40);
    sawButton->setTooltip("Saw");
    sawButton->onClick = [this] {
        lfoTypeSlider->setValue(Vibrado<float>::LFO_Types::Saw, juce::NotificationType::sendNotificationSync);
        audioProcessor.setLfoType(Vibrado<float>::LFO_Types::Saw);
        updateButtons();
    };

    updateButtons();
}

VibradoPluginAudioProcessorEditor::~VibradoPluginAudioProcessorEditor()
{
    rateSliderAtt = nullptr;
    depthSliderAtt = nullptr;
    levelSliderAtt = nullptr;
    lfoTypeSliderAtt = nullptr;
}

//==============================================================================
void VibradoPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void VibradoPluginAudioProcessorEditor::resized()
{

}

void VibradoPluginAudioProcessorEditor::setMeters()
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

void VibradoPluginAudioProcessorEditor::updateButtons()
{
    assetManager.setButtonAsset(sineButton, audioProcessor.getLfoType(), Vibrado<float>::LFO_Types::Sine);
    assetManager.setButtonAsset(triangleButton, audioProcessor.getLfoType(), Vibrado<float>::LFO_Types::Triangle);
    assetManager.setButtonAsset(sawButton, audioProcessor.getLfoType(), Vibrado<float>::LFO_Types::Saw);
}