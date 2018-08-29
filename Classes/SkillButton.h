#ifndef _SKILLBUTTON_H_
#define _SKILLBUTTON_H_
#include <cocos2d.h>
#include "Hero.h"

class SkillButton : public cocos2d::CCNode
{
public:
	SkillButton();
	virtual ~SkillButton();
	//�������ܰ�ť
	static SkillButton* createSkillButton(float cdTime,
		const char* stencil_file_name,
		const char* button_normal_name,
		const char* button_click_name);

	//����CDԤ���ӿ�
	void setCDTime(float time) { mCDTime = time; }
	float getCDTime() const { return mCDTime; }

	//������ܻص�
	void skillClickCallBack(cocos2d::CCObject* obj);

	//��ȴ�����ص�
	void skillCoolDownCallBack(cocos2d::CCNode* node);

	//����Ӣ��
	void setHero(Hero*);						

private:
	bool init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name);

private:
	cocos2d::CCMenuItemImage*   mItemSkill;     //���ܰ�ť����
	cocos2d::CCMenu*            mMenuSkill;     //���ܰ�ť����menu
	cocos2d::CCSprite*          mStencil;       //�ɰ徫��
	cocos2d::CCProgressTimer*   mProgressTimer; //˳ʱ�����������
	float                       mCDTime;        //CDʱ��
	Hero* hero;									
};
#endif