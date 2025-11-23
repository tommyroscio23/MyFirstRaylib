#include "raylib.h"

int main()
{
	const int windowWidth = 1600;
	const int windowHeight = 1200;

	InitWindow(windowWidth, windowHeight, "Success");
	SetTargetFPS(165);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("System Online: Hello World", 190, 200, 50, LIGHTGRAY);
		DrawRectangle(windowWidth / 2 - 25, windowHeight / 2 - 25, 50, 50, RED);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}