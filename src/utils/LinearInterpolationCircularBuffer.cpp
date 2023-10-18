#include "LinearInterpolationCircularBuffer.h"

template <typename SampleType>
LinearInterpolationCircularBuffer<SampleType>::LinearInterpolationCircularBuffer()
{
    buffer.reset(new std::vector<SampleType>);
}

template <typename SampleType>
LinearInterpolationCircularBuffer<SampleType>::~LinearInterpolationCircularBuffer()
{
    buffer->clear();
    buffer.reset(nullptr);
}

template <typename SampleType>
void LinearInterpolationCircularBuffer<SampleType>::prepare(int sampleRate)
{
    this->sampleRate = sampleRate;
}

template <typename SampleType>
void LinearInterpolationCircularBuffer<SampleType>::clear()
{
    buffer->clear();
}

template <typename SampleType>
void LinearInterpolationCircularBuffer<SampleType>::setSize(int newBufferSize)
{
    clear();
    buffer->resize(newBufferSize);
    this->bufferSize = newBufferSize;
    writePointer = 0;
    readPointer = 0;
}

template <typename SampleType>
int LinearInterpolationCircularBuffer<SampleType>::getNumSamples()
{
    return buffer->size();
}

template <typename SampleType>
void LinearInterpolationCircularBuffer<SampleType>::setDelayInSamples(SampleType delayInSamples)
{
    delay = limitWithinRange(SampleType(0), SampleType(bufferSize - 1), delayInSamples);    
    delayInt  = static_cast<int> (std::floor (delay));
    delayFrac = delay - (SampleType) delayInt;
}

template <typename SampleType>
void LinearInterpolationCircularBuffer<SampleType>::setDelayInMs(SampleType delayInMs)
{
    setDelayInSamples((delayInMs / 1000) * sampleRate);
}

template <typename SampleType>
SampleType LinearInterpolationCircularBuffer<SampleType>::processSample(SampleType input)
{
    pushSample(input);

    return popSample();
}

template <typename SampleType>
void LinearInterpolationCircularBuffer<SampleType>::process(SampleType* channelData, int startSample, int endSample)
{
    for(int sample = startSample; sample < endSample; ++sample)
        channelData[sample] = processSample(channelData[sample]);
}

template <typename SampleType>
void LinearInterpolationCircularBuffer<SampleType>::pushSample(SampleType sample)
{
    (*buffer)[writePointer] = sample;
    writePointer = (writePointer + bufferSize - 1) % bufferSize;
}

template <typename SampleType>
SampleType LinearInterpolationCircularBuffer<SampleType>::popSample()
{
    SampleType returnValue = interpolateSample();
    readPointer = (readPointer + bufferSize - 1) % bufferSize;

    return returnValue;
}

template <typename SampleType>
SampleType LinearInterpolationCircularBuffer<SampleType>::interpolateSample()
{
    auto index1 = readPointer + delayInt;
    auto index2 = index1 + 1;

    if(index2 >= bufferSize)
    {
        index1 %= bufferSize;
        index2 %= bufferSize;
    }

    SampleType value1 = (*buffer)[index1];
    SampleType value2 = (*buffer)[index2];

    return value1 + delayFrac * (value2 - value1);
}

template <typename SampleType>
int LinearInterpolationCircularBuffer<SampleType>::getReadPointerIndex()
{
    return readPointer;
}

template <typename SampleType>
int LinearInterpolationCircularBuffer<SampleType>::getWritePointerIndex()
{
    return writePointer;
}

template <typename SampleType>
SampleType LinearInterpolationCircularBuffer<SampleType>::limitWithinRange(SampleType lowerLimit, SampleType upperLimit, SampleType value)
{
    return value < lowerLimit ? lowerLimit : (upperLimit < value ? upperLimit : value);
}

template class LinearInterpolationCircularBuffer<float>;
template class LinearInterpolationCircularBuffer<double>;

