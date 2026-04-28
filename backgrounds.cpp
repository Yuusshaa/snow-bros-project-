#include "backgrounds.h"
#include <iostream>
using namespace std;

Background::Background()
{
    currentFrame = 0;
    timer = 0;
    frameSpeed = 0.1f;  // change this to make animation faster or slower
}

void Background::loadLevel(int level)
{
    currentFrame = 0;
    timer = 0;

    if (level == 1)
    {
        totalFrames = 7;
        frames[0].loadFromFile("lvl1bgs/ezgif-frame-001.png");
        frames[1].loadFromFile("lvl1bgs/ezgif-frame-002.png");
        frames[2].loadFromFile("lvl1bgs/ezgif-frame-003.png");
        frames[3].loadFromFile("lvl1bgs/ezgif-frame-004.png");
        frames[4].loadFromFile("lvl1bgs/ezgif-frame-005.png");
        frames[5].loadFromFile("lvl1bgs/ezgif-frame-006.png");
        frames[6].loadFromFile("lvl1bgs/ezgif-frame-007.png");
    }

    else if (level == 2)
    {
        totalFrames = 20;
        frames[0].loadFromFile("lvl2bgs/lvl2_1.png");
        frames[1].loadFromFile("lvl2bgs/lvl2_2.png");
        frames[2].loadFromFile("lvl2bgs/lvl2_3.png");
        frames[3].loadFromFile("lvl2bgs/lvl2_4.png");
        frames[4].loadFromFile("lvl2bgs/lvl2_5.png");
        frames[5].loadFromFile("lvl2bgs/lvl2_6.png");
        frames[6].loadFromFile("lvl2bgs/lvl2_7.png");
        frames[7].loadFromFile("lvl2bgs/lvl2_8.png");
        frames[8].loadFromFile("lvl2bgs/lvl2_9.png");
        frames[9].loadFromFile("lvl2bgs/lvl2_10.png");
        frames[10].loadFromFile("lvl2bgs/lvl2_11.png");
		frames[11].loadFromFile("lvl2bgs/lvl2_12.png");
        frames[12].loadFromFile("lvl2bgs/lvl2_13.png");
        frames[13].loadFromFile("lvl2bgs/lvl2_14.png");
        frames[14].loadFromFile("lvl2bgs/lvl2_15.png");
        frames[15].loadFromFile("lvl2bgs/lvl2_16.png");
        frames[16].loadFromFile("lvl2bgs/lvl2_17.png");
        frames[17].loadFromFile("lvl2bgs/lvl2_18.png");
        frames[18].loadFromFile("lvl2bgs/lvl2_19.png");
        frames[19].loadFromFile("lvl2bgs/lvl2_20.png");
    }

    else if (level == 3)
    {
        totalFrames = 40;
        frames[0].loadFromFile("lvl3bgs/ezgif-frame-001.png");
        frames[1].loadFromFile("lvl3bgs/ezgif-frame-002.png");
        frames[2].loadFromFile("lvl3bgs/ezgif-frame-003.png");
        frames[3].loadFromFile("lvl3bgs/ezgif-frame-004.png");
        frames[4].loadFromFile("lvl3bgs/ezgif-frame-005.png");
        frames[5].loadFromFile("lvl3bgs/ezgif-frame-006.png");
        frames[6].loadFromFile("lvl3bgs/ezgif-frame-007.png");
        frames[7].loadFromFile("lvl3bgs/ezgif-frame-008.png");
        frames[8].loadFromFile("lvl3bgs/ezgif-frame-009.png");
        frames[9].loadFromFile("lvl3bgs/ezgif-frame-010.png");
        frames[10].loadFromFile("lvl3bgs/ezgif-frame-011.png");
        frames[11].loadFromFile("lvl3bgs/ezgif-frame-012.png");
        frames[12].loadFromFile("lvl3bgs/ezgif-frame-013.png");
        frames[13].loadFromFile("lvl3bgs/ezgif-frame-014.png");
        frames[14].loadFromFile("lvl3bgs/ezgif-frame-015.png");
        frames[15].loadFromFile("lvl3bgs/ezgif-frame-016.png");
        frames[16].loadFromFile("lvl3bgs/ezgif-frame-017.png");
        frames[17].loadFromFile("lvl3bgs/ezgif-frame-018.png");
        frames[18].loadFromFile("lvl3bgs/ezgif-frame-019.png");
        frames[19].loadFromFile("lvl3bgs/ezgif-frame-020.png");
        frames[20].loadFromFile("lvl3bgs/ezgif-frame-021.png");
        frames[21].loadFromFile("lvl3bgs/ezgif-frame-022.png");
        frames[22].loadFromFile("lvl3bgs/ezgif-frame-023.png");
        frames[23].loadFromFile("lvl3bgs/ezgif-frame-024.png");
        frames[24].loadFromFile("lvl3bgs/ezgif-frame-025.png");
        frames[25].loadFromFile("lvl3bgs/ezgif-frame-026.png");
        frames[26].loadFromFile("lvl3bgs/ezgif-frame-027.png");
        frames[27].loadFromFile("lvl3bgs/ezgif-frame-028.png");
        frames[28].loadFromFile("lvl3bgs/ezgif-frame-029.png");
        frames[29].loadFromFile("lvl3bgs/ezgif-frame-030.png");
        frames[30].loadFromFile("lvl3bgs/ezgif-frame-031.png");
        frames[31].loadFromFile("lvl3bgs/ezgif-frame-032.png");
        frames[32].loadFromFile("lvl3bgs/ezgif-frame-033.png");
        frames[33].loadFromFile("lvl3bgs/ezgif-frame-034.png");
        frames[34].loadFromFile("lvl3bgs/ezgif-frame-035.png");
        frames[35].loadFromFile("lvl3bgs/ezgif-frame-036.png");
        frames[36].loadFromFile("lvl3bgs/ezgif-frame-037.png");
        frames[37].loadFromFile("lvl3bgs/ezgif-frame-038.png");
        frames[38].loadFromFile("lvl3bgs/ezgif-frame-039.png");
        frames[39].loadFromFile("lvl3bgs/ezgif-frame-040.png");
    }

    else if (level == 4)
    {
        totalFrames = 13;
		frames[0].loadFromFile("lvl4bgs/ezgif-frame-001.png");
        frames[1].loadFromFile("lvl4bgs/ezgif-frame-002.png");
        frames[2].loadFromFile("lvl4bgs/ezgif-frame-003.png");
        frames[3].loadFromFile("lvl4bgs/ezgif-frame-004.png");
        frames[4].loadFromFile("lvl4bgs/ezgif-frame-005.png");
        frames[5].loadFromFile("lvl4bgs/ezgif-frame-006.png");
        frames[6].loadFromFile("lvl4bgs/ezgif-frame-007.png");
        frames[7].loadFromFile("lvl4bgs/ezgif-frame-008.png");
        frames[8].loadFromFile("lvl4bgs/ezgif-frame-009.png");
        frames[9].loadFromFile("lvl4bgs/ezgif-frame-010.png");
        frames[10].loadFromFile("lvl4bgs/ezgif-frame-011.png");
        frames[11].loadFromFile("lvl4bgs/ezgif-frame-012.png");
        frames[12].loadFromFile("lvl4bgs/ezgif-frame-013.png");
    }

    else if (level == 5)
    {
        totalFrames = 1;
		frames[0].loadFromFile("lvl5.jpeg");
    }


    else if (level == 6)
    {
        totalFrames = 13;
        frames[0].loadFromFile("lvl6bgs/ezgif-frame-001.png");
        frames[1].loadFromFile("lvl6bgs/ezgif-frame-002.png");
        frames[2].loadFromFile("lvl6bgs/ezgif-frame-003.png");
        frames[3].loadFromFile("lvl6bgs/ezgif-frame-004.png");
        frames[4].loadFromFile("lvl6bgs/ezgif-frame-005.png");
        frames[5].loadFromFile("lvl6bgs/ezgif-frame-006.png");
        frames[6].loadFromFile("lvl6bgs/ezgif-frame-007.png");
        frames[7].loadFromFile("lvl6bgs/ezgif-frame-008.png");
        frames[8].loadFromFile("lvl6bgs/ezgif-frame-009.png");
        frames[9].loadFromFile("lvl6bgs/ezgif-frame-010.png");
        frames[10].loadFromFile("lvl6bgs/ezgif-frame-011.png");
        frames[11].loadFromFile("lvl6bgs/ezgif-frame-012.png");
        frames[12].loadFromFile("lvl6bgs/ezgif-frame-013.png");
    }

    else if (level == 7)
    {
        totalFrames = 20;
		frames[0].loadFromFile("lvl7bgs/ezgif-frame-001.png");
        frames[1].loadFromFile("lvl7bgs/ezgif-frame-002.png");
        frames[2].loadFromFile("lvl7bgs/ezgif-frame-003.png");
        frames[3].loadFromFile("lvl7bgs/ezgif-frame-004.png");
        frames[4].loadFromFile("lvl7bgs/ezgif-frame-005.png");
        frames[5].loadFromFile("lvl7bgs/ezgif-frame-006.png");
        frames[6].loadFromFile("lvl7bgs/ezgif-frame-007.png");
        frames[7].loadFromFile("lvl7bgs/ezgif-frame-008.png");
        frames[8].loadFromFile("lvl7bgs/ezgif-frame-009.png");
        frames[9].loadFromFile("lvl7bgs/ezgif-frame-010.png");
        frames[10].loadFromFile("lvl7bgs/ezgif-frame-011.png");
        frames[11].loadFromFile("lvl7bgs/ezgif-frame-012.png");
        frames[12].loadFromFile("lvl7bgs/ezgif-frame-013.png");
        frames[13].loadFromFile("lvl7bgs/ezgif-frame-014.png");
        frames[14].loadFromFile("lvl7bgs/ezgif-frame-015.png");
        frames[15].loadFromFile("lvl7bgs/ezgif-frame-016.png");
        frames[16].loadFromFile("lvl7bgs/ezgif-frame-017.png");
        frames[17].loadFromFile("lvl7bgs/ezgif-frame-018.png");
        frames[18].loadFromFile("lvl7bgs/ezgif-frame-019.png");
		frames[19].loadFromFile("lvl7bgs/ezgif-frame-020.png");
    }

    else if (level == 8)
    {
        totalFrames = 13;
		frames[0].loadFromFile("lvl8bgs/ezgif-frame-001.png");
        frames[1].loadFromFile("lvl8bgs/ezgif-frame-002.png");
        frames[2].loadFromFile("lvl8bgs/ezgif-frame-003.png");
        frames[3].loadFromFile("lvl8bgs/ezgif-frame-004.png");
        frames[4].loadFromFile("lvl8bgs/ezgif-frame-005.png");
        frames[5].loadFromFile("lvl8bgs/ezgif-frame-006.png");
        frames[6].loadFromFile("lvl8bgs/ezgif-frame-007.png");
        frames[7].loadFromFile("lvl8bgs/ezgif-frame-008.png");
        frames[8].loadFromFile("lvl8bgs/ezgif-frame-009.png");
        frames[9].loadFromFile("lvl8bgs/ezgif-frame-010.png");
        frames[10].loadFromFile("lvl8bgs/ezgif-frame-011.png");
        frames[11].loadFromFile("lvl8bgs/ezgif-frame-012png");
        frames[12].loadFromFile("lvl8bgs/ezgif-frame-013.png");
    }

    else if (level == 9)
    {
        totalFrames = 42;
		frames[0].loadFromFile("lvl9bgs/ezgif-frame-001.png");
        frames[1].loadFromFile("lvl9bgs/ezgif-frame-002.png");
        frames[2].loadFromFile("lvl9bgs/ezgif-frame-003.png");
        frames[3].loadFromFile("lvl9bgs/ezgif-frame-004.png");
        frames[4].loadFromFile("lvl9bgs/ezgif-frame-005.png");
        frames[5].loadFromFile("lvl9bgs/ezgif-frame-006.png");
        frames[6].loadFromFile("lvl9bgs/ezgif-frame-007.png");
        frames[7].loadFromFile("lvl9bgs/ezgif-frame-008.png");
        frames[8].loadFromFile("lvl9bgs/ezgif-frame-009.png");
        frames[9].loadFromFile("lvl9bgs/ezgif-frame-010.png");
        frames[10].loadFromFile("lvl9bgs/ezgif-frame-011.png");
        frames[11].loadFromFile("lvl9bgs/ezgif-frame-012.png");
        frames[12].loadFromFile("lvl9bgs/ezgif-frame-013.png");
        frames[13].loadFromFile("lvl9bgs/ezgif-frame-014.png");
        frames[14].loadFromFile("lvl9bgs/ezgif-frame-015.png");
        frames[15].loadFromFile("lvl9bgs/ezgif-frame-016.png");
        frames[16].loadFromFile("lvl9bgs/ezgif-frame-017.png");
        frames[17].loadFromFile("lvl9bgs/ezgif-frame-018.png");
        frames[18].loadFromFile("lvl9bgs/ezgif-frame-019.png");
		frames[19].loadFromFile("lvl9bgs/ezgif-frame-020.png");
		frames[20].loadFromFile("lvl9bgs/ezgif-frame-021.png");
        frames[21].loadFromFile("lvl9bgs/ezgif-frame-022.png");
        frames[22].loadFromFile("lvl9bgs/ezgif-frame-023.png");
        frames[23].loadFromFile("lvl9bgs/ezgif-frame-024.png");
        frames[24].loadFromFile("lvl9bgs/ezgif-frame-025.png");
        frames[25].loadFromFile("lvl9bgs/ezgif-frame-026.png");
        frames[26].loadFromFile("lvl9bgs/ezgif-frame-027.png");
        frames[27].loadFromFile("lvl9bgs/ezgif-frame-028.png");
        frames[28].loadFromFile("lvl9bgs/ezgif-frame-029.png");
        frames[29].loadFromFile("lvl9bgs/ezgif-frame-030.png");
        frames[30].loadFromFile("lvl9bgs/ezgif-frame-031.png");
        frames[31].loadFromFile("lvl9bgs/ezgif-frame-032.png");
        frames[32].loadFromFile("lvl9bgs/ezgif-frame-033.png");
        frames[33].loadFromFile("lvl9bgs/ezgif-frame-034.png");
        frames[34].loadFromFile("lvl9bgs/ezgif-frame-035.png");
        frames[35].loadFromFile("lvl9bgs/ezgif-frame-036.png");
        frames[36].loadFromFile("lvl9bgs/ezgif-frame-037.png");
        frames[37].loadFromFile("lvl9bgs/ezgif-frame-038.png");
        frames[38].loadFromFile("lvl9bgs/ezgif-frame-039.png");
        frames[39].loadFromFile("lvl9bgs/ezgif-frame-040.png");
		frames[40].loadFromFile("lvl9bgs/ezgif-frame-041.png");
		frames[41].loadFromFile("lvl9bgs/ezgif-frame-042.png");
    }

    else if (level == 10)
    {
        totalFrames = 4;
		frames[0].loadFromFile("lvl10bgs/ezgif-frame-001.png");
        frames[1].loadFromFile("lvl10bgs/ezgif-frame-002.png");
        frames[2].loadFromFile("lvl10bgs/ezgif-frame-003.png");
        frames[3].loadFromFile("lvl10bgs/ezgif-frame-004.png");
    }

    else if (level == 11)
    {
        totalFrames = 12;
		frames[0].loadFromFile("lvl11bgs/ezgif-frame-001.png");
        frames[1].loadFromFile("lvl11bgs/ezgif-frame-002.png");
        frames[2].loadFromFile("lvl11bgs/ezgif-frame-003.png");
        frames[3].loadFromFile("lvl11bgs/ezgif-frame-004.png");
        frames[4].loadFromFile("lvl11bgs/ezgif-frame-005.png");
        frames[5].loadFromFile("lvl11bgs/ezgif-frame-006.png");
        frames[6].loadFromFile("lvl11bgs/ezgif-frame-007.png");
        frames[7].loadFromFile("lvl11bgs/ezgif-frame-008.png");
        frames[8].loadFromFile("lvl11bgs/ezgif-frame-009.png");
        frames[9].loadFromFile("lvl11bgs/ezgif-frame-010.png");
        frames[10].loadFromFile("lvl11bgs/ezgif-frame-011.png");
        frames[11].loadFromFile("lvl11bgs/ezgif-frame-012.png");
    }

    sprite.setTexture(frames[0]);
    sprite.setScale
    (
        800.f / frames[0].getSize().x,
        600.f / frames[0].getSize().y
    );
}

void Background::update(float deltaTime)
{
    timer += deltaTime;

    if (timer >= frameSpeed)
    {
        timer = 0;
        currentFrame++;
        if (currentFrame >= totalFrames) currentFrame = 0;  // loop back to start

        sprite.setTexture(frames[currentFrame]);
    }
}

void Background::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}