#ifndef __IMP_SKILL_TRAIT__H_
#define __IMP_SKILL_TRAIT__H_

#include "Types.h"

void EnterIMPSkillTrait( void );
void RenderIMPSkillTrait( void );
void ExitIMPSkillTrait( void );
void HandleIMPSkillTrait( void );

enum
{
	IMP_SKILL_TRAITS__LOCKPICK,
	IMP_SKILL_TRAITS__HAND_2_HAND,
	IMP_SKILL_TRAITS__ELECTRONICS,
	IMP_SKILL_TRAITS__NIGHT_OPS,
	IMP_SKILL_TRAITS__THROWING,
	IMP_SKILL_TRAITS__TEACHING,
	IMP_SKILL_TRAITS__HEAVY_WEAPONS,
	IMP_SKILL_TRAITS__AUTO_WEAPONS,
	IMP_SKILL_TRAITS__STEALTHY,
	IMP_SKILL_TRAITS__AMBIDEXTROUS,
	IMP_SKILL_TRAITS__KNIFING,
	IMP_SKILL_TRAITS__PROF_SNIPER,
	IMP_SKILL_TRAITS__CAMO,
	IMP_SKILL_TRAITS__MARTIAL_ARTS,
	IMP_SKILL_TRAITS__NONE,
	IMP_SKILL_TRAITS__NUMBER_SKILLS,
};

// STR16	gzIMPSkillTraitsText[];

INT8	DoesPlayerHaveExtraAttibutePointsToDistributeBasedOnSkillSelection();

void AddSelectedSkillsToSkillsList();

#endif
