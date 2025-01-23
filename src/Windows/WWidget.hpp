#pragma once

#include "src/ImWindow.hpp"

class WWidget : public ImWindow {

    public:
    
    WWidget();

    void Draw() override;
};