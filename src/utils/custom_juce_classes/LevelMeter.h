#pragma once

class LevelMeter : public juce::Component,
                    public juce::Timer
{
public:

    LevelMeter(int orientationIndex, std::function<float()>&& valueFunction)
        : valueSupplier(std::move(valueFunction))
    {
        if(orientationIndex < 0 || orientationIndex > 1)
            orientationIndex = 0;

        orientation = orientationIndex;           

        startTimerHz(60.0);

    }

    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();

        meterLevel = valueSupplier();

        g.setColour(backgroundColour);
        g.fillRoundedRectangle(bounds, cornerSize);

        g.setColour(meterColor);

        if(orientation == Orientations::Horizontal)
        {
            const auto scaledX = juce::jmap(meterLevel, -60.0f, 6.0f, 0.0f, static_cast<float>(getWidth()));
            g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), cornerSize);
        }
        else
        {
            const auto scaledY = juce::jmap(meterLevel, -60.0f, 6.0f, 0.0f, static_cast<float>(getHeight()));
            g.fillRoundedRectangle(bounds.removeFromBottom(scaledY), cornerSize);
        }
    }

    
    void setMeterColour(juce::Colour newColor)
    {
        meterColor = newColor;
    }

    void setBackgroundColour(juce::Colour newColor)
    {
        backgroundColour = newColor;
    }

    void timerCallback()
    {
        repaint();
    }

    enum Orientations
    {
        Horizontal = 0,
        Vertical
    };


private:

    float meterLevel{-30.0f};
    int orientation;
    float cornerSize {1.5};

    juce::Colour meterColor{juce::Colours::white}, backgroundColour {juce::Colours::white.withBrightness(0.4f)};

    std::function<float()> valueSupplier;


};
