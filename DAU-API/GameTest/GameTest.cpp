//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>
#include <math.h>
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
CSimpleSprite *testSprite;
enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite = App::CreateSprite(".\\TestData\\ufo.bmp", 1, 6);
	testSprite->SetPosition(500.0f, 50.0f);
	float speed = 3.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, {1, 2, 3, 4, 5});
	testSprite->SetScale(2.0f);
	//------------------------------------------------------------------------
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	testSprite->SetAnimation(ANIM_BACKWARDS);
	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite->Update(deltaTime);
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_RIGHT);
		float x, y;
		testSprite->GetPosition(x, y);
		x += 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_LEFT);
		float x, y;
		testSprite->GetPosition(x, y);
		x -= 1.0f;

		// if out of bounds (x - 1.0f, y)
		// 	do nothing
		// else x -= 1.0f
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_FORWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y += 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_BACKWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y -= 1.0f;
		testSprite->SetPosition(x, y);
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
	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite->Draw();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	App::Print(20, 730, "Level: 1     Score: 0");

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	// static float a = 0.0f;
	// float r = 1.0f;
	// float g = 1.0f;
	// float b = 1.0f;
	// a += 0.1f;
	// // for (int i = 0; i < 20; i++)
	// // {
	// float sx = 200 + sinf(a + i * 0.1f) * 60.0f;
	// float sy = 200 + cosf(a + i * 0.1f) * 60.0f;
	// float ex = 700 - sinf(a + i * 0.1f) * 60.0f;
	// float ey = 700 - cosf(a + i * 0.1f) * 60.0f;
	// g = (float)i / 20.0f;
	// b = (float)i / 20.0f;
	// App::DrawLine(sx, sy, ex, ey, r, g, b);
	// // }
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	delete testSprite;
	//------------------------------------------------------------------------
}