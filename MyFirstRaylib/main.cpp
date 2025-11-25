#include "raylib.h"

// Player variables
int playerX = 350;
int playerY = 250;
const int playerRectangleWidth = 250;
const int playerRectangleHeight = 100;

// Target variables
int targetX = 400;
int targetY = 100;
const int targetSize = 40;

// Window variables
const int windowWidth = 800;
const int windowHeigth = 600;
const int targetFPS = 60;

// -- FUNCTIONS --
void UpdatePlayer() {
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
}

int main()
{	
	InitWindow(windowWidth, windowHeigth, "Success");
	SetTargetFPS(targetFPS);

	while (!WindowShouldClose())
	{	
		UpdatePlayer();
		
		// Collision logic - left and top edges are X and Y
		int playerRightEdge = playerX + playerRectangleWidth;
		int playerBottomEdge = playerY + playerRectangleHeight;
		int targetRightEdge = targetX + targetSize;
		int targetBottomEdge = targetY + targetSize;

		if (playerRightEdge > targetX && playerX < targetRightEdge && playerBottomEdge > targetY && playerY < targetBottomEdge) {
			targetX = GetRandomValue(0, windowWidth - targetSize);
			targetY = GetRandomValue(0, windowHeigth - targetSize);
		}


		// Drawing Logic
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawRectangle(playerX, playerY, playerRectangleWidth, playerRectangleHeight, RED);
		DrawRectangle(targetX, targetY, targetSize, targetSize, GREEN);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}