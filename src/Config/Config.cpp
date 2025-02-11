#include "boost/pfr.hpp"
#include "imgui.h"

#include "Config.hpp"
#include "magic_enum/magic_enum.hpp"

/// @brief Given a parsed toml file and struct, tries to update the structs contents from the loaded toml table. If one or more elements can't be loaded it defaults to the default value found in the struct.
/// @tparam T Type of struct
/// @param a_toml Parsed TOML File.
/// @param a_data Reference to a data only struct.
/// @return true on success, false on failure.
template<typename T>
bool Config::LoadStructFromTOML(const auto& a_toml, T& a_data) {
    static_assert(std::is_class_v<T>, "a_data must be a struct or class type");
    try{
        std::lock_guard<std::mutex> lock(_ReadWriteLock);
        auto _Name = std::string(GetStructName(a_data));
        a_data = toml::find_or<T>(a_toml, _Name, T{});
        //logger::info("Struct: {} Parsed!", _Name);
        return true;
    }
    catch(toml::exception e){
        //logger::error("Could not parse the toml table into a struct: {}",e.what());
        return false;
    }
    catch(...){
        //logger::error("LoadStructFromTOML() -> Something really bad happened with {} and not even TOML11's Handler caught it", reflect::type_name<T&>(a_data) );
        return false;
    }
}

/// @brief 
/// @tparam T Given a parsed toml file and struct, replaces the toml table with the data found in the given stuct.
/// @param a_toml Parsed TOML File.
/// @param a_data Reference to a data only struct.
/// @return true on success, false on failure.
template<typename T>
bool Config::UpdateTOMLFromStruct(auto& a_toml, T& a_data) {
    static_assert(std::is_class_v<T>, "a_data must be a struct or class type");
    try {
        std::lock_guard<std::mutex> lock(_ReadWriteLock);
        std::string _StructName = std::string(GetStructName(a_data));

        // Convert the struct to a toml::value
        toml::ordered_value table = a_data;

        // Replace the entire table to remove unused data
        a_toml.as_table()[_StructName] = table;
        //logger::info("TOML Data for Table {} Has been Replaced",_StructName);
        return true;
    }
    catch(toml::exception e) {
        //logger::error("Could not parse the struct into a TOML table table into a struct: {}",e.what());
        return false;
    }
    catch(...) {
        //logger::error("UpdateTOMLFromStruct() -> Something really bad happened with {} and not even TOML11's Handler caught it", reflect::type_name<T&>(a_data) );
        return false;
    }
}


/// @brief 
/// @param a_toml TOML data.
/// @param a_file path to the file to write to.
/// @return true on success, false on failure.
bool Config::SaveTOMLToFile(const auto& a_toml, const std::filesystem::path& a_file){
    
    try{
        std::lock_guard<std::mutex> lock(_ReadWriteLock);

        //Check if file exists else create it.
        if(!CheckFile(a_file)){
            //logger::error("Settings file was missing and could not be created");
            return false;
        };

        //Create a output file stream and enable exceptions for it.
        std::ofstream file(a_file);
        file.exceptions(std::ofstream::failbit);
        
        //Check if the file is writable...
        if (file.is_open()) {
            file << toml::format(a_toml);
            file.close();
            return true;
        }
       
        //logger::error("Could not open the settings for writing. Settings not saved!");
        return false;
        
    }
    catch(toml::exception e){
        //logger::error("Could not parse the toml table when trying to save: {}",e.what());
        return false;
    }
    catch(const std::ios_base::failure& e){
        //logger::error("Could not parse the toml table when trying to save: {}",e.what());
        return false;
    }
    catch(const std::exception e){
        //logger::error("SaveTOMLToFile() -> Misc Exception: {},e.what());
        return false;
    }
    catch(...){
        //logger::error("SaveTOMLToFile() -> Unknown Exception));
        return false;
    }
}

/// @brief Reinit all data to defaults.
void Config::ResetToDefaults(){
    Advanced = SettingsAdvanced{};
    General = SettingsGeneral{};
    AI = SettingsAI{};
    Audio = SettingsAudio{};
    Balance = SettingsBalance{};
    Camera = SettingsCamera{};
    Gameplay = SettingsGameplay{};
    UI = SettingsUI{};

    TomlData = toml::ordered_table();
}

//TODO Add Ingame Check. If this fails ingame dont immediatly die. if it happens during plugin init die.
bool Config::LoadSettings() {
    
    if (!CheckFile(ConfigFile)) {
        return false;
    }

    try {
        TomlData = toml::parse<toml::ordered_type_config>(ConfigFile.string());
    }
    catch (const toml::exception& e) {
        
        //We shouldn't immediatly panic while ingame like we do in the constructor call. 
        //The only way to even trigger this exception would be to modify the file incorrectly while ingame.
        //You'd never need to mess with the file though in the first place
        //Except to enable the hidden options. But... if someone does decide to be an idiot
        //Atleast I can say I tried to handle said someone being an idiot...

        //Set TomlData to a clean table. So any loaded settings can still be saved propperly if needed.
        TomlData = toml::ordered_table();
        // logger::error("Could not parse {}: {}",_ConfigFile, e.what());
        return false;

    }
    catch(...){
        //logger::error("LoadSettings() -> TOML::Parse Exception Outside of TOML11's Scope);
        return false;
    }

    try{
        bool LoadRes = true;

        LoadRes &= LoadStructFromTOML(TomlData, General);
        LoadRes &= LoadStructFromTOML(TomlData, Gameplay);
        LoadRes &= LoadStructFromTOML(TomlData, Balance);
        LoadRes &= LoadStructFromTOML(TomlData, Audio);
        LoadRes &= LoadStructFromTOML(TomlData, AI);
        LoadRes &= LoadStructFromTOML(TomlData, Camera);
        LoadRes &= LoadStructFromTOML(TomlData, UI);
        LoadRes &= LoadStructFromTOML(TomlData, Hidden);

        //If Enabled Allow Loading Advanced Settings from TOML.
        if(Hidden.IKnowWhatImDoing){
           LoadRes &= LoadStructFromTOML(TomlData, Advanced);
        }

        if(!LoadRes){
            //logger::error("One or more structs could not be deserialized with the fallback init failing too...");
            //This is where we halt and catch fire as this is a litteral imposibility
            //A bad deserialization should ALWAYS result in a clean struct instance. If this fails something really bad happened.
        }
        return LoadRes;
    }
    catch (const toml::exception& e) {
        // logger::error("Could not parse {}: {}",_ConfigFile, e.what());
        return false;
    }
    catch (const std::exception e) {
        // logger::error("Could not parse {}: {}",_ConfigFile, e.what());
        return false;
    }
    catch(...){
        //logger::error("LoadSettings() -> Unknown Exception);
        return false;
    }

}

bool Config::SaveSettings() {

    if (!CheckFile(ConfigFile)) {
        return false;
    }
    
    try {

        bool UpdateRes = true;

        //If Enabled Allow Saving Advanced Settings
        if(Hidden.IKnowWhatImDoing){
          UpdateRes &= UpdateTOMLFromStruct(TomlData, Advanced);
          UpdateRes &= UpdateTOMLFromStruct(TomlData, Hidden);
        }

        UpdateRes &= UpdateTOMLFromStruct(TomlData, General);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, Gameplay);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, Balance);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, Audio);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, AI);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, Camera);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, UI);

        if(!UpdateRes){
            //logger::error("One or more structs could not be serialized to TOML, Skipping Disk Write");
            return false;
        }
        
        const bool SaveRes = SaveTOMLToFile(TomlData,ConfigFile);

        if(!SaveRes){
            //logger::error("Something went wrong when trying to save the TOML to disk... Settings are probably not saved...");
        }

        return SaveRes;
    } 
    catch (const toml::exception& e) {
        // logger::error("TOML Exception: Could not update one or more structs: {}",_ConfigFile, e.what());
        return false;
    }
    catch(...){
        //logger::error("SaveSettings() -> Unknown Exception);
        return false;
    }
}