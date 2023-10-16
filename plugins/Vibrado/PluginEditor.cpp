/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibradoPluginAudioProcessorEditor::VibradoPluginAudioProcessorEditor (VibradoPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize(370, 470);

    //Rate Slider
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    rateSlider.setTextValueSuffix(" Hz");
    rateSlider.setRange(0.1f, 10.0f, 0.1f);
    addAndMakeVisible(&rateSlider);
    rateSlider.addListener(this);
    rateSlider.setValue(audioProcessor.vibrado.getParameter(Vibrado::Parameters::Rate));
    rateSlider.setLookAndFeel(&graphics);


    //Depth Slider
    depthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    depthSlider.setTextValueSuffix(" %");
    depthSlider.setRange(0.1f, 100.0f, 0.1f);
    addAndMakeVisible(&depthSlider);
    depthSlider.addListener(this);
    depthSlider.setValue(audioProcessor.vibrado.getParameter(Vibrado::Parameters::Depth));
    depthSlider.setLookAndFeel(&graphics);


    //Level Slider
    levelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    levelSlider.setRange(-12.0f, 12.0f, 0.1f);
    levelSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&levelSlider);
    levelSlider.addListener(this);
    levelSlider.setValue(audioProcessor.vibrado.getParameter(Vibrado::Parameters::Level));
    levelSlider.setLookAndFeel(&graphics);
   

    addAndMakeVisible(&sineButton);
    sineButton.setBounds(84, 269, 50, 20);
    sineButton.setTooltip("Sine");
    sineButton.setAlpha(0);
    sineButton.onClick = [this] {
        audioProcessor.vibrado.setLFOType(Vibrado::LFO_Types::Sine);
        repaint();
    };

    addAndMakeVisible(&triangleButton);
    triangleButton.setBounds(84, 297, 50, 20);
    triangleButton.setTooltip("Triangle");
    triangleButton.setAlpha(0);
    triangleButton.onClick = [this] {
        audioProcessor.vibrado.setLFOType(Vibrado::LFO_Types::Triangle);
        repaint();
    };

    addAndMakeVisible(&sawButton);
    sawButton.setBounds(84, 339, 50, 20);
    sawButton.setTooltip("Saw");
    sawButton.setAlpha(0);
    sawButton.onClick = [this] {
        audioProcessor.vibrado.setLFOType(Vibrado::LFO_Types::Saw);
        repaint();
    };

}

VibradoPluginAudioProcessorEditor::~VibradoPluginAudioProcessorEditor()
{
}

//==============================================================================
void VibradoPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    switch (audioProcessor.vibrado.getLFOType())
    {
    case Vibrado::LFO_Types::Sine:
        g.drawImageAt(graphics.getVibradoBackground(GUIGraphics::VibradoStates::Sine), 0, 0);
        break;
    case Vibrado::LFO_Types::Triangle:
        g.drawImageAt(graphics.getVibradoBackground(GUIGraphics::VibradoStates::Triangle), 0, 0);
        break;
    case Vibrado::LFO_Types::Saw:
        g.drawImageAt(graphics.getVibradoBackground(GUIGraphics::VibradoStates::Saw), 0, 0);
        break;
    }
}

void VibradoPluginAudioProcessorEditor::resized()
{
    //lfoType.setBounds((getWidth() / 2) - (getWidth() - 180) / 2, 90, getWidth() - 100,  25);
    rateSlider.setBounds(44, 91, 124, 124);
    depthSlider.setBounds(198, 91, 124, 124);
    levelSlider.setBounds(198, 252, 124, 124);
}

void VibradoPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &rateSlider)
        audioProcessor.vibrado.setParameter(Vibrado::Parameters::Rate, slider->getValue());
    else if (slider == &depthSlider)
        audioProcessor.vibrado.setParameter(Vibrado::Parameters::Depth, slider->getValue());
    else if (slider == &levelSlider)
        audioProcessor.vibrado.setParameter(Vibrado::Parameters::Level, slider->getValue());
}
