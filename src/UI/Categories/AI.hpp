#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"

#include "src/Config.hpp"

namespace UI{

    class CategoryAI: public ImCategorySplit {
        public:
        CategoryAI(){
            title = "AI";
            description = "Configure the behavior of NPCs/Followers";
        }

        void DrawLeft() override;
        void DrawRight() override;

        private:
        Config& Settings = Config::GetSingleton();
    };

}