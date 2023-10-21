#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IirfilterPluginAudioProcessorEditor::IirfilterPluginAudioProcessorEditor (IirfilterPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (370, 470);

    
    freqSlider.reset(new juce::Slider("FrequencySlider"));
    freqSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freqSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    freqSlider->setTextValueSuffix(" Hz");
    addAndMakeVisible(freqSlider.get());
    freqSlider->addListener(this);
    freqSlider->setLookAndFeel(&graphics);

    freqSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "FREQUENCY_ID", *freqSlider);

    gainSlider.reset(new juce::Slider("GainSlider"));
    gainSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 25);
    gainSlider->setTextValueSuffix(" dB");
    addAndMakeVisible(gainSlider.get());
    gainSlider->addListener(this);
    gainSlider->setLookAndFeel(&graphics);

    gainSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "GAIN_ID", *gainSlider);
    
    /*
    qSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    qSlider.setRange(0.2, 10.0, .001);
    //addAndMakeVisible(&qSlider);
    qSlider.addListener(this);
    qLabel.setText("Q", juce::dontSendNotification);
    qLabel.setJustificationType(juce::Justification::topLeft);
    qLabel.attachToComponent(&qSlider, false);
    */

    if (audioProcessor.getFilterType() != IIRFilter<float>::FilterTypes::Parametric)
    {
        gainSlider->setEnabled(false);
        gainSlider->setAlpha(0.5);
    }
        

    addAndMakeVisible(&hpButton);
    hpButton.setBounds(80, 97, 50, 30);
    hpButton.setTooltip("High-Pass");
    hpButton.setAlpha(0);
    hpButton.onClick = [this] {
        audioProcessor.setFilterType(IIRFilter<float>::FilterTypes::HPF);
        gainSlider->setEnabled(false);
        gainSlider->setAlpha(0.5);
        gainSlider->setValue(0);
        repaint();
    };

    addAndMakeVisible(&lpButton);
    lpButton.setBounds(80, 137, 50, 30);
    lpButton.setTooltip("Low-Pass");
    lpButton.setAlpha(0);
    lpButton.onClick = [this] {
        audioProcessor.setFilterType(IIRFilter<float>::FilterTypes::LPF);
        gainSlider->setEnabled(false);
        gainSlider->setAlpha(0.5);
        gainSlider->setValue(0);
        repaint();
    };

    addAndMakeVisible(&parButton);
    parButton.setBounds(80, 172, 50, 30);
    parButton.setTooltip("Parametric");
    parButton.setAlpha(0);
    parButton.onClick = [this] {
        audioProcessor.setFilterType(IIRFilter<float>::FilterTypes::Parametric);
        gainSlider->setEnabled(true);
        gainSlider->setAlpha(1);
        repaint();
    };

    freqSlider->setBounds(198, 91, 124, 124);
    gainSlider->setBounds(44, 252, 124, 124);
    //qSlider->setBounds(10, 240, getWidth(), 30);
    //filterSelect->setBounds(145, 60, getWidth() / 3, 30);

}

IirfilterPluginAudioProcessorEditor::~IirfilterPluginAudioProcessorEditor()
{
    freqSliderAtt = nullptr;
    gainSliderAtt = nullptr;
}

//==============================================================================
void IirfilterPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    switch (audioProcessor.getFilterType())
    {
    case IIRFilter<float>::FilterTypes::HPF:
        g.drawImageAt(graphics.getFilterBackground(GUIGraphics::FilterStates::HighPass), 0, 0);
        break;
    case IIRFilter<float>::FilterTypes::LPF:
        g.drawImageAt(graphics.getFilterBackground(GUIGraphics::FilterStates::LowPass), 0, 0);
        break;
    case IIRFilter<float>::FilterTypes::Parametric:
        g.drawImageAt(graphics.getFilterBackground(GUIGraphics::FilterStates::Parametric), 0, 0);
        break;
    }
}

void IirfilterPluginAudioProcessorEditor::resized()
{
    
}

void IirfilterPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{

}


