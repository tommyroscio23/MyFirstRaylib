#include "raylib.h"

struct Player {
	int x;
	int y;
	const int width;
	const int height;
	Color color;
};

struct Target {
	int x;
	int y;
	const int size;
};

struct Window {
	const int width;
	const int height;
	const int targetFPS;
};

Player myPlayer = { 350, 250, 250, 100, RED };
Target myTarget = { 400, 100, 50 };
Window myWindow = { 800, 600, 60 };

/*
 * Updates Player position based on movement and boundaries
 * @return void
**/
void UpdatePlayer() {
	// Movement
	if (IsKeyDown(KEY_RIGHT)) {
		myPlayer.x += 5;
	}
	if (IsKeyDown(KEY_LEFT)) {
		myPlayer.x -= 5;
	}
	if (IsKeyDown(KEY_UP)) {
		myPlayer.y -= 5;
	}
	if (IsKeyDown(KEY_DOWN)) {
		myPlayer.y += 5;
	}

	// Boundaries Check
	if (myPlayer.x < 0) {
		myPlayer.x = 0;
	}

	if (myPlayer.x + myPlayer.width > myWindow.width) {
		myPlayer.x = myWindow.width - myPlayer.width;
	}

	if (myPlayer.y < 0) {
		myPlayer.y = 0;
	}

	if (myPlayer.y + myPlayer.height > myWindow.height) {
		myPlayer.y = myWindow.height - myPlayer.height;
	}
}

/*
 * Updates the target position on collision
 * @return void
**/
void UpdateCollision() {

	// Collision logic - left and top edges are X and Y
	int playerRightEdge = myPlayer.x + myPlayer.width;
	int playerBottomEdge = myPlayer.y + myPlayer.height;
	int targetRightEdge = myTarget.x + myTarget.size;
	int targetBottomEdge = myTarget.y + myTarget.size;

	if (playerRightEdge > myTarget.x && myPlayer.x < targetRightEdge && playerBottomEdge > myTarget.y && myPlayer.y < targetBottomEdge) {
		myTarget.x = GetRandomValue(0, myWindow.width - myTarget.size);
		myTarget.y = GetRandomValue(0, myWindow.height - myTarget.size);
	}
}

/*
 * Draws objects like Player and Target Rectangles 
 * @return void
**/
void DrawGame() {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawRectangle(myPlayer.x, myPlayer.y, myPlayer.width, myPlayer.height, RED);
	DrawRectangle(myTarget.x, myTarget.y, myTarget.size, myTarget.size, GREEN);
	EndDrawing();
}

int main()
{	
	InitWindow(myWindow.width, myWindow.height, "Success");
	SetTargetFPS(myWindow.targetFPS);

	while (!WindowShouldClose())
	{	
		UpdatePlayer();
		UpdateCollision();
		DrawGame();
	}

	CloseWindow();
	return 0;
}