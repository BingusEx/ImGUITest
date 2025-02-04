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
* stucts don't get a special notation
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
    kSizeLocked //<-------------- Combines both
};

//-------------------------------------------------------------------------------------------------------------------
//  CHILD STRUCTS 
//  (Not Directly Serialized, but used within other structs)
//-------------------------------------------------------------------------------------------------------------------

//------------------------------------------- Gameplay
struct GameplayActorSettings {
    // Basic settings
    std::string sGameMode = "kNone";
    float fRandomGrowthDelay = 1.0f;

    // Growth/Shrink parameters
    float fGrowthRate = 0.001f;
    float fShrinkRate = 0.001f;
    float fGrowthSizeLimit = 25.0f;

    // Curse-related settings
    float fCurseTargetScale = 1.5f;

    // Update settings
    float fUpdateInterval = 3.0f;
    bool bMultiplyGrowthrate = false;
};
TOML_SERIALIZABLE(GameplayActorSettings);


//------------------------------------------- Camera
struct CameraOffsets {
    // Bone to center on
    std::string sCenterOnBone = "kNone";

    // Stand offsets
    std::array<float, 3> f3NormalStand = {0.0f, 0.0f, 0.0f};  
    std::array<float, 3> f3CombatStand = {0.0f, 0.0f, 0.0f};

    // Sneak/Crawl offsets
    std::array<float, 3> f3NormalSneak = {0.0f, 0.0f, 0.0f}; 
    std::array<float, 3> f3CombatSneak = {0.0f, 0.0f, 0.0f};
};
TOML_SERIALIZABLE(CameraOffsets);


//------------------------------------------- AI

// Stateless actions: simple probability-based triggers.
struct AIStatelessAction {
    bool bEnableAction = true;
    float fProbability = 50.0f;
};
TOML_SERIALIZABLE(AIStatelessAction);

// Statefull actions: have additional probability settings and an interval.
struct AIStatefullAction {
    bool bEnableAction = true;
    float fProbability = 50.0f;
    float fProbabilityLight = 50.0f;
    float fProbabilityHeavy = 50.0f;
    float fInterval = 2.0f;
};
TOML_SERIALIZABLE(AIStatefullAction);

// Complex action: Hug
struct AIHugAction {
    // Basic toggle and overall probability
    bool bEnableAction = true;
    float fProbability = 50.0f;

    // Conditions
    bool bStopAtFullHP = true;
    bool bKillFriendlies = true;
    bool bKillFollowers = false;
    
    // Outcome probabilities
    float fHealProb = 50.0f;
    float fShrinkProb = 50.0f;
    float fKillProb = 50.0f;

    // Timing
    float fInterval = 4.0f;
};
TOML_SERIALIZABLE(AIHugAction);

// Complex action: Butt Crush
struct AIButtAction {
    bool bEnableAction = true;
    float fProbability = 50.0f;

    // Different probabilities for variations of the action
    float fFastProb = 50.0f;
    float fTargetedProb = 50.0f;
    float fGrowProb = 80.0f;

    // Timing and limit
    float fInterval = 2.0f;
    float fGrowUntilScale = 30.0f;
};
TOML_SERIALIZABLE(AIButtAction);

// Complex action: Grab
struct AIGrabAction {
    bool bEnableAction = true;
    float fProbability = 10.0f;

    // Different attack types
    float fThrowProb = 50.0f;
    float fVoreProb = 50.0f;
    float fCrushProb = 50.0f;

    // Cleavage (multiple stages) probabilities
    float fCleavageProb = 50.0f;
    float fCleavageAttackProb = 50.0f;
    float fCleavageAbsorbProb = 50.0f;
    float fCleavageSuffocateProb = 50.0f;

    // Timing
    float fInterval = 2.0f;
};
TOML_SERIALIZABLE(AIGrabAction);


//------------------------------------------- Interface/UI

struct WindowConfStatus {
    // Window lock and visibility
    bool bLock = true;
    bool bVisible = false;

    // Positioning and appearance
    std::array<float, 2> f2Offset = {20.0f, 20.0f};
    std::string sAnchor = "kTopRight";
    float fAlpha = 1.0f;

    // Display control
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
//  PARENT STRUCTS 
//  (Serialized directly, with instances assumed in the config singleton)
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//  HIDDEN
//-------------------------------------------------------------------------------------------------------------------
// This struct is only loaded (not saved) and enables the advanced category in the configuration window.
struct SettingsHidden {
    bool IKnowWhatImDoing = false;
};
TOML_SERIALIZABLE(SettingsHidden);

//-------------------------------------------------------------------------------------------------------------------
//  DEBUG / ADVANCED
//-------------------------------------------------------------------------------------------------------------------
struct SettingsAdvanced {
    // Logging levels
    std::string sLogLevel = "err";
    std::string sFlushLevel = "trace";

    // Toggles for advanced features
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
    // Footstep sounds
    bool bFootstepSounds = true;
    bool bUseOldSounds = false;

    // Voice settings
    bool bSlowGrowMoans = true;
    bool bEnableVoiceOverride = true;
    float fMaxVoiceFrequency = 1.0f;

    // Volume levels
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
    // Visual settings
    bool bLessGore = false;
    bool bShowHearts = true;
    bool bShowIcons = true;

    // Compatibility options
    bool bDevourmentCompat = false;
    bool bConversationCamCompat = false;

    // Protection toggles
    bool bProtectEssentials = true;
    bool bProtectFollowers = true;

    // Gameplay enhancements
    bool bDynamicSize = true;
    bool bDynamicAnimspeed = true;
    bool bEnableHighHeels = true;
    bool bHighheelsFurniture = true;
    bool bEnableMales = false;
    bool bEnableFOVEdits = false;

    // Miscellaneous
    bool bLayeredSneak = false;
    bool bPlayerCrawling = true;
    bool bFollowerCrawling = true;

    // Bone tracking for foot Animations
    bool bTrackBonesDuringAnim = true;
};
TOML_SERIALIZABLE(SettingsGeneral);


//-------------------------------------------------------------------------------------------------------------------
//  GAMEPLAY
//-------------------------------------------------------------------------------------------------------------------
struct SettingsGameplay {
    // Gamemode settings for different actor types
    GameplayActorSettings GamemodePlayer = {};
    GameplayActorSettings GamemodeFollower = {};

    // Size Effects
    bool bPlayerAnimEffects = true;
    bool bNPCAnimEffects = true;
    bool bLaunchObjects = false;
    bool bLaunchAllCells = false;

    // Cloth Tearing parameters
    bool bClothTearing = true;
    float fClothRipStart = 1.5f;
    float fClothRipThreshold = 2.2f;

    // Perk settings
    bool bEnableCrushGrowth = true;
    bool bEnableGrowthOnHit = false;
    float fSizeConvLevelCap = 1.0f;

    // Animation options
    bool bStompAlternative = false;
    bool bStomAlternativeOther = false;
    bool bSneakTransitions = true;
    bool bSneakTransitionsOther = true;

    // Vore-related settings
    float fVoreGainMult = 1.0f;
    bool bVoreFreecam = false;
    bool bVoreWeightGain = false;
    bool bAllowSpiders = false;
    bool bAllowUndead = false;

    // Cleavage offset for forward/back and up/down adjustments
    std::array<float,2> f2CleavageOffset = {0.0f, 0.0f};
};
TOML_SERIALIZABLE(SettingsGameplay);


//-------------------------------------------------------------------------------------------------------------------
//  CAMERA
//-------------------------------------------------------------------------------------------------------------------
struct SettingsCamera {
    // Shake and crawl multipliers
    float fCameraShakePlayer = 1.0f;
    float fCameraShakeOther = 1.0f;
    float fFPCrawlHeightMult = 0.40f;
    float fTPCrawlHeightMult = 0.40f;
    
    // Offset settings (for first-person and third-person)
    CameraOffsets OffsetsNormal = {};
    CameraOffsets OffsetsAlt = {};

    // Foot camera offset
    float fFootCameraFBOffset = 0.0;
    
    // Automatic camera controls
    bool bAutomaticCamera = true;
    std::string sAutoCameraModeFP = "kNormal";
    std::string sAutoCameraModeTP = "kDisabled";

    // Distance and zoom controls
    float fCameraDistMin = 6.0f;
    float fCameraDistMax = 400.0f;
    float fCameraZoom = 20.0f;
    float fCameraStep = 0.075f;

    // Collision settings
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
    // General balance parameters
    std::string sSizeMode = "kNormal";
    float fSpellEfficiency = 0.55f;     
    float fSizeDamageMult = 1.0f;
    float fExpMult = 1.0f;
    float fStatBonusDamageMult = 1.0f;

    // Friendly interaction settings
    bool bPlayerFriendlyImmunity = false;
    bool bFollowerFriendlyImmunity = false;
    bool bAllowFriendlyStagger = true;
    bool bAllowOthersStagger = true;

    // Size limits
    float fMaxPlayerSize = 0.0f;
    float fMaxFollowerSize = 0.0f;
    float fMaxOtherSize = 0.0f;
    
    // Balance mode adjustments
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
    // Global AI settings
    bool bEnableActionAI = true;
    float fMasterTimer = 3.0f;

    // Stateless Actions
    AIStatelessAction Vore = { .bEnableAction = true, .fProbability = 20.0f };
    AIStatelessAction Stomp = { .bEnableAction = true, .fProbability = 20.0f };
    AIStatelessAction KickSwipe = { .bEnableAction = true, .fProbability = 20.0f };

    // Statefull Actions
    AIStatefullAction ThighCrush = { .bEnableAction = true, .fProbability = 20.0f };
    AIStatefullAction ThighSandwich = { .bEnableAction = true, .fProbability = 20.0f };

    // Complex Actions
    AIHugAction Hugs = {};
    AIButtAction ButtCrush = {};
    AIGrabAction Grab = {};

    // Additional AI toggles
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
    // Display settings
    std::string sDisplayUnits = "kMetric";
    float fScale = 1.0f;
    float fItemWidth = 0.55f;
    std::array<float, 3> f3AccentColor = {0.486f, 0.431f, 0.529f};

    // Window configurations
    WindowConfSettings SettingsWindow {};
    WindowConfStatus StatusWindow {};
};
TOML_SERIALIZABLE(SettingsUI);

class Config {
    private:

    template <typename T>
    constexpr std::string_view GetStructName(const T&) {
        return reflect::type_name<T>();
    }

    #define REGISTER_STRUCT_NAME(TYPE, NAME)                        \
    template <>                                                     \
    constexpr std::string_view GetStructName<TYPE>(const TYPE&) {   \
        return NAME;                                                \
    }

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

    //Too much effort to make a parser for it, So Define the names here.
    REGISTER_STRUCT_NAME(SettingsGeneral, "General")
    REGISTER_STRUCT_NAME(SettingsAdvanced, "Advanced")
    REGISTER_STRUCT_NAME(SettingsAI, "AI")
    REGISTER_STRUCT_NAME(SettingsAudio, "Audio")
    REGISTER_STRUCT_NAME(SettingsBalance, "Balance")
    REGISTER_STRUCT_NAME(SettingsCamera, "Camera")
    REGISTER_STRUCT_NAME(SettingsGameplay, "Gameplay")
    REGISTER_STRUCT_NAME(SettingsUI, "UI")
    REGISTER_STRUCT_NAME(SettingsHidden, "Hidden")


    const std::string FileDescription = "";
    const std::string _Subfolder = "GTSPlugin"; 
    const std::string _ConfigFile = "Settings.toml";
    const std::filesystem::path ConfigFile = std::filesystem::current_path() / _Subfolder / _ConfigFile;

    toml::basic_value<toml::ordered_type_config> TomlData;
    std::mutex _ReadWriteLock;

    Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    template<typename T>
    [[nodiscard]] bool LoadStructFromTOML(const auto& a_toml, T& a_data);

    template<typename T>
    [[nodiscard]] bool UpdateTOMLFromStruct(auto& a_toml, T& a_data);

    [[nodiscard]] bool SaveTOMLToFile(const auto& a_toml, const std::filesystem::path& a_file);
    [[nodiscard]] bool CheckFile(const std::filesystem::path& a_file);
    [[nodiscard]] bool DeleteFile(const std::filesystem::path& a_file);
    public: 
    
    //Static Accessors (Helpers)

    [[nodiscard]] static inline SettingsGeneral& GetGeneral(){
        return GetSingleton().General;
    }

    [[nodiscard]] static inline SettingsAdvanced& GetAdvanced(){

        return GetSingleton().Advanced;
    }

    [[nodiscard]] static inline SettingsAI& GetAI(){
        return GetSingleton().AI;
    }

    [[nodiscard]] static inline SettingsAudio& GetAudio(){
        return GetSingleton().Audio;
    }

    [[nodiscard]] static inline SettingsBalance& GetBalance(){
        return GetSingleton().Balance;
    }

    [[nodiscard]] static inline SettingsCamera& GetCamera(){
        return GetSingleton().Camera;
    }

    [[nodiscard]] static inline SettingsGameplay& GetGameplay(){
        return GetSingleton().Gameplay;
    }

    [[nodiscard]] static inline SettingsUI& GetUI(){
        return GetSingleton().UI;
    }

    [[nodiscard]] static inline SettingsHidden& GetHidden(){
        return GetSingleton().Hidden;
    }

    [[nodiscard]] static inline Config& GetSingleton() {
        static Config Instance;

        static std::atomic_bool Initialized;
        static std::latch Latch(1);

        if (!Initialized.exchange(true)) {
            //logger::info("Loading TOML Settings in .ctor...")

            if(!Instance.LoadSettings()){
                MessageBoxA(nullptr,"Settings.toml is either invalid or corrupted. Click OK to clear out the settings file and delete the old settings.","Size Matters - GTSPlugin.dll",MB_OK);
        
                Instance.ResetToDefaults();
                
                //Delete the config file
                if(!Instance.DeleteFile(Instance.ConfigFile)){
                    MessageBoxA(nullptr,"Could not delete Settings.toml\nCheck GTSPlugin.log for more info.\nThe game will now close", "Size Matters - GTSPlugin.dll", MB_OK);
                    TerminateProcess(GetCurrentProcess(), EXIT_FAILURE);
                }
                
                //Recreate the config file and start with a fresh table.
                if(!Instance.CheckFile(Instance.ConfigFile)){
                    MessageBoxA(nullptr,"Could not create a blank Settings.toml file.\nCheck GTSPlugin.log for more info.\nThe game will now close", "Size Matters - GTSPlugin.dll", MB_OK);
                    TerminateProcess(GetCurrentProcess(), EXIT_FAILURE);
                }
            }

            //Incase the File is empty/missing newly added data...
            //Explicitly Ignore the [[Nodiscard]]
            std::ignore = Instance.SaveSettings();

            //logger::info(".ctor Load OK")

            Latch.count_down();
        }
        Latch.wait();

        return Instance;
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
};