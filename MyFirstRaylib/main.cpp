#include <algorithm>
#include <vector>
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

struct Bullet {
	int x;
	int y;
	int width;
	int height;
	int speed;
	bool active;
};

Player myPlayer = { 350, 250, 250, 100, RED };
Target myTarget = { 400, 100, 50 };
Window myWindow = { 800, 600, 60 };
std::vector<Bullet> bullets;

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

	// Collision logic between Player and Target - left and top edges are X and Y
	int playerRightEdge = myPlayer.x + myPlayer.width;
	int playerBottomEdge = myPlayer.y + myPlayer.height;
	int targetRightEdge = myTarget.x + myTarget.size;
	int targetBottomEdge = myTarget.y + myTarget.size;

	if (playerRightEdge > myTarget.x && myPlayer.x < targetRightEdge && playerBottomEdge > myTarget.y && myPlayer.y < targetBottomEdge) {
		myTarget.x = GetRandomValue(0, myWindow.width - myTarget.size);
		myTarget.y = GetRandomValue(0, myWindow.height - myTarget.size);
	}

	// Collision logic between bullet and Target
	for (int i = 0; i < bullets.size(); i++) {
		int bulletRightEdge = bullets[i].x + bullets[i].width;
		int bulletBottomEdge = bullets[i].y + bullets[i].height;

		if (bulletRightEdge > myTarget.x && bullets[i].x < targetRightEdge && bulletBottomEdge > myTarget.y && bullets[i].y <  targetBottomEdge) {
			bullets[i].active = false;
			myTarget.x = GetRandomValue(0, myWindow.width - myTarget.size);
			myTarget.y = GetRandomValue(0, myWindow.height - myTarget.size);
		}
	}
}

/*
 * Draws objects like Player and Target Rectangles 
 * @return void
**/
void DrawGame() {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawBullets();
	DrawRectangle(myPlayer.x, myPlayer.y, myPlayer.width, myPlayer.height, RED);
	DrawRectangle(myTarget.x, myTarget.y, myTarget.size, myTarget.size, GREEN);
	EndDrawing();
}

void ShootBullet() {
	if (IsKeyPressed(KEY_SPACE)) {
		Bullet newBullet;
		newBullet.x = myPlayer.x + (myPlayer.width / 2) - 5;
		newBullet.y = myPlayer.y;
		newBullet.width = 10;
		newBullet.height = 20;
		newBullet.speed = 10;
		newBullet.active = true;

		bullets.push_back(newBullet);
	}
}

void UpdateBullets() {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].y -= bullets[i].speed;

		if (bullets[i].y < 0) {
			bullets[i].active = false;
		}
	}
}

void RemoveInactiveBullets() {
	std::erase_if(bullets, [](const Bullet& bullet) {
		return !bullet.active;
		});
}

void DrawBullets() {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].active) {
			DrawRectangle(bullets[i].x, bullets[i].y, bullets[i].width, bullets[i].height, BLACK);
		}
	}
}

int main()
{	
	InitWindow(myWindow.width, myWindow.height, "Success");
	SetTargetFPS(myWindow.targetFPS);

	while (!WindowShouldClose())
	{	
		UpdatePlayer();
		UpdateCollision();
		ShootBullet();
		UpdateBullets();
		RemoveInactiveBullets();
		DrawGame();
	}

	CloseWindow();
	return 0;
}