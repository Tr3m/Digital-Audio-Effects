#pragma once


/**
 * Base Class for Audio Effect Processors
 * 
 */
template <typename SampleType>
class EffectProcessorBase
{
public:

    /**
	 * @brief Prepares object for playback
	 * 
	 * @param sampleRate Current sampling rate
	 */
    virtual void prepare(SampleType sampleRate) = 0; 

    /**
	 * @brief Processes a single sample
	 * 
	 * @param input Input sample
	 */
    virtual SampleType processSample(SampleType input) = 0;

    /**
	 * @brief Processes a memory block that holds audio samples
	 * 
	 * @param data Memory block start pointer 
	 * @param startSample Sample index to start processing from
	 * @param endSample Number of samples to process
	 */
    virtual void process(SampleType* channelData, int startSample, int endSample) = 0;

protected:
    SampleType sampleRate;
};