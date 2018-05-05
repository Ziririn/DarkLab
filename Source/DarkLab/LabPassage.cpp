// Fill out your copyright notice in the Description page of Project Settings.

#include "LabPassage.h"
#include "LabRoom.h"

// Sets default values
LabPassage::LabPassage(int botLeftLocX, int botLeftLocY, EDirectionEnum direction, LabRoom* from, LabRoom* to, bool isDoor, int width) : BotLeftLocX(botLeftLocX), BotLeftLocY(botLeftLocY), GridDirection(direction), From(from), To(to), bIsDoor(isDoor)
{
	if (width > 2)
		Width = width;
	if (from)
		from->AddPassage(this);
	if (to)
		to->AddPassage(this);
}

// Called on destruction
LabPassage::~LabPassage()
{
	// We don't delete rooms if passage is deleted
	// But we do delete passage if both rooms are deleted
}