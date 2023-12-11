#include"HomeHealth.hpp"


Castle::Castle(int maxHealth) {
    health = new Healthbar(maxHealth);
}

Healthbar* Castle::getHealth() const {
    return health;
}

void Castle::decreaseHealth() {
    health->currHealth -= -1;
// if (health->currHealth <= 0) {
    //     health->currHealth = 0;
    //     gameOver = true;
    // }
}
// bool Castle::isGameOver(){
//     return gameOver;
// }

