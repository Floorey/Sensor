#include <iostream>
#include <random>

class WaterLevelSenor {
public:
    virtual int getCurrentWaterLevel() const = 0;
    virtual void releaseWater(int waterLevel) const = 0;
    virtual  ~WaterLevelSenor() {}
};
class RandomWaterLevelSensor : public WaterLevelSenor {
public:
    int getCurrentWaterLevel() const override {
       std::random_device rd;
       std::mt19937 gen(rd());
       std::uniform_int_distribution<> dis(1, 1000);
        return dis(gen);
    }
    void releaseWater(int waterLevel) const override {
        if (waterLevel > 30) {
            std::cout << "Water released!" << std::endl;
        } else {
            std::cout << "Water level is too low to release water!" << std::endl;
        }
    }
};
class OverflowSensor : public WaterLevelSenor {
private:
    int waterLevel;
public:

    OverflowSensor() : waterLevel(0) {}

    int getCurrentWaterLevel() const override {
        return waterLevel;
    }
    void addWater(int amount) {
        waterLevel += amount;
        checkOverflow();
    }
    void checkOverflow() {
        if (waterLevel > 1000) {
            std::cout << "Overflow detected in the cistern. Signaling to stop water supply!" << std::endl;
            stopWaterSupply();
        }
    }
    void stopWaterSupply() const {
        std::cout << "Stopping water supply from rainwater collector to prevent overflow in the cistern!" << std::endl;
    }
    void releaseWater(int waterLevel) const override {
        if(waterLevel < 30) {
            std::cout << "Cistern water level is too low. Stopping water outlet." <<std::endl;
        } else {
            std::cout << "Cistern water level is sufficient. Proceeding with water outlet." << std::endl;
        }
    }
};
class FountaininBasinSensor : public WaterLevelSenor {
private:
    int waterLevel;


public:
    FountaininBasinSensor() : waterLevel(0) {}

    int getCurrentWaterLevel() const override {
        return waterLevel;
    }
    void addWater(int amount) {
        waterLevel += amount;
        checkAlarm();
    }
    void checkAlarm() const {
        if (waterLevel > 2000) {
            std::cout << "Alarm: Water level in the fountain basin is too high!" << std::endl;
        } else if (waterLevel < 20) {
            std::cout << "Alarm: Water level in the fountain basin is too low! Ussing fountain is not possible!" << std::endl;
        }
    }
    void releaseWater(int ) const override {
        // does not release Water
    }
};

int main() {
    RandomWaterLevelSensor sensor1;
    RandomWaterLevelSensor sensor2;
    OverflowSensor sensor3;
    FountaininBasinSensor sensor4;

    while (true) {
        int waterLevel1 = sensor1.getCurrentWaterLevel();
        int waterLevel2 = sensor2.getCurrentWaterLevel();
        int waterLevel3 = sensor3.getCurrentWaterLevel();
        int waterLevel4 = sensor4.getCurrentWaterLevel();

        std::cout << "Current water level - Sensor 1:" << waterLevel1 << std::endl;
        std::cout << "Current water level - Sensor 2:" << waterLevel2 << std::endl;
        std::cout << "Current water level -. Sensor 3:" << waterLevel3 << std::endl;
        std::cout << "Current water level . Sensor 4:" << waterLevel4 << std::endl;

        std::cout << "Please select an action (1: Add water to cistern, 2: Release water from cistern, 3: Quit): " << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1, 100);
                int waterAmount = dis(gen);
                std::cout << "Random water amount added to cistern: " << waterAmount << std::endl;
                sensor3.addWater(waterAmount);
                sensor4.addWater(waterAmount);
                break;
            }
            case 2: {
                sensor3.releaseWater(sensor3.getCurrentWaterLevel());
                break;
            }
            case 3:
                return 0;
            default:
                std::cout << "Invalid input. Please use 1, 2, or 3 to select an action." << std::endl;
        }
    }

    return 0;
}