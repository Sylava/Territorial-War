#pragma once
#include <vector>

#include "NPC.h"

class WaveInfini {
public:
    WaveInfini();

    void update(float dt);


private:
    void spawnWave();

    std::vector<std::unique_ptr<Npc>> enemies;

    int currentWave;
    float timeSinceLastWave;
    float waveInterval;
};
