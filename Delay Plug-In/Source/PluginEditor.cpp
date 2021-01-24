/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayPluginAudioProcessorEditor::DelayPluginAudioProcessorEditor (DelayPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize (370, 471);

    delayLengthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayLengthSlider.addListener(this);
    delayLengthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    delayLengthSlider.setRange(0.01, 2.0, 0.01);
    addAndMakeVisible(&delayLengthSlider);

    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.addListener(this);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    feedbackSlider.setRange(0.0, 0.995, 0.005);
    addAndMakeVisible(&feedbackSlider);

    dryMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryMixSlider.addListener(this);
    dryMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    dryMixSlider.setRange(0.0, 1.0, 0.01);
    addAndMakeVisible(&dryMixSlider);

    wetMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetMixSlider.addListener(this);
    wetMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    wetMixSlider.setRange(0.0, 1.0, 0.01);
    addAndMakeVisible(&wetMixSlider);

    delayLengthLabel.attachToComponent(&delayLengthSlider, false);
    delayLengthLabel.setJustificationType(juce::Justification::centred);
    delayLengthLabel.setFont(juce::Font(11.0f));
    delayLengthLabel.setText("Delay Length", juce::dontSendNotification);

    feedbackLabel.attachToComponent(&feedbackSlider, false);
    feedbackLabel.setJustificationType(juce::Justification::centred);
    feedbackLabel.setFont(juce::Font(11.0f));
    feedbackLabel.setText("Feedback", juce::dontSendNotification);

    dryMixLabel.attachToComponent(&dryMixSlider, false);
    dryMixLabel.setJustificationType(juce::Justification::centred);
    dryMixLabel.setFont(juce::Font(11.0f));
    dryMixLabel.setText("Dry", juce::dontSendNotification);

    wetMixLabel.attachToComponent(&wetMixSlider, false);
    wetMixLabel.setJustificationType(juce::Justification::centred);
    wetMixLabel.setFont(juce::Font(11.0f));
    wetMixLabel.setText("Wet", juce::dontSendNotification);

    startTimer(50);
}

DelayPluginAudioProcessorEditor::~DelayPluginAudioProcessorEditor()
{
}

//==============================================================================
void DelayPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (30.0f);
    g.drawFittedText ("Digital Delay",10,10,getWidth(), 40, juce::Justification::centred, 1);
}

void DelayPluginAudioProcessorEditor::resized()
{
    delayLengthSlider.setBounds(20, 90, 140, 140);
    feedbackSlider.setBounds(200, 90, 140, 140);
    dryMixSlider.setBounds(20, 270, 140, 140);
    wetMixSlider.setBounds(200, 270, 140, 140);
}

void DelayPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &delayLengthSlider)
    {
        audioProcessor.delay.setParameter(Delay::Parameters::delayLengthParam, slider->getValue());
    }
    else if (slider == &feedbackSlider)
    {
        audioProcessor.delay.setParameter(Delay::Parameters::feedbackParam, slider->getValue());
    }
    else if (slider == &wetMixSlider)
    {
        audioProcessor.delay.setParameter(Delay::Parameters::wetMixParam, slider->getValue());
    }
    else if (slider == &dryMixSlider)
    {
        audioProcessor.delay.setParameter(Delay::Parameters::dryMixParam, slider->getValue());
    }
}

void DelayPluginAudioProcessorEditor::timerCallback()
{
    delayLengthSlider.setValue(audioProcessor.delay.getParameter(Delay::Parameters::delayLengthParam));
    feedbackSlider.setValue(audioProcessor.delay.getParameter(Delay::Parameters::feedbackParam));
    wetMixSlider.setValue(audioProcessor.delay.getParameter(Delay::Parameters::wetMixParam));
    dryMixSlider.setValue(audioProcessor.delay.getParameter(Delay::Parameters::dryMixParam));

}