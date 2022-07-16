#pragma once

#include"SFML/Graphics.hpp"
//#include"SFML/Audio.hpp"

using namespace sf;
using namespace std;

enum button_states {BTN_IDLE, BTN_HOVER, BTN_PRESSED, BTN_DISABLED, BTN_CLICKED};

class Button {

private:
	
	short unsigned buttonState;

	int FontSize;

	Text text;
	Font font;
	Sprite BtnSprite;
	
	Vector2f texSize;

	Color FontColor;
	Color IdleColor = Color::White;
	Color HoverColor = Color(200,200,200,255);
	Color PressedColor = Color(170, 170, 170, 255);
	Color DisabledColor = Color(200, 200, 200, 170);
	
	bool disabled=false;

public:
	
	Button(float x, float y, const Texture& tex, const Font& TextFont, string text, Color FontColor, int FontSize);
	~Button();


	//-------------------- F U N C T I O N S -----------------------
	void SetFontSize(int size);
	void SetFontColor(Color color);
	void SetText(string text);
	void SetFontStyle(Uint32 style);

	void SetIdleColor(Color color);
	void SetHoverColor(Color color);
	void SetPressedColor(Color color);
	void SetDisabledColor(Color color);
	
	void SetPosition(float x, float y);
	void SetButtonScale(Vector2f scale);

	void SetActive(bool boolshit);
	
	void Render(RenderTarget& target);
	void Update(const Vector2f& mousePos);
	const bool isPressed()const;
	const bool isHovered()const;

};