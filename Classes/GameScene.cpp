#include "GameScene.h"
#include <iostream>
#include "GameOverScene.h"
#include "Definitions.h"
USING_NS_CC;
using namespace std;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld();
        //->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));
    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // màn hình
    /*auto background = Sprite::create("img/bg.png");
    background->setPosition(origin + visibleSize / 2);
    this->addChild(background);*/
    auto landSprite = Sprite::create("img/landSprite.png");
    landSprite->setPosition(184, 40);
    this->addChild(landSprite);
    auto landAnimation = Animation::create();
    landAnimation->setDelayPerUnit(0.2f);
    landAnimation->setLoops(-1);
    landAnimation->addSpriteFrame(Sprite::create("img/landSprite.png")->getSpriteFrame());
    landAnimation->addSpriteFrame(Sprite::create("img/land_0.png")->getSpriteFrame());
    landAnimation->addSpriteFrame(Sprite::create("img/land_1.png")->getSpriteFrame());
    landAnimation->addSpriteFrame(Sprite::create("img/land_2.png")->getSpriteFrame());
    Animate* landAnimate = Animate::create(landAnimation);
    landSprite->runAction(landAnimate);




    
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 1);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);
    //Vật cản
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);

    //Character
    bird = new Bird(this);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


    score = 0;

    __String* tempScore = __String::createWithFormat("%i", score);
    scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));
    this->addChild(scoreLabel, 10000);

    this->scheduleUpdate();
     

    return true;
}

void GameScene::SpawnPipe(float m_pipe)
{
    pipe.SpawnPipe(this);
}
bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        
        auto scene = GameOverScene::createScene(score);

        Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
    }
    else if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        score++;
        CCLOG("AAAAAAAAAAAAAA");
        __String* tempScore = __String::createWithFormat("%i", score);

        scoreLabel->setString(tempScore->getCString());
    }
    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    bird->Fly();
    this->scheduleOnce(schedule_selector(GameScene::StopFlying), BIRD_FLY_DURATION);
    return true;
}
void GameScene::StopFlying(float s_bird)
{
    bird->StopFlying();
}

void GameScene::update(float up_bird)
{
    bird->Fall();
}