#include "Button.h"


Button::Button(float x, float y, const Texture& tex, const Font& TextFont, string text, Color FontColor, int FontSize) {
	
	texSize=Vector2f(tex.getSize().x, tex.getSize().y);

	this->buttonState=BTN_IDLE;
	this->BtnSprite.setColor(IdleColor);

	this->BtnSprite=Sprite(tex);
	this->BtnSprite.setPosition(x, y);

	this->font=TextFont;
	this->FontColor=FontColor;
	this->FontSize=FontSize;

	this->text.setFont(TextFont);
	this->text.setString(text);
	this->text.setFillColor(FontColor);
	this->text.setCharacterSize(FontSize);
	
	// FINALLY THIS MATHS GEOMETRY SHIT IS WORKING FINE (POSITIONING THE TEXT INSIDE BUTTON AT EXACT CENTER)
	this->text.setPosition(this->BtnSprite.getPosition().x + (texSize.x / 2) - (this->text.getLocalBounds().width / 2),
							this->BtnSprite.getPosition().y + (texSize.y / 2) - (this->text.getLocalBounds().height));

}

Button::~Button() {}

void Button::SetFontSize(int size) {
	FontSize=size;
	text.setCharacterSize(size);
}

void Button::SetFontColor(Color color) {
	FontColor = color;
	text.setFillColor(color);
}

void Button::SetFontStyle(Uint32 style) {
	text.setStyle(style);
	this->text.setPosition(this->BtnSprite.getPosition().x + (texSize.x / 2) - (this->text.getLocalBounds().width / 2),
							this->BtnSprite.getPosition().y + (texSize.y / 2) - (this->text.getLocalBounds().height));
}

void Button::SetIdleColor(Color color) {
	IdleColor = color;
}

void Button::SetHoverColor(Color color) {
	HoverColor = color;
}

void Button::SetPressedColor(Color color) {
	PressedColor = color;
}

void Button::SetDisabledColor(Color color) {
	DisabledColor = color;
}

void Button::SetButtonScale(Vector2f scale) {
	BtnSprite.setScale(scale);
	this->text.setPosition(this->BtnSprite.getPosition().x + ( (texSize.x * scale.x) / 2 ) - (this->text.getLocalBounds().width / 2),
							this->BtnSprite.getPosition().y + ( (texSize.y * scale.y) / 2) - (this->text.getLocalBounds().height ));

}

void Button::SetPosition(float x, float y) {
	this->BtnSprite.setPosition(x, y);

	this->text.setPosition(this->BtnSprite.getPosition().x + (texSize.x / 2) - (this->text.getLocalBounds().width / 2),
		this->BtnSprite.getPosition().y + (texSize.y / 2) - (this->text.getLocalBounds().height));
}

void Button::SetText(string text) {
	this->text.setString(text);
	this->text.setPosition(this->BtnSprite.getPosition().x + ((texSize.x * BtnSprite.getScale().x) / 2) - (this->text.getLocalBounds().width / 2),
							this->BtnSprite.getPosition().y + ((texSize.y * BtnSprite.getScale().y) / 2) - (this->text.getLocalBounds().height));

}

void Button::SetActive(bool boolshit) {
	disabled = !boolshit;
}

const bool Button::isPressed() const {
	if (buttonState == BTN_CLICKED) {
		return true;
	}
	else return false;
}

const bool Button::isHovered()const {
	if (buttonState == BTN_HOVER) {
		return true;
	}
	else return false;
}

void Button::Render(RenderTarget& target) {
	target.draw(BtnSprite);
	target.draw(text);
}

void Button::Update(const Vector2f& mousePos) {
	// ghatia chuss
	//mouse position update kr k pass krni hai

	if (disabled) {
		buttonState = BTN_DISABLED;
	}
	else {

		if (buttonState != BTN_PRESSED) {
			buttonState = BTN_IDLE;
		}
		
		if (BtnSprite.getGlobalBounds().contains(mousePos)) {
			
			if (buttonState != BTN_PRESSED) {
				buttonState = BTN_HOVER;
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				buttonState = BTN_PRESSED;
			}

			else if (buttonState == BTN_PRESSED) {
				buttonState = BTN_CLICKED;
			}
		}
		else buttonState = BTN_IDLE;
	}

	switch (buttonState) {

	case BTN_IDLE:
		BtnSprite.setColor(IdleColor);
		text.setFillColor(FontColor);
		break;

	case BTN_HOVER:
		BtnSprite.setColor(HoverColor);
		text.setFillColor(FontColor);
		break;

	case BTN_PRESSED:
		BtnSprite.setColor(PressedColor);
		text.setFillColor(FontColor);
		break;

	case BTN_DISABLED:
		BtnSprite.setColor(DisabledColor);
		text.setFillColor(Color(200, 200, 200, 255));
		break;

	//default:
		//NOT POSSIBLE AS FAR AS SHIT WORKS FINE HAH
			
		// NOW AFTER UPDATE IT IS POSSIBLE DUE TO SOME PROBLEM BUT THAT DOESNT BOTHER THE BUTTON AT ALL LOL
		//BtnSprite.setColor(Color::Red);
	
	}
	
}