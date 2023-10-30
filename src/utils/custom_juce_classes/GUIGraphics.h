#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "BinaryData.h"

using namespace juce;

class GUIGraphics : public juce::LookAndFeel_V4
{
public:

    GUIGraphics(int effectType, bool isSmallSlider = false);

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    void reloadImage(int _effectType);
    juce::Image getBackground();
    juce::Image getFilterBackground(int filterState);

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


    public: Slider::SliderLayout getSliderLayout (Slider& slider) override
    {
        // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints

        int minXSpace = 0;
        int minYSpace = 0;

        auto textBoxPos = slider.getTextBoxPosition();

        if (textBoxPos == Slider::TextBoxLeft || textBoxPos == Slider::TextBoxRight)
            minXSpace = 30;
        else
            minYSpace = 15;

        auto localBounds = slider.getLocalBounds();

        auto textBoxWidth  = jmax (0, jmin (slider.getTextBoxWidth(),  localBounds.getWidth() - minXSpace));
        auto textBoxHeight = jmax (0, jmin (slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));

        Slider::SliderLayout layout;

        // 2. set the textBox bounds

        if (textBoxPos != Slider::NoTextBox)
        {
            if (slider.isBar())
            {
                layout.textBoxBounds = localBounds;
            }
            else
            {
                layout.textBoxBounds.setWidth (textBoxWidth);
                layout.textBoxBounds.setHeight (textBoxHeight);

                if (textBoxPos == Slider::TextBoxLeft)           layout.textBoxBounds.setX (0);
                else if (textBoxPos == Slider::TextBoxRight)     layout.textBoxBounds.setX (localBounds.getWidth() - textBoxWidth);
                else /* above or below -> centre horizontally */ layout.textBoxBounds.setX ((localBounds.getWidth() - textBoxWidth) / 2);

                if (textBoxPos == Slider::TextBoxAbove)          layout.textBoxBounds.setY (0);
                else if (textBoxPos == Slider::TextBoxBelow)     
                {
                    if(isSmallSlider)
                        layout.textBoxBounds.setY (localBounds.getHeight() - textBoxHeight - 12);
                    else
                        layout.textBoxBounds.setY (localBounds.getHeight() - textBoxHeight - 10);
                }
                else /* left or right -> centre vertically */    layout.textBoxBounds.setY ((localBounds.getHeight() - textBoxHeight) / 2);
            }
        }

        // 3. set the slider bounds

        layout.sliderBounds = localBounds;

        if (slider.isBar())
        {
            layout.sliderBounds.reduce (1, 1);   // bar border
        }
        else
        {
            if (textBoxPos == Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft (textBoxWidth);
            else if (textBoxPos == Slider::TextBoxRight) layout.sliderBounds.removeFromRight (textBoxWidth);
            else if (textBoxPos == Slider::TextBoxAbove) layout.sliderBounds.removeFromTop (textBoxHeight);
            else if (textBoxPos == Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom (textBoxHeight + 15);

            const int thumbIndent = getSliderThumbRadius (slider);

            if (slider.isHorizontal())    layout.sliderBounds.reduce (thumbIndent, 0);
            else if (slider.isVertical()) layout.sliderBounds.reduce (0, thumbIndent);
        }

        return layout;
    }

    void drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& textEditor) override
    {
        if (textEditor.isEnabled())
        {
            if (textEditor.hasKeyboardFocus (true) && ! textEditor.isReadOnly())
            {
                const int border = 2;

                //g.setColour (textEditor.findColour (TextEditor::focusedOutlineColourId));
                g.setColour (juce::Colours::transparentBlack);
                g.drawRect (0, 0, width, height, border);

                g.setOpacity (1.0f);
                auto shadowColour = textEditor.findColour (TextEditor::shadowColourId).withMultipliedAlpha (0.75f);
                //drawBevel (g, 0, 0, width, height + 2, border + 2, shadowColour, shadowColour);
            }
            else
            {
                g.setColour (textEditor.findColour (TextEditor::outlineColourId));
                g.drawRect (0, 0, width, height);

                g.setOpacity (1.0f);
                auto shadowColour = textEditor.findColour (TextEditor::shadowColourId);
                //drawBevel (g, 0, 0, width, height + 2, 3, shadowColour, shadowColour);
            }
        }
    }
    
private:

    juce::Image knobImage, backgroundImage;
    int effectType;
    bool isSmallSlider;
};

