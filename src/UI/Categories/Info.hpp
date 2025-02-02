
#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"
#include "src/Config.hpp"

namespace UI{

    class CategoryInfo : public ImCategory {
        public:
        CategoryInfo(){
            title = "Info";
        }
        void Draw() override;

        private:
        SettingsHidden& Settings = Config::GetHidden();
    };

}