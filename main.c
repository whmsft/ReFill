#include <stdio.h>
#include "./include/raylib.h"

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

int screenWidth, screenHeight, targetValue;
int wheelValue = 0;
int gameScore = 0;

void UpdateDrawFrame(void);

int abs(int number) {
	if (number>0) {
		return number;
	} else {
		return number*-1;
	}
}

int main(void) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(320, 640, "ReFill");
	screenWidth  = GetScreenWidth();
	screenHeight = GetScreenHeight();
	targetValue = GetRandomValue(1,49)*2;
	#if defined(PLATFORM_WEB)
		emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
	#else
		SetTargetFPS(60);
		while (!WindowShouldClose()) {
			UpdateDrawFrame();
		}
	#endif
	CloseWindow();
	return 0;
}

void UpdateDrawFrame(void) {
	// Update
	if (wheelValue>100) wheelValue=0;
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) wheelValue+=2;
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		wheelValue = 0;
		if (abs(wheelValue-targetValue)<10) {
			targetValue = GetRandomValue(1,49)*2;
			gameScore += 1;
		}
	}

	// Draw
	BeginDrawing();
	ClearBackground(BLACK);
	DrawRectangle(screenWidth/14, (screenHeight-screenWidth)+screenWidth/14, screenWidth*12/14, screenWidth*12/14, RAYWHITE);
	DrawRectangle(screenWidth*1.5/14, (screenHeight-screenWidth)+screenWidth*1.5/14, screenWidth*11/14, screenWidth*11/14, BLACK);
	DrawRectangle(screenWidth*2/14, (screenHeight-screenWidth)+screenWidth*(120-wheelValue)/140, screenWidth*10/14, screenWidth*wheelValue/140, RAYWHITE);
	EndDrawing();
}
