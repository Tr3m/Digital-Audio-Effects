#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LimiterPluginAudioProcessorEditor::LimiterPluginAudioProcessorEditor (LimiterPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(370, 470);

    thresholdSlider.reset(new juce::Slider("ThresholdSlider"));
    thresholdSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thresholdSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    thresholdSlider->setTextValueSuffix(" dB");
    addAndMakeVisible(thresholdSlider.get());
    thresholdSlider->setLookAndFeel(&graphics);

    thresholdSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "THRESHOLD_ID", *thresholdSlider);

    attackSlider.reset(new juce::Slider("AttackSlider"));
    attackSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    attackSlider->setTextValueSuffix(" ms");
    addAndMakeVisible(attackSlider.get());
    attackSlider->setLookAndFeel(&graphics);

    attackSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "ATTACK_ID", *attackSlider);

    releaseSilder.reset(new juce::Slider("ReleaseSlider"));
    releaseSilder->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSilder->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    releaseSilder->setTextValueSuffix(" ms");
    addAndMakeVisible(releaseSilder.get());
    releaseSilder->setLookAndFeel(&graphics);

    releaseSilderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "RELEASE_ID", *releaseSilder);

    gainSlider.reset(new juce::Slider("GainSlider"));
    gainSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    gainSlider->setTextValueSuffix(" dB");
    addAndMakeVisible(gainSlider.get());
    gainSlider->setLookAndFeel(&graphics);

    gainSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "GAIN_ID", *gainSlider);

    addAndMakeVisible(&hardKnee);
    hardKnee.setBounds(227, 150, 50, 30);
    hardKnee.setAlpha(0);
    hardKnee.onClick = [this] {
        audioProcessor.setKneeType(Limiter<float>::KneeTypes::Hard);
        repaint();
    };

    addAndMakeVisible(&softKnee);
    softKnee.setBounds(227, 116, 50, 30);
    softKnee.setAlpha(0);
    softKnee.onClick = [this] {
        audioProcessor.setKneeType(Limiter<float>::KneeTypes::Soft);
        repaint();
    };

    thresholdSlider->setBounds(62, 100, 124, 124);  
    attackSlider->setBounds(20, 266, 100, 100);
    releaseSilder->setBounds(132, 266, 100, 100);
    gainSlider->setBounds(243, 266, 100, 100);
}

LimiterPluginAudioProcessorEditor::~LimiterPluginAudioProcessorEditor()
{
    thresholdSliderAtt = nullptr;
    attackSliderAtt = nullptr;
    releaseSilderAtt = nullptr;
    gainSliderAtt = nullptr;
}

//==============================================================================
void LimiterPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getLimiterBackground(audioProcessor.getKneeType()), 0, 0);
}

void LimiterPluginAudioProcessorEditor::resized()
{

}