#pragma once
#include <JuceHeader.h>

class GUIGraphics : public juce::LookAndFeel_V4
{
public:

    GUIGraphics(int effectType);

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    void reloadImage(int _effectType);
    juce::Image getBackground();
    juce::Image getFilterBackground(int filterState);
    juce::Image getVibradoBackground(int vibradoState);

    enum EffectTypes
    {
        Distortion = 0,
        Delay,
        Reverb,
        Flanger,
        Chorus,
        Vibrado,
        Filter,
        Compressor,
        Limiter
    };

    enum FilterStates
    {
        HighPass = 0,
        LowPass,
        Parametric
    };

    enum VibradoStates
    {
        Sine = 0,
        Triangle,
        Saw
    };

private:

    juce::Image knobImage, backgroundImage;
    int effectType;
};