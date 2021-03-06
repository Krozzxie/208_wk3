#ifndef _sprite_app_H
#define _sprite_app_H

#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector4.h>
#include <vector>
#include <input/input_manager.h>

#include <string>

using namespace std;


// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
}

class SpriteApp : public gef::Application
{
public:
	SpriteApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	string GetButton(int key);

	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::Font* buttonText_;

	float fps_;
	float angle;
	gef::Sprite my_sprite_;

	gef::InputManager* input_manager_;
};

#endif // _sprite_app_H
