#include "stdafx.h"
#include "DamageText.h"

DamageText::DamageText(Vector2 spawnPos, int value, int color)
{
	this->spawnPos = spawnPos;

	text = new ObImage(L"ui_pixel_font3.png");

	text->SetWorldPos(this->spawnPos);
	text->maxFrame.x = 10;
	text->maxFrame.y = 6;
	text->scale.x = text->imageSize.x / text->maxFrame.x * 4.0f;
	text->scale.y = text->imageSize.y / text->maxFrame.y * 4.0f;

	if (value == 0)
		text->frame.x = 0;
	else if (value == 1)
		text->frame.x = 1;
	else if (value == 2)
		text->frame.x = 2;
	else if (value == 3)
		text->frame.x = 3;
	else if (value == 4)
		text->frame.x = 4;
	else if (value == 5)
		text->frame.x = 5;
	else if (value == 6)
		text->frame.x = 6;
	else if (value == 7)
		text->frame.x = 7;
	else if (value == 8)
		text->frame.x = 8;
	else if (value == 9)
		text->frame.x = 9;
	else 
		text->frame.x = 0;

	if (color == 0)
		text->frame.y = 0;
	else if (color == 1)
		text->frame.y = 1;
	else if (color == 2)
		text->frame.y = 2;
	else if (color == 3)
		text->frame.y = 3;
	else if (color == 4)
		text->frame.y = 4;
	else if (color == 5)
		text->frame.y = 5;
	else if (color == 6)
		text->frame.y = 6;
	else 
		text->frame.y = 0;

	traveledDistance = 0.0f;
	speed = 50.0f;
	range = 150.0f;
}

DamageText::~DamageText()
{
	delete text;
}

void DamageText::Init()
{
}

void DamageText::Release()
{
}

void DamageText::Update()
{
	text->MoveWorldPos(UP * speed * DELTA);
	text->color.w -= 0.5f * DELTA;

	text->Update();
}

void DamageText::LateUpdate()
{
}

void DamageText::Render()
{
	text->Render();
}

bool DamageText::hasTraveledTooFar()
{
	if (TIMER->GetTick(traveledDistance,2.0f))
	{
		delete this;
		return true;
	}
	return false;
}
