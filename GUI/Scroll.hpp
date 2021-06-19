#pragma once
#include <SFML/Graphics.hpp>
#include "Clickable.hpp"
#include <map>
#include <vector>

namespace gui {
    class Scroll : public Clickable {
	private:
		sf::RectangleShape bar, rect;
		float oldY, barY;
		bool freeze;
		struct {
			sf::Color backgroundColor;
		} original, highlight;

		void InitVariables();
		void InitHighlight();

		void updateHighlight();

	public:
		Scroll(float);
		~Scroll();

		void move(float x, float y);
		void setPosition(const sf::Vector2f&&);
		void moveBy(float mouseY);
		void reset(float);
		void connect(Clickable*);

		sf::Vector2f getPosition() const;
		Clickable* isHit(sf::Vector2f&);

		void render(sf::RenderTarget&);

		std::vector<Clickable*> scrollable;

		static void Move(float);
		static void Reset(float);

		static std::map<std::string, Scroll*> Group;
    };
}