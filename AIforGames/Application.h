#ifndef RAYLIB_APPLICATION_HEADER
#define RAYLIB_APPLICATION_HEADER

#include <raylib.h>
#include <string>
#include <stdexcept>

class Application
{
private:
	void ShutDown() {
		OnShutDown();
		CloseWindow();        // Close window and OpenGL context
	}
	
	void Draw() {
		BeginDrawing();
		try
		{
			ClearBackground(background);
			OnDraw();
		}
		catch (const std::exception& e) {
			ClearBackground(Color{ 128,0,0,255 });
			DrawText(e.what(), 190, 200, 20, LIGHTGRAY);
		}
		EndDrawing();
	}

	void MainLoop() {
		float deltaTime = 0;
		while (!WindowShouldClose())    // Detect window close button or ESC key
		{
			// Update
			//----------------------------------------------------------------------------------
			// TODO: Update your variables here
			//----------------------------------------------------------------------------------
			deltaTime = GetFrameTime();
			OnUpdate(deltaTime);

			Draw();
		}
		ShutDown();
	}

protected:
	int screenWidth;
	int screenHeight;
	std::string name;
	Color background;

	virtual void OnUpdate(const float deltaTime) {
	}

	virtual void OnShutDown() {
	}

	virtual void OnStart() {}
	
	virtual void OnDraw() {}


public:
	Application(int sx,int sy,const char* n)
		: screenWidth{sx}
		, screenHeight{sy}
		, name{ n }
		/*, background{RAYWHITE}*/
	{}

	//This blocks
	void StartUp() {
		SetConfigFlags(FLAG_MSAA_4X_HINT);
		InitWindow(screenWidth, screenHeight, "Hooking in Raylib in a new project");
		SetTargetFPS(60);
		OnStart();
		MainLoop();
	}

	void SetBackground(Color colour) {
		background = colour;
	}
};

#endif