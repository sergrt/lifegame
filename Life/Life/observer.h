#pragma once

class Observer {
public:
    virtual void fieldDimensionsChanged() = 0;
    virtual void fieldChanged() = 0;
};