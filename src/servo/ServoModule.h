/**
 * @brief Class representing a servo module
 * @file ServoModule.h
 * @date 4 Jan 2026
 * @author cyberreefguru
 */
#pragma once

#include <Arduino.h>
#include <core/AbstractModule.h>
#include <Servo_megaTinyCore.h>

class ServoModule : public AbstractModule
{
public:
    ServoModule();
    virtual ~ServoModule();
    virtual void initialize() override;

protected:

private:
    ServoModule(const ServoModule &) = delete;
    ServoModule &operator=(const ServoModule &) = delete;

    Servo servos[MODULE_CHANNELS];
    uint8_t value[MODULE_CHANNELS];

    // Servo servo1;
    // Servo servo2;
    // Servo servo3;

    virtual void handleReceiveEvent() override;
    virtual void handleRequestEvent() override;

    void handleServoReceive();
    void handleServoRequest();

};