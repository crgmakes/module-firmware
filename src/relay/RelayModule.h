/**
 * @brief Class representing a GPIO module
 * @file RelayModule.h
 * @date 26 Jan 2026
 * @author cyberreefguru
 */
#pragma once

#include <Arduino.h>
#include <core/AbstractModule.h>

class Relay
{
public:
    Relay();
    virtual ~Relay(){}

    void initialize(uint8_t pin);
    void set(bool b);
    bool get();

protected:
    uint8_t pin = 0;
};

class RelayModule : public AbstractModule
{
public:
    RelayModule();
    virtual ~RelayModule();
    virtual void initialize() override;

protected:
private:
    Relay relays[MODULE_CHANNELS];

    RelayModule(const RelayModule &) = delete;
    RelayModule &operator=(const RelayModule &) = delete;

    virtual void handleReceiveEvent() override;
    virtual void handleRequestEvent() override;
};