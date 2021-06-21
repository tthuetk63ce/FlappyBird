#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameScene.h"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create("img/bg.png");
    background->setPosition(origin + visibleSize / 2);
    this->addChild(background);
    

    auto tutorial = Sprite::create("img/tutorial.png");
    tutorial->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/1.5);
    this->addChild(tutorial);
    auto getReady = Sprite::create("img/getReady.png");
    getReady->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(getReady);
    auto landSprite = Sprite::create("img/landSprite.png");
    landSprite->setPosition(184,40);
    this->addChild(landSprite);
    auto playItem = MenuItemImage::create("img/getReady.png", "img/getReady.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playItem->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);
    /*auto landAnimation = Animation::create();
    landAnimation->setDelayPerUnit(0.2f);
    landAnimation->setLoops(-1);
    landAnimation->addSpriteFrame(Sprite::create("img/landSprite.png")->getSpriteFrame());
    landAnimation->addSpriteFrame(Sprite::create("img/land_0.png")->getSpriteFrame());
    landAnimation->addSpriteFrame(Sprite::create("img/land_1.png")->getSpriteFrame());
    landAnimation->addSpriteFrame(Sprite::create("img/land_2.png")->getSpriteFrame());
    Animate* landAnimate = Animate::create(landAnimation);
    landSprite->runAction(landAnimate);*/
    return true;
}
void MainMenuScene::GoToGameScene(cocos2d::Ref* sender)
{
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

