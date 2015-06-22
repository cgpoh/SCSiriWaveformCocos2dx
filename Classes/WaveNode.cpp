/*
 * WaveNode.cpp
 *
 *  Created on: June 22, 2015
 *      Author: CG
 */

#include "WaveNode.h"

USING_NS_CC;

WaveNode::WaveNode()
	: Node()
{
}

WaveNode::~WaveNode()
{
}

bool WaveNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	m_frequency = 1.5;
	m_phase = 0;
	m_amplitude = 1.0;
	m_waveColor = Color4F(1, 1, 1, 1);
	m_idleAmplitude = 0.01f;
	m_waves = 5;
	m_phaseShift = -0.15;
	m_density = 5.0;
	m_primaryWaveLineWidth = 3.0f;
	m_secondaryWaveLineWidth = 1.0f;
	m_listen = true;
	
	m_visibleSize = Director::getInstance()->getVisibleSize();
	
	return true;
}

void WaveNode::update(float dt)
{	
	m_phase += m_phaseShift;
	m_amplitude = fmax(0.1f, m_idleAmplitude);
}

void WaveNode::onDraw(const Mat4& transform, uint32_t flags)
{
	// We draw multiple sinus waves, with equal phases but altered amplitudes, multiplied by a parable function.
	for (int i = 0; i <m_waves; i++)
	{
		glLineWidth(i == 0 ? m_primaryWaveLineWidth : m_secondaryWaveLineWidth);
		
		float halfHeight = m_visibleSize.height * 0.5f;
		float width = m_visibleSize.width;
		float mid = width * 0.5f;
		
		const float maxAmplitude = halfHeight - 4.0f; // 4 corresponds to twice the stroke width

		// Progress is a value between 1.0 and -0.5, determined by the current wave idx, which is used to alter the wave's amplitude.
		float progress = 1.0f - (float)i / m_waves;
		float normedAmplitude = (1.5f * progress - 0.5f) * m_amplitude;
		
		float multiplier = MIN(1.0, (progress / 3.0f * 2.0f) + (1.0f / 3.0f));
		m_waveColor.a = multiplier * m_waveColor.a;
		
		DrawPrimitives::setDrawColor4F(m_waveColor.r, m_waveColor.g, m_waveColor.b, m_waveColor.a);
				
		Vec2* pts = new Vec2[(int)width + (int)m_density];
		int counter = 0;
		
		for (float x = 0; x<width + m_density; x += m_density)
		{
			// We use a parable to scale the sinus wave, that has its peak in the middle of the view.
			float scaling = -pow(1 / mid * (x - mid), 2) + 1;
			
			float y = scaling * maxAmplitude * normedAmplitude * sinf(2 * M_PI *(x / width) * m_frequency + m_phase) + halfHeight;
			
			pts[counter++] = Vec2(x, y);
		}
		
		DrawPrimitives::drawPoly(pts, counter, false);
		delete[] pts;
	}
}