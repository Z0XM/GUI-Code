#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace gui {
	class guiEntry {
	public:
		virtual void render(sf::RenderTarget&) = 0;
	};
}
