#include "MainScene.h"


#define PIXELMPLUS_FONT "fonts/PixelMplus10-Regular.ttf"
USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
/*
    //背景の作成
    auto bk = Sprite::create();
    bk->setTexture("");
*/
    //ボタンの作成
    auto configItem = MenuItemImage::create(
                                           "set_config.png",
                                           "set_config.png",
                                           CC_CALLBACK_1(MainScene::configCallback, this));
    
	configItem->setPosition(Vec2(origin.x + visibleSize.width - configItem->getContentSize().width/2 ,configItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto configMenu = Menu::create(configItem, NULL);
    configMenu->setPosition(Vec2::ZERO);
    
    this->addChild(configMenu, 1);
    
    //ボタンの作成
    auto prayItem = MenuItemImage::create(
                                           "pray.png",
                                           "pray.png",
                                           CC_CALLBACK_1(MainScene::prayCallback, this));
    
    prayItem->setPosition(Vec2(prayItem->getContentSize().width/2 ,visibleSize.height-prayItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto prayMenu = Menu::create(prayItem, NULL);
    prayMenu->setPosition(Vec2::ZERO);
    
    this->addChild(prayMenu, 1);


    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    
    
    //確率仮うち
    MainScene::prayPercentage = 20;
    
    log("横は%f、縦は%f",visibleSize.width,visibleSize.height);
    log("xは%f、yは%f",origin.x,origin.y);


    auto bk = Sprite::create();
    bk->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
    bk->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    bk->setColor(Color3B::WHITE);
    this->addChild(bk);

    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("god.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    // add the sprite as a child to this layer
    this->addChild(sprite);
    
    return true;
}


//抽選
void MainScene::goodLuck(){
    
    
    //抽選
    
    if(arc4random_uniform(100 / MainScene::prayPercentage) == 0){
        
        //あたってしまった演出
        log("当たっちゃったよ");
        
    }else{
        
        //外し演出
        log("外れたよ");
    }

    
    
}

//編集
void MainScene::editLuck(){
    
    
    
    
}

void MainScene::prayCallback(Ref* pSender)
{
    this->goodLuck();
/*
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
 */
}

void MainScene::configCallback(Ref* pSender)
{
    this->goodLuck();
    /*
     Director::getInstance()->end();
     
     #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
     exit(0);
     #endif
     */
    
    Size winSize = Director::getInstance()->getVisibleSize();
    
    auto config = Sprite::create("config.png");
    config->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(config);
    
    
    //Scale9Spriteが画像を引き延ばしをしてくれるので便利
    auto _input = EditBox::create(Size(300.0f,100.0f), Scale9Sprite::create("input.png"));
   	_input->setAnchorPoint(Point(0.5,0.5));
    _input->setPosition(Vec2(config->getContentSize().width/2, config->getContentSize().height/2));
    _input->setMaxLength(6); //６文字制限
    _input->setFont(PIXELMPLUS_FONT,30);
    _input->setFontSize(30);
    _input->setFontColor(Color3B::BLACK);
    _input->setPlaceHolder(StringUtils::format("%f",MainScene::prayPercentage).c_str());
    _input->setPlaceholderFont(PIXELMPLUS_FONT, 30);
    _input->setPlaceholderFontColor(Color3B::BLACK);
//    _input->setContentSize(Size(winSize.width/2,winSize.height/2));
    _input->setDelegate(this);
    _input->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
    _input->setReturnType(EditBox::KeyboardReturnType::DONE);
    config->addChild(_input);
}

void MainScene::editBoxEditingDidBegin(EditBox* editBox){
}

void MainScene::editBoxEditingDidEnd(EditBox* editBox){
    
    log("入力おわり");
    std::string value = editBox->getPlaceHolder();
    
    
}

void MainScene::editBoxTextChanged(EditBox* editBox, const std::string& text){
}

void MainScene::editBoxReturn(EditBox* editBox){
    
    
}

