#include <gtest/gtest.h>
#include "Ammo.h"

TEST(AmmoTest, InitialBullets) {
    Ammo ammo(1, false, 0, 0);
    EXPECT_EQ(ammo.get_bullets(), 20);
}

TEST(AmmoTest, CollectAmmo) {
    Ammo ammo(1, false, 0, 0);
    ammo.collect();
    EXPECT_EQ(ammo.get_collected_status(), true);
}

TEST(AmmoTest, BulletsAfterCollection) {
    Ammo ammo(1, false, 0, 0);
    ammo.collect();
    EXPECT_EQ(ammo.get_bullets(), 0);
}

TEST(AmmoTest, CollectTwice) {
    Ammo ammo(1, false, 0, 0);
    ammo.collect();
    ammo.collect();
    EXPECT_EQ(ammo.get_bullets(), 0);
}

TEST(AmmoTest, CollectStatusAfterCollection) {
    Ammo ammo(1, false, 0, 0);
    ammo.collect();
    EXPECT_EQ(ammo.get_collected_status(), true);
}

TEST(AmmoTest, CollectStatusWithoutCollection) {
    Ammo ammo(1, false, 0, 0);
    EXPECT_EQ(ammo.get_collected_status(), false);
}

TEST(AmmoTest, BulletsAfterMultipleCollections) {
    Ammo ammo(1, false, 0, 0);
    ammo.collect();
    ammo.collect();
    ammo.collect();
    EXPECT_EQ(ammo.get_bullets(), 0);
}