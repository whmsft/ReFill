#include <stdio.h>
#include <stdlib.h>
#include "./include/raylib.h"

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

int screenWidth, screenHeight, targetValue;
int wheelValue = 0;
int gameScore = 0;
char targetStr[10];
char scoreStr[10];

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
		emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
	#else
		SetTargetFPS(30);
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
	sprintf(targetStr, "Target: %d", targetValue);
	sprintf(scoreStr, "Score:  %d", gameScore);
	if (wheelValue>100) wheelValue=0;
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) wheelValue+=2;
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
	DrawText(targetStr, screenWidth/14, screenWidth/14, 16, RAYWHITE);
	DrawText(scoreStr, screenWidth/14, screenWidth/14+18, 16, RAYWHITE);
	DrawRectangle(screenWidth/14, (screenHeight-screenWidth)+screenWidth/14, screenWidth*12/14, screenWidth*12/14, RAYWHITE);
	DrawRectangle(screenWidth*1.5/14, (screenHeight-screenWidth)+screenWidth*1.5/14, screenWidth*11/14, screenWidth*11/14, BLACK);
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		DrawTriangle(tri11, tri12, tri13, RAYWHITE);
		DrawTriangle(tri13, tri22, tri11, RAYWHITE);
	}
	EndDrawing();
}
