#include "Bird.h"
#include <iostream>
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(cocos2d::Scene* scene)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    flappyBird = Sprite::create("img/bird_0.png");
    CCLOG("%f", visibleSize.width / 2 + origin.x);
    flappyBird->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+100));

    auto flappyBody = PhysicsBody::createCircle(flappyBird->getContentSize().width / 2);
    flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    flappyBody->setContactTestBitmask(true);



    flappyBird->setPhysicsBody(flappyBody);

    scene->addChild(flappyBird);

    isFalling = true;
}

void Bird::Fall()
{
    if (isFalling)
    {
        flappyBird->setPositionY(flappyBird->getPositionY() - (BIRD_FALLING_SPEED * visibleSize.height));
    }
    else
    {
        flappyBird->setPositionY(flappyBird->getPositionY() + (BIRD_FLYING_SPEED * visibleSize.height));
    }
}