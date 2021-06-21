#include "GameOverScene.h"
#include "GameScene.h"
#include "Definitions.h"
USING_NS_CC;
unsigned int score;
Scene* GameOverScene::createScene(unsigned int tempScore)
{
    score = tempScore;
    return GameOverScene::create();
}

bool GameOverScene::init()
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


    /*auto tutorial = Sprite::create("img/tutorial.png");
    tutorial->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.5);
    this->addChild(tutorial);*/
    auto gameOver = Sprite::create("img/gameOver.png");
    gameOver->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.5);
    this->addChild(gameOver);
    auto playAgain = Sprite::create("img/playAgain.png");
    playAgain->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(playAgain);
    auto landSprite = Sprite::create("img/landSprite.png");
    landSprite->setPosition(184, 40);
    this->addChild(landSprite);
    auto playItem = MenuItemImage::create("img/playAgain.png", "img/playAgain.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
    playItem->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    UserDefault* def = UserDefault::getInstance();
    auto highScore = def->getIntegerForKey("HIGHSCORE FLAPPY", 0);

    if (score > highScore)
    {
        highScore = score;

        def->setIntegerForKey("HIGHSCORE FLAPPY", highScore);
    }

    def->flush();

    __String* tempScore = __String::createWithFormat("%i", score);

    auto currentScore = LabelTTF::create(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    currentScore->setPosition(Point(visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(currentScore);

    __String* tempHighScore = __String::createWithFormat("%i", highScore);

    auto highScoreLabel = LabelTTF::create(tempHighScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);

    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(Point(visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(highScoreLabel);
    return true;
}
void GameOverScene::GoToGameScene(cocos2d::Ref* sender)
{
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

