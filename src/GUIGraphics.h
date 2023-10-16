#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "BinaryData.h"

class GUIGraphics : public juce::LookAndFeel_V4
{
public:

    GUIGraphics(int effectType);

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    void reloadImage(int _effectType);
    juce::Image getBackground();
    juce::Image getFilterBackground(int filterState);
    juce::Image getVibradoBackground(int vibradoState);
    juce::Image getCompressorBackground(int compressorState);
    juce::Image getLimiterBackground(int LimiterState);

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

    enum CompressorStates
    {
        SoftKnee = 0,
        HardKnee
    };

    enum LimiterStates
    {
        SoftKneeLimiter = 0,
        HardKneeLimiter
    };
private:

    juce::Image knobImage, backgroundImage;
    int effectType;
};