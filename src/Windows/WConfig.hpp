#pragma once

#include "src/ImWindow.hpp"

class WConfig : public ImWindow {

    public:
    
    WConfig();

    void Draw() override;

    void LoadAll();

    void SaveAll();

    
};