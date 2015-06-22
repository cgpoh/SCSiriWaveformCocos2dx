/*
 * WaveNode.h
 *
 *  Created on: June 22, 2015
 *      Author: CG
 */

#ifndef WAVENODE_H_
#define WAVENODE_H_

#include "cocos2d.h"

class WaveNode : public cocos2d::Node
{
public:
	WaveNode();
	virtual ~WaveNode();

	virtual bool init();

	void update(float dt);
	
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	
private:
	cocos2d::Size m_visibleSize;
	
	// The frequency of the sinus wave. The higher the value, the more sinus wave peaks you will have. Default: 1.5
	float m_frequency;
	
	// The phase of the sinus wave. Default: 0.
	float m_phase;
	
	// The actual amplitude the view is visualizing. This amplitude is based on the microphone's amplitude
	float m_amplitude;
	
	// The color to draw the waves with. Default: white.
	cocos2d::Color4F m_waveColor;

	// The amplitude that is used when the incoming microphone amplitude is near zero. Setting a value greater 0 provides a more vivid visualization.
	float m_idleAmplitude;
	
	// The number of additional waves in the background. The more waves, to more CPU power is needed. Default: 4.
	float m_waves;
	
	// The phase shift that will be applied with each delivering of the microphone's value. A higher value will make the waves look more nervous. Default: -0.15.
	float m_phaseShift;
	
	// The lines are joined stepwise, the more dense you draw, the more CPU power is used. Default: 5.
	float m_density;
		
	/*
	 * Line width used for the primary wave
	 * Default: 3.0f
	 */
	float m_primaryWaveLineWidth;

	/*
	 * Line width used for all secondary waves
	 * Default: 1.0f
	 */
	float m_secondaryWaveLineWidth;
	
	// Set to NO, if you want the microphone to stop listening. Default: YES.
	bool m_listen;
};

#endif /* WAVENODE_H_ */