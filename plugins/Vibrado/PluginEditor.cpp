#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibradoPluginAudioProcessorEditor::VibradoPluginAudioProcessorEditor (VibradoPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize(370, 470);

    //Rate Slider
    rateSlider.reset(new juce::Slider("RateSlider"));
    rateSlider->setSliderStyle(juce::Slider::Rotary);
    rateSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    rateSlider->setTextValueSuffix(" Hz");
    rateSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(rateSlider.get());    

    rateSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "RATE_ID", *rateSlider);


    //Depth Slider
    depthSlider.reset(new juce::Slider("DepthSlider"));
    depthSlider->setSliderStyle(juce::Slider::Rotary);
    depthSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    depthSlider->setTextValueSuffix(" %");
    depthSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(depthSlider.get());

    depthSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "DEPTH_ID", *depthSlider);

    //Level Slider
    levelSlider.reset(new juce::Slider("LevelSlider"));
    levelSlider->setSliderStyle(juce::Slider::Rotary);
    levelSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    levelSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(levelSlider.get()); 
    
    levelSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "LEVEL_ID", *levelSlider);
    
    rateSlider->setBounds(44, 91, 124, 124);
    depthSlider->setBounds(198, 91, 124, 124);
    levelSlider->setBounds(198, 252, 124, 124);

    addAndMakeVisible(&sineButton);
    sineButton.setBounds(84, 269, 50, 20);
    sineButton.setTooltip("Sine");
    sineButton.setAlpha(0);
    sineButton.onClick = [this] {
        audioProcessor.setLfoType(Vibrado<float>::LFO_Types::Sine);
        repaint();
    };

    addAndMakeVisible(&triangleButton);
    triangleButton.setBounds(84, 297, 50, 20);
    triangleButton.setTooltip("Triangle");
    triangleButton.setAlpha(0);
    triangleButton.onClick = [this] {
        audioProcessor.setLfoType(Vibrado<float>::LFO_Types::Triangle);
        repaint();
    };

    addAndMakeVisible(&sawButton);
    sawButton.setBounds(84, 339, 50, 20);
    sawButton.setTooltip("Saw");
    sawButton.setAlpha(0);
    sawButton.onClick = [this] {
        audioProcessor.setLfoType(Vibrado<float>::LFO_Types::Saw);
        repaint();
    };

}

VibradoPluginAudioProcessorEditor::~VibradoPluginAudioProcessorEditor()
{
    rateSliderAtt = nullptr;
    depthSliderAtt = nullptr;
    levelSliderAtt = nullptr;
}

//==============================================================================
void VibradoPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    switch (audioProcessor.getLfoType())
    {
    case Vibrado<float>::LFO_Types::Sine:
        g.drawImageAt(graphics.getVibradoBackground(GUIGraphics::VibradoStates::Sine), 0, 0);
        break;
    case Vibrado<float>::LFO_Types::Triangle:
        g.drawImageAt(graphics.getVibradoBackground(GUIGraphics::VibradoStates::Triangle), 0, 0);
        break;
    case Vibrado<float>::LFO_Types::Saw:
        g.drawImageAt(graphics.getVibradoBackground(GUIGraphics::VibradoStates::Saw), 0, 0);
        break;
    }
}

void VibradoPluginAudioProcessorEditor::resized()
{
    
}