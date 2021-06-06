/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LimiterPluginAudioProcessorEditor::LimiterPluginAudioProcessorEditor (LimiterPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(370, 470);

    thresholdSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thresholdSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    thresholdSlider.setRange(-80.0, 0.0, 0.01);
    thresholdSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&thresholdSlider);
    thresholdSlider.addListener(this);
    thresholdSlider.setValue(audioProcessor.limL.getParameter(Limiter::Parameters::Threshold));
    thresholdSlider.setLookAndFeel(&graphics);



    attackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    attackSlider.setRange(1.0, 100.0, 0.01);
    attackSlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&attackSlider);
    attackSlider.addListener(this);
    attackSlider.setValue(audioProcessor.limL.getParameter(Limiter::Parameters::Attack));
    attackSlider.setLookAndFeel(&graphics);

    releaseSilder.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSilder.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    releaseSilder.setRange(10.0, 1000.0, 0.01);
    releaseSilder.setTextValueSuffix(" ms");
    addAndMakeVisible(&releaseSilder);
    releaseSilder.addListener(this);
    releaseSilder.setValue(audioProcessor.limL.getParameter(Limiter::Parameters::Release));
    releaseSilder.setLookAndFeel(&graphics);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    gainSlider.setRange(-20.0, 20.0, 0.01);
    gainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&gainSlider);
    gainSlider.addListener(this);
    gainSlider.setValue(audioProcessor.limL.getParameter(Limiter::Parameters::MakeupGain));
    gainSlider.setLookAndFeel(&graphics);

    addAndMakeVisible(&hardKnee);
    hardKnee.setBounds(227, 150, 50, 30);
    hardKnee.setAlpha(0);
    hardKnee.onClick = [this] {
        audioProcessor.limL.setKneeType(Limiter::KneeTypes::Hard);
        audioProcessor.limR.setKneeType(Limiter::KneeTypes::Hard);
        repaint();
    };

    addAndMakeVisible(&softKnee);
    softKnee.setBounds(227, 116, 50, 30);
    softKnee.setAlpha(0);
    softKnee.onClick = [this] {
        audioProcessor.limL.setKneeType(Limiter::KneeTypes::Soft);
        audioProcessor.limR.setKneeType(Limiter::KneeTypes::Soft);

        repaint();
    };
}

LimiterPluginAudioProcessorEditor::~LimiterPluginAudioProcessorEditor()
{
}

//==============================================================================
void LimiterPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getLimiterBackground(audioProcessor.limL.getKneeType()), 0, 0);

}

void LimiterPluginAudioProcessorEditor::resized()
{
    thresholdSlider.setBounds(62, 100, 124, 124);
    

    attackSlider.setBounds(20, 266, 100, 100);
    releaseSilder.setBounds(132, 266, 100, 100);
    gainSlider.setBounds(243, 266, 100, 100);
}

void LimiterPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &thresholdSlider)
    {
        audioProcessor.limL.setParameter(Limiter::Parameters::Threshold, slider->getValue());
        audioProcessor.limR.setParameter(Limiter::Parameters::Threshold, slider->getValue());
    }
    else if (slider == &attackSlider)
    {
        audioProcessor.limL.setParameter(Limiter::Parameters::Attack, slider->getValue());
        audioProcessor.limR.setParameter(Limiter::Parameters::Attack, slider->getValue());
    }
    else if (slider == &releaseSilder)
    {
        audioProcessor.limL.setParameter(Limiter::Parameters::Release, slider->getValue());
        audioProcessor.limR.setParameter(Limiter::Parameters::Release, slider->getValue());
    }
    else if (slider == &gainSlider)
    {
        audioProcessor.limL.setParameter(Limiter::Parameters::MakeupGain, slider->getValue());
        audioProcessor.limR.setParameter(Limiter::Parameters::MakeupGain, slider->getValue());
    }
}
