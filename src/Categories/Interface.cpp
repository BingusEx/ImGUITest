#include "Interface.hpp"
#include "src/ImCategory.hpp"
#include "src/ImUtil.hpp"
#include "src/ImFont.hpp"
#include "src/ImStyle.hpp"
#include "src/ImWindow.hpp"

using namespace GTSUi;



void CategoryInterface::Draw(){

    ImWindowManager& WinMgr = ImWindowManager::GetSingleton();

    if(auto configwindow = WinMgr.GetWindowByName("ConfigWindow")){

        ImGui::Checkbox("Allow Resize", &configwindow->AllowResize);
        ImGui::Checkbox("Allow Move", &configwindow->AllowMove);

        
        // ImGui::SliderFloat("Padding", &configwindow->CornerPadding, 0.05f, 0.2f);
        // ImGui::SliderInt("Anchor", &pos, 0, AnchorPos::kTotal - 1);



    }
    else{
        ImGui::TextColored(ImUtil::ColorError,"Can't find the reference to the config window!");
    }
}


bool CategoryInterface::Load(){
    return true;
}

bool CategoryInterface::Save(){
    return true;
}