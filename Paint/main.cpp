#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "Button.h"

using namespace sf;
using namespace std;

/*		Main Parent			*/

struct point {
	double x, y;
	point(float x, float y) : x(x),y(y) { }
};

class shape {
	int points;
	int color;
	int numberOfPoints;
public:
	shape() {
		points = 0;
		color = 0;
		numberOfPoints = 0;
	}
	~shape() {
		
		points = 0;
		color = 0;
		numberOfPoints = 0;
		
	}
	virtual void draw(RenderWindow& target) = 0;
	virtual bool contains(point p) = 0;
};

/*		Child Classes of Shape		*/
class text : public shape {
		
	Text textt;
	string str;
	Font font;

public:

	text(Vector2i pos) {
		textt.setPosition(Vector2f(pos.x, pos.y));
		font.loadFromFile("calibri.ttf");
		textt.setFont(font);
		textt.setFillColor(Color::Black);
	}

	void appendstr(char c) {
		str += c;
		textt.setString(str);
	}
	void trunc() {
		if (str.length() != 0) {
			str.pop_back();
			textt.setString(str);
		}
	}

	void changeColour(Color col) {
		textt.setFillColor(col);
	}

	void draw(RenderWindow& target) {
		target.draw(textt);
	}
	bool contains(point p) {
		return (textt.getGlobalBounds().contains(p.x, p.y));
	}
};

class OpenShape : public shape {
	bool style; // This Will tell us whether the OpenShape will be Line or Curve
public:
	virtual void changeColor() = 0;
};

class Polygon : public shape {
	bool fillColor; // This Will Tell Us Whether To Fill Color or Not
public:

	void fill(int color);
	void draw(RenderWindow& target);
	bool contains(point p);
};

class circle : public shape {
	bool fillColor; // This Will Tell Us Whether To Fill Color or Not
public:
	void fill(int color);
	void draw(RenderWindow& target);
	bool contains(point p);
};

/*		Child Classes of OpenShape		*/

class line: public OpenShape{
public:
	void draw(RenderWindow& target);
	bool contains(point p);
	void changeColor();
};

class curve : public OpenShape {
public:
	void draw(RenderWindow& target);
	bool contains(point p);
	void changeColor();
};

/*		Child Class of Polygon			*/

class rectangle : public Polygon {
public:
	bool contains(point p);
	void fill(int color);
};

int main() {
	
	RenderWindow window(VideoMode(1152, 648), "Paint");

	Font font;
	
	Texture fillTex;
	fillTex.loadFromFile("fill.png");
	
	Texture eraserTex;
	eraserTex.loadFromFile("eraser.png");

	Texture lineTex;
	lineTex.loadFromFile("line.png");
	
	Texture textTex;
	textTex.loadFromFile("text.png");


	//SIDEBAR
	RectangleShape sidebar = RectangleShape(Vector2f(120, 2000));
	sidebar.setFillColor(Color(150, 150, 150));
	
	Button* fillBtn = new Button(10, 0, fillTex, font, "", Color::Black, 0);
	Button* lineBtn = new Button(10, 100, lineTex, font, "", Color::Black, 0);
	Button* eraserBtn = new Button(10, 200, eraserTex, font, "", Color::Black, 0);
	Button* textBtn = new Button(10, 300, textTex, font, "", Color::Black, 0);

	//fill, eraser, line, text 
	string mode="eraser";
	bool clicked = false;
	
	vector<shape*> allShapes;
	shape* currentShape = NULL;

	
	while (window.isOpen()) {
		Vector2i mousePos;
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					cout << "Left Button is Pressed\n";
					clicked = true;
				}
			}
			
			else if (event.type == Event::TextEntered) {
				
				if ((event.text.unicode < 127 && event.text.unicode > 31) || event.text.unicode == 8) {
					if (currentShape != NULL) {
						text* temp = dynamic_cast<text*>(currentShape);
						if (event.text.unicode != 8) {
							temp->appendstr(event.text.unicode);
						}
						else temp->trunc();
					}	
				}
			}

			else if (event.type == Event::Closed) {
				window.close();
			}
		}
		mousePos = Mouse::getPosition(window);

		fillBtn->Update(Vector2f(mousePos));
		lineBtn->Update(Vector2f(mousePos));
		eraserBtn->Update(Vector2f(mousePos));
		textBtn->Update(Vector2f(mousePos));
		
		if (fillBtn->isPressed()) {
			mode = "fill";
			cout << mode;
			currentShape = NULL;
			clicked = false;
		}
		else if (lineBtn->isPressed()) {
			mode = "line";
			cout << mode;
			currentShape = NULL;
			clicked = false;
		}
		
		else if (eraserBtn->isPressed()) {
			mode = "eraser";
			cout << mode;
			currentShape = NULL;
			clicked = false;
		}
		
		else if (textBtn->isPressed()) {
			mode = "text";
			cout << mode;
			currentShape = NULL;
			clicked = false;
		}

		else if (clicked) {
			clicked = false;
			if (mode == "fill") {

			}
			else if (mode == "text") {
				currentShape = new text(mousePos);
				allShapes.push_back(currentShape);
			}
			else if (mode == "eraser") {
				for (vector<shape*>::iterator itr = allShapes.begin(); itr != allShapes.end(); itr++) {
					if ((*itr)->contains(point(mousePos.x, mousePos.y))) {
						allShapes.erase(itr);
						break;
					}
				}
			}
			else if (mode == "line") {

			}
		}


		window.clear(Color::White);
		window.draw(sidebar);
		fillBtn->Render(window);
		lineBtn->Render(window);
		eraserBtn->Render(window);
		textBtn->Render(window);
		

		for (int i = 0; i < allShapes.size(); i++) {
			allShapes[i]->draw(window);
		}

		window.display();
	}
}
