//#include "WaveInfini.h"
//#include "Map.h"
//#include "Warrior.h"
//
//
//
//
//WaveInfini::WaveInfini()
//    : currentWave(0), timeSinceLastWave(0.f), waveInterval(5.f) {
//}
//
//void WaveInfini::update(float dt) {
//    timeSinceLastWave += dt;
//
//    if (timeSinceLastWave >= waveInterval) {
//        spawnWave();
//        timeSinceLastWave = 0.f;
//    }
//
//    for (auto& e : npcs)
//        e->update(dt);
//}
//
//
//void WaveInfini::spawnWave() {
//    currentWave++;
//
//    int enemyCount = 4 + currentWave * 2;
//
//    for (int i = 0; i < enemyCount; i++) {
//        float x = 50.f + (i * 60.f);
//        
//        int type = rand() % 2; 
//
//        if (type == 0)
//            npcs.push_back(std::make_unique<Warrior>(sf::Vector2f(window, map)));
//        /*else
//            npcs.push_back(std::make_unique<EnemyTypeB>(sf::Vector2f(x, -50.f)));*/
//    }
//
//    std::cout << "Vague " << currentWave << " ("
//        << enemyCount << " ennemis, types mélangés)\n";
//}
