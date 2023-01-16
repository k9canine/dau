//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string>
//------------------------------------------------------------------------
#include "app\app.h"
#include "levels.h"
#include "utils.h"
#include "gem.h"

//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
CSimpleSprite *background = nullptr;
CSimpleSprite *player = nullptr;
CSimpleSprite *gem = nullptr;

int METEOR_COLUMNS = 11;
int METEOR_ROWS = 8;

std::vector<std::vector<CSimpleSprite *>> allMeteors(METEOR_ROWS); // (size: 8 x 11)

bool lose = false;
bool lastRender = true;
int level = level1;
float score = 0;
float SCORE_SPEED = 1000.0f; // decreasing this value gives more score per second survived

float totalTime = 0;			  // total time elapsed
float timeLastUpdated = 0;		  // when the game was last updated
float UPDATE_FREQUENCY = 4000.0f; // (in milliseconds) how often to update the meteors falling

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
	player->SetScale(1.8f);
	//------------------------------------------------------------------------
	gem = App::CreateSprite(".\\TestData\\gem.bmp", 7, 6);
	setGem(gem);
	gem->CreateAnimation(ANIMATE, speed, {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});
	gem->SetScale(1.8f);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	// if (lose && lastRender) // makes the visuals look a bit choppy, might remove
	// {
	// 	lastRender = false;
	// 	updateMeteors(allMeteors, level);
	// }
	if (lose == false)
	{
		score += deltaTime / 1000.0f;
		totalTime += deltaTime / UPDATE_FREQUENCY;

		if (totalTime > timeLastUpdated)
		{
			timeLastUpdated += 1.0f;
			updateMeteors(allMeteors, level);
			gameOver(player, allMeteors, lose);
		}
	}

	for (auto arr : allMeteors)
	{
		for (auto meteor : arr)
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
		if (gem)
		{
			gem->SetAnimation(ANIMATE);
			gem->Update(deltaTime);
		}
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
				gameOver(player, allMeteors, lose);
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
				gameOver(player, allMeteors, lose);
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
				gameOver(player, allMeteors, lose);
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
				gameOver(player, allMeteors, lose);
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
	if (gem)
		gem->Draw();

	for (auto arr : allMeteors)
	{
		for (auto *meteor : arr)
		{
			if (meteor)
				meteor->Draw();
		}
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	std::string text = "Level: " + std::to_string(level) + "     Score: " + std::to_string(score);
	App::Print(20, 730, text);

	if (lose)
		App::Print(470, 384, "GAME OVER", 255.0f, 0.0f, 0.0f);
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
	delete gem;

	for (auto arr : allMeteors)
	{
		for (auto *meteor : arr)
		{
			delete meteor;
		}
	}

	//------------------------------------------------------------------------
}