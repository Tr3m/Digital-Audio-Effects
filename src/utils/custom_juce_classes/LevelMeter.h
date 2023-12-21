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

        if(orientation == Orientations::Horizontal)
            bounds.setX(bounds.getX() - 6);
        else
            bounds.setY(bounds.getY() + 6);
            

        meterLevel = valueSupplier();

        g.setColour(outlineColour);
        g.drawRoundedRectangle(bounds, cornerSize, 1.0);

        g.setColour(backgroundColour);
        g.fillRoundedRectangle(bounds, cornerSize);
        
        g.setColour(meterColor);

        if(orientation == Orientations::Horizontal)
        {
            const auto scaledX = juce::jmap(meterLevel, -90.0f, 0.0f, 0.0f, static_cast<float>(getWidth() - 6));
            g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), cornerSize);
        }
        else
        {
            const auto scaledY = juce::jmap(meterLevel, -90.0f, 0.0f, 0.0f, static_cast<float>(getHeight() - 6));
            g.fillRoundedRectangle(bounds.removeFromBottom(scaledY), cornerSize);
        }

        if(clipped)
        {   
            g.setColour(juce::Colours::red);

            if(orientation == Orientations::Horizontal)
                g.fillRect(bounds.getX() + bounds.getWidth(), bounds.getY(), 6.0, bounds.getHeight());
            else
                g.fillRect(bounds.getX(), bounds.getY() - 6.0, bounds.getWidth(), 6.0);
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

    void setOutlineColour(juce::Colour newColor)
    {
        outlineColour = newColor;
    }

    void timerCallback()
    {
        if (meterLevel >= 0)
            clipped = true;

        repaint();
    }

    enum Orientations
    {
        Horizontal = 0,
        Vertical
    };

    void mouseDown (const MouseEvent& event) override
    {
        if(orientation == Orientations::Horizontal)
        {
            if(event.getPosition().getX() > getBounds().getWidth() - 7)
                clipped = false;
        }
        else
        {
            if(event.getPosition().getY() < 7)
                clipped = false;
        }
    }


private:

    float meterLevel{-30.0f};
    int orientation;
    float cornerSize {1.5};
    bool clipped {false};

    juce::Colour meterColor{juce::Colours::white}, backgroundColour {juce::Colours::white.withBrightness(0.4f)}, outlineColour {juce::Colours::black};

    std::function<float()> valueSupplier;


};