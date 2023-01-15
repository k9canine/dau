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

std::vector<std::vector<CSimpleSprite *>> allMeteors(METEOR_ROWS); // (size: 8 x 11)

bool temp = false;
bool lose = false;
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
		for (int j = 0; j < METEOR_COLUMNS; j++)
		{
			allMeteors[i].emplace_back(nullptr);
		}
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

		// return value: another array to put back into the other array

		// erase first row of meteors before deleting them
		for (auto meteor : allMeteors.front())
		{
			delete meteor;
		}
		allMeteors.erase(allMeteors.begin());

		// every x seconds:
		// update/set the positions of all of the meteors after you delete the bottom row, based on their position in the 2D array
		// then add the new row to the top

		allMeteors.emplace_back(generateMeteors(level1)); // option COULD GENERATE EMPTY ROWS IN BETWEEN
	}

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

	if (lose == false)
	{
		player->SetAnimation(ANIMATE);
		player->Update(deltaTime);

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
				if (gameOver(player, &allMeteors))
					lose = true;
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
				if (gameOver(player, &allMeteors))
					lose = true;
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
				if (gameOver(player, &allMeteors))
					lose = true;
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
				if (gameOver(player, &allMeteors))
					lose = true;
			}
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

	if (lose)
		App::Print(470, 384, "GAME OVER", 255);
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