#include <gtest/gtest.h>
#include "BotBehaviour.h"
#include "Object.h"

TEST(BotBehaviourTest, InitialColor) {
    BotBehaviour bot(1, 0, 0);
    EXPECT_EQ(bot.get_color(), sf::Color::Blue);
}

TEST(BotBehaviourTest, InitialDirection) {
    BotBehaviour bot(1, 0, 0);
    int dir = bot.get_direction();
    EXPECT_TRUE(dir == movement::up || dir == movement::down || dir == movement::left || dir == movement::right);
}

TEST(BotBehaviourTest, BotBullets) {
    BotBehaviour bot(1, 0, 0);
    bot.attack();
    EXPECT_EQ(bot.get_bullets().size(), 1);
}

TEST(BotBehaviourTest, BotBulletCollisionWithPlayer) {
    BotBehaviour bot(1, 0, 0);
    Player player(2, 10, 10);
    bot.attack();
    bot.bulletCollision(&player);
    EXPECT_EQ(player.get_health(), 90);
}

TEST(BotBehaviourTest, BotBulletCollisionWithObject) {
    BotBehaviour bot(1, 0, 0);
    Object object(3, 5, 5);
    bot.attack();
    bot.bulletCollision(&object);
    EXPECT_EQ(object.is_passthrough(), true);
}