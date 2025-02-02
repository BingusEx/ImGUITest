#pragma once

#include "toml.hpp"
#include "TOMLUtil.hpp"
#include "magic_enum/magic_enum.hpp"

void Test();
//TODO Move/Replace this eventually

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
* i(x) -> integer(Ammount of elements if array)
* f(x) -> float(Ammount of elements if array)
* b(x) -> bool(Ammount of elements if array)
* s(x) -> string(Ammount of elements if array)
* t -> struct
*/

struct InputEvent {
    //     InputEvent(const toml::value& v)
    //     :   Event(toml::find<std::string>(v, "Event")),
    //         Keys(toml::find<std::vector<std::string>>(v, "Keys")),
    //         Exclusive(toml::find<bool>(v, "Exclusive")),
    //         Duration(toml::find<float>(v, "Duration")),
    //         Trigger(toml::find<std::string>(v, "Trigger")),
    //         BlockInput(toml::find<bool>(v, "BlockInput"))
    // {}



    std::string Event;
    std::vector<std::string> Keys;
    bool Exclusive = false;
    float Duration = 0.0;
    std::string Trigger = "once";
    bool BlockInput = false;
};
//TOML11_DEFINE_CONVERSION_NON_INTRUSIVE(InputEvent, Event, Keys, Exclusive, Duration, BlockInput)
TOML_SERIALIZABLE(InputEvent);

//-------------------------------------------------------------------------------------------------------------------
//  ENUMS ----- Assumed to be the reference values 
//  magic_enum will use to convert an enum to a string representation for serialization (Saving The TOML)
//-------------------------------------------------------------------------------------------------------------------

//TODO THESE SHOULD NOT BE HERE
enum class CameraTrackingUsr {
    kNone,
    kSpine,
    kClavicle,
    kBreasts_01,
    kBreasts_02,
    kBreasts_03, // 3BBB tip
    kNeck,
    kButt,
};

enum class CameraModeTP {
    kDisabled,
    kNormal,
    kAlternative,
    kFootLeft,
    kFootRight,
    kFeetCenter
};

enum class CameraModeFP {
    kNormal,
    kCombat,
    kLoot
};

enum class DisplayUnit {
    kMetric,
    kImperial,
    kMammoth
};

enum class SizeMode {
    kNormal,
    kMassBased
};

enum class GameMode {
    kNone,
    kGrow,
    kShrink,
    kCombatGrowth,
    kSlowCombatGrowth,          //Curse of growth already exists as random growth, its superfluous
    kCurseOfTheGiantess,        //<------- TODO Implement these... AKA: Just take them from my dll
    kCurseOfDiminishing,
    kCurseOfTheDiminishingGiantess //<-------------- Combines both
};



//-------------------------------------------------------------------------------------------------------------------
//  CHILD STRUCTS ----- Not Directly Serialized, But are part of another struct.
//-------------------------------------------------------------------------------------------------------------------

//------------------------------------------- Gameplay
struct GameplayActorSettings {
    float fRandomGrowthDelay = 1.0f;
    std::string sGameMode = "kNone";
    float fGrowthRate = 0.001f;
    float fShrinkRate = 0.001f;
    float fGrowthSizeLimit = 25.0f;

    //Curses
    float fCurseTargetScale = 1.5f;

    float fUpdateInterval = 3.0f;
    bool bMultiplyGrowthrate = false;
};
TOML_SERIALIZABLE(GameplayActorSettings);


//------------------------------------------- Camera
struct CameraOffsets {
    std::string sCenterOnBone = "kNone";

    //LeftRight //BackForth //UpDown
    //Normal Cam
    std::array<float, 3> f3NormalStand = {0.0f, 0.0f, 0.0f};  
    std::array<float, 3> f3CombatStand = {0.0f, 0.0f, 0.0f};

    //Sneak / Crawl
    std::array<float, 3> f3NormalSneak = {0.0f, 0.0f, 0.0f}; 
    std::array<float, 3> f3CombatSneak = {0.0f, 0.0f, 0.0f};

};
TOML_SERIALIZABLE(CameraOffsets);


//------------------------------------------- AI
struct AIStatelessAction {
    bool bEnableAction = true;
    float fProbability = 50.0f;
};
TOML_SERIALIZABLE(AIStatelessAction);

struct AIStatefullAction {
    bool bEnableAction = true;
    float fProbability = 50.0f;

    float fProbabilityLight = 50.0f;
    float fProbabilityHeavy = 50.0f;

    float fInterval = 2.0f;

};
TOML_SERIALIZABLE(AIStatefullAction);

struct AIHugAction {
    bool bEnableAction = true;
    float fProbability = 50.0f;

    bool bStopAtFullHP = true;
    bool bKillFriendlies = true;
    bool bKillFollowers = false;
    
    float fHealProb = 50.0f;
    float fShrinkProb = 50.0f;
    float fKillProb = 50.0f;
    float fInterval = 4.0f;
};
TOML_SERIALIZABLE(AIHugAction);

struct AIButtAction {
    bool bEnableAction = true;
    float fProbability = 50.0f;

    float fFastProb = 50.0f;
    float fTargetedProb = 50.0f;
    float fGrowProb = 80.0f;
    float fInterval = 2.0f;

    float fGrowUntilScale = 30.0f;
};
TOML_SERIALIZABLE(AIButtAction);

struct AIGrabAction {
    bool bEnableAction = true;
    float fProbability = 10.0f;

    float fThrowProb = 50.0f;
    float fVoreProb = 50.0f;
    float fCrushProb = 50.0f;
    
    float fCleavageProb = 50.0f;
    float fCleavageAttackProb = 50.0f;
    float fCleavageAbsorbProb = 50.0f;
    float fCleavageSuffocateProb = 50.0f;

    float fInterval = 2.0f;

};
TOML_SERIALIZABLE(AIGrabAction);

//------------------------------------------- Interface/UI
struct WindowConfStatus {
    bool bLock = true;
    std::array<float, 2> f2Offset = {20.0f, 20.0f};
    std::string sAnchor = "kTopRight";
    bool bVisible = false;
    float fAlpha = 1.0f;
    uint32_t iDisplayItems = UINT32_MAX;
};
TOML_SERIALIZABLE(WindowConfStatus);

struct WindowConfSettings {
    bool bLock = true;
    std::array<float, 2> f2Offset = {0.0f, 0.0f};
    std::string sAnchor = "kCenter";
    float fWindowSize = 80.f;
};
TOML_SERIALIZABLE(WindowConfSettings);

//-------------------------------------------------------------------------------------------------------------------
//  PARENT STRUCTS ----- Get directly serialized are assumed to have instances in the config singleton.
//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
//  HIDDEN
//-------------------------------------------------------------------------------------------------------------------
//This Struct does not get saved only loaded. Enables the advanced category in the ConfWindow.
//If this bool is false the SettingsAdvanced struct does not get saved/loaded from the toml. Its default values are used.
struct SettingsHidden {
    bool IKnowWhatImDoing = false;
};
TOML_SERIALIZABLE(SettingsHidden);

//-------------------------------------------------------------------------------------------------------------------
//  DEBUG
//-------------------------------------------------------------------------------------------------------------------
struct SettingsAdvanced {
    std::string sLogLevel = "err";
    std::string sFlushLevel = "trace";
    bool bProfile = false;
    bool bShowOverlay = false;
    bool bAllActorSizeEffects = false;
    bool bDamageAV = true;
    bool bCooldowns = true;
    bool bAllocConsole = false;
};
TOML_SERIALIZABLE(SettingsAdvanced);


//-------------------------------------------------------------------------------------------------------------------
//  AUDIO
//-------------------------------------------------------------------------------------------------------------------
struct SettingsAudio {
    // Footstep
    bool bFootstepSounds = true;
    bool bUseOldSounds = false;

    //Voice
    bool bSlowGrowMoans = true;
    bool bEnableVoiceOverride = true;
    float fMaxVoiceFrequency = 1.0f;

    float fVolumeVoice = 1.0f;
    float fVolumeEffects = 1.0f;
    float fVolumeFootstep = 1.0f;
    float fVolumeFootstepEffects = 1.0f;
    float fVolumeImpacts = 1.0f;
};
TOML_SERIALIZABLE(SettingsAudio);

//-------------------------------------------------------------------------------------------------------------------
//  GENERAL
//-------------------------------------------------------------------------------------------------------------------

struct SettingsGeneral {
    // ---------- Visuals
    bool bLessGore = false;
    bool bShowHearts = true;
    bool bShowIcons = true;

    // ---------- Compatibility
    bool bDevourmentCompat = false;
    bool bConversationCamCompat = false;

    // ---------- Protect
    bool bProtectEssentials = true;
    bool bProtectFollowers = true;

    //----------- Other
    bool bDynamicSize = true;
    bool bDynamicAnimspeed = true;
    bool bEnableHighHeels = true;
    bool bHighheelsFurniture = true;
    bool bEnableMales = false;
    bool bEnableFOVEdits = false;

    //----------- Misc
    //Todo Experimental Idea Needs to be implemented first. This is a reminder to do it.
    bool bLayeredSneak = false;
};
TOML_SERIALIZABLE(SettingsGeneral);

//-------------------------------------------------------------------------------------------------------------------
//  GAMEPLAY
//-------------------------------------------------------------------------------------------------------------------

struct SettingsGameplay {
    //---------- Gamemode
    GameplayActorSettings tGamemodePlayer = {};
    GameplayActorSettings tGamemodeFollower = {};

    //---------- Size Effects
    bool bAdditionalEffects = true;
    bool bFollowerEffects = true;
    bool bLaunchObjects = false;
    bool bLaunchAllCells = false;

    //---------- Cloth Tearing
    bool bClothTearing = true;
    float fClothRipStart = 1.5f;
    float fClothRipThreshold = 2.2f;

    //----------- Perks
    bool bEnableCrushGrowth = true;
    bool bEnableGrowthOnHit = false;
    float fSizeConvLevelCap = 1.0f;

    //----------- Animations
    bool bStompAlternative = false;
    bool bStomAlternativeOther = false;
    bool bSneakTransitions = true;
    bool bSneakTransitionsOther = true;

    //These Two Should Be Saved In persistent, Actually Not Needed at all graph vars are saved in the save
    // bool bCrawl = true; <---------------------- TODO Move To Info Page and place checkbox at Each Active Actor
    // bool bCrawlOther = true; --- Same here

    bool bTrackBones = true;

    //----------- Vore
    float fVoreGainMult = 1.0f;
    bool bVoreFreecam = false;
    bool bVoreWeightGain = false;
    bool bAllowSpiders = false;
    bool bAllowUndead = false;

    //------------ Forward/Back and Up/Down
    std::array<float,2> f2CleavageOffset = {0.0f, 0.0f};

};
TOML_SERIALIZABLE(SettingsGameplay);

//-------------------------------------------------------------------------------------------------------------------
//  CAMERA
//-------------------------------------------------------------------------------------------------------------------

struct SettingsCamera {
    float fCameraShakePlayer = 1.0f;
    float fCameraShakeOther = 1.0f;
    float fFPCrawlHeightMult = 0.40f;
    float fTPCrawlHeightMult = 0.40f;
    
    CameraOffsets tCONormal = {};
    CameraOffsets tCOAlt = {};

    float fFootCameraFBOffset = 0.0;

    bool bAutomaticCamera = true;
    std::string sAutoCameraModeFP = "kNormal";
    std::string sAutoCameraModeTP = "kDisabled";

    //TODO These Should be Hooks Not Ini Settings
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

    std::string sSizeMode = "kNormal";
    float fSpellEfficiency = 0.55f;     

    float fSizeDamageMult = 1.0f;
    float fExpMult = 1.0f;

    //Attack Damage mult
    float fStatBonusDamageMult = 1.0f;

    bool bPlayerFriendlyImmunity = false;
    bool bFollowerFriendlyImmunity = false;
    bool bAllowFriendlyStagger = true;
    bool bAllowOthersStagger = true;

    //----------- Size Limits
    float fMaxPlayerSize = 1.0f;
    float fMaxFollowerSize = 1.0f;
    float fMaxOtherSize = 1.0f;
    
    //----------- Balance mode vars
    bool bBalanceMode = false;
    float fBMSizeGainPenaltyMult = 1.0f;
    float fBMShrinkRate = 1.0f;
    float fBMShrinkRateCombat = 0.08f;
    float fBMShrinkOnHitMult = 1.0f;
};
TOML_SERIALIZABLE(SettingsBalance);

//-------------------------------------------------------------------------------------------------------------------
//  AI
//-------------------------------------------------------------------------------------------------------------------

struct SettingsAI {
    //Action Toggles

    bool bEnableActionAI = true;
    //Main Time Interval for Selecting an Action.
    float fMasterTimer = 3.0f;

    //Stateless Actions
    AIStatelessAction tVore = {
        .bEnableAction = true,
        .fProbability = 20.0f,
    };

    AIStatelessAction tStomp = {
        .bEnableAction = true,
        .fProbability = 20.0f,
    };

    AIStatelessAction tKickSwipe = {
        .bEnableAction = true,
        .fProbability = 20.0f,
    };

    //Statefull Actions
    AIStatefullAction tThighCrush = {
        .bEnableAction = true,
        .fProbability = 20.0f,
    };

    AIStatefullAction tThighSandwich = {
        .bEnableAction = true,
        .fProbability = 20.0f,
    };

    //Complex Actions
    AIHugAction tHugs = {};
    AIButtAction tButtCrush = {};
    AIGrabAction tGrab = {};

    //Other Values
    bool bPanic = true;
    bool bCombatOnly = true;
    bool bAllowPlayer = true;
    bool bAllowFollowers = true;
    bool bDisableAttacks = true;
};
TOML_SERIALIZABLE(SettingsAI);

//-------------------------------------------------------------------------------------------------------------------
//  UI
//-------------------------------------------------------------------------------------------------------------------

struct SettingsUI {
    std::string sDisplayUnits = "kMetric";
    float fScale = 1.0f;
    float fItemWidth = 0.55f;
    std::array<float, 3> f3AccentColor = {0.486f, 0.431f, 0.529f};
    WindowConfSettings wSettings {};
    WindowConfStatus wStatus {};
};
TOML_SERIALIZABLE(SettingsUI);

class Config {
    public:
    //Create structs with default values.
    //These act as sane defaults in case new data is loaded or the toml itself is corrupted.
    SettingsGeneral General = {};
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

    template<typename Enum>
    static Enum StringToEnum(const std::string& name) {
        auto value = magic_enum::enum_cast<Enum>(name);
        if (value.has_value()) {
            return *value;
        } else {
            throw std::invalid_argument("Invalid enum name: " + name);
        }
    }
            
    private:
    

    const std::string FileDescription = "";


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