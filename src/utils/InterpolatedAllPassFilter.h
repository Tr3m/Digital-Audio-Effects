#pragma once
#include <utils/LinearInterpolationCircularBuffer.h>

#define FEEDBACK_LIMIT 0.99

/**
 * First Order All-Pass Filter that utilizes linear interpolation when poping samples.
 * 
 * Allows for smoother delay time changes and modulation.
 * 
 */
template <typename SampleType>
class InterpolatedAllPassFilter
{
public:

    /**
     * @brief Constructor
     */
    InterpolatedAllPassFilter();

    /**
     * @brief Destructor
     */
    ~InterpolatedAllPassFilter();
    
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
     * @param delayInMs Delay time in samples
     */
    void setDelaySamples(SampleType delayInSamples);

    /**
     * @brief Sets the amount of feedback.
     * 
     * Values must range between 0 and 1
     * 
     * @param newFeedback Feedback amount
     */
    void setFeedback(SampleType newFeedback);
    /**
     * @brief Processes a single sample
     * 
     * @param input Input sample
     */
    SampleType processSample(SampleType input);

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
    LinearInterpolationCircularBuffer<SampleType> circularBuffer;
    SampleType delayTime {0.0};
    SampleType feedback {0.0};

    SampleType lastOutput {0.0};
    SampleType lastInput {0.0};
    
};
