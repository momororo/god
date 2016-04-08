#ifndef __MainScene_H__
#define __MainScene_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
using namespace cocos2d::ui;

class MainScene : public cocos2d::Layer, public EditBoxDelegate
{
public:
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    float prayPercentage;
    
    // a selector callback
    void prayCallback(cocos2d::Ref* pSender);
    
    // a selector callback
    void configCallback(cocos2d::Ref* pSender);

    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    //抽選
    void goodLuck();
    
    //確率の変更
    void editLuck();
    
    //文字を入力し始めると実行される
    virtual void editBoxEditingDidBegin(EditBox* editBox);
    
    //文字の入力が終わると実行される
    virtual void editBoxEditingDidEnd(EditBox* editBox);
    //文字の入力中に実行される
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
    
    //returnを押したら実行される
    virtual void editBoxReturn(EditBox* editBox);
    
};

#endif // __MainScene_H__
