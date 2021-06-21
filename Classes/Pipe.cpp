#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::SpawnPipe(cocos2d::Scene* scene)
{

    auto topPipe = Sprite::create("img/pipe2.png");
    auto bottomPipe = Sprite::create("img/pipe2.png");
    auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
    auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());
    auto random = CCRANDOM_0_1();
    
    if (random < LOWER_SCREEN_PIPE_THRESHOLD)
    {
        random = LOWER_SCREEN_PIPE_THRESHOLD;
    }
    else if (random > UPPER_SCREEN_PIPE_THRESHOLD)
    {
        random = UPPER_SCREEN_PIPE_THRESHOLD;
    }

    auto topPipePosition = (random * visibleSize.height) + (topPipe->getContentSize().height/2);
    topPipeBody->setDynamic(false);
    bottomPipeBody->setDynamic(false);
    topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topPipeBody->setContactTestBitmask(true);
    bottomPipeBody->setContactTestBitmask(true);
    topPipe->setPhysicsBody(topPipeBody);
    bottomPipe->setPhysicsBody(bottomPipeBody);
    

    topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition));
    bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - (Sprite::create("img/bird_0.png")->getContentSize().height * PIPE_GAP) - topPipe->getContentSize().height));
    auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0));
    auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0));
    topPipe->runAction(topPipeAction);
    bottomPipe->runAction(bottomPipeAction);
    
    

    auto pointNode = Node::create();
    auto pointBody = PhysicsBody::createBox(Size(1, Sprite::create("img/bird_0.png")->getContentSize().height * PIPE_GAP));

    pointBody->setDynamic(false);
    pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
    pointBody->setContactTestBitmask(true);

    pointNode->setPhysicsBody(pointBody);
    pointNode->setPosition(Point(topPipe->getPositionX(), topPipe->getPositionY() - (topPipe->getContentSize().height / 2) - ((Sprite::create("img/bird_0.png")->getContentSize().height * PIPE_GAP) / 2)));

    auto pointNodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0));

    pointNode->runAction(pointNodeAction);

    scene->addChild(topPipe);
    scene->addChild(bottomPipe);
    scene->addChild(pointNode);
}
