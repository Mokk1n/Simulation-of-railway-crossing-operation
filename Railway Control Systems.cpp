#include <iostream>
#include <string>
#include <cmath>
#include <vector>  //to work with data
#include <chrono>   //to work with time
#include <thread>   //to work with streams
using namespace std;

//class representing a train
class Train {
private:
    string message = "Driver - decided to slow down";//message
public:
    void cross() {
        std::cout << "Train is crossing the railroad crossing\n"; //train crosses the level crossing
    }
    void setMessage(const string& msg) {
        message = msg;//setting the message
        cout << "Send: " << message << endl;//playback messsage
    }
};

//class representing a vehicle
class Vehicle {
public:
    //vehicle crosses the railway crossing
    void cross() {
        std::cout << "Car is crossing the railroad crossing\n";
    }
    //vehicle stops at the barrier
    void stop() {
        std::cout << "Car stops near the barrier\n";
    }
    //vehicle starts moving
    void go() {
        std::cout << "Car goes\n";
    }
};

//class representing the power supply
class PowerSupply {
private:
    bool poweredOn; //indicates whether the power supply is on or off
public:
    PowerSupply() : poweredOn(false) {}
    //on power
    void turnOn() {
        poweredOn = true;
        cout << "Power supply turned on" << endl;
    }
    //off power
    void turnOff() {
        poweredOn = false;
        cout << "Power supply turned off" << endl;
    }
};

//class representing the Internet module
class InternetModule {
private:
    bool connected; //indicates whether the Internet is connected
    string message; //message
public:
    InternetModule() : connected(true) {} // Припускаємо, що під час запуску ми маємо з'єднання
    //disconnect from the Internet
    void disconnect() {
        connected = false;
        cout << "Internet connection disconnected" << endl;
    }
    //connect to the Internet
    void available() {
        connected = true;
        cout << "Internet connection is available" << endl;
    }
    //message make
    void setMessage(const string& msg) {
        message = msg;
        cout << "Send: " << message << endl;//playback messsage
    }
};

//class representing a moving sensor
class MotionSensor {
private:
    double distanceThreshold; //detection threshold
    double trainPosition; //position of the train
    double carPosition; //position of the train
public:
    MotionSensor(double distanceThreshold, double trainPosition) :
        distanceThreshold(distanceThreshold), trainPosition(trainPosition) {}
    void updateTrainPosition(double position) {
        trainPosition = position; //update train position
    }
    void checkTrain() {
        if (isTrainDetected(trainPosition)) {
            //train is detected in the approaching field
            cout << "Train manifestations in the approaching lane!\n";
        }
        else {
            //train not detected in approaching field
            cout << "The train does not appear in the approaching lane.\n";
        }
    }
    void checkCar(double carPosition) {
        if (isCarDetected(carPosition)) {
            //car was detected at a railway crossing
            cout << "Car in the railroad crossing!\n";
        }
        else {
            //car was not detected at the railway crossing
            cout << "Car does not appear in the railroad crossing.\n";
        }
    }
    bool isTrainDetected(double trainPosition) {
        return abs(trainPosition) <= distanceThreshold; //checking the train availability
    }
    bool isCarDetected(double carPosition) {
        return abs(carPosition - trainPosition) <= distanceThreshold; //checking the availability of cars
    }
};

//class representing a traffic light
class TrafficLight {
private:
    bool redLight;
public:
    TrafficLight() : redLight(false) {}
    //turn on the red light
    void turnRed() {
        redLight = true;
        cout << "Red light turned on" << endl;
    }
    void turnOff() {
        redLight = false;
        cout << "Light turned off" << endl; //turn off the light
    }
};

//class representing the barrier
class Barrier {
private:
    bool raised;
public:
    Barrier() : raised(true) {}
    //raising the barrier
    void raise() {
        raised = true;
        cout << "Barrier raised" << endl;
    }
    //lowering the barrier
    void lower() {
        raised = false;
        cout << "Barrier lowered" << endl;
    }
};

//class that represents a sound signal
class SoundSignal {
private:
    string message;
public:
    //setting the message
    SoundSignal() : message("No message") {}
    // message
    void setMessage(const string& msg) {
        message = msg;
        cout << "Playing sound signal: " << message << endl; //playbacl message
    }
};

//class representing the base state
class BaseState {
public:
    virtual void handle(TrafficLight& light, Barrier& barrier, SoundSignal& sound, PowerSupply& power, InternetModule& internet, Train& train, Vehicle& car) = 0;
};

//class representing the disabled state
class OffState : public BaseState {
public:
    void handle(TrafficLight& light, Barrier& barrier, SoundSignal& sound, PowerSupply& power, InternetModule& internet, Train& train, Vehicle& car) override {
        cout << "There are no obstacles!!!" << endl; //No obstacles
        this_thread::sleep_for(chrono::seconds(1)); //delay for 1 second before the next call
        power.turnOff();  //power off
        light.turnOff(); //turning off the traffic light
        barrier.raise(); //raising the barrier
        car.go(); //car starts moving
        car.cross(); //car crosses the railway crossing
        internet.available(); //internet is connected
        internet.setMessage("State off!");
        internet.disconnect(); //disconnect from the Internet

    }
};

//class representing the on state
class OnState : public BaseState {
public:
    void handle(TrafficLight& light, Barrier& barrier, SoundSignal& sound, PowerSupply& power, InternetModule& internet, Train& train, Vehicle& car) override {
        cout << "Approaching train!!!" << endl; //train is coming
        this_thread::sleep_for(chrono::seconds(1)); //delay for 1 second before the next call
        power.turnOn(); //turn on the power supply
        sound.setMessage("Train is approaching. Please be cautious. Stop!");
        light.turnRed();  //turn on the red light
        barrier.lower(); //lowering the barrier
        car.stop(); //stop the car 
        train.cross(); //train crosses
        internet.available(); //internet is connected
        internet.setMessage("State on!");
        internet.disconnect(); //disconnect from the Internet
    }
};

//class representing the emergency state class
class EmergencyState : public BaseState {
public:
    void handle(TrafficLight& light, Barrier& barrier, SoundSignal& sound, PowerSupply& power, InternetModule& internet, Train& train, Vehicle& car) override {
        cout << "threat of collision!!!" << endl; //threat of collision
        this_thread::sleep_for(chrono::seconds(1)); //delay for 1 second before the next call
        power.turnOn(); //turn on the power 
        sound.setMessage("Emergency.");
        light.turnRed(); //turn on the red light
        barrier.lower(); //lowering the barrier
        power.turnOn(); //turn on the power
        car.stop(); //stop the car
        internet.available(); //internet is connected
        internet.setMessage("Emergency!");
        internet.setMessage("Trains heading to the station should slow down; there is an emergency situation at the crossing; the car has stalled");
        internet.setMessage("Train can drive normally, the car has left area");
        internet.disconnect(); //disconnect from the Internet
    }
};

//class that performs the move control
class LevelCrossingControl {
private:
    BaseState* currentState;
public:
    LevelCrossingControl(BaseState* initialState) : currentState(initialState) {}
    //set new state
    void setState(BaseState* newState) {
        currentState = newState;
    }
    void request(TrafficLight& light, Barrier& barrier, SoundSignal& sound, PowerSupply& power, InternetModule& internet, Train& train, Vehicle& car, MotionSensor& sensor, MotionSensor& carSensor, double trainPositions, double carPosition) {
        if (sensor.isTrainDetected(trainPositions) and carSensor.isCarDetected(carPosition)) {
            currentState = new EmergencyState(); //transition to an emergency state if a car and train are detected on the crossing
        }
        else if (carSensor.isCarDetected(carPosition)) {
            currentState = new EmergencyState();//transition to an emergency state if a car is detected on the crossing
        }
        else if (sensor.isTrainDetected(trainPositions)) {
            currentState = new OnState(); //transition to onState if a train is detected
        }
        else
            currentState = new OffState(); //transition to offState if a train and car aren`t detected
        (*currentState).handle(light, barrier, sound, power, internet, train, car); //handle state
        delete currentState;
    }
};

int main() {
    //creat of specific states
    OffState offState;
    OnState onState;
    EmergencyState emergencyState;

    //creat of motion sensors for trains and cars
    MotionSensor train_s(10.0, 0.0);
    MotionSensor car_s(5.0, 0.0);

    //creat of objects 
    TrafficLight trafficLight;
    Barrier barrier;
    SoundSignal soundSignal;
    PowerSupply powerSupply;
    InternetModule internetModule;
    Train train;
    Vehicle car;
    /* create an object to control the transition level with a default state of offState*/
    LevelCrossingControl control(&offState);

    vector<double> trainPositions = { 15.0, 10.0, 15.0 ,1.0, 9.0, 15.0 }; //positions of the train
    vector<double> carPositions = { 6.0, 8.0, 8.0, 4.0, 8.0, 7.0 }; //auto positions
   
    //call the current state
    for (size_t i = 0; i < trainPositions.size(); ++i) {
        control.request(trafficLight, barrier, soundSignal, powerSupply, internetModule, train, car, train_s, car_s, trainPositions[i], carPositions[i]);
        //delay for 2 second before the next call
        this_thread::sleep_for(chrono::seconds(2));
        cout << endl;
    }
    return 0; 
}
