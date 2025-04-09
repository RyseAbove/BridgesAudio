#include "AudioClip.h"
#include <iostream>
#include <fstream>
#include "Bridges.h"
#include <math.h>

using namespace std;
using namespace bridges;

/** 
 * Return a new AudioClip of the two AudioClips mixed together
*/
AudioClip mixClips(const AudioClip& ac1, const AudioClip& ac2, float duration) {
	cout << "Entered mix clip function" << endl;
  if (ac1.getSampleRate() != ac2.getSampleRate()) 
    try {
		throw "can't mix audio clips of varying rates";
	} catch (const string& e) {
		cout << "Caught error: " << e << endl;
	}
  

  //create an audio clip configured appropriately
  int SAMPLE_RATE = ac1.getSampleRate();
  int sampleCount = SAMPLE_RATE * duration;
  
  AudioClip acMix = AudioClip(sampleCount, 1, ac1.getSampleBits(), SAMPLE_RATE);

  cout << "Mix clip created" << endl;
  
  // Loop through the samples of both clips and use the average amplitude value
  // TODO
  for (int i = 0; i < acMix.getSampleCount(); i++) {
	int sample1 = ac1.getSample(0, i);
	int sample2 = ac2.getSample(0, i);
	acMix.setSample(0, i, (sample1 + sample2) / 2);
	cout << "Mix loop" << endl;
  }
  
  return acMix;
}	

AudioClip mixClips(const AudioClip& ac1, const AudioClip& ac2) {
  // If no duration is given then just use the minimum song duration
	cout << "Returning mix clip wihtout duration given" << endl;
  return mixClips(ac1, ac2, min((float)ac1.getSampleCount() / ac1.getSampleRate(), (float)ac2.getSampleCount()  / ac2.getSampleRate()));
}

AudioClip mixFadeClips(const AudioClip& ac1, const AudioClip& ac2, float duration) {
	cout << "Entered fade clip function" << endl;
	if (ac1.getSampleRate() != ac2.getSampleRate())
    	try {
			throw "can't mix audio clips of varying rates";
		} catch (const string& e) {
			cout << "Caught error: " << e << endl;
		}
	

	int sampleRate = ac1.getSampleRate();
	int sampleCount = sampleRate * duration;

	AudioClip acMix = AudioClip(sampleCount, 1, ac1.getSampleBits(), sampleRate);

	cout << "Fade clip created" << endl;

	for (int i = 0; i < acMix.getSampleCount(); i++) {
		float fadeFactor = static_cast<float>(i) / (sampleCount - 1);
		int sample1 = ac1.getSample(0, i);
		int sample2 = ac2.getSample(0, i);
		int mixedSample = (1 - fadeFactor) * sample1 + fadeFactor * sample2;
		cout << "Fade loop";

		acMix.setSample(0, i, mixedSample);
	}

	return acMix;
}

AudioClip slowClip(const AudioClip& ac1, float duration) {
	cout << "Entered slow clip function" << endl;
	int sampleRate = ac1.getSampleRate();
	int sampleCount = sampleRate * duration;

	//AudioClip acSlow = AudioClip(sampleCount, 1, ac1.getSampleSize(), sampleRate);
	AudioClip slowClip(sampleCount * 2, 1, ac1.getSampleBits(), 0.5);

	cout << "Slow clip created" << endl;

	return slowClip;
	
}

int main() {
	cout << "Entered main" << endl;

    Bridges bridges = Bridges(133, "mchlyng97", "396628113786");
    bridges.setTitle("Audio Mixing");
    bridges.setDescription("Mixing two AudioClips together");

	
    // Load the clips
	cout << "Loading clips" << endl;
    AudioClip acPiano = AudioClip("piano.wav");
	cout << "Piano loaded" << endl;
    bridges.setDataStructure(acPiano);
    bridges.visualize();
   	
	AudioClip acBass = AudioClip("bass.wav");
	cout << "Bass loaded" << endl;
    bridges.setDataStructure(acBass);
    bridges.visualize();
	cout << "Clips loaded" << endl;
    
    // Apply simple mixing of the two AudioClips and visualize
	cout << "Mixing" << endl;
    AudioClip acMix = mixClips(acPiano, acBass);
    bridges.setDataStructure(acMix);
    bridges.visualize();
	cout << "Mixed" << endl;

	// Fade mixing of the two AudioClips and visualize
	cout << "Fading" << endl;
	AudioClip acFadeMix = mixFadeClips(acPiano, acBass, 5);
	bridges.setDataStructure(acFadeMix);
	bridges.visualize();
	cout << "Faded" << endl;

	// Slow down one AudioClip
	cout << "Slowing" << endl;
	AudioClip acSlow = slowClip(acSlow, acSlow.getSampleCount());
	bridges.setDataStructure(acSlow);
	bridges.visualize();
	cout << "Slowed" << endl;	

    return 0;
}
