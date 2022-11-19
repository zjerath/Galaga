#include "model.hxx"
#include "space_object.hxx"
#include "view.hxx"
#include <catch.hxx>
using namespace ge211;

ge211::Dims<int> screen_dimensions {1024, 768};
Model model({1024,768});

//Checks that model initializes spaceship correctly
TEST_CASE("Spaceship")
{
    ge211::Posn<double> pos {512, 688};
    CHECK(model.space_ship_.position() == pos);
}

//Checks that spaceship moves left
TEST_CASE("Move Left")
{
    int dt = 1;
    model.turn_left(true);
    model.update(dt);
    ge211::Posn<double> pos {502, 688};
    CHECK(model.space_ship_.position() == pos);
}

//Checks that spaceship cannot go off right side of screen
TEST_CASE("Off Right")
{
    int dt = 1;
    for(int i = 0; i < 60; i++){
        model.turn_right(true);
        model.update(dt);
    }
    CHECK(model.space_ship_.position().x < 1024);
}

//Checks that spaceship fires torpedo
TEST_CASE("Fire Torpedo")
{
    int before = model.space_objects().size();
    int dt = 1;
    model.fire_torpedo();
    model.update(dt);
    int after = model.space_objects().size();
    CHECK(after > before);
    model.fire_torpedo2();
    model.update(dt);
    int after2 = model.space_objects().size();
    CHECK(after2 > after);
}

//Checks that invaders are created when one is eliminated
TEST_CASE("New Asteroid")
{
    int before = model.space_objects().size();
    int dt = 1;
    model.new_asteroid_(50, {512, 600});
    model.update(dt);
    model.fire_torpedo();
    for(int i = 0; i < 5; i++){
        model.update(dt);
    }
    int after = model.space_objects().size();
    CHECK(after > before);
}
