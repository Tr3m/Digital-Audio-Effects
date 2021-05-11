#include <JuceHeader.h>
#include "Delay.h"

class Reverb
{
	public:

		Reverb();

		float getParameter(int index);
	    void setParameter(int index, float newValue);

	    //TODO: Need to add a reverb time calculator function.
	   

	    void prepare(double sampleRate, int samplesPerBlock);
	    void process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels);

	    //TODO: Add Parameters Enum

    //=======================================================================

	private:

		//TODO: Maybe do these in an array or something...

		Delay comb1, comb2, comb3, comb4; //TODO: Test the new Delay contructor and use it here if it works properly...

		//juce::AudioBuffer<float> buff_1, buff_2, buff_3, buff_4;
	    
};