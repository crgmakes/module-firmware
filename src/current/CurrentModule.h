/**
 * @brief Class representing a Current Module
 * @file CurrentModule.h
 * @date Sep 3, 2026
 * @author cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <core/AbstractModule.h>

class CurrentModule : public AbstractModule
{
public:
    CurrentModule();
    virtual ~CurrentModule();
    virtual void initialize() override;
 

protected:

private:
    CurrentModule(const CurrentModule &) = delete;
    CurrentModule &operator=(const CurrentModule &) = delete;

    volatile uint32_t values[MODULE_CHANNELS];

    virtual void handleReceiveEvent() override;
    virtual void handleRequestEvent() override;

};