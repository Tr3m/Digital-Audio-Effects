/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IirfilterPluginAudioProcessorEditor::IirfilterPluginAudioProcessorEditor (IirfilterPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (370, 470);

    

    freqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    freqSlider.setRange(20.0, 20000.0, 10);
    freqSlider.setTextValueSuffix(" Hz");
    freqSlider.setValue(audioProcessor.leftFilter.getCutoff());
    addAndMakeVisible(&freqSlider);
    freqSlider.addListener(this);
    freqSlider.setLookAndFeel(&graphics);  


    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    gainSlider.setRange(-12.0, 12.0, 1);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.setValue(audioProcessor.leftFilter.getGain());
    addAndMakeVisible(&gainSlider);
    gainSlider.addListener(this);
    gainSlider.setLookAndFeel(&graphics);
    

    qSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    qSlider.setRange(0.2, 10.0, .001);
    //addAndMakeVisible(&qSlider);
    qSlider.addListener(this);
    qLabel.setText("Q", juce::dontSendNotification);
    qLabel.setJustificationType(juce::Justification::topLeft);
    qLabel.attachToComponent(&qSlider, false);

    if (audioProcessor.leftFilter.getFilterType() != IIRFilter::FilterTypes::Parametric)
    {
        gainSlider.setEnabled(false);
        gainSlider.setAlpha(0.5);
    }
        

    addAndMakeVisible(&hpButton);
    hpButton.setBounds(80, 97, 50, 30);
    hpButton.setTooltip("High-Pass");
    hpButton.setAlpha(0);
    hpButton.onClick = [this] {
        audioProcessor.leftFilter.setFilterType(IIRFilter::FilterTypes::HPF);
        audioProcessor.rightFilter.setFilterType(IIRFilter::FilterTypes::HPF);
        gainSlider.setEnabled(false);
        gainSlider.setAlpha(0.5);
        gainSlider.setValue(0);
        repaint();
    };

    addAndMakeVisible(&lpButton);
    lpButton.setBounds(80, 137, 50, 30);
    lpButton.setTooltip("Low-Pass");
    lpButton.setAlpha(0);
    lpButton.onClick = [this] {
        audioProcessor.leftFilter.setFilterType(IIRFilter::FilterTypes::LPF);
        audioProcessor.rightFilter.setFilterType(IIRFilter::FilterTypes::LPF);
        gainSlider.setEnabled(false);
        gainSlider.setAlpha(0.5);
        gainSlider.setValue(0);
        repaint();
    };

    addAndMakeVisible(&parButton);
    parButton.setBounds(80, 172, 50, 30);
    parButton.setTooltip("Parametric");
    parButton.setAlpha(0);
    parButton.onClick = [this] {
        audioProcessor.leftFilter.setFilterType(IIRFilter::FilterTypes::Parametric);
        audioProcessor.rightFilter.setFilterType(IIRFilter::FilterTypes::Parametric);
        gainSlider.setEnabled(true);
        gainSlider.setAlpha(1);
        repaint();
    };


}

IirfilterPluginAudioProcessorEditor::~IirfilterPluginAudioProcessorEditor()
{
}

//==============================================================================
void IirfilterPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    switch (audioProcessor.leftFilter.getFilterType())
    {
    case IIRFilter::FilterTypes::HPF:
        g.drawImageAt(graphics.getFilterBackground(GUIGraphics::FilterStates::HighPass), 0, 0);
        break;
    case IIRFilter::FilterTypes::LPF:
        g.drawImageAt(graphics.getFilterBackground(GUIGraphics::FilterStates::LowPass), 0, 0);
        break;
    case IIRFilter::FilterTypes::Parametric:
        g.drawImageAt(graphics.getFilterBackground(GUIGraphics::FilterStates::Parametric), 0, 0);
        break;
    }
}

void IirfilterPluginAudioProcessorEditor::resized()
{
    freqSlider.setBounds(198, 91, 124, 124);
    gainSlider.setBounds(44, 252, 124, 124);
    //qSlider.setBounds(10, 240, getWidth(), 30);
    //filterSelect.setBounds(145, 60, getWidth() / 3, 30);
}

void IirfilterPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &freqSlider)
    {
        audioProcessor.leftFilter.setCutoff(slider->getValue());
        audioProcessor.rightFilter.setCutoff(slider->getValue());        
    }
    else if (slider == &gainSlider)
    {
        audioProcessor.leftFilter.setGain(slider->getValue());
        audioProcessor.rightFilter.setGain(slider->getValue());
    }
    else if (slider == &qSlider)
    {
        audioProcessor.leftFilter.setQ(slider->getValue());
        audioProcessor.rightFilter.setQ(slider->getValue());
    }
}


