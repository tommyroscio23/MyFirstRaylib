#include "raylib.h"

int main()
{	
	int playerX = 350;
	int playerY = 250;
	const int playerRectangleWidth = 250;
	const int playerRectangleHeight = 100;
	const int windowWidth = 800;
	const int windowHeigth = 600;

	InitWindow(windowWidth, windowHeigth, "Success");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{	
		// Movement
		if (IsKeyDown(KEY_RIGHT)) {
			playerX += 5;
		}
		if (IsKeyDown(KEY_LEFT)) {
			playerX -= 5;
		}
		if (IsKeyDown(KEY_UP)) {
			playerY -= 5;
		}
		if (IsKeyDown(KEY_DOWN)) {
			playerY += 5;
		}

		// Boundaries Check
		if (playerX < 0) {
			playerX = 0;
		}

		if (playerX + playerRectangleWidth > windowWidth) {
			playerX = windowWidth - playerRectangleWidth;
		}

		if (playerY < 0) {
			playerY = 0;
		}

		if (playerY + playerRectangleHeight > windowHeigth) {
			playerY = windowHeigth - playerRectangleHeight;
		}

		// Drawing Logic
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawRectangle(playerX, playerY, playerRectangleWidth, playerRectangleHeight, RED);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}