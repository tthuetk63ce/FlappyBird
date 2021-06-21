#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"

class Bird
{
public:
    Bird(cocos2d::Scene* scene);

    void Fall();
    void StopFlying() { isFalling = true; };
    void Fly() { isFalling = false; };

private:    
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite* flappyBird;

    bool isFalling;

};

#endif // __BIRD_H__
