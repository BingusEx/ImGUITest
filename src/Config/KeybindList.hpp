#pragma once
#include <windows.h>

struct InputEvent {
    std::string Event;                      //Event Name
    std::vector<std::string> Keys;          //List Of Dinput key names Minus "DIK_ preffix"
    bool Exclusive = false;                 //Exclusive Flag
    std::string Trigger = "Once";           //Trigger Type
    float Duration = 0.0;                   //Trigger Duration
    std::string BlockInput = "Automatic";   //Block Game Input
    bool Disabled = false;                  //Completely Ignore Event
};
TOML_SERIALIZABLE(InputEvent);

enum class TriggerType {
    Once,
    Continuous,
    Release,
};

enum class BlockInputTypes {
    Automatic,
    Always,
    Never,
};

inline bool CheckDuplicateEvent(const std::vector<InputEvent>& items) {
    // Use a simple O(n^2) check (acceptable if n is small)
    for (std::size_t i = 0; i < items.size(); ++i) {
        for (std::size_t j = i + 1; j < items.size(); ++j) {
            if (items[i].Event == items[j].Event)
                return true;
        }
    }
    return false;
}


namespace Input {
    //----------------------------------------
    // EVENT LIST ----
    //----------------------------------------
    
    //Add New Events Here
    
    //--------------------------------------------------------
    // Pls... No Duplicate events the UI can't handle it. :(
    //--------------------------------------------------------
    inline const std::vector<InputEvent> DefaultEvents = [](){
        const std::vector<InputEvent> DefaultVec = {

            //=======================================================
            //================ UI
            //=======================================================

            {
                .Event = "OpenSettings",
                .Keys = {"LSHIFT", "F1"},
                .Trigger = "Once",
                .BlockInput = "Never"
            },
            {
                .Event = "OpenSettings",
                .Keys = {"LSHIFT", "F1"},
                .Trigger = "Once",
                .BlockInput = "Never"
            },

            //========================================================
            //================ V O R E
            //========================================================

            {
                .Event = "Vore",
                .Keys = {"LSHIFT", "V"},
                .Trigger = "Once"
            },
            {
                .Event = "PlayerVore",
                .Keys = {"LSHIFT", "V"},
                .Trigger = "Continuous",
                .Duration = 1.0,
                .BlockInput = "Never"
            },

            //========================================================
            //================ S T O M P S
            //========================================================

            {
                .Event = "RightStomp",
                .Keys = {"LSHIFT", "E"},
                .Trigger = "Release",
            },
            {
                .Event = "LeftStomp",
                .Keys = {"LSHIFT", "Q"},
                .Trigger = "Release",
            },
            {
                .Event = "RightStomp_Strong",
                .Keys = {"LSHIFT", "E"},
                .Trigger = "Continuous",
                .Duration = 0.44f,
            },
            {
                .Event = "LeftStomp_Strong",
                .Keys = {"LSHIFT", "Q"},
                .Trigger = "Continuous",
                .Duration = 0.44f,
            },
            {
                .Event = "TrampleRight",
                .Keys = {"LSHIFT", "E"},
                .Trigger = "Release",
                .Duration = 0.20f,
            },
            {
                .Event = "TrampleLeft",
                .Keys = {"LSHIFT", "V"},
                .Trigger = "Release",
                .Duration = 0.20f,
            },

            //========================================================
            //================ T H I G H  C R U S H
            //========================================================

            {
                .Event = "ThighCrush",
                .Keys = {"LSHIFT", "W", "C"},
                .Exclusive = true
            },
            {
                .Event = "ThighCrushKill",
                .Keys = {"LMB"},
                .BlockInput = "Never"
            },
            {
                .Event = "ThighCrushSpare",
                .Keys = {"W"},
                .Exclusive = true,
                .BlockInput = "Never"
            },

            //========================================================
            //============ T H I G H  S A N D W I C H
            //========================================================

            {
                .Event = "ThighSandwichEnter",
                .Keys = {"LSHIFT", "C"},
                .Exclusive = true,
            },
            {
                .Event = "PlayerThighSandwichEnter",
                .Keys = {"LSHIFT", "C"},
                .Exclusive = true,
                .Trigger = "Continuous",
                .Duration = 1.0f,
                .BlockInput = "Never"
            },
            {
                .Event = "ThighSandwichAttackHeavy",
                .Keys = {"LMB"},
                .Trigger = "Continuous",
                .Duration = 0.33f,
                .BlockInput = "Never"
            },
            {
                .Event = "ThighSandwichAttack",
                .Keys = {"LMB"},
                .Trigger = "Release",
                .BlockInput = "Never"
            },
            {
                .Event = "ThighSandwichExit",
                .Keys = {"W"},
                .Exclusive = true,
                .BlockInput = "Never"
            },

            //========================================================
            //============ K I C K S
            //========================================================

            {
                .Event = "LightKickRight",
                .Keys = {"LALT", "E"},
                .Trigger = "Release",
            },
            {
                .Event = "LightKickLeft",
                .Keys = {"LALT", "Q"},
                .Trigger = "Release",
            },
            {
                .Event = "HeavyKickRight",
                .Keys = {"LALT", "E"},
                .Trigger = "Continuous",
                .Duration = 0.33f,
            },
            {
                .Event = "HeavyKickLeft",
                .Keys = {"LALT", "Q"},
                .Trigger = "Continuous",
                .Duration = 0.33f,
            },
            {
                .Event = "HeavyKickRight_Low",
                .Keys = {"LALT", "E"},
                .Trigger = "Release",
                .Duration = 0.1f,
            },
            {
                .Event = "HeavyKickLeft_Low",
                .Keys = {"LALT", "Q"},
                .Trigger = "Release",
                .Duration = 0.1f,
            },

            //========================================================
            //============ C R A W L I N G
            //========================================================

            {
                .Event = "LightSwipeRight",
                .Keys = {"LALT", "E"},
                .Trigger = "Release",
            },
            {
                .Event = "LightSwipeLeft",
                .Keys = {"LALT", "Q"},
                .Trigger = "Release",
            },
            {
                .Event = "HeavySwipeRight",
                .Keys = {"LALT", "E"},
                .Trigger = "Continuous",
                .Duration = 0.33f,
            },
            {
                .Event = "HeavySwipeLeft",
                .Keys = {"LALT", "Q"},
                .Trigger = "Continuous",
                .Duration = 0.33f,
            },


            //========================================================
            //============ C L E A V A G E
            //========================================================

            {
                .Event = "CleavageEnter",
                .Keys = {"LSHIFT", "H"},
            },
            {
                .Event = "CleavageExit",
                .Keys = {"RMB"},
                .BlockInput = "Never"
            },
            {
                .Event = "CleavageLightAttack",
                .Keys = {"LMB"},
                .Exclusive = true,
                .Trigger = "Release",
                .BlockInput = "Never"
            },
            {
                .Event = "CleavageHeavyAttack",
                .Keys = {"LMB"},
                .Exclusive = true,
                .Trigger = "Continuous",
                .Duration = 0.33f,
                .BlockInput = "Never"
            },
            {
                .Event = "CleavageSuffocate",
                .Keys = {"W"},
                .BlockInput = "Never"
            },
            {
                .Event = "CleavageAbsorb",
                .Keys = {"S"},
                .BlockInput = "Never"
            },
            {
                .Event = "CleavageVore",
                .Keys = {"V"},
                .BlockInput = "Never"
            },

            //========================================================
            //============ H U G S
            //========================================================

            {
                .Event = "HugAttempt",
                .Keys = {"LSHIFT", "H"},
                .Trigger = "Release",
            },
            {
                .Event = "HugPlayer",
                .Keys = {"LSHIFT", "H"},
                .Trigger = "Continuous",
                .Duration = 1.0f,
                .BlockInput = "Never"
            },
            {
                .Event = "HugShrink",
                .Keys = {"LMB"},
                .Exclusive = true,
                .Trigger = "Release"
            },
            {
                .Event = "HugHeal",
                .Keys = {"LMB"},
                .Exclusive = true,
                .Trigger = "Continuous",
                .Duration = 0.33f,
            },
            {
                .Event = "HugCrush",
                .Keys = {"S"},
            },
            {
                .Event = "HugRelease",
                .Keys = {"RMB"},
                .Exclusive = true,
                .BlockInput = "Never"
            },

            //========================================================
            //============ B U T T / B R E A S T   C R U S H
            //========================================================

            {
                .Event = "QuickButtCrushStart",
                .Keys = {"LSHIFT", "B"},
                .Trigger = "Continuous",
                .Duration = 1.0f,
            },
            {
                .Event = "ButtCrushStart",
                .Keys = {"LSHIFT", "B"},
                .Trigger = "Release",
            },
            {
                .Event = "ButtCrushStart_Player",
                .Keys = {"LSHIFT", "B"},
                .Trigger = "Continuous",
                .Duration = 1.0f,
                .BlockInput = "Never"
            },
            {
                .Event = "ButtCrushGrow",
                .Keys = {"W"},
                .Trigger = "Continuous",
            },
            {
                .Event = "ButtCrushAttack",
                .Keys = {"RMB"},
                .Duration = 0.25f,
            },

            //========================================================
            //======== P R O N E   B E H A V I O R
            //========================================================

            {
                .Event = "SBO_ToggleProne",
                .Keys = {"X"},
                .Trigger = "Continuous",
                .Duration = 0.66f,
                .BlockInput = "Never"
            },
            {
                .Event = "SBO_ToggleDive_Standing",
                .Keys = {"W", "S"},
                .Trigger = "Continuous",
                .Duration = 0.50f,
                .BlockInput = "Never"
            },
            {
                .Event = "SBO_ToggleDive_Sneak",
                .Keys = {"W", "S"},
                .Trigger = "Continuous",
                .Duration = 0.50f,
                .BlockInput = "Never"
            },

            //========================================================
            //========================= G R A B
            //======================================================== 

            {
                .Event = "GrabOther",
                .Keys = {"F"},
                .Duration = 0.25f,
                .BlockInput = "Never"
            },
            {
                .Event = "GrabPlayer",
                .Keys = {"F"},
                .Trigger = "Continuous",
                .Duration = 1.0f,
                .BlockInput = "Never"
            },
            {
                .Event = "GrabAttack",
                .Keys = {"E"},
                .Trigger = "Continuous",
                .Duration = 0.50f,
                .BlockInput = "Never"
            },
            {
                .Event = "GrabVore",
                .Keys = {"V"},
                .Trigger = "Continuous",
                .Duration = 0.50f,
            },
            {
                .Event = "GrabThrow",
                .Keys = {"X"},
                .Trigger = "Continuous",
                .BlockInput = "Never"
            },
            {
                .Event = "GrabRelease",
                .Keys = {"RMB"},
            },
            {
                .Event = "BreastsPut",
                .Keys = {"LSHIFT", "B"},
                .Duration = 0.50f,
            },
            {
                .Event = "BreastsRemove",
                .Keys = {"LSHIFT", "B"},
                .Duration = 0.50f,
            },


            //========================================================
            //========================= C A M E R A
            //========================================================


            {
                .Event = "HorizontalCameraReset",
                .Keys = {"RIGHT", "LEFT"},
                .Trigger = "Continuous",
            },
            {
                .Event = "VerticalCameraReset",
                .Keys = {"UP", "DOWN"},
                .Trigger = "Continuous",
            },
            {
                .Event = "CameraLeft",
                .Keys = {"LALT", "LEFT"},
                .Trigger = "Continuous",
            },
            {
                .Event = "CameraRight",
                .Keys = {"LALT", "RIGHT"},
                .Trigger = "Continuous",
            },
            {
                .Event = "CameraUp",
                .Keys = {"LALT", "UP"},
                .Trigger = "Continuous",
            },
            {
                .Event = "CameraDown",
                .Keys = {"LALT", "DOWN"},
                .Trigger = "Continuous",
            },

            //========================================================
            //========================= A N I M  S P E E D
            //========================================================

            {
                .Event = "AnimSpeedUp",
                .Keys = {"LMB"},
                .Trigger = "Continuous",
            },
            {
                .Event = "AnimSpeedDown",
                .Keys = {"RMB"},
                .Trigger = "Continuous",
            },
            {
                .Event = "AnimMaxSpeed",
                .Keys = {"LMB", "RMB"},
                .Trigger = "Continuous",
            },

            //========================================================
            //========================= P E R K S
            //========================================================

            {
                .Event = "ShrinkOutburst",
                .Keys = {"LSHIFT", "F"},
            },


            {
                .Event = "SizeReserve",
                .Keys = {"E"},
                .Trigger = "Continuous",
                .Duration = 1.33f,
                .BlockInput = "Never"
            },
            {
                .Event = "DisplaySizeReserve",
                .Keys = {"F"},
                .Trigger = "Continuous",
                .Duration = 1.33f,
                .BlockInput = "Never"
            },
            {
                .Event = "RapidGrowth",
                .Keys = {"LSHIFT", "1"},
            },
            {
                .Event = "RapidShrink",
                .Keys = {"LSHIFT", "2"},
            },
            {
                .Event = "TotalControlGrow",
                .Keys = {"UP", "LEFT"},
                .Trigger = "Continuous",
            },
            {
                .Event = "TotalControlShrink",
                .Keys = {"DOWN", "LEFT"},
                .Trigger = "Continuous",
            },
            {
                .Event = "TotalControlGrowOther",
                .Keys = {"LSHIFT", "UP", "LEFT"},
                .Trigger = "Continuous",
            },
            {
                .Event = "TotalControlShrinkOther",
                .Keys = {"LSHIFT", "DOWN", "LEFT"},
                .Trigger = "Continuous",
            },


            //========================================================
            //========================= M I S C
            //========================================================

            {
                .Event = "PartyReport",
                .Keys = {"LCONTROL"},
                .Duration = 1.33f,
                .BlockInput = "Never"
            },
            {
                .Event = "DebugReport",
                .Keys = {"RCONTROL"},
                .Duration = 1.33f,
                .BlockInput = "Never"
            },
            {
                .Event = "ProtectSmallOnes",
                .Keys = {"C"},
                .Duration = 1.0f,
                .BlockInput = "Never"
            }

        };

        if(CheckDuplicateEvent(DefaultVec)){
            MessageBoxA(nullptr,"No duplicate event names in DefaultEvents pls :(\nThe UI can't handle it.","KeybindList.hpp",MB_OK);
            TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS);
        }

        return DefaultVec;
    }();
};