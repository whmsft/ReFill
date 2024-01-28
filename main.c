#include <stdio.h>
#include <stdlib.h>
#include "./include/raylib.h"

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

int screenWidth, screenHeight, targetValue;
int wheelValue = 0;
int gameScore = 0;
char targetStr[20];
char scoreStr[20];

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
	targetValue = GetRandomValue(1,49)*2;
	#if defined(PLATFORM_WEB)
		emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
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
	screenWidth  = GetScreenWidth();
	screenHeight = GetScreenHeight();
	snprintf(targetStr, 20, "Target: %d", targetValue);
	snprintf(scoreStr, 20, "Score: %d", gameScore);
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) wheelValue+=2;
	if (wheelValue>100) wheelValue=0;
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		if (abs(targetValue-wheelValue)<20) {
			targetValue = GetRandomValue(1,49)*2;
			gameScore += 1;
		} else {
			targetValue = GetRandomValue(1,49)*2;
			gameScore -= 1;
		}
		wheelValue = 0;
	}
	Vector2 tri11 = {screenWidth*2/14, (screenHeight-screenWidth)+screenWidth*(120-wheelValue)/140};
	Vector2 tri12 = {screenWidth*2/14, screenHeight-(screenWidth*2/14)};
	Vector2 tri13 = {screenWidth*12/14, screenHeight-(screenWidth*2/14)};
	Vector2 tri22 = {screenWidth*12/14, (screenHeight-screenWidth)+screenWidth*(120-wheelValue)/140};

	// Draw
	BeginDrawing();
	ClearBackground(BLACK);
	DrawText(targetStr, screenWidth/14, screenWidth/14, 20, RAYWHITE);
	DrawText(scoreStr, screenWidth/14, screenWidth/14+18, 20, RAYWHITE);
	DrawRectangle(screenWidth/14, (screenHeight-screenWidth)+screenWidth/14, screenWidth*12/14, screenWidth*12/14, RAYWHITE);
	DrawRectangle(screenWidth*1.5/14, (screenHeight-screenWidth)+screenWidth*1.5/14, screenWidth*11/14, screenWidth*11/14, BLACK);
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		DrawTriangle(tri11, tri12, tri13, RAYWHITE);
		DrawTriangle(tri13, tri22, tri11, RAYWHITE);
	}
	EndDrawing();
}
