#include "./include/raylib.h"
#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

int screenWidth, screenHeight;
int value = 0;

void UpdateDrawFrame(void);

int main(void) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(320, 640, "ReFill");
	screenWidth  = 320; //GetScreenWidth();
	screenHeight = 640; //GetScreenHeight();
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
	if (value>100) value=0;
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		value+=2;
	}
	// (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))


	// Draw
	BeginDrawing();
	ClearBackground(BLACK);
	DrawRectangle(screenWidth/14, (screenHeight-screenWidth)+screenWidth/14, screenWidth*12/14, screenWidth*12/14, RAYWHITE);
	DrawRectangle(screenWidth*1.5/14, (screenHeight-screenWidth)+screenWidth*1.5/14, screenWidth*11/14, screenWidth*11/14, BLACK);
	DrawRectangle(screenWidth*2/14, (screenHeight-screenWidth)+screenWidth*(120-value)/140, screenWidth*10/14, screenWidth*value/140, RAYWHITE);
	EndDrawing();
}
