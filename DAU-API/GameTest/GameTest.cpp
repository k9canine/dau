//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>
#include <math.h>
#include <vector>
#include <algorithm>
//------------------------------------------------------------------------
#include "app\app.h"
#include "levels.h"
#include "utils.h"

//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
CSimpleSprite *background = nullptr;
CSimpleSprite *player = nullptr;

int METEOR_COLUMNS = 11;
int METEOR_ROWS = 8;

std::vector<std::vector<CSimpleSprite *>> allMeteors(METEOR_ROWS); // (size: 7 x 10)

bool temp = false;
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//------------------------------------------------------------------------
	// initialize allMeteors
	for (int i = 0; i < METEOR_ROWS; i++)
	{
		allMeteors[i] = {};
	}

	//------------------------------------------------------------------------
	// set background sprite
	background = App::CreateSprite(".\\TestData\\background.bmp", 1, 1);
	background->SetPosition(500.0f, 300.0f);
	background->SetScale(1.5f);
	//------------------------------------------------------------------------

	player = App::CreateSprite(".\\TestData\\ufo.bmp", 1, 6);
	player->SetPosition(500.0f, 50.0f);
	float speed = 3.0f / 15.0f;
	player->CreateAnimation(ANIMATE, speed, {1, 2, 3, 4, 5});
	player->SetScale(2.0f);
	//------------------------------------------------------------------------
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	if (temp == false)
	{
		temp = true;

		// set the meteors and make them appear, then abstract to a new function
		// return value: another array to put back into the other array

		allMeteors.emplace_back(generateMeteors(level1));
	}

	player->SetAnimation(ANIMATE);
	player->Update(deltaTime);

	for (auto arr : allMeteors)
	{
		for (CSimpleSprite *meteor : arr)
		{
			if (meteor)
			{
				meteor->SetAnimation(ANIMATE);
				meteor->Update(deltaTime);
			}
		}
	}

	// =====================================================
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		float x, y;
		player->GetPosition(x, y);

		// bounds checking
		if (!outOfBounds(x + 1.0f, y))
		{
			x += 1.0f;
			player->SetPosition(x, y);
			// if (gameOver(player, &allMeteors))
			// 	exit(0);
		}
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		float x, y;
		player->GetPosition(x, y);

		if (!outOfBounds(x - 1.0f, y))
		{
			x -= 1.0f;
			player->SetPosition(x, y);
			// if (gameOver(player, &allMeteors))
			// 	exit(0);
		}
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		float x, y;
		player->GetPosition(x, y);

		if (!outOfBounds(x, y + 1.0f))
		{
			y += 1.0f;
			player->SetPosition(x, y);
			// if (gameOver(player, &allMeteors))
			// 	exit(0);
		}
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		float x, y;
		player->GetPosition(x, y);

		if (!outOfBounds(x, y - 1.0f))
		{
			y -= 1.0f;
			player->SetPosition(x, y);
			// if (gameOver(player, &allMeteors))
			// 	exit(0);
		}
	}

	//------------------------------------------------------------------------
	// Sample Sound. - USE FOR SHOOTING ENEMIES
	//------------------------------------------------------------------------
	// if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	// {
	// 	App::PlaySound(".\\TestData\\Test.wav");
	// }
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print,DrawSprite.)
// See App.h
//------------------------------------------------------------------------
void Render()
{
	background->Draw();
	player->Draw();

	for (auto arr : allMeteors)
	{
		for (CSimpleSprite *meteor : arr)
		{
			if (meteor)
				meteor->Draw();
		}
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	App::Print(20, 730, "Level: 1     Score: 0");
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	delete player;
	delete background;

	for (auto arr : allMeteors)
	{
		for (CSimpleSprite *meteor : arr)
		{
			delete meteor;
		}
	}
	//------------------------------------------------------------------------
}