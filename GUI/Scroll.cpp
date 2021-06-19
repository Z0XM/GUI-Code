#include "Scroll.hpp"
#include <algorithm>

namespace gui {
    std::map<std::string, Scroll*> Scroll::Group;

    Scroll::Scroll(float height)
    {
        this->rect.setSize(sf::Vector2f(20, height));
        this->bar.setSize(sf::Vector2f(20, height));
        this->InitVariables();
        this->InitHighlight();
    }

    Scroll::~Scroll()
    {

    }

    void Scroll::InitVariables()
    {
        rect.setFillColor(sf::Color(41, 41, 41));
        bar.setFillColor(sf::Color(150, 150, 150, 70));
        this->setClickField(this->bar.getGlobalBounds());
        this->setAction([] {});
        this->freeze = false;
    }
    void Scroll::InitHighlight()
    {
        original.backgroundColor = bar.getFillColor(); 
        highlight.backgroundColor = rect.getFillColor() + sf::Color(50, 50, 50);
    }

    void Scroll::updateHighlight()
    {
        auto property = this->state == ORIGINAL ? this->original : this->highlight;
        this->bar.setFillColor(property.backgroundColor);
    }

    void Scroll::reset(float y)
    {
        this->oldY = y;
        this->barY = y - this->bar.getPosition().y;
    }

    void Scroll::move(float x, float y)
    {
        this->bar.setPosition(this->getPosition() + sf::Vector2f(x, y));
        this->setClickField(this->bar.getGlobalBounds());
    }
    void Scroll::setPosition(const sf::Vector2f&& position)
    {
        this->rect.setPosition(position);
        this->bar.setPosition(this->rect.getPosition());
        this->setClickField(this->bar.getGlobalBounds());
    }
    void Scroll::moveBy(float mouseY)
    {      
        float dy = mouseY - this->oldY;
        float y = this->bar.getPosition().y + dy;
        
        if (y < this->rect.getPosition().y) {
            y = this->rect.getPosition().y;
        }
        else if (y + this->bar.getSize().y > this->rect.getPosition().y + this->rect.getSize().y) {
            y = this->rect.getPosition().y + this->rect.getSize().y - this->bar.getSize().y;
        }
        this->bar.setPosition(this->bar.getPosition().x, y);
        this->setClickField(this->bar.getGlobalBounds());

        for (auto it : this->scrollable)
           it->move(0, -dy);

        this->oldY = mouseY;
        
    }
    sf::Vector2f Scroll::getPosition() const
    {
        return rect.getPosition();
    }
    Clickable* Scroll::isHit(sf::Vector2f& position)
    {
        return this->contains(position) ? this : nullptr;
    }
    void Scroll::render(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->rect);
        renderTarget.draw(this->bar);
    }

    void Scroll::connect(Clickable* clickable)
    {
        this->scrollable.push_back(clickable);
        this->bar.setSize(sf::Vector2f(this->bar.getSize().x, this->bar.getSize().y - clickable->getClickField().height));
        this->setClickField(this->bar.getGlobalBounds());
    }

    void Scroll::Move(float mouseY)
    {
        for (auto it = Group.begin(); it != Group.end(); it++) {
            if (Clickable::clicked == (Clickable*)(it->second)) {
                it->second->moveBy(mouseY); break;
            }
        }
    }

    void Scroll::Reset(float Y)
    {
        for (auto it = Group.begin(); it != Group.end(); it++) {
            if (Clickable::clicked == (Clickable*)(it->second)) {
                it->second->reset(Y); break;
            }
        }
    }
}