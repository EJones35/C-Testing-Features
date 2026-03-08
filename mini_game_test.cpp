#include <raylib.h>
#include <iostream>
#include <vector>
using namespace std; 

int screen_width = 960;
int screen_height = 525;
int screen_width_centre = screen_width/2;
int screen_height_centre = screen_height/2;
int move_speed = 1000;
float player_x = 0;
float player_y = 0;
float delta_time;
bool touching_enemy = false;
string screen = "Main Menu";
Rectangle player = {0, 0, 50, 50};
Rectangle play_button = {0,0,0,0};
vector<Rectangle> enemies;

Rectangle draw_interactable_rect_from_centre(int x_offset,int y_offset,float width,float height,Color colour,bool enemy = false) {
	DrawRectangle(screen_width_centre-x_offset,screen_height_centre-y_offset,width,height,colour);
	float x = screen_width_centre-x_offset;
	float y = screen_height_centre-y_offset;
	Rectangle result = {x, y, width, height};
	if (enemy) {
		enemies.push_back(result);
	}
	return result;
}

void draw_text_from_centre(const char* text,int x_offset,int y_offset,int size,Color colour) {
	float x = screen_width_centre-x_offset;
	float y = screen_height_centre-y_offset;
	float text_width = MeasureText(text,size);
	x -= text_width/2;
	y -= size/2;
	DrawText(text, x, y, size, colour);
}

Rectangle draw_button_from_centre(const char* button_text,int x_offset,int y_offset,float width,float height,Color button_colour,Color text_colour, int text_size) {
	Rectangle button = draw_interactable_rect_from_centre(x_offset+(width/2),y_offset+(height/2),width,height,button_colour);
	draw_text_from_centre(button_text,x_offset,y_offset,text_size,text_colour);
	return button;
}

void new_enemy(float x, float y, float width, float height) {
	x = screen_width_centre-x;
	y = screen_height_centre-y;
	Rectangle temp = {x,y,width,height};
	enemies.push_back(temp);
}

int main() {
	touching_enemy = false;
	InitWindow(screen_width,screen_height,"Mini Game Test");
	SetTargetFPS(60);
	new_enemy(100,150,50,50);
	new_enemy(-100,150,50,50);
	new_enemy(100,-150,50,50);
	new_enemy(-100,-150,50,50);
	while (!WindowShouldClose()) {
		Vector2 mouse_pos = GetMousePosition();
		delta_time = GetFrameTime();
		if (screen=="Game") {
			touching_enemy = false;
			if (IsKeyDown(KEY_LEFT)) {
				player_x += move_speed*delta_time;
			}
			if (IsKeyDown(KEY_RIGHT)) {
				player_x -= move_speed*delta_time;
			}
			if (IsKeyDown(KEY_UP)) {
				player_y += move_speed*delta_time;
			}
			if (IsKeyDown(KEY_DOWN)) {
				player_y -= move_speed*delta_time;
			}
			if (IsKeyDown(KEY_R)) {
				player_x = 0;
				player_y = 0;
			}
		}
		if (IsKeyDown(KEY_ONE)) {
			screen = "Main Menu";
		}
		if (IsKeyDown(KEY_TWO)) {
			screen = "Game";
		}
		BeginDrawing();
		if (screen=="Main Menu") {
			play_button = draw_button_from_centre("Play",0,0,200,100,GRAY,BLACK,50);
		}
		if (screen=="Game") {
			for (Rectangle e : enemies) {
				DrawRectangle(e.x,e.y,e.width,e.height,RED);
		}
		player = draw_interactable_rect_from_centre(player_x,player_y,50,50,DARKBLUE); // Draw player after enemy
		for (Rectangle e : enemies) {
			touching_enemy = touching_enemy || CheckCollisionRecs(player, e);
		}
		if (touching_enemy) {
			ClearBackground(YELLOW);
		}
		else {
			ClearBackground(RAYWHITE);
		}
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (CheckCollisionPointRec(mouse_pos, play_button)) {
				screen = "Game";
			}
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}