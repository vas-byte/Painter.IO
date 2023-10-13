// BotBehavior.h

#pragma once

class BotBehavior {
public:
    virtual ~BotBehavior() {}
    virtual void attack() = 0;
    virtual void roam() = 0;
    virtual void dodge() = 0;
};
