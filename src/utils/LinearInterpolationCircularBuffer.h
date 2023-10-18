#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

/**
 * Circular buffer that utilizes linear interpolation when reading samples, allowing for fractional delay lines.
 */
template <typename SampleType>
class LinearInterpolationCircularBuffer
{
public:

    LinearInterpolationCircularBuffer();
    ~LinearInterpolationCircularBuffer();

    /**
     * @brief Prepares buffer for playback
     * 
     * @param sampleRate Current sampling rate
     */
    void prepare(int sampleRate);

    void reset();

    /**
     * @brief Clears the buffer
     * 
     */
    void clear();

    /**
     * @brief Sets buffer size
     * 
     * @param newBufferSize New buffer size in samples
     */
    void setSize(int newBufferSize);

    /**
     * @brief Returns buffer size
     */
    int getNumSamples();

    /**
     * @brief Sets delay time in samples
     * 
     * @param delayInSamples New delay time in samples
     */
    void setDelayInSamples(SampleType delayInSamples);

    /**
     * @brief Sets delay time in milliseconds
     * 
     * @param delayInMs New delay time in milliseconds
     */
    void setDelayInMs(SampleType delayInMs);

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

    /**
     * @brief Returns read pointer index
     */
    int getReadPointerIndex();

    /**
     * @brief Returns write pointer index
     */    
    int getWritePointerIndex();

    /**
     * @brief Pushes a sample to the buffer and advances the write pointer by an index of 1
     * 
     * @warning Meant to be used in a sample by sample processing context
     * 
     * @param sample input sample
     */
    void pushSample(SampleType sample);

    /**
     * @brief Returns a sample from the buffer read position and advances the read pointer by an index of 1
     * 
     * The return value is linearly interpolated
     * 
     * @warning Meant to be used in a sample by sample processing context
     */
    SampleType popSample();

private:
    SampleType interpolateSample();
    SampleType limitWithinRange(SampleType lowerLimit, SampleType upperLimit, SampleType value); 

private:

    SampleType sampleRate;
    std::unique_ptr<std::vector<SampleType>> buffer;
    SampleType delayFrac {0.0}, delay {0.0};
    int readPointer, writePointer, delayInt, bufferSize;    
};



