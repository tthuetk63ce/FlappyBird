#ifndef __PIPE_H__
#define __PIPE_H__

#include "cocos2d.h"

class Pipe 
{
private: 
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
public:
    Pipe();

    void SpawnPipe(cocos2d::Scene* scene);
    void update(float dt);

};

#endif // __PIPE_H__
