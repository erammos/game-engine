
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



//#include "Object2D.h"

using namespace Engine;
using namespace Graphics;
using namespace Math;

int main()
{
	//image format
	
	Window window = Window("engine", 800, 600);
	

	
	
	//Mat4f proj = Mat4f::persp2(M_PI/4, 800.0f/600.0f, 1.0f, 10.0f);
	
	
	int angle = 0.0f;
	
//	Sprite sprite(80, 80/2, 4, 4, Color(1, 0, 0, 0.5));
	//Sprite sprite2(5, 3, 2, 3, Color(0.2f, 0, 1.0f, 0.5f));


	

	Shader shader("VertexShader.vert", "FragmentShader.frag");
	shader.enable();
	SpriteRenderer renderer;
	renderer.SetShaderId(shader.program_id);
	renderer.SetProjectionMatrix(Mat4f::ortho(0.0, 80.0f, 0.0f, 60.0f, 1.0f, -1.0f));

	//glUniformMatrix4fv(glGetUniformLocation(shader.program_id, "model_matrix"), 1, GL_FALSE, Mat4f::identity().values);
	//glActiveTexture(GL_TEXTURE0);

	

	
	
	

	//glUniform1i(glGetUniformLocation(shader.program_id, "tex[1]"), 1);


	
	//world->Add(obj1);
	
	// 0, GL_RBG

	

	glUniform1i(glGetUniformLocation(shader.program_id, "tex0"), 0);
	glUniform1i(glGetUniformLocation(shader.program_id, "tex1"), 1);
	glUniform1i(glGetUniformLocation(shader.program_id, "tex2"), 2);
	
    // TextureManager::Inst()->LoadTexture("red.png",0,width,height);
	 GameObject * world = new GameObject();
	
	 world->AddGraphicComponent(new SpriteComponent("pink.png"));

	 world->LocalTransform = Mat4f::translation(0, 0, 0);
	 world->LocalTransform = Mat4f::scale(0.2, 0.2, 0.2);

	 GameObject * group = new GameObject();
	

	 for (int i = 0; i < 2; i++)
	 {
		 GameObject * obj = new GameObject();
		 obj->AddGraphicComponent(new SpriteComponent("red.png"));
		 obj->LocalTransform = Mat4f::translation(i*100, 0, 0) * Mat4f::scale(0.2, 0.2, 0.2);
		 group->Add(obj);
	 }
	 world->Add(group);
	
	// glActiveTexture(GL_TEXTURE0);
	 //TextureManager::Inst()->BindTexture(0);
	// glActiveTexture(GL_TEXTURE1);
	 //TextureManager::Inst()->BindTexture(1);
	// glActiveTexture(GL_TEXTURE2);
	// TextureManager::Inst()->BindTexture(2);
	// glActiveTexture(GL_TEXTURE0);
	 //glBindTexture(GL_TEXTURE_2D, 0);
	 //TextureManager::Inst()->BindTexture(1);
	 //TextureManager::Inst()->BindTexture(1);
	// TextureManager::Inst()->BindTexture(1);

	//TextureManager::Inst()->BindTexture(0);
	//GLint texID[] 
	//{
		//1,2,3,4,5,7,8,9
	//}
	//glUniform1i(glGetUniformLocation(shader.program_id, "tex"), 0);
	//glUniform1i(glGetUniformLocation(shader.program_id, "tex"), texIDS,10);
	
	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		
		//Mat4f model_m = Mat4f::translation(0,0,-5) *Mat4f::rotateY(TO_RADIANS(angle));
		//
		glUniform2f(glGetUniformLocation(shader.program_id, "light_pos"), (window.mouse_x / 800.0f)*80.0f, 60.0f - ((window.mouse_y) / 600.0f)*60.0f);

		window.clear();
		renderer.Begin();
		//world->SetTransform(Mat4f::translation((window.mouse_x/800.0f)*80.0f, 60.0f-((window.mouse_y)/600.0f)*60.0f, 1)* Mat4f::scale(0.2, 0.2, 0.2));
		//group->SetTransform(Mat4f::translation((window.mouse_x / 800.0f)*80.0f, 60.0f - ((window.mouse_y) / 600.0f)*60.0f, 1));
		//world->SetTransform(Mat4f::translation((window.mouse_x/800.0f)*80.0f, 60.0f-((window.mouse_y)/600.0f)*60.0f, 1));
		world->Draw(&renderer);
		renderer.End();

		window.update();
		frames++;

		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			//printf("%d fps\n", frames);
			frames = 0;
		}
	}
	 
	delete world;
	return 0;

}