#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayPluginAudioProcessorEditor::DelayPluginAudioProcessorEditor (DelayPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    inputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextInput();}),
    outputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextOutput();})
{    
    setSize (370, 470);

    graphics.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));

    addAndMakeVisible(&inputMeter);
    addAndMakeVisible(&outputMeter);

    inputMeter.setMeterColour(juce::Colours::ivory);
    outputMeter.setMeterColour(juce::Colours::ivory);
    inputMeter.setBackgroundColour(juce::Colours::transparentBlack);
    outputMeter.setBackgroundColour(juce::Colours::transparentBlack);

    inputMeter.setBounds(13, getHeight() / 2 + 13, 6, 195);
    outputMeter.setBounds(getWidth() - 17, 24, 6, 195);

    delayLengthSlider.reset(new juce::Slider("DelayLengthSlider"));
    delayLengthSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayLengthSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    delayLengthSlider->setTextValueSuffix(" ms");
    delayLengthSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(delayLengthSlider.get());

    delayLengthSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "DELAY_TIME_ID", *delayLengthSlider);

    feedbackSlider.reset(new juce::Slider("FeedbackSlider"));
    feedbackSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    feedbackSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(feedbackSlider.get());

    feedbackSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "FEEDBACK_ID", *feedbackSlider);

    mixSlider.reset(new juce::Slider("mixSlider"));
    mixSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mixSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    mixSlider->setTextValueSuffix(" %");
    mixSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(mixSlider.get());

    mixSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "MIX_ID", *mixSlider);

    levelSlider.reset(new juce::Slider("levelSlider"));
    levelSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    levelSlider->setTextValueSuffix(" dB");
    levelSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(levelSlider.get());

    levelSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "LEVEL_ID", *levelSlider);

    int knobSize = 133;

    delayLengthSlider->setBounds(40, 107, knobSize, knobSize);
    feedbackSlider->setBounds(198, 63, knobSize, knobSize);
    mixSlider->setBounds(40, 283, knobSize, knobSize);
    levelSlider->setBounds(198, 234, knobSize, knobSize);
}

DelayPluginAudioProcessorEditor::~DelayPluginAudioProcessorEditor()
{
    delayLengthSliderAtt = nullptr;
    feedbackSliderAtt = nullptr;
    mixSliderAtt = nullptr;
    levelSliderAtt = nullptr;
}

//==============================================================================
void DelayPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void DelayPluginAudioProcessorEditor::resized()
{

}
