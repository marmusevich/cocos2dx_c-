#include "CSpaceGame.hpp"

USING_NS_CC;

Scene* CSpaceGame::createScene()
{
    return CSpaceGame::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    log("Error while loading: %s\n", filename);
    log("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CSpaceGame.cpp\n");
}


//auto sprite = Sprite::create("SpaceGameResources/Backgrounds/bg_spacialanomaly.png");
//if (sprite == nullptr)
//{
//    problemLoading("'HelloWorld.png'");
//}
//else
//{
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
//}


bool CSpaceGame::init()
{
    if (!Scene::init())
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



    addCloseButton(visibleSize, origin);
    addShip(visibleSize);
    addBackgrund(visibleSize);



    // creating a keyboard event listener
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(CSpaceGame::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(CSpaceGame::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    auto listener2 = EventListenerTouchAllAtOnce::create();
    listener2->onTouchesMoved = CC_CALLBACK_2(CSpaceGame::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);



    return true;
}



// Implementation of the keyboard event callback function prototype
void CSpaceGame::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
}

void CSpaceGame::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);


    const float duration = 0.25f;
    const float delta = 20.0f;

    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        m_ship->runAction(MoveBy::create(duration, Vec2(0.0f, delta)));
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        m_ship->runAction(MoveBy::create(duration, Vec2(0.0f, -delta)));
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        m_ship->runAction(MoveBy::create(duration, Vec2(-delta, 0.0f)));
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        m_ship->runAction(MoveBy::create(duration, Vec2(delta, 0.0f)));
    }


    

}

void CSpaceGame::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    auto diff = touches[0]->getDelta();

    auto node = m_backgroundNode/*getChildByTag(kTagNode)*/;
    auto currentPos = node->getPosition();
    node->setPosition(currentPos + diff);

    log("onTouchesMoved diff = ", diff);
}


void CSpaceGame::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

///-----------------


bool CSpaceGame::addCloseButton(const Size& visibleSize, const Vec2& origin)
{

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(CSpaceGame::menuCloseCallback, this));

    bool ret = !(closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0);

    if (ret)
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));

        // create menu, it's an autorelease object
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
    }
    else
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }

    return ret;
}

bool CSpaceGame::addShip(const Size& visibleSize)
{
    m_batchNode = SpriteBatchNode::create("SpaceGameResources/Spritesheets/Sprites.pvr.ccz");
    this->addChild(m_batchNode);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpaceGameResources/Spritesheets/Sprites.plist");
    m_ship = Sprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
    m_ship->setPosition(visibleSize.width * 0.1f, visibleSize.height * 0.5f);
    m_batchNode->addChild(m_ship, 1);

    return true;
}

bool CSpaceGame::addBackgrund(const Size& visibleSize)
{
    m_backgroundNode = ParallaxNode::create();
    this->addChild(m_backgroundNode, -1);

    m_spaceDust1 = Sprite::create("SpaceGameResources/Backgrounds/bg_front_spacedust.png");
    m_spaceDust2 = Sprite::create("SpaceGameResources/Backgrounds/bg_front_spacedust.png");
    m_planetSunrise = Sprite::create("SpaceGameResources/Backgrounds/bg_planetsunrise.png");
    m_galaxy = Sprite::create("SpaceGameResources/Backgrounds/bg_galaxy.png");
    m_spatialAnomaly1 = Sprite::create("SpaceGameResources/Backgrounds/bg_spacialanomaly.png");
    m_spatialAnomaly2 = Sprite::create("SpaceGameResources/Backgrounds/bg_spacialanomaly2.png");

    auto bgSpeed = Point(0.5F, 0.5F);

    //m_backgroundNode->addChild(m_spaceDust1, 0, dustSpeed, Point(0, visibleSize.height / 2));
    //m_backgroundNode->addChild(m_spaceDust2, 0, dustSpeed, Point(_spaceDust1->getContentSize().width, visibleSize.height / 2));
    m_backgroundNode->addChild(m_galaxy, -1, bgSpeed, Point(0, visibleSize.height * 0.7f));
    m_backgroundNode->addChild(m_planetSunrise, -1, bgSpeed, Point(600, visibleSize.height * 0.0f));
    m_backgroundNode->addChild(m_spatialAnomaly1, -1, bgSpeed, Point(900, visibleSize.height * 0.3f));
    m_backgroundNode->addChild(m_spatialAnomaly2, -1, bgSpeed, Point(1500, visibleSize.height * 0.9f));


    return true;
}

