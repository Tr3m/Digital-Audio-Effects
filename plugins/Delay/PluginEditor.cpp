#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayPluginAudioProcessorEditor::DelayPluginAudioProcessorEditor (DelayPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{    
    setSize (370, 470);

    delayLengthSlider.reset(new juce::Slider("DelayLengthSlider"));
    delayLengthSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayLengthSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    delayLengthSlider->setTextValueSuffix(" ms");
    delayLengthSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(delayLengthSlider.get());

    delayLengthSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "DELAY_TIME_ID", *delayLengthSlider);

    feedbackSlider.reset(new juce::Slider("FeedbackSlider"));
    feedbackSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    feedbackSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(feedbackSlider.get());

    feedbackSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "FEEDBACK_ID", *feedbackSlider);

    dryMixSlider.reset(new juce::Slider("DrySlider"));
    dryMixSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryMixSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    dryMixSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(dryMixSlider.get());

    dryMixSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "DRY_ID", *dryMixSlider);

    wetMixSlider.reset(new juce::Slider("WetSlider"));
    wetMixSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetMixSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    wetMixSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(wetMixSlider.get());

    wetMixSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "WET_ID", *wetMixSlider);

    delayLengthSlider->setBounds(44, 91, 124, 124);
    feedbackSlider->setBounds(198, 91, 124, 124);
    dryMixSlider->setBounds(44, 252, 124, 124);
    wetMixSlider->setBounds(198, 252, 124, 124);
}

DelayPluginAudioProcessorEditor::~DelayPluginAudioProcessorEditor()
{
    delayLengthSliderAtt = nullptr;
    feedbackSliderAtt = nullptr;
    dryMixSliderAtt = nullptr;
    wetMixSliderAtt = nullptr;
}

//==============================================================================
void DelayPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void DelayPluginAudioProcessorEditor::resized()
{

}