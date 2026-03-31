/**
 * @brief Class representing a Switch module
 * @file SwitchModule.h
 * @date 26 Jan 2026
 * @author cyberreefguru
 */
#pragma once

#include <Arduino.h>
#include <core/AbstractModule.h>

class Switch
{
public:
    Switch();
    virtual ~Switch(){}

    void initialize(uint8_t pin);
    void set(bool b);
    bool get();

protected:
    uint8_t pin = 0;
};

class SwitchModule : public AbstractModule
{
public:
    SwitchModule();
    virtual ~SwitchModule();
    virtual void initialize() override;

protected:
private:
    Switch switches[MODULE_CHANNELS];

    SwitchModule(const SwitchModule &) = delete;
    SwitchModule &operator=(const SwitchModule &) = delete;

    virtual void handleReceiveEvent() override;
    virtual void handleRequestEvent() override;
};