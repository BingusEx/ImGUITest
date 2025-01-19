#include "General.hpp"

#include "src/ImCategory.hpp"
#include "src/ImUtil.hpp"
#include "src/ImFont.hpp"
#include "src/ImStyle.hpp"

using namespace GTSUi;

float f = 1.0;

void CategoryGeneral::Draw(){
    ImGui::Text("CategoryGeneral");
    
    auto& StyleMgr = ImStyleManager::GetSingleton();
    ImGui::SliderFloat("Scale",&f, 0.1f, 2.0f);
    
    StyleMgr.SetScale(f);
}

bool CategoryGeneral::Load(){
    return true;
}

bool CategoryGeneral::Save(){
    return true;
}