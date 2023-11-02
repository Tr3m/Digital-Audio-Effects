#pragma once

#include <iostream>
#include <vector>
#include <memory>

/**
 * Circular Buffer Class used to create delay lines. 
 */
template <typename SampleType>
class CircularBuffer
{
public:

    /**
     * @brief Constructor
     */
    CircularBuffer();

    /**
     * @brief Destructor
     */
    ~CircularBuffer();

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
     * @brief Changes the buffer size
     * 
     * @param newBufferSize Number of buffer samples
     */
    void setSize(int newBufferSize);

    /**
     * @brief Returns buffer size
     */
    int getNumSamples();

    /**
     * @brief Sets the delay time in samples
     * 
     * @param delayInSamples Delay time in samples
     */
    void setDelayInSamples(int delayInSamples);

    /**
     * @brief Sets the delay time in milliseconds
     * 
     * @param delayInMs Delay time in milliseconds
     */
    void setDelayInMs(SampleType delayInMs);

    /**
     * @brief Processes a single sample
     * 
     * @param input Input sample
     * @return SampleType 
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
     * @param sample Sample to push
     */
    void pushSample(SampleType sample);

     /**
     * @brief Returns the sample from the buffer read position and advances the read pointer by an index of 1
     * 
     * @warning Meant to be used in a sample by sample processing context
     * 
     */
    SampleType popSample();

private:

    double sampleRate;
    std::unique_ptr<std::vector<SampleType>> buffer;
    int readPointer, writePointer;    
    
};



