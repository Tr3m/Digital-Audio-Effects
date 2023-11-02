#include "CircularBuffer.h"

template <typename SampleType>
CircularBuffer<SampleType>::CircularBuffer()
{
    buffer.reset(new std::vector<SampleType>);
}

template <typename SampleType>
CircularBuffer<SampleType>::~CircularBuffer()
{
    buffer->clear();
    buffer.reset(nullptr);
}

template <typename SampleType>
void CircularBuffer<SampleType>::prepare(int sampleRate)
{
    this->sampleRate = sampleRate;
}

template <typename SampleType>
void CircularBuffer<SampleType>::clear()
{
    buffer->clear();
}

template <typename SampleType>
void CircularBuffer<SampleType>::setSize(int newBufferSize)
{
    clear();
    buffer->resize(newBufferSize);
    writePointer = 0;
    readPointer = buffer->size() / 2;
}

template <typename SampleType>
int CircularBuffer<SampleType>::getNumSamples()
{
    return buffer->size();
}

template <typename SampleType>
void CircularBuffer<SampleType>::setDelayInSamples(int delayInSamples)
{
    readPointer = int(writePointer - delayInSamples + buffer->size()) % buffer->size();
}

template <typename SampleType>
void CircularBuffer<SampleType>::setDelayInMs(SampleType delayInMs)
{
    readPointer = int(writePointer - ((delayInMs / 1000) * sampleRate) + buffer->size()) % buffer->size();    
}

template <typename SampleType>
SampleType CircularBuffer<SampleType>::processSample(SampleType input)
{
    pushSample(input);

    return popSample();
}

template <typename SampleType>
void CircularBuffer<SampleType>::process(SampleType* channelData, int startSample, int endSample)
{
    for(int sample = startSample; sample < endSample; ++sample)
        channelData[sample] = processSample(channelData[sample]);
}

template <typename SampleType>
void CircularBuffer<SampleType>::pushSample(SampleType sample)
{
    (*buffer)[writePointer] = sample;
    writePointer + 1 > buffer->size() ? writePointer = 0 : writePointer++;
}

template <typename SampleType>
SampleType CircularBuffer<SampleType>::popSample()
{
    SampleType returnValue = (*buffer)[readPointer];
    readPointer + 1 > buffer->size() ? readPointer = 0 : readPointer++;

    return returnValue;
}

template <typename SampleType>
int CircularBuffer<SampleType>::getReadPointerIndex()
{
    return readPointer;
}

template <typename SampleType>
int CircularBuffer<SampleType>::getWritePointerIndex()
{
    return writePointer;
}

template class CircularBuffer<float>;
template class CircularBuffer<double>;

