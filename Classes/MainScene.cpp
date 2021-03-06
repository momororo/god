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
    //cocostudioのMainSceneを読みこませる
    auto mainScene = CSLoader::getInstance() -> createNode("MainScene.csb");
    mainScene -> setName("mainScene");
    this -> addChild(mainScene);
    
    //各種ボタン作成へ
    makeButton();
    
    
    /*
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
     */


    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    
    
    //確率仮うち
    MainScene::prayPercentage = 20;
    
    log("横は%f、縦は%f",visibleSize.width,visibleSize.height);
    log("xは%f、yは%f",origin.x,origin.y);

/*
    auto bk = Sprite::create();
    bk->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
    bk->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    bk->setColor(Color3B::WHITE);
    this->addChild(bk);
*/
    /*
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("god.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    // add the sprite as a child to this layer
    this->addChild(sprite);
    */
    
    return true;
}

void MainScene::makeButton(){
    
    /**********************  各種ボタン・スプライト作成  ***************************/
    
    //設定画面表示ボタン作成
    auto settingBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("settingBt"));
    
    
    //確率設定画面
        //設定画面
        auto configuration = dynamic_cast<Sprite*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("configuration"));
    
        //決定ボタン
        auto decideBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("configuration")->getChildByName("decideBt"));
    
        //入力画面
        //Scale9Spriteが画像を引き延ばしをしてくれるので便利
        auto _input = EditBox::create(Size(300.0f,100.0f), Scale9Sprite::create());
        _input->setAnchorPoint(Point(0.5,0.5));
        _input->setPosition(Vec2(configuration->getContentSize().width/2,configuration->getContentSize().height/2));
        _input->setMaxLength(6); //６文字制限
        _input->setFont(PIXELMPLUS_FONT,30);
        _input->setFontSize(80);
        _input->setFontColor(Color3B::BLACK);
        _input->setPlaceHolder(StringUtils::format("%f",MainScene::prayPercentage).c_str());
        _input->setPlaceholderFont(PIXELMPLUS_FONT, 30);
        _input->setPlaceholderFontColor(Color3B::BLACK);
            //    _input->setContentSize(Size(winSize.width/2,winSize.height/2));
        _input->setDelegate(this);
        _input->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
        _input->setReturnType(EditBox::KeyboardReturnType::DONE);
        configuration ->addChild(_input);
    
    //祈るボタン作成
    auto prayBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("prayBt"));
    
    //やめるボタン作成
    auto quiteBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("quiteBt"));
    
    
    
    /************************** 各種ボタン・スプライト作成(終) *****************************/
    
    /************************** 各種ボタンの動作 *****************************/
    
    //設定画面表示ボタンの動作
    settingBt -> addTouchEventListener([&](Ref* pSender,ui::Widget::TouchEventType type){
        
        //タップ終わり時、設定画面を出す
        if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
            
            auto configuration = dynamic_cast<Sprite*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("configuration"));
            //設定画面の可視化
            configuration -> setVisible(true);
            //決定ボタンのタッチ可
            auto decideBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("configuration")->getChildByName("decideBt"));
            decideBt -> setTouchEnabled(true);
            
        }
    });
    
    
    //決定ボタン(設定画面内にある)の動作
    decideBt -> addTouchEventListener([&](Ref* pSender,ui::Widget::TouchEventType type){
        
        //タップ終わり時、設定画面を非表示、祈るボタンの追加
        if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
            
            //設定ボタンの非表示＆操作不可
            auto settingBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("settingBt"));
            settingBt -> setVisible(false);
            settingBt -> setTouchEnabled(false);
            
            //設定画面の非表示
            auto configuration = dynamic_cast<Sprite*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("configuration"));
            configuration -> setVisible(false);
            
                //決定ボタンのタッチ不可に(念のため)
                auto decideBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("configuration")->getChildByName("decideBt"));
                decideBt -> setTouchEnabled(false);
            
            //祈るボタンの表示
            auto prayBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("prayBt"));
            prayBt -> setVisible(true);
            prayBt -> setTouchEnabled(true);
            
            //やめるボタンの表示
            auto quiteBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("quiteBt"));
            quiteBt -> setVisible(true);
            quiteBt -> setTouchEnabled(true);
            
            
        }
    });
    
    //祈るボタンの動作
    prayBt -> addTouchEventListener([&](Ref* pSender,ui::Widget::TouchEventType type){
        
        //タップ終わり時、祈りの判定
        if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
            
            //抽選
            this->goodLuck();
            
        }
    });
    
    //やめるボタンの動作
    quiteBt -> addTouchEventListener([&](Ref* pSender,ui::Widget::TouchEventType type){
        
        //タップ終わり時、祈りの判定
        if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
            
            //祈るボタンの非表示
            auto prayBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("prayBt"));
            prayBt -> setVisible(false);
            prayBt -> setTouchEnabled(false);
            
            //やめるボタンの非表示
            auto quiteBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("quiteBt"));
            quiteBt -> setVisible(false);
            quiteBt -> setTouchEnabled(false);
            
            //設定ボタンの表示
            auto settingBt = dynamic_cast<ui::Button*>(this -> getChildByName("mainScene")->getChildByName("haikei")->getChildByName("settingBt"));
            settingBt -> setVisible(true);
            settingBt -> setTouchEnabled(true);
            
        }
    });
    
    /************************* 各種動作(終) *******************************/
    

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

