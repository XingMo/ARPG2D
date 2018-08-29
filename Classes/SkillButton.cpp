#include "SkillButton.h"

USING_NS_CC;

SkillButton::SkillButton() :
mItemSkill(NULL),
mMenuSkill(NULL),
mStencil(NULL),
mProgressTimer(NULL),
mCDTime(1.f)
{

}
SkillButton::~SkillButton()
{

}

SkillButton* SkillButton::createSkillButton(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, Skill_type type)
{
	SkillButton* skillButton = new SkillButton();
	if (skillButton && skillButton->init(cdTime, stencil_file_name, button_normal_name, button_click_name, type))
	{
		skillButton->autorelease();
		return skillButton;
	}
	else
	{
		delete skillButton;
		skillButton = NULL;
	}

	return NULL;
}

bool SkillButton::init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, Skill_type type)
{
	//在底层添加技能按钮
	mItemSkill = MenuItemImage::create(button_normal_name, button_click_name, [=](Ref *){
		//使用技能
		switch (type){
		case JUMP:
			hero->actJump();
			break;
		default:
			break;
		}
	});
	mItemSkill->setPosition(CCPointZero);
	mMenuSkill = CCMenu::create(mItemSkill, NULL);
	mMenuSkill->setPosition(CCPointZero);
	addChild(mMenuSkill, -100);

	//在中间层添加阴影模版
	mStencil = CCSprite::create(stencil_file_name);
	mStencil->setPosition(CCPointZero);
	mStencil->setVisible(false);
	addChild(mStencil);

	//在最上层添加旋转进度条精灵
	CCSprite* progressSprite = CCSprite::create(button_normal_name);
	mProgressTimer = CCProgressTimer::create(progressSprite);
	mProgressTimer->setPosition(CCPointZero);
	mProgressTimer->setVisible(false);
	addChild(mProgressTimer, 100);

	mCDTime = cdTime;
	return true;
}

void SkillButton::skillClickCallBack(cocos2d::CCObject* obj)
{
	//冷却计时
	mItemSkill->setEnabled(false);
	//显示蒙版
	mStencil->setVisible(true);

	//设置精灵进度条为顺时针
	mProgressTimer->setVisible(true);
	mProgressTimer->setType(kCCProgressTimerTypeRadial);

	//技能冷却动画
	CCActionInterval* action_progress_to = CCProgressTo::create(mCDTime, 100);
	CCCallFunc* action_callback = CCCallFuncN::create(this, callfuncN_selector(SkillButton::skillCoolDownCallBack));
	mProgressTimer->runAction(CCSequence::create(action_progress_to, action_callback, NULL));
}

void SkillButton::skillCoolDownCallBack(CCNode* node)
{
	//冷却结束后将各种冷却时的精灵隐藏
	//蒙板不可见
	mStencil->setVisible(false);

	//进度条精灵不可见
	mProgressTimer->setVisible(false);

	//技能按钮变为可用状态
	mItemSkill->setEnabled(true);
}

void SkillButton::setHero(Hero* h){
	this->hero = h;
}

//添加技能按钮
//以下代码加入到场景的init
//SkillButton* mSkillButton = SkillButton::createSkillButton(2.f, "Sprite-0008.png", "CloseNormal.png", "CloseSelected.png", JUMP);
//mSkillButton->setHero(hero);
//mSkillButton->setPosition(VISIBLE_SIZE.width * 2 / 3, VISIBLE_SIZE.height / 3);
//addChild(mSkillButton);