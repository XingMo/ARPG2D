#ifndef _SKILLBUTTON_H_
#define _SKILLBUTTON_H_
#include <cocos2d.h>
#include "Hero.h"
typedef enum
{
	JUMP,
}Skill_type;
class SkillButton : public cocos2d::CCNode
{
public:
	SkillButton();
	virtual ~SkillButton();
	//创建技能按钮
	static SkillButton* createSkillButton(float cdTime,
		const char* stencil_file_name,
		const char* button_normal_name,
		const char* button_click_name,
		Skill_type type);

	//技能CD预留接口
	void setCDTime(float time) { mCDTime = time; }
	float getCDTime() const { return mCDTime; }

	//点击技能回调
	void skillClickCallBack(cocos2d::CCObject* obj);

	//冷却结束回调
	void skillCoolDownCallBack(cocos2d::CCNode* node);

	//传入英雄
	void setHero(Hero*);						

private:
	bool init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, Skill_type type);

private:
	cocos2d::CCMenuItemImage*   mItemSkill;     //技能按钮精灵
	cocos2d::CCMenu*            mMenuSkill;     //技能按钮所属menu
	cocos2d::CCSprite*          mStencil;       //蒙板精灵
	cocos2d::CCProgressTimer*   mProgressTimer; //顺时针进度条精灵
	float                       mCDTime;        //CD时间
	Hero* hero;									
};
#endif