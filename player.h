#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <algorithm>
#include "entity.h"
#include "bullet.h"

using namespace std;

class player : public entity
{
private:
    nsGraphics::Vec2D limit;
    time_t lastBulletShot = 0;
    int maxBullets = 10;
    vector<bullet> bullets;
public:
    player(nsGraphics::Vec2D coords, nsGraphics::Vec2D limit = nsGraphics::Vec2D(0, 830));
    void setPosition(const nsGraphics::Vec2D& delta);
    bool canShoot() const;
    bool isInvaderHit(const nsGui::Sprite& invaderSprite);
    void shoot();
    void draw(MinGL& window) override;
    void removeOffscreenBullets();
};

#endif // PLAYER_H
