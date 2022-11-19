#include "view.hxx"
#include <iostream>

///
/// Constructor
///

View::View(Model& model)
        : model_(model),
        explanation_(),
        life_()
{
}

///
/// Member functions
///

void
View::draw(ge211::Sprite_set& sprites)
{
    std::vector<std::unique_ptr<Space_object>>
            & space_objects = model_.space_objects();
    for (std::unique_ptr<Space_object>& so : space_objects) {
        if (!so->is_space_junk()) {
            ge211::Posn<int> pos {0, 0};
            pos.x = (int) so->position().x;
            pos.y = (int) so->position().y;
            ge211::Transform
                    rotation = ge211::Transform::rotation(so->heading());
            switch (so->material()) {
            case Space_object::Material::metal: // spaceship
                rotation.set_scale(space_ship_scale_);
                pos.x -= space_ship_.dimensions().width * space_ship_scale_ / 2;
                pos.y
                        -=
                        space_ship_.dimensions().height * space_ship_scale_ / 2;
                sprites.add_sprite(space_ship_, pos, 2, rotation);
                break;
            case Space_object::Material::rock: // asteroid
            {
                Asteroid *ss = dynamic_cast<Asteroid *> (so.get());
                rotation.set_scale(asteroid_scale_ * ss->mass());
                pos.x
                        -=
                        asteroid_.dimensions().width * asteroid_scale_ *
                        ss->mass() / 2;
                pos.y
                        -=
                        asteroid_.dimensions().height * asteroid_scale_ *
                        ss->mass() / 2;
                sprites.add_sprite(asteroid_, pos, 0, rotation);
                rotation.set_scale(torpedo2_scale_);
                pos.x += torpedo2_.dimensions().width * torpedo_scale_ / .42;
                pos.y += torpedo2_.dimensions().height * torpedo_scale_ / .6;
                sprites.add_sprite(torpedo2_, pos, 1, rotation);
            }
                break;
            case Space_object::Material::light2: // light
                rotation.set_scale(torpedo2_scale_);
                pos.x += torpedo2_.dimensions().width * torpedo_scale_ / 4.7;
                pos.y += torpedo2_.dimensions().height * torpedo_scale_ / 6;
                sprites.add_sprite(torpedo2_, pos, 1, rotation);
                break;
            case Space_object::Material::light: // light
                rotation.set_scale(torpedo_scale_);
                pos.x -= torpedo_.dimensions().width * torpedo_scale_ / 2;
                pos.y -= torpedo_.dimensions().height * torpedo_scale_ / 2;
                sprites.add_sprite(torpedo_, pos, 1, rotation);
                break;
            }
        }
    }
    ge211::Text_sprite:: Builder scoreboard(sans42_);
    scoreboard.color(ge211::Color(142,232,166));
    scoreboard << "Score:" << model_.score;
    explanation_.reconfigure(scoreboard);
    sprites.add_sprite(explanation_, {425,25}, 5);

    ge211::Text_sprite:: Builder lives(sans42_);
    lives.color(ge211::Color(232,142,166));
    lives << "Lives:" << model_.space_ship_.get_slives();
    life_.reconfigure(lives);
    sprites.add_sprite(life_, {25,500}, 5);
}
