#include <JuceHeader.h>
#include "Delay.h"
#include "iirFilter.h"

class Reverb
{
	public:

		Reverb();

		float getParameter(int index);
	    void setParameter(int index, float newValue);
   

	    void prepare(double sampleRate, int samplesPerBlock);
	    void process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels);

		enum Parameters
		{
			length = 0,
			feedback,
			wetMix,
			dryMix,
			Filter
		};

    //=======================================================================

	private:

		double m_SampleRate;

		void updateReverbParameters();

		float len = 0.09; //Length
		float g = 0.8;	//Feedback
		float dry = 0.5;
		float wet = 0.5;
		float filterValue = 20000.0;

		//TODO: Maybe do these in an array...

		Delay comb1, comb2, comb3, comb4; //TODO: Test the new Delay contructor and use it here if it works properly...
		IIRFilter filterLeft{ 44100, IIRFilter::FilterTypes::LPF, filterValue };
		IIRFilter filterRight{ 44100, IIRFilter::FilterTypes::LPF, filterValue };

		
	    
};