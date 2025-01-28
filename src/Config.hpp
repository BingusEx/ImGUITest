#pragma once

#include "TOMLUtil.hpp"
#include <string>
#include <mutex>
#include <filesystem>

int TomlTest();


/* 

C++ lacks proper reflection support.
Because of this, doing any form of type introspection (Except RTTI) is an absolute pain in the ass.

Thanks to this little library however we can somewhat achieve this.
https://github.com/qlibs/reflect

TOML11 versions > 4.0.0 provide some examples, using this library to deduce runtime information of user defined structs
which normally gets omitted during compilation thus allowing us to serialize / deserialize them into toml tables.

Since all of this is just one big hack, there are some limitations present namely:
 - C style arrays are unsupported so no "char foo[32]" for example
 - std::array arrays or std::vectors however do work with basic types (aggregate types are untested)
 - Data types like std::tuple or ordered map are unsupported (others are untested)
 - Nested structs are supported as long as these also are put through the TOML_SERIALIZABLE() macro.
 - Structs can only contain a total of 64 unique entries, this is a limitation of the reflect library.
   In order to be able to have > 64 the visit template in the reflect library needs to be expanded.
 - Enums are also unsupported. They can however be saved as either int or string. Its better to save them as a string though
   and use something like magic_enum to do the conversion between string <-> enum.
*/

/* Naming Convention
* f(x) -> float(Ammount of elements if array)
* b(x) -> bool(Ammount of elements if array)
* s(x) -> string(Ammount of elements if array)
* t -> struct
*/

//-------------------------------------------------------------------------------------------------------------------
//  HIDDEN
//-------------------------------------------------------------------------------------------------------------------
//This Struct does not get saved only loaded. Enables the debug category in the ConfWindow.
//If this bool is false the SettingsAdvanced struct does not get saved/loaded from the toml. Its default values are used.
struct SettingsHidden {
    bool IKnowWhatImDoing = false;
};
TOML_SERIALIZABLE(SettingsHidden);

//-------------------------------------------------------------------------------------------------------------------
//  DEBUG
//-------------------------------------------------------------------------------------------------------------------
struct SettingsAdvanced {
    std::string sLogLevel = "error";
    std::string sFlushLevel = "trace";
    bool bProfile = false;
    bool bShowOverlay = false;
    bool bAllActorSizeEffects = false;
};
TOML_SERIALIZABLE(SettingsAdvanced);


//-------------------------------------------------------------------------------------------------------------------
//  AUDIO
//-------------------------------------------------------------------------------------------------------------------
struct SettingsAudio {
    float fMaxVoiceFrequency = 1.0f;
    bool bFootstepSounds = true;
    bool bUseOldSounds = false;
    bool bEnableVoiceOverride = true;
};
TOML_SERIALIZABLE(SettingsAudio);

//-------------------------------------------------------------------------------------------------------------------
//  GAMEPLAY
//-------------------------------------------------------------------------------------------------------------------
struct GameplayActorSettings {
    float fRandomGrowthDelay = 1.0f;
    std::string sGameMode = "None";
    float fGrowthRate = 0.001f;
    float fShrinkRate = 0.001f;
    float fGrowthSizeLimit = 25.0f;
    bool bMultiplyGrowthrate = false;
};
TOML_SERIALIZABLE(GameplayActorSettings);

struct SettingsGameplay {
    // ---------- Other
    bool bEnableMales = false;

    // ---------- Visuals
    bool bLessGore = false;
    bool bUseMetric = true;

    // ---------- Compatibility
    bool bDevourmentCompat = false;
    bool bConversationCamCompat = false;

    // ---------- Protect
    bool bProtectEssentials = true;
    bool bProtectFollowers = true;

    //---------- Gamemode
    GameplayActorSettings tGamemodePlayer = {};
    GameplayActorSettings tGamemodeFollower = {};

    //---------- Size Effects
    bool bAdditionalEffects = true;
    bool bFollowerEffects = true;

    //---------- Cloth Tearing
    bool bClothTearing = true;
    float fClothRipStart = 1.5f;
    float fClothRipThreshold = 2.2f;

    //----------- Size Limits
    float fMaxPlayerSize = 1.0f;
    float fMaxFollowerSize = 1.0f;
    float fMaxOtherSize = 1.0f;

    //----------- Perks
    bool bEnableCrushGrowth = true;
    bool bEnableFOVEdits = false;
    bool bEnableGrowthOnHit = false;
    bool bSlowGrowMoans = true;

    //----------- Other
    bool bDynamicSize = true;
    bool bDynamicAnimspeed = true;
    bool bEnableHighHeels = true;
    bool bHighheelsFurniture = true;
    bool bLaunchObjects = false;
    bool bLaunchAllCells = false;

};
TOML_SERIALIZABLE(SettingsGameplay);

//-------------------------------------------------------------------------------------------------------------------
//  CAMERA
//-------------------------------------------------------------------------------------------------------------------
struct CameraOffsets {
    std::string sCenterOnBone = "None";

    //LeftRight //UpDown //BackForth
    //Normal Cam
    std::array<float, 3> f3Normal = {0.0f, 0.0f, 0.0f};  
    std::array<float, 3> f3Combat = {0.0f, 0.0f, 0.0f};

    //Sneak / Crawl
    std::array<float, 3> f3NormalSneak = {0.0f, 0.0f, 0.0f}; 
    std::array<float, 3> f3CombatSneak = {0.0f, 0.0f, 0.0f};

    //Prone
    std::array<float, 3> f3NormalProne = {0.0f, 0.0f, 0.0f}; 
    std::array<float, 3> f3CombatProne = {0.0f, 0.0f, 0.0f};

};
TOML_SERIALIZABLE(CameraOffsets);

//Camera Category Settings
struct SettingsCamera {
    float fCameraShakePlayer = 1.0f;
    float fCameraShakeOther = 1.0f;
    float fFPCrawlHeightMult = 0.40f;
    float fTPCrawlHeightMult = 0.40f;
    
    CameraOffsets tCONormal = {};
    CameraOffsets tCOAlt = {};
    CameraOffsets tCOFeet = {};

    bool bAutomaticCamera = true;

    float fCameraDistMin = 6.0f;
    float fCameraDistMax = 400.0f;
    float fCameraZoom = 20.0f;
    float fCameraStep = 0.075f;

    bool bCamCollideActor = false;
    bool bCamCollideTree = false;
    bool bCamCollideDebris = true;
    bool bCamCollideTerrain = true;
    bool bCamCollideStatics = true;
    float fModifyCamCollideAt = 3.0f;

};
TOML_SERIALIZABLE(SettingsCamera);

//-------------------------------------------------------------------------------------------------------------------
//  BALANCE
//-------------------------------------------------------------------------------------------------------------------
struct SettingsBalance {

    std::string sSizeFormula = "Normal";
    float fSizeDamageMult = 1.0f;
    float fExpMult = 1.0f;
    float fShrinkOnHitMult = 1.0f;      //Is this a mult?
    float fSizeConvLevelCap = 1.0f;     //Is this a perk?
    float fSpellEfficiency = 0.55f;     
    float fStatBonusDamageMult = 1.0f;  //What does this do?
    bool bPlayerFriendlyImmunity = false;
    bool bOthersFriendlyImmunity = false;
    bool bAllowStagger = true;
    
    //Balance mode vars
    bool bBalanceMode = false;
    float fBMSizeGainPenaltyMult = 1.0f;
    float fBMShrinkRate = 1.0f;
    float fBMShrinkRateCombat = 0.08f;
};
TOML_SERIALIZABLE(SettingsBalance);

//-------------------------------------------------------------------------------------------------------------------
//  ACTIONS
//-------------------------------------------------------------------------------------------------------------------
struct SettingsActions {
    bool bStompAlternative = false;
    bool bStomAlternativeOther = false;

    bool bSneakTransitions = true;
    bool bSneakTransitionsOther = true;

    bool bCrawl = true;
    bool bCrawlOther = true;

    //Todo Experimental Needs to be implemented first. This is a reminder to do it.
    bool bLayeredSneak = false;

    bool bTrackBones = true;

    bool bVoreFreecam = false;
    bool bVoreWeightGain = false;

    bool bAllowSpiders = false;
    bool bAllowUndead = false;

    bool bShowHearts = true;
    bool bShowIcons = true;
    
    //Forward/Back and Up/Down
    std::array<float,2> f2CleavageOffset = {0.0f, 0.0f};
};
TOML_SERIALIZABLE(SettingsActions);


//-------------------------------------------------------------------------------------------------------------------
//  AI
//-------------------------------------------------------------------------------------------------------------------
struct SettingsAI {
    //Action Toggles
    bool bAllowVore = true;
    bool bAllowStomp = true;
    bool bAllowSwipe = true;
    bool bAllowKick = true;
    bool bAllowHugs = true;
    bool bAllowButtCrush = true;
    bool bAllowThighCrush = true;
    bool bAllowThighSandwich = true;

    //Other Values
    bool bPanic = true;
    bool bCombatOnly = true;
    bool bIgnorePlayer = true;
    bool bIgnoreFollowers = true;
};
TOML_SERIALIZABLE(SettingsAI);

//-------------------------------------------------------------------------------------------------------------------
//  UI
//-------------------------------------------------------------------------------------------------------------------
struct WindowConfStatus {
    bool bLock = true;
    std::array<float, 2> f2Offset = {30.0f, 30.0f};
    std::string sAnchor = "kTopRight";
    bool bVisible = false;
    float fAlpha = 0.8f;
};
TOML_SERIALIZABLE(WindowConfStatus);

struct WindowConfSettings {
    bool bLock = true;
    std::array<float, 2> f2Offset = {30.0f, 30.0f};
    float fWindowScale = 75.f;
    std::string sAnchor = "kCenter";
};
TOML_SERIALIZABLE(WindowConfSettings);

struct SettingsUI {
    float fFontScale = 1.0f;
    std::array<float, 3> f3AccentColor = {0.486f, 0.431f, 0.529f};
    WindowConfSettings wSettings {};
    WindowConfStatus wStatus {};
};
TOML_SERIALIZABLE(SettingsUI);

class Config {
    public:
    //Create structs with default values.
    //These act as sane defaults in case new data is loaded or the toml itself is corrupted.
    SettingsActions Actions = {};
    SettingsAdvanced Advanced = {};
    SettingsAI AI = {};
    SettingsAudio Audio = {};
    SettingsBalance Balance = {};
    SettingsCamera Camera = {};
    SettingsGameplay Gameplay {};
    SettingsUI UI = {};
    SettingsHidden Hidden = {}; 

    [[nodiscard]] static inline Config& GetSingleton() {
        static Config instance;
        return instance;
    }

    [[nodiscard]] bool LoadSettings();

    [[nodiscard]] bool SaveSettings();

    void ResetToDefaults();
        
    private:
    
    const std::string _ConfigFile = "Settings.toml";
    //Should be a relative path to the dll. Combined this should be \\Data\\SKSE\\Plugins\\GTSPlugin
    const std::string _Subfolder = "GTSPlugin"; 

    std::mutex _ReadWriteLock;

    template<typename T>
    [[nodiscard]] bool LoadStructFromTOML(const auto& a_toml, T& a_data);

    template<typename T>
    [[nodiscard]] bool UpdateTOMLFromStruct(auto& a_toml, T& a_data);

    [[nodiscard]] bool SaveTOMLToFile(const auto& a_toml, const std::filesystem::path& a_file);

    [[nodiscard]] bool CheckFile(const std::filesystem::path& a_file);

    toml::basic_value<toml::ordered_type_config> TomlData;

    Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
};