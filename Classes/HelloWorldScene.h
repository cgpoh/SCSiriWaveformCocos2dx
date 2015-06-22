#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class WaveNode;

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	
	virtual ~HelloWorld();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	
	virtual void onEnter();
	
	virtual void onExit();
	
	virtual void update(float delta);
	
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
		
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
protected:
	void createWave();
	
private:
	WaveNode* m_pWaveNode;
	
	cocos2d::CustomCommand mCustomCommand;
};

#endif // __HELLOWORLD_SCENE_H__
