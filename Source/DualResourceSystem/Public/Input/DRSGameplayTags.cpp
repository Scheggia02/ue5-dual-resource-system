// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/DRSGameplayTags.h"

namespace DRSGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Move, "Input.Move", "Tag for move input");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Look, "Input.Look", "Tag for look input");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Jump, "Input.Jump", "Tag for jump input");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Attack, "Input.Attack", "Tag for attack input");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Dash, "Input.Dash", "Tag for dash input");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(SetByCaller_Cost, "SetByCaller.Cost", "Tag for SetByCaller cost magnitude in resource execution gameplay effects");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Overdraw, "Status.Overdraw", "Tag for overdraw status, which allows abilities to overdraft health to cover costs");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_OutOfHealth, "Status.OutOfHealth", "Tag for out of health status, which indicates the character has been reduced to zero health");
}
