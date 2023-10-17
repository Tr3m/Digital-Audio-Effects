#pragma once
#include <utils/CombFilter.h>
#include <utils/FirstOrderSmoother.h>


/**
 * Simple Delay Effect
 */
template <typename SampleType>
class Delay
{
public:
    
    /**
     * @brief Constructor
     * 
     */
    Delay();

    /**
     * @brief Destructor
     * 
     */
    ~Delay();

    /**
     * @brief Prepares object for playback
     * 
     * @param sampleRate Current sampling rate
     */
    void prepare(SampleType sampleRate);

    /**
     * @brief Sets the delay time
     * 
     * @param delayInMs Delay time in milliseconds
     */
    void setDelayTime(SampleType delayInMs);

    /**
     * @brief Sets the amount of feedback
     * 
     * @param newFeedback New feedback value
     * 
     * Values must range between 0 and 1
     */
    void setFeedback(SampleType newFeedback);

    /**
     * @brief Sets the delay wet/dry mix
     * 
     * @param newMix New dry/wet mix value
     */
    void setMix(SampleType newMix);

    /**
     * @brief Processes a memory block that holds audio samples
     * 
     * @param channelData Memory block start pointer 
     * @param startSample Sample index to start processing from
     * @param endSample Number of samples to process
     */
    void process(SampleType* channelData, int startSample, int endSample);

private:

    SampleType sampleRate;
    CombFilter<SampleType> combFilter;
    double delayTime {500.0};
    double feedback {0.7};
    double mix {0.4};

    FirstOrderSmoother smoother;
};

