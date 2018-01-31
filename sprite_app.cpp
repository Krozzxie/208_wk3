#include "sprite_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <maths/math_utils.h>
#include <input\sony_controller_input_manager.h>


string boob;

SpriteApp::SpriteApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	input_manager_(NULL),
	font_(NULL)
{
}

void SpriteApp::Init()
{
	// create a sprite renderer to draw your sprites
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	
	
	InitFont();

	my_sprite_.set_position(platform_.width()*0.5f, platform_.height()*0.5f, 0.0f);
	my_sprite_.set_width(32.0f);
	my_sprite_.set_height(32.0f);


	//create the input manager

	input_manager_ = gef::InputManager::Create(platform_);
}

void SpriteApp::CleanUp()
{
	CleanUpFont();

	//delet te input manager

	delete input_manager_;
	input_manager_ = NULL;

// destroy sprite renderer once you've finished using it
	
}

string SpriteApp::GetButton(int keyID)
{

	switch (keyID) {

		case 1:gef_SONY_CTRL_START;

			return "CNTRL: Start";

		break;

			case 2:gef_SONY_CTRL_SELECT;

				return "CNTRL: Select";

			break;

				case 3:gef_SONY_CTRL_OPTIONS;

					return "CNTRL: Options";

				break;
		
					case 4:gef_SONY_CTRL_L1;

						return "BTN: L1";

					break;

						case 5:gef_SONY_CTRL_L2;

							return "BTN: L2";

						break;

							case 6:gef_SONY_CTRL_L3;

								return "BTN: L3";

							break;

								case 7:gef_SONY_CTRL_R1;

									return "BTN: R1";

								break;

									case 8:gef_SONY_CTRL_R2;

										return "BTN: R2";

									break;

										case 9:gef_SONY_CTRL_R3;
						
											return "BTN: R3";

										break;

											case 10:gef_SONY_CTRL_TOUCH_PAD;

												return "CNTRL: TouchPad";

											break;
		
												case 11:gef_SONY_CTRL_TRIANGLE;

													return "BTN: Triangle";

												break;
		
													case 12:gef_SONY_CTRL_CROSS;

														return "BTN: Cross";

													break;

														case 13:gef_SONY_CTRL_SQUARE;

															return "BTN: Square";
														break;

															case 14:gef_SONY_CTRL_CIRCLE;

																return "BTN: Circle";

															break;

																case 15:gef_SONY_CTRL_UP;

																	return "DPAD: Up";

																break;

																	case 16:gef_SONY_CTRL_DOWN;

																		return "DPAD: Down";

																	break;

																		case 17:gef_SONY_CTRL_LEFT;

																			return "DPAD: Left";

																		break;

																			case 18:gef_SONY_CTRL_RIGHT;

																				return "DPAD: Right";

																			break;
	}

}

bool SpriteApp::Update(float frame_time)
{
	// frame rate = 1 second / frame_delta_time
	fps_ = 1.0f / frame_time;

	// get the recent data from the input devices
	if (input_manager_)
	{
		input_manager_->Update();

		// get controller input data for all controllers

		gef::SonyControllerInputManager* controller_input = input_manager_->controller_input();

		if (controller_input)
		{
			// read controller data for controller 0
			const gef::SonyController* controller = controller_input->GetController(0);

			if(controller)
			{
				gef::Vector4 sprite_position = my_sprite_.position();

				// Actions
				if (controller->buttons_down() & gef_SONY_CTRL_CROSS)
				{
					// Action
				}
				if (controller->buttons_down() & gef_SONY_CTRL_CIRCLE)
				{
					// Action
				}
				if (controller->buttons_down() & gef_SONY_CTRL_TRIANGLE)
				{
					// Action
					sprite_position.set_x(480.0f);
					sprite_position.set_y(272.0f);
				}
				if (controller->buttons_down() & gef_SONY_CTRL_SQUARE)
				{
					// Action
				}
				// Shoulder
				if (controller->buttons_down() & gef_SONY_CTRL_L2)
				{
					gef::Vector4 sprite_position = my_sprite_.position();

					sprite_position.set_x(sprite_position.x() + my_sprite_.xSpeed());
					sprite_position.set_y(sprite_position.y() + my_sprite_.ySpeed());

					my_sprite_.set_rotation(my_sprite_.rotation());
					my_sprite_.set_position(sprite_position);
				}
				if (controller->buttons_down() & gef_SONY_CTRL_R2)
				{
					gef::Vector4 sprite_position = my_sprite_.position();

					sprite_position.set_x(sprite_position.x() + my_sprite_.xSpeed());
					sprite_position.set_y(sprite_position.y() + my_sprite_.ySpeed());

					my_sprite_.set_rotation(my_sprite_.rotation());
					my_sprite_.set_position(sprite_position);
				}
				// System buttons
				if (controller->buttons_pressed() & gef_SONY_CTRL_START)
				{
					//paused = !paused;
				}
				if (controller->buttons_down() & gef_SONY_CTRL_SELECT)
				{
					// Menu
				}
				// Dpad
				if (controller->buttons_down() & gef_SONY_CTRL_UP)
				{
					sprite_position.set_y(sprite_position.y() - my_sprite_.ySpeed());
				}
				if (controller->buttons_down() & gef_SONY_CTRL_RIGHT)
				{
					sprite_position.set_x(sprite_position.x() + my_sprite_.xSpeed());
				}
				if (controller->buttons_down() & gef_SONY_CTRL_DOWN)
				{
					sprite_position.set_y(sprite_position.y() + my_sprite_.ySpeed());
				}
				if (controller->buttons_down() & gef_SONY_CTRL_LEFT)
				{
					sprite_position.set_x(sprite_position.x() - my_sprite_.xSpeed());
				}
				// Sticks
				// Read left stick
				float left_x_axis = controller->left_stick_x_axis();
				float left_y_axis = controller->left_stick_y_axis();

				// Read right stick
				float right_x_axis = controller->right_stick_x_axis();
				float right_y_axis = controller->right_stick_y_axis();

				// Set position from left stick
				sprite_position.set_x(sprite_position.x() + (my_sprite_.xSpeed() * left_x_axis));
				sprite_position.set_y(sprite_position.y() + (my_sprite_.ySpeed() * left_y_axis));

				// Set rotation from right stick
				if (right_x_axis != 0 || right_y_axis != 0)
				{
					angle = atan(right_y_axis / right_x_axis);
				}

				// Start+Select
				if ((controller->buttons_down() & (gef_SONY_CTRL_START | gef_SONY_CTRL_SELECT)) == (gef_SONY_CTRL_START | gef_SONY_CTRL_SELECT))
				{
					// Exit app
					exit(0);
				}

				my_sprite_.set_rotation(angle);
				my_sprite_.set_position(sprite_position);
			}
		}
	}
}



void SpriteApp::Render()
{
	// draw all sprites between the Begin() and End() calls
	sprite_renderer_->Begin();

	// draw my sprite here
	sprite_renderer_->DrawSprite(my_sprite_);

	DrawHUD();
	sprite_renderer_->End();
}


void SpriteApp::InitFont()
{
	// create a Font object and load in the comic_sans font data
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");

	buttonText_ = new gef::Font(platform_);
	buttonText_->Load("comic_sans");
}

void SpriteApp::CleanUpFont()
{
	// destroy the Font object
	delete font_;
	font_ = NULL;

	delete buttonText_;
	buttonText_ = NULL;
}

void SpriteApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(650.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"FPS: %.1f xpos: %.1f",							// string of text to render
			fps_,									// any variables used in formatted text string http://www.cplusplus.com/reference/cstdio/printf/
			my_sprite_.position().x()
			);
	}

}

