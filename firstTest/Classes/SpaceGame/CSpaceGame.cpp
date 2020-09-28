#include "CSpaceGame.hpp"

#include "audio/include/AudioEngine.h"

#include <cmath>

USING_NS_CC;



#define SPACE_GAME "SpaceGameResources/Sounds/SpaceGame.wav"
#define EXPLOSION_LARGE "SpaceGameResources/Sounds/explosion_large.wav"
#define LASER_SHIP "SpaceGameResources/Sounds/laser_ship.wav"


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



//// Hack to access CCPointObject (which is not a public class)
//class PointObject : public Ref {
//	CC_SYNTHESIZE(Point, _ratio, Ratio)
//	CC_SYNTHESIZE(Point, _offset, Offset)
//	CC_SYNTHESIZE(Node*, _child, Child)	// weak ref
//};
class PointObject : public Ref
{
public:
    static PointObject* create(Point ratio, Point offset)
    {
        PointObject* ret = new PointObject();
        ret->initWithPoint(ratio, offset);
        ret->autorelease();
        return ret;
    }

    bool initWithPoint(Point ratio, Point offset)
    {
        _ratio = ratio;
        _offset = offset;
        _child = nullptr;
        return true;
    }

    inline const Point& getRatio() const { return _ratio; };
    inline void setRatio(const Point& ratio) { _ratio = ratio; };

    inline const Point& getOffset() const { return _offset; };
    inline void setOffset(const Point& offset) { _offset = offset; };

    inline Node* getChild() const { return _child; };
    inline void setChild(Node* child) { _child = child; };

private:
    Point _ratio;
    Point _offset;
    Node* _child; // weak ref
};


// Need to provide a constructor
CSpaceGame::ParallaxNodeExtras::ParallaxNodeExtras() 
{
    ParallaxNode::create(); // call parent constructor
}

CSpaceGame::ParallaxNodeExtras* CSpaceGame::ParallaxNodeExtras::create()
{
    return new ParallaxNodeExtras();
}

void CSpaceGame::ParallaxNodeExtras::incrementOffset(Point offset, Node* node) 
{
    for (int i = 0; i < _parallaxArray->num; i++) {
        PointObject* point = (PointObject*)_parallaxArray->arr[i];
        Node* curNode = point->getChild();
        if (curNode ==/*->isEqual*/(node)) {
            point->setOffset(point->getOffset() + offset);
            break;
        }
    }
}



float CSpaceGame::getTimeTick() 
{
    timeval time;
    gettimeofday(&time, NULL);
    unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (float)millisecs;
}

float CSpaceGame::randomValueBetween(float low, float high) 
{
    // from http://stackoverflow.com/questions/686353/c-random-float-number-generation
    return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}

void CSpaceGame::setInvisible(Node* node)
{
    node->setVisible(false);
}



bool CSpaceGame::init()
{
    if (!Scene::init())
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // load all sprites
    m_batchNode = SpriteBatchNode::create("SpaceGameResources/Spritesheets/Sprites.pvr.ccz");
    this->addChild(m_batchNode);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpaceGameResources/Spritesheets/Sprites.plist");

    addCloseButton(visibleSize, origin);
    addShip(visibleSize);
    addBackgrund(visibleSize);
    addAsteroid(visibleSize);
    addLaser(visibleSize);


    //AudioEngine::play2d(SPACE_GAME, true, 1.0f);
    AudioEngine::preload(EXPLOSION_LARGE);
    AudioEngine::preload(LASER_SHIP);


    int audio_id = AudioEngine::play2d("d:/_GitHub/cocos2dx_c-/firstTest/Resources/SpaceGameResources/Sounds/SpaceGame.wav", true, 1.0f);



    m_lives = 3;
    double curTime = getTimeTick();
    m_gameOverTime = curTime + 30000;





    // creating a keyboard event listener
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(CSpaceGame::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(CSpaceGame::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    auto listener2 = EventListenerTouchAllAtOnce::create();
    listener2->onTouchesMoved = CC_CALLBACK_2(CSpaceGame::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);


    this->scheduleUpdate();

    return true;
}


void CSpaceGame::onFire()
{
    AudioEngine::play2d(LASER_SHIP);
    auto winSize = Director::getInstance()->getWinSize();
    auto shipLaser = m_shipLasers->at(m_nextShipLaser++);
    if (m_nextShipLaser >= m_shipLasers->size())
        m_nextShipLaser = 0;
    shipLaser->setPosition(m_ship->getPosition() + Point(shipLaser->getContentSize().width / 2, 0));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(
        Sequence::create(
            MoveBy::create(0.5, Point(winSize.width, 0)),
            CallFuncN::create(CC_CALLBACK_1(CSpaceGame::setInvisible, this)),
            NULL));
}




// Implementation of the keyboard event callback function prototype
void CSpaceGame::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    //log("Key with keycode %d pressed", keyCode);
}

void CSpaceGame::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);


    //const float duration = 0.25f;
    //const float delta = 20.0f;

    const float delta = 20.0f;
    const float maxDelta = 40.0f;

    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || keyCode == EventKeyboard::KeyCode::KEY_W)
    {
        //m_ship->runAction(MoveBy::create(duration, Vec2(0.0f, delta)));
        m_shipPointsPerSecY += delta;
        m_shipPointsPerSecY = MAX(m_shipPointsPerSecY, maxDelta);
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW || keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        //m_ship->runAction(MoveBy::create(duration, Vec2(0.0f, -delta)));
        m_shipPointsPerSecY -= delta;
        m_shipPointsPerSecY = MIN(m_shipPointsPerSecY, -maxDelta);
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        //m_ship->runAction(MoveBy::create(duration, Vec2(-delta, 0.0f)));
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        //m_ship->runAction(MoveBy::create(duration, Vec2(delta, 0.0f)));
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        onFire();
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


void CSpaceGame::update(float dt)
{
    Size winSize = Director::getInstance()->getWinSize();

    {
        auto backgroundScrollVert = Point(-1000, 0);
        m_backgroundNode->setPosition(m_backgroundNode->getPosition() + (backgroundScrollVert * dt));
    }

    //Parallax
    {
        auto spaceDusts = new Vector<Sprite*>(2);
        spaceDusts->pushBack(m_spaceDust1);
        spaceDusts->pushBack(m_spaceDust2);
        for (auto spaceDust : *spaceDusts)
        {
            float xPosition = m_backgroundNode->convertToWorldSpace(spaceDust->getPosition()).x;
            float size = spaceDust->getContentSize().width;
            if (xPosition < -size / 2)
            {
                m_backgroundNode->incrementOffset(Point(spaceDust->getContentSize().width * 2, 0), spaceDust);
            }
        }

        auto backGrounds = new Vector<Sprite*>(4);
        backGrounds->pushBack(m_galaxy);
        backGrounds->pushBack(m_planetSunrise);
        backGrounds->pushBack(m_spatialAnomaly1);
        backGrounds->pushBack(m_spatialAnomaly2);
        for (auto background : *backGrounds)
        {
            float xPosition = m_backgroundNode->convertToWorldSpace(background->getPosition()).x;
            float size = background->getContentSize().width;
            if (xPosition < -size)
            {
                m_backgroundNode->incrementOffset(Point(2000, 0), background);
            }
        }
    }


    //Acceleration
    {
        //const float delta = 20.0f;
        //const float maxDelta = 40.0f;

        //if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_W))
        //{
        //    m_shipPointsPerSecY += delta;
        //    m_shipPointsPerSecY = MAX(m_shipPointsPerSecY, maxDelta);
        //}

        //if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_S))
        //{
        //    //m_ship->runAction(MoveBy::create(duration, Vec2(0.0f, -delta)));
        //    m_shipPointsPerSecY -= delta;
        //    m_shipPointsPerSecY = MIN(m_shipPointsPerSecY, -maxDelta);
        //}




        float maxY = winSize.height - m_ship->getContentSize().height / 2;
        float minY = m_ship->getContentSize().height / 2;
        float diff = (m_shipPointsPerSecY * dt * 10);
        float newY = m_ship->getPosition().y + diff;
        newY = MIN(MAX(newY, minY), maxY);
        m_ship->setPosition(m_ship->getPosition().x, newY);

        if (std::abs(m_shipPointsPerSecY) > 0.001f)
        {
            m_shipPointsPerSecY = std::copysign(0.9f * std::abs(m_shipPointsPerSecY) - dt * 15, m_shipPointsPerSecY);
        }
        else
        {
            m_shipPointsPerSecY = 0.0f;
        }
    }

    float curTimeMillis = getTimeTick();

    // Asteroids
    {
        if (curTimeMillis > m_nextAsteroidSpawn) 
        {

            float randMillisecs = randomValueBetween(0.20F, 1.0F) * 1000;
            m_nextAsteroidSpawn = randMillisecs + curTimeMillis;

            float randY = randomValueBetween(0.0F, winSize.height);
            float randDuration = randomValueBetween(2.0F, 10.0F);

            Sprite* asteroid = m_asteroids->at(m_nextAsteroid);
            m_nextAsteroid++;

            if (m_nextAsteroid >= m_asteroids->size())
                m_nextAsteroid = 0;

            asteroid->stopAllActions();
            asteroid->setPosition(winSize.width + asteroid->getContentSize().width / 2, randY);
            asteroid->setVisible(true);
            asteroid->runAction(
                Sequence::create(
                    MoveBy::create(randDuration, Point(-winSize.width - asteroid->getContentSize().width, 0)),
                    CallFuncN::create(CC_CALLBACK_1(CSpaceGame::setInvisible, this)),
                    NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
            );
        }


        for (auto asteroid : *m_asteroids) 
        {
            if (!(asteroid->isVisible()))
                continue;
            for (auto shipLaser : *m_shipLasers) 
            {
                if (!(shipLaser->isVisible()))
                    continue;
                if (shipLaser->getBoundingBox().intersectsRect(asteroid->getBoundingBox())) {
                    AudioEngine::play2d(EXPLOSION_LARGE);
                    shipLaser->setVisible(false);
                    asteroid->setVisible(false);
                }
            }
            if (m_ship->getBoundingBox().intersectsRect(asteroid->getBoundingBox())) {
                asteroid->setVisible(false);
                m_ship->runAction(Blink::create(1.0F, 9));
                m_lives--;
            }
        }
    }


    if (m_lives <= 0) 
    {
        m_ship->stopAllActions();
        m_ship->setVisible(false);
        this->endScene(KENDREASONLOSE);
    }
    else if (curTimeMillis >= m_gameOverTime) 
    {
        this->endScene(KENDREASONWIN);
    }
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
    m_ship = Sprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
    m_ship->setPosition(visibleSize.width * 0.1f, visibleSize.height * 0.5f);
    m_batchNode->addChild(m_ship, 1);

    return true;
}

bool CSpaceGame::addBackgrund(const Size& visibleSize)
{
    m_backgroundNode = ParallaxNodeExtras::create();
    this->addChild(m_backgroundNode, -1);

    m_spaceDust1 = Sprite::create("SpaceGameResources/Backgrounds/bg_front_spacedust.png");
    m_spaceDust2 = Sprite::create("SpaceGameResources/Backgrounds/bg_front_spacedust.png");
    m_planetSunrise = Sprite::create("SpaceGameResources/Backgrounds/bg_planetsunrise.png");
    m_galaxy = Sprite::create("SpaceGameResources/Backgrounds/bg_galaxy.png");
    m_spatialAnomaly1 = Sprite::create("SpaceGameResources/Backgrounds/bg_spacialanomaly.png");
    m_spatialAnomaly2 = Sprite::create("SpaceGameResources/Backgrounds/bg_spacialanomaly2.png");

    auto dustSpeed = Point(0.1F, 0.1F);
    auto bgSpeed = Point(0.5F, 0.5F);

    m_backgroundNode->addChild(m_spaceDust1, 0, dustSpeed, Point(0, visibleSize.height / 2));
    m_backgroundNode->addChild(m_spaceDust2, 0, dustSpeed, Point(m_spaceDust1->getContentSize().width, visibleSize.height / 2));
    m_backgroundNode->addChild(m_galaxy, -1, bgSpeed, Point(0, visibleSize.height * 0.7f));
    m_backgroundNode->addChild(m_planetSunrise, -1, bgSpeed, Point(600, visibleSize.height * 0.0f));
    m_backgroundNode->addChild(m_spatialAnomaly1, -1, bgSpeed, Point(900, visibleSize.height * 0.3f));
    m_backgroundNode->addChild(m_spatialAnomaly2, -1, bgSpeed, Point(1500, visibleSize.height * 0.9f));

    CSpaceGame::addChild(ParticleSystemQuad::create("SpaceGameResources/Particles/Stars1.plist"));
    CSpaceGame::addChild(ParticleSystemQuad::create("SpaceGameResources/Particles/Stars2.plist"));
    CSpaceGame::addChild(ParticleSystemQuad::create("SpaceGameResources/Particles/Stars3.plist"));


    return true;
}

bool CSpaceGame::addAsteroid(const cocos2d::Size& visibleSize)
{
    const int KNUMASTEROIDS = 15;
    m_asteroids = new Vector<Sprite*>(KNUMASTEROIDS);
    for (int i = 0; i < KNUMASTEROIDS; ++i)
    {
        auto* asteroid = Sprite::createWithSpriteFrameName("asteroid.png");
        asteroid->setVisible(false);
        m_batchNode->addChild(asteroid);
        m_asteroids->pushBack(asteroid);
    }

    return true;
}

bool CSpaceGame::addLaser(const cocos2d::Size& visibleSize)
{
    const int KNUMLASERS = 15;

    m_shipLasers = new Vector<Sprite*>(KNUMLASERS);
    for (int i = 0; i < KNUMLASERS; ++i) 
    {
        auto shipLaser = Sprite::createWithSpriteFrameName("laserbeam_blue.png");
        shipLaser->setVisible(false);
        m_batchNode->addChild(shipLaser);
        m_shipLasers->pushBack(shipLaser);
    }

    return true;
}

void CSpaceGame::endScene(EndReason endReason) 
{
    if (m_gameOver)
        return;
    m_gameOver = true;

    auto winSize = Director::getInstance()->getWinSize();
    char message[10] = "You Win";
    if (endReason == KENDREASONLOSE)
        strcpy(message, "You Lose");
    auto label = Label::createWithBMFont("SpaceGameResources/fonts/Arial.fnt", message);
    label->setScale(0.1F);
    label->setPosition(winSize.width / 2, winSize.height * 0.6F);
    this->addChild(label);

    strcpy(message, "Restart");
    auto restartLabel = Label::createWithBMFont("SpaceGameResources/fonts/Arial.fnt", message);
    auto restartItem = MenuItemLabel::create(restartLabel, CC_CALLBACK_1(CSpaceGame::restartTapped, this));
    restartItem->setScale(0.1F);
    restartItem->setPosition(winSize.width / 2, winSize.height * 0.4);

    auto* menu = Menu::create(restartItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    // clear label and menu
    restartItem->runAction(ScaleTo::create(0.9F, 1.0F));
    label->runAction(ScaleTo::create(.9F, 1.0F));

    // Terminate update callback
    this->unscheduleUpdate();
}

void CSpaceGame::restartTapped(Ref* pSender) 
{
    Director::getInstance()->replaceScene(TransitionZoomFlipX::create(0.5, this->createScene()));
    // reschedule
    this->scheduleUpdate();
}


