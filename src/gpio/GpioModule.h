/**
 * @brief Class representing a GPIO module
 * @file GpioModule.h
 * @date 26 Jan 2026
 * @author cyberreefguru
 */
#pragma once

#include <Arduino.h>
#include <core/AbstractModule.h>

class GpioModule : public AbstractModule
{
public:
    GpioModule();
    virtual ~GpioModule();
    virtual void initialize() override;

protected:

private:
    GpioModule(const GpioModule &) = delete;
    GpioModule &operator=(const GpioModule &) = delete;

    virtual void handleReceiveEvent() override;
    virtual void handleRequestEvent() override;

};