#pragma once
#include <algorithm>
#include "model.hxx"
#include "space_object.hxx"

// Controls how the game is shown to the user:
class View
{
public:
    ///
    /// Public member functions
    ///
    explicit View(Model&);

    void draw(ge211::Sprite_set&);

private:
    ///
    /// Private helper functions
    ///

    // The view can look at the model but doesn't change it.
    Model& model_;

    ge211::Text_sprite explanation_ ;
    ge211::Text_sprite life_ ;
    ge211::Font sans42_{"sans.ttf", 42};

    // Sprites for tiles:
    ge211::Image_sprite asteroid_ {"asteroid.png"};
    ge211::Image_sprite space_ship_ {"space_ship.gif"};
    ge211::Image_sprite torpedo_ {"torpedo.gif"};
    ge211::Image_sprite torpedo2_ {"torpedo2.png"};

    double asteroid_scale_ = .1;
    double space_ship_scale_ = .1;
    double torpedo_scale_ = .1;
    double torpedo2_scale_ = .7;
};
