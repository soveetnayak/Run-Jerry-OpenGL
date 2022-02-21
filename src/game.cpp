/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"

#include <iostream>

#include "game_level.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "text_renderer.h"

// #include "game_object.h"
// Game-related State data
SpriteRenderer *Renderer;
GameObject *Player;
TextRenderer *Text;
float start_time;
Game::Game(unsigned int width, unsigned int height)
	: State(GAME_MENU), Keys(), Width(width), Height(height) {}

Game::~Game() {
	delete Renderer;
	delete Player;
}

void game_map(int level) {
	//
	srand(time(0));
	int array[16][25] = {0};
	int totalcoins = 3 + level * 2;
	int totalenemies = 3 + level * 2;

	// for (auto i = 0; i < 15; i++) map[7][i] = 0;

	FILE *fptr;
	// Wow
	if (level == 1) {
		fptr = fopen(
			"/home/zed/Desktop/Study/Computer Graphics/Assignment "
			"1/Submission/src/levels/one.lvl",
			"w");
		for (int i = 0; i < 16; i++) {
			int r1 = rand() % 25;
			int r2 = rand() % 25;
			array[i][r1] = 1;
			array[i][r2] = 1;
		}
		for (int i = 0; i < totalcoins; i++) {
			int x = rand() % 16;
			int y = rand() % 25;
			array[x][y] = 2;
		}
		for (int i = 0; i < totalenemies; i++) {
			int x = rand() % 16;
			int y = rand() % 25;
			array[x][y] = 3;
		}
		// Put 1 at all the walls of the matrix
		for (int i = 0; i < 16; i++) {
			array[i][0] = 1;
			array[i][24] = 1;
		}
		for (int i = 0; i < 25; i++) {
			array[0][i] = 1;
			array[15][i] = 1;
		}
		array[0][11] = 4;
		array[0][12] = 4;
		array[0][13] = 4;
		array[15][11] = 0;
		array[15][12] = 0;
		array[15][13] = 0;
		array[14][11] = 0;
		array[14][12] = 0;
		array[14][13] = 0;
		array[1][11] = 0;
		array[1][12] = 0;
		array[1][13] = 0;
	}

	else if (level == 2) {
		fptr = fopen(
			"/home/zed/Desktop/Study/Computer Graphics/Assignment "
			"1/Submission/src/levels/two.lvl",
			"w");
		for (int i = 0; i < 16; i++) {
			int r1 = rand() % 25;
			int r2 = rand() % 25;
			int r3 = rand() % 25;
			array[i][r1] = 1;
			array[i][r2] = 1;
			array[i][r3] = 1;
		}
		for (int i = 0; i < totalcoins; i++) {
			int x = rand() % 16;
			int y = rand() % 25;
			array[x][y] = 2;
		}
		for (int i = 0; i < totalenemies; i++) {
			int x = rand() % 16;
			int y = rand() % 25;
			array[x][y] = 3;
		}
		// Put 1 at all the walls of the matrix
		for (int i = 0; i < 16; i++) {
			array[i][0] = 1;
			array[i][24] = 1;
		}
		for (int i = 0; i < 25; i++) {
			array[0][i] = 1;
			array[15][i] = 1;
		}

		array[0][11] = 4;
		array[0][12] = 4;
		array[0][13] = 4;
		array[15][11] = 0;
		array[15][12] = 0;
		array[15][13] = 0;
		array[14][11] = 0;
		array[14][12] = 0;
		array[14][13] = 0;
		array[1][11] = 0;
		array[1][12] = 0;
		array[1][13] = 0;
	} else if (level == 3) {
		fptr = fopen(
			"/home/zed/Desktop/Study/Computer Graphics/Assignment "
			"1/Submission/src/levels/three.lvl",
			"w");
		for (int i = 0; i < 16; i++) {
			int r1 = rand() % 25;
			int r2 = rand() % 25;
			int r3 = rand() % 25;
			int r4 = rand() % 25;
			array[i][r1] = 1;
			array[i][r2] = 1;
			array[i][r3] = 1;
			array[i][r4] = 1;
		}
		for (int i = 0; i < totalcoins; i++) {
			int x = rand() % 16;
			int y = rand() % 25;
			array[x][y] = 2;
		}
		for (int i = 0; i < totalenemies; i++) {
			int x = rand() % 16;
			int y = rand() % 25;
			array[x][y] = 3;
		}
		// Put 1 at all the walls of the matrix
		for (int i = 0; i < 16; i++) {
			array[i][0] = 1;
			array[i][24] = 1;
		}
		for (int i = 0; i < 25; i++) {
			array[0][i] = 1;
			array[15][i] = 1;
		}

		array[0][11] = 4;
		array[0][12] = 4;
		array[0][13] = 4;
		array[15][11] = 0;
		array[15][12] = 0;
		array[15][13] = 0;
		array[14][11] = 0;
		array[14][12] = 0;
		array[14][13] = 0;
		array[1][11] = 0;
		array[1][12] = 0;
		array[1][13] = 0;
	}

	for (auto i = 0; i < 16; i++) {
		for (auto j = 0; j < 25; j++) {
			std::fprintf(fptr, "%d ", array[i][j]);
		}
		std::fprintf(fptr, "\n");
	}

	fclose(fptr);
}

void Game::Init() {
	Text = new TextRenderer(this->Width, this->Height);
	Text->Load(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/fonts/OCRAEXT.TTF",
		24);

	// load shaders
	ResourceManager::LoadShader(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/shaders/sprite.vs",
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/shaders/sprite.frag",
		nullptr, "sprite");
	// configure shaders
	glm::mat4 projection =
		glm::ortho(0.0f, static_cast<float>(this->Width),
				   static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// set render-specific controls
	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);
	// load textures
	ResourceManager::LoadTexture(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/textures/triangle.jpg",
		false, "background");
	ResourceManager::LoadTexture(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/textures/tommy.png",
		true, "enemy");
	ResourceManager::LoadTexture(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/textures/fence.png",
		true, "block_solid");
	ResourceManager::LoadTexture(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/textures/shreyas.png",
		true, "block");
	ResourceManager::LoadTexture(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/textures/jerry.png",
		true, "paddle");
	ResourceManager::LoadTexture(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/textures/finish2.png",
		true, "finish");
	// load levels
	game_map(1);
	game_map(2);
	game_map(3);
	GameLevel one;
	one.Load(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/levels/one.lvl",
		this->Width, this->Height / 2);
	GameLevel two;
	two.Load(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/levels/two.lvl",
		this->Width, this->Height / 2);
	GameLevel three;
	three.Load(
		"/home/zed/Desktop/Study/Computer Graphics/Assignment "
		"1/Submission/src/levels/three.lvl",
		this->Width, this->Height / 2);
	// GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height /
	// 2);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	// this->Levels.push_back(four);
	this->Level = 0;
	// configure game objects
	glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
									this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE,
							ResourceManager::GetTexture("paddle"));
}

bool Check_Collision(GameObject &one, GameObject &two)  // AABB - AABB collision
{
	// collision x-axis?
	std::tuple<int, int, int, int> ans(0, 0, 0, 0);
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
					  two.Position.x + two.Size.x >= one.Position.x;
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
					  two.Position.y + two.Size.y >= one.Position.y;

	return collisionX && collisionY;
	// collision only if on both axes
	// return collisionX && collisionY;
}

bool Game::enemyCollision(GameObject &enemy) {
	for (GameObject &box : this->Levels[this->Level].Bricks) {
		if (!box.IsEnemy && !box.IsFinish && box.IsSolid) {
			if (!box.Destroyed) {
				if (Check_Collision(enemy, box)) {
					return true;
				}
			}
		}
	}
	return false;
}

void Game::Update(float dt) {
	float velocity = PLAYER_VELOCITY * dt;
	// update objects
	Player->Move(dt, this->Width);
	// check for collisions
	this->DoCollisions();
	// check if reached exit
	if (this->State == GAME_ACTIVE && this->Levels[this->Level].IsCompleted()) {
		std::cout << "Level " << this->Level + 1 << " completed!" << std::endl;
		if (this->Level == 2) {
			this->State = GAME_WON;  // Yeyeye
		}
		if (this->Level == 0 || this->Level == 1) {
			this->Level++;
			this->ResetLevel();  // This is to go to the next level
		}
		this->ResetPlayer();  // This is to reset the player position
							  // this->State = GAME_WON;
	}
	for (GameObject &enemy : this->Levels[this->Level].Bricks) {
		if (enemy.IsEnemy) {
			if (enemy.Right) {
				if (enemy.Position.x >= 0.0f) {
					enemy.Position.x -= velocity;
					if (enemyCollision(enemy)) {
						enemy.Position.x += velocity;
						enemy.Right = false;
					}
				} else {
					enemy.Right = false;
				}
			}
			if (!enemy.Right) {
				if (enemy.Position.x <= this->Width - enemy.Size.x) {
					enemy.Position.x += velocity;
					if (enemyCollision(enemy)) {
						enemy.Position.x -= velocity;
						enemy.Right = true;
					}
				} else
					enemy.Right = true;
			}
		}
	}
	if (1) {
		glm::vec3 Position =
			glm::vec3(Player->Position.x, Player->Position.y, 0.0f);
		std::cout << Position.x << " " << Position.y << " " << Position.z
				  << "\n";
		ResourceManager::GetShader("sprite").Use().SetVector3f("LightPos",
															   Position);
		ResourceManager::GetShader("sprite").Use().SetInteger("LightOn",
															  this->LightOn);
	}
}

void Game::ProcessInput(float dt) {
	if (this->State == GAME_ACTIVE) {
		float velocity = PLAYER_VELOCITY * dt;
		// move playerboard
		if (this->Keys[GLFW_KEY_A]) {
			if (Player->Position.x >= 0.0f)
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D]) {
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}
		// add keybinds for w and s
		if (this->Keys[GLFW_KEY_W]) {
			if (Player->Position.y >= 0.0f) {
				Player->Position.y -= velocity;
			}
		}
		// woww
		if (this->Keys[GLFW_KEY_S]) {
			if (Player->Position.y <= this->Height - Player->Size.y) {
				Player->Position.y += velocity;
			}
		}
	}
	if (this->State == GAME_MENU) {
		if (this->Keys[GLFW_KEY_ENTER] &&
			!this->KeysProcessed[GLFW_KEY_ENTER]) {
			this->State = GAME_ACTIVE;
			StartTime = time(NULL);
			this->KeysProcessed[GLFW_KEY_ENTER] = true;
		}
	}
	if (this->State == GAME_WON) {
		if (this->Keys[GLFW_KEY_ENTER]) {
			this->KeysProcessed[GLFW_KEY_ENTER] = true;
			this->State = GAME_MENU;
		}
	}
}

void Game::Render() {
	if (this->State == GAME_ACTIVE) {
		// draw background
		Texture2D myTexture;
		myTexture = ResourceManager::GetTexture("background");
		Renderer->DrawSprite(myTexture, glm::vec2(0.0f, 0.0f),
							 glm::vec2(this->Width, this->Height), 0.0f);
		// draw level
		this->Levels[this->Level].Draw(*Renderer);
		// draw player
		Player->Draw(*Renderer);
	}

	if (this->State == GAME_MENU || this->State == GAME_LOST || this->State == GAME_WON) {
		Texture2D myTexture;
		myTexture = ResourceManager::GetTexture("background");
		Renderer->DrawSprite(myTexture, glm::vec2(0.0f, 0.0f),
							 glm::vec2(this->Width, this->Height), 0.0f);

		Player->Draw(*Renderer);
	}

	// if (this->State == GAME_MENU || this->State == GAME_WON || this->State == GAME_LOST) {
	// 	Texture2D myTexture;
	// 	myTexture = ResourceManager::GetTexture("background");
	// 	Renderer->DrawSprite(myTexture, glm::vec2(0.0f, 0.0f),
	// 						 glm::vec2(this->Width, this->Height), 0.0f);

	//}

	if(this->State == GAME_MENU) {
		if (this->Keys[GLFW_KEY_ENTER]) {
			StartTime = time(NULL);
			this->State = GAME_ACTIVE;
		}
	}
	if (this->State == GAME_MENU) {
		Text->RenderText("Press ENTER to start", 600.0f, Height / 2, 1.5f,
						 glm::vec3(1.0f, 0.0f, 0.0f));
		Text->RenderText("Press Space to toggle light", 600.0f,
						 Height / 2 + 50.0f, 1.5f, glm::vec3(1.0f, 0.0f, 0.0f));
		// Text->RenderText("Press W or S to select level", 245.0f, Height / 2
		// + 20.0f, 0.75f);
		std::cout << "Press ENTER to start" << std::endl;
		// std::cout << "Press W or S to select level" << std::endl;
	}
	if (this->State == GAME_WON) {
		Text->RenderText("You WON!!!", 400.0, Height / 2, 2.0,
						 glm::vec3(0.0, 0.0, 1.0));
		// Text->RenderText(
		//     "Press ENTER to retry or ESC to quit", 130.0, Height / 2, 1.0,
		//     glm::vec3(1.0, 1.0, 0.0)
		// );
		//Score
		Text->RenderText("Final Coins: " + std::to_string(this->Coins), 80.0,
						 Height - 100.0, 1.0, glm::vec3(0.0, 0.0, 1.0));
		std::cout << "You WON!!!" << std::endl;
		// wait for 2 sec before exiting the game
		// time_t currentTime = time(NULL);
		// time_t bufferTime = time(NULL);
		// while (currentTime - bufferTime < 2) {
		// 	currentTime = time(NULL);
		// }
		// exit(0);
	}
	if (this->State == GAME_LOST) {
		Text->RenderText("You LOST!!!", 400.0, Height / 2, 2.0,
						 glm::vec3(0.0, 0.0, 1.0));
		// Text->RenderText(
		//     "Press ENTER to retry or ESC to quit", 130.0, Height / 2, 1.0,
		//     glm::vec3(1.0, 1.0, 0.0)
		// );
		std::cout << "You LOST!!!" << std::endl;
		// wait for 2 sec before exiting the game
		// sleep(2);
		// time_t currentTime = time(NULL);
		// time_t bufferTime = time(NULL);
		// if(currentTime - bufferTime < 2) {
		// 	currentTime = time(NULL);
		// }
		// else {
		// 	exit(0);
		// }
	}
	if (this->State == GAME_ACTIVE) {
		// Coins
		Text->RenderText("Coins: " + std::to_string(this->Coins), 80.0,
						 Height - 100.0, 1.0, glm::vec3(0.0, 1.0, 0.0));
		std::cout << "Score: " << this->Coins << std::endl;
		// Time
		time_t currentTime = time(NULL);
		int timeElapsed = currentTime - StartTime;
		Text->RenderText("Time: " + std::to_string(timeElapsed), 250.0,
						 Height - 100.0, 1.0, glm::vec3(0.0, 1.0, 0.0));
		// Text->RenderText(
		//     "Time: " + std::to_string(this->Time), 10.0, Height - 40.0, 1.0,
		//     glm::vec3(0.0, 1.0, 0.0)
		// );
	}
}

Direction VectorDirection(glm::vec2 target) {
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),   // up
		glm::vec2(1.0f, 0.0f),   // right
		glm::vec2(0.0f, -1.0f),  // down
		glm::vec2(-1.0f, 0.0f)   // left
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++) {
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max) {
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}

Collision CheckCollision(GameObject &one,
						 GameObject &two)  // AABB - AABB collision
{
	// Convert this to return direction and distance vector

	if (one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x) {
		if (one.Position.y + one.Size.y >= two.Position.y &&
			two.Position.y + two.Size.y >= one.Position.y) {
			// find distance vector
			glm::vec2 distance = one.Position - two.Position;
			return std::make_tuple(true, VectorDirection(distance), distance);
		}
	}
	return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

void Game::DoCollisions() {
	// for (GameObject &box : this->Levels[this->Level].Bricks) {
	// 	if (!box.Destroyed) {
	// 		if (!box.IsSolid)
	// 			box.Destroyed = true;
	// 	}
	// }
	for (GameObject &box : this->Levels[this->Level].Bricks) {
		if (!box.Destroyed) {
			Collision collision = CheckCollision(*Player, box);
			if (std::get<0>(collision))  // if collision is true
			{
				// destroy block if not solid
				if (!box.IsSolid) {
					if (!box.IsFinish) {
						box.Destroyed = true;
						this->Coins += 1;
						if(this->LightOn==0)
							this->Coins += 2;
						std::cout << "Coins: " << this->Coins << std::endl;
					} else {
						for (GameObject &box :
							 this->Levels[this->Level].Bricks) {
							if (box.IsFinish) {
								box.Destroyed = true;
							}
						}
					}
					continue;
				}
				if (box.IsEnemy) {
					// close window
					std::cout << "You LOST!!!" << std::endl;
					// exit(0);
					// ResetPlayer();
					this->State = GAME_LOST;
				}
				// collision resolution
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT)  // horizontal collision
				{
					// Ball->Velocity.x = -Ball->Velocity.x; // reverse
					// horizontal velocity relocate
					float penetration =
						Player->Size.x / 2 - std::abs(diff_vector.x);
					if (dir == LEFT) {
						Player->Position.x += penetration;
						// box.Size.x;  // move ball to right}
					} else {
						Player->Position.x -=
							penetration +
							box.Size.x / 1.8;  // move ball to left;
					}

				} else  // vertical collision
				{
					// Ball->Velocity.y = -Ball->Velocity.y; // reverse vertical
					// velocity relocate
					float penetration =
						Player->Size.y / 2 - std::abs(diff_vector.y);
					if (dir == UP) {
						Player->Position.y -= penetration + box.Size.y / 2;
					}  // move ball back up
					else {
						Player->Position.y +=
							penetration;  // move ball back down
					}
				}
			}
		}
	}
}

void Game::ResetLevel() {
	if (this->Level == 0)
		this->Levels[1].Load(
			"/home/zed/Desktop/Study/Computer Graphics/Assignment "
			"1/Submission/src/levels/two.lvl",
			this->Width, this->Height / 2);
	else if (this->Level == 1)
		this->Levels[2].Load(
			"/home/zed/Desktop/Study/Computer Graphics/Assignment "
			"1/Submission/src/levels/three.lvl",
			this->Width, this->Height / 2);
	else if (this->Level == 3)
		this->State = GAME_WON;
	// else if (this->Level == 2)
	// this->Levels[2].Load("levels/three.lvl", this->Width, this->Height / 2);

	this->Levels[this->Level].Draw(*Renderer);
}

void Game::ResetPlayer() {
	// reset player
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
								 this->Height - PLAYER_SIZE.y);
	Player->Color = glm::vec3(1.0f);
}
