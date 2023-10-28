#pragma once
#include <utils/InterpolatedCombFilter.h>
#include <utils/LFO.h>

/**
 * Comb Filter with modulating delay time
 * 
 */
template <typename SampleType>
class ModulatedCombFilter
{
public:

    /**
     * @brief Constructor
     */
    ModulatedCombFilter();

    /**
     * @brief Destructor
     */
    ~ModulatedCombFilter();

    /**
     * @brief Prepares object for playback
     * 
     * @param sampleRate Current sampling rate
     */
    void prepare(SampleType sampleRate);

    /**
     * @brief Sets the delay time in milliseconds 
     * 
     * @param delayInMs Delay time in milliseconds
     */
    void setDelayMs(SampleType delayInMs);

    /**
     * @brief Sets the delay time in samples 
     * 
     * @param delayInSamples Delay time in samples
     */
    void setDelayInSamples(SampleType delayInSamples);

    /**
     * @brief Sets the amount of feedback.
     * 
     * Values must range between 0 and 1
     * 
     * @param newFeedback Feedback amount
     */
    void setFeedback(SampleType newFeedback);

    /**
     * @brief Sets the delay time modulation rate
     * 
     * @param newRate New modulation rate value in Hz
     */
    void setRate(SampleType newRate);

    /**
     * @brief Sets the delay time modulation depth
     * 
     * @param newDepth New modulation depth value
     * 
     * Values must range between 0.0 to 1.0
     */    
    void setDepth(SampleType newDepth);

    /**
     * @brief Sets the bounds the delay time values can modulate between
     * 
     * @param newWidth New modulation width in samples
     */
    void setWidth(SampleType newWidth);

    /**
     * @brief Processes a single sample
     * 
     * @param input Input sample
     */
    SampleType processSample(SampleType input);

    /**
     * @brief Processes a memory block that holds audio samples
     * 
     * @param data Memory block start pointer 
     * @param startSample Sample index to start processing from
     * @param endSample Number of samples to process
     */
    void process(SampleType* data, int startSample, int endSample);

private:
    SampleType doUnipolarModulationFromMin(SampleType unipolarModulatorValue, SampleType minValue, SampleType maxValue);
    SampleType bipolarToUnipolar(SampleType value);

private:
    SampleType sampleRate;
    InterpolatedCombFilter<SampleType> combFilter;
    LFO lfo;
    SampleType delayTime {0.0}, feedback {0.0}, rate {0.0}, depth {0.0}, width {0.0};
};