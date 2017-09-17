
#include <iostream>
#include <windows.h>
#include "window.h"
#include "math.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Layer.h"
#include "FreeImage.h"
#include "TextureManager.h"
#include "Timer.h"
#include "TextComponent.h"
#include "main.h"


//#include "Object2D.h"

using namespace Engine;
using namespace Graphics;
using namespace Math;
SpriteRenderer* renderer;
float orthoWidth = 800 ;
float orthoHeight = 600 ;
void windowResizeCB(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
	renderer->SetProjectionMatrix(Mat4f::ortho(0.0, orthoWidth, 0.0f, orthoHeight, 1.0f, -1.0f));
	orthoWidth = width;
	orthoHeight = height;
}

int main()
{
	//image format
	

	Window window = Window("engine", orthoWidth, orthoHeight, windowResizeCB);
	
	renderer = new SpriteRenderer();
	
		
	
	int angle = 0.0f;
	
//


	Shader *shader = new Shader("VertexShader.vert", "FragmentShader.frag");
	shader->enable();
	Layer layer(shader, renderer);
	renderer->SetShaderId(shader->program_id);
	renderer->SetProjectionMatrix(Mat4f::ortho(0.0, orthoWidth, 0.0f, orthoHeight, 1.0f, -1.0f));


	int numCellHorizontal = 50;
	int numCellVertical = 50;
	
	int cellWidth = orthoWidth /  numCellHorizontal;
	int cellHeight = orthoHeight / numCellVertical;

	
	GameObject * world = new GameObject();

	GameObject * grid = new GameObject();

	for (int j = 0; j < numCellVertical; j++)
	{
		for (int i = 0; i < numCellHorizontal; i++)
		{
			GameObject *cell = new GameObject();
			SpriteComponent *sprite = new SpriteComponent("large_sprite.png");
			float sx = cellWidth / (float)sprite->GetWidth();
			float sy = cellHeight /(float)sprite->GetHeight();

			float r = ((double)rand() / (RAND_MAX)) ;
			//std::cout << r << std::endl;
			RectComponent *rect = new RectComponent(0,0, sprite->GetWidth(), sprite->GetHeight(),Color(1.0f * r, 1.0f * r, 1.0f * r,1));

			cell->SetTransform(Mat4f::translation(i*cellWidth, j * cellHeight,0) * Mat4f::scale(sx, sy,1));
			cell->AddGraphicComponent(rect);
			grid->Add(cell);
		}
	}


	world->Add(grid);

	GameObject *fpsObject = new GameObject();
	TextComponent *fpsText = new TextComponent(0, 0, "", "fonts/Vera.ttf",Color(1.0,1.0,0.0));

	
	fpsObject->AddGraphicComponent(fpsText);
	world->Add(fpsObject);
	
	TextureManager::Inst()->CreateTextureAtlas();
	world->Init();
	layer.add(world);

texture_font_t *font = TextureManager::Inst()->LoadFont("fonts/Vera.ttf");

	
	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float rotation = 0;
	Vec2f pen;

	
	Color color = Color(1, 0, 1);
	
	

	
	

	std::string s_fps = "";
	float curremtTime = 0;
	while (!window.closed())
	{
		

		LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
		LARGE_INTEGER Frequency;

		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&StartingTime);

		// Activity to be timed



		
		//Mat4f model_m = Mat4f::translation(0,0,-5) *Mat4f::rotateY(TO_RADIANS(angle));
		//
		//glUniform2f(glGetUniformLocation(shader->program_id, "light_pos"), (window.mouse_x / orthoWidth)*orthoWidth, orthoHeight - ((window.mouse_y) / orthoHeight)*orthoHeight);

		window.clear();
		//fps->setText(s_fps.c_str());
		
		layer.render();
		
		world->getChilds();

		
		QueryPerformanceCounter(&EndingTime);
		ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
		ElapsedMicroseconds.QuadPart *= 1000000;
		ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	
		curremtTime+= ElapsedMicroseconds.QuadPart / 1000000.0f;
		grid->SetTransform(Mat4f::rotateZ(TO_RADIANS(rotation)));

		if (curremtTime >= 1.0)
		{

			s_fps = std::to_string(frames) + " fps";
			fpsText->SetText(s_fps.c_str());
			curremtTime = 0;
			frames = 0;

		}

		window.update();
		frames++;
		rotation+=2.0f;
		
	
	
		
		
  
		
	}
	 
	//delete world;
	return 0;

}