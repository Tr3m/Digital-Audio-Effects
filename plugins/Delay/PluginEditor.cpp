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
    
    setSize (370, 470);

    delayLengthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayLengthSlider.addListener(this);
    delayLengthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    delayLengthSlider.setTextValueSuffix(" s");
    delayLengthSlider.setRange(0.01, 2.0, 0.01);
    addAndMakeVisible(&delayLengthSlider);
    delayLengthSlider.setLookAndFeel(&graphics);

    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.addListener(this);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    feedbackSlider.setRange(0.0, 0.995, 0.01);
    addAndMakeVisible(&feedbackSlider);
    feedbackSlider.setLookAndFeel(&graphics);

    dryMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryMixSlider.addListener(this);
    dryMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    dryMixSlider.setRange(0.0, 1.0, 0.01);
    addAndMakeVisible(&dryMixSlider);
    dryMixSlider.setLookAndFeel(&graphics);

    wetMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetMixSlider.addListener(this);
    wetMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    wetMixSlider.setRange(0.0, 1.0, 0.01);
    addAndMakeVisible(&wetMixSlider);
    wetMixSlider.setLookAndFeel(&graphics);

  
    startTimer(50);
}

DelayPluginAudioProcessorEditor::~DelayPluginAudioProcessorEditor()
{
}

//==============================================================================
void DelayPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void DelayPluginAudioProcessorEditor::resized()
{
    delayLengthSlider.setBounds(44, 91, 124, 124);
    feedbackSlider.setBounds(198, 91, 124, 124);
    dryMixSlider.setBounds(44, 252, 124, 124);
    wetMixSlider.setBounds(198, 252, 124, 124);
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