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

SkillButton* SkillButton::createSkillButton(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name)
{
	SkillButton* skillButton = new SkillButton();
	if (skillButton && skillButton->init(cdTime, stencil_file_name, button_normal_name, button_click_name))
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

bool SkillButton::init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name)
{
	//�ڵײ���Ӽ��ܰ�ť
	mItemSkill = CCMenuItemImage::create(button_normal_name, button_click_name, this, menu_selector(SkillButton::skillClickCallBack));
	mItemSkill->setPosition(CCPointZero);
	mMenuSkill = CCMenu::create(mItemSkill, NULL);
	mMenuSkill->setPosition(CCPointZero);
	addChild(mMenuSkill, -100);

	//���м�������Ӱģ��
	mStencil = CCSprite::create(stencil_file_name);
	mStencil->setPosition(CCPointZero);
	mStencil->setVisible(false);
	addChild(mStencil);

	//�����ϲ������ת����������
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
	//ʹ�ü���
	hero->actJump();
	//��ȴ��ʱ
	mItemSkill->setEnabled(false);
	//��ʾ�ɰ�
	mStencil->setVisible(true);

	//���þ��������Ϊ˳ʱ��
	mProgressTimer->setVisible(true);
	mProgressTimer->setType(kCCProgressTimerTypeRadial);

	//������ȴ����
	CCActionInterval* action_progress_to = CCProgressTo::create(mCDTime, 100);
	CCCallFunc* action_callback = CCCallFuncN::create(this, callfuncN_selector(SkillButton::skillCoolDownCallBack));
	mProgressTimer->runAction(CCSequence::create(action_progress_to, action_callback, NULL));
}

void SkillButton::skillCoolDownCallBack(CCNode* node)
{
	//��ȴ�����󽫸�����ȴʱ�ľ�������
	//�ɰ岻�ɼ�
	mStencil->setVisible(false);

	//���������鲻�ɼ�
	mProgressTimer->setVisible(false);

	//���ܰ�ť��Ϊ����״̬
	mItemSkill->setEnabled(true);
}

void SkillButton::setHero(Hero* h){
	this->hero = h;
}

//��Ӽ��ܰ�ť
//���´�����뵽������init
//SkillButton* mSkillButton = SkillButton::createSkillButton(2.f, "Sprite-0008.png", "CloseNormal.png", "CloseSelected.png");
//mSkillButton->setHero(hero);
//mSkillButton->setPosition(VISIBLE_SIZE.width * 2 / 3, VISIBLE_SIZE.height / 3);
//addChild(mSkillButton);