#include <gtest/gtest.h>
#include "Bullet.h"
#include "tileFeature.h"
#include "Object.h"

TEST(BulletTest, InitialPosition) {
    Bullet bullet(10, 10, 0, 5);
    sf::Vector2f position = bullet.getPosition();
    EXPECT_EQ(position.x, 10);
    EXPECT_EQ(position.y, 10);
}

TEST(BulletTest, BulletDirection) {
    Bullet bullet(10, 10, 0, 5);
    sf::Vector2f direction = bullet.getDirection();
    EXPECT_EQ(direction.x, 2.f);
    EXPECT_EQ(direction.y, 0.f);
}

TEST(BulletTest, BulletMovement) {
    Bullet bullet(10, 10, 0, 5);
    sf::Sprite sprite = bullet.shootBullet();
    sf::Vector2f position = sprite.getPosition();
    EXPECT_EQ(position.x, 12);
    EXPECT_EQ(position.y, 10);
}

TEST(BulletTest, InsideMap) {
    Bullet bullet(10, 10, 0, 5);
    bool insideMap = bullet.isInsideMap(800, 600);
    EXPECT_TRUE(insideMap);
}

TEST(BulletTest, OutsideMap) {
    Bullet bullet(800, 600, 0, 5);
    bool insideMap = bullet.isInsideMap(800, 600);
    EXPECT_FALSE(insideMap);
}

TEST(BulletTest, TileCollision) {
    Bullet bullet(10, 10, 0, 5);
    tileFeature tile(1, 10, 10);
    tileFeature tiles[] = { tile };
    bool collision = bullet.checkCollision(tiles, 1);
    EXPECT_TRUE(collision);
}

TEST(BulletTest, NoTileCollision) {
    Bullet bullet(10, 10, 0, 5);
    tileFeature tile(1, 50, 50);
    tileFeature tiles[] = { tile };
    bool collision = bullet.checkCollision(tiles, 1);
    EXPECT_FALSE(collision);
}

TEST(BulletTest, ObjectCollision) {
    Bullet bullet(10, 10, 0, 5);
    Object obj(2, 10, 10);
    bool collision = bullet.checkCollision(&obj);
    EXPECT_TRUE(collision);
}

TEST(BulletTest, NoObjectCollision) {
    Bullet bullet(10, 10, 0, 5);
    Object obj(2, 50, 50);
    bool collision = bullet.checkCollision(&obj);
    EXPECT_FALSE(collision);
}

TEST(BulletTest, Damage) {
    Bullet bullet(10, 10, 0, 5);
    int damage = bullet.get_damage();
    EXPECT_EQ(damage, 5);
}