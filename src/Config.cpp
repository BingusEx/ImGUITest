#include "TOMLUtil.hpp"
#include "boost/pfr.hpp"
#include "imgui.h"

#include "Config.hpp"

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
        a_data = toml::find_or<T>(a_toml, std::string(reflect::type_name<T&>(a_data)), T{});
        return true;
    }
    catch(toml::exception e){
        //logger::error("Could not parse the toml table into a struct: {}",e.what());
        return false;
    }
}

/// @brief 
/// @tparam T Given a parsed toml file and struct, tries to update the contents of the toml table/value with the data found in the stuct.
/// @param a_toml Parsed TOML File.
/// @param a_data Reference to a data only struct.
/// @return true on success, false on failure.
template<typename T>
bool Config::UpdateTOMLFromStruct(auto& a_toml, T& a_data) {
    static_assert(std::is_class_v<T>, "a_data must be a struct or class type");
    try{
        std::lock_guard<std::mutex> lock(_ReadWriteLock);
        std::string _StructName = std::string(reflect::type_name<T&>(a_data));

        // Convert the struct to a toml::value... which is basically a toml table in this case.
        toml::ordered_value table = a_data;

        // Merge the new data with the existing data
        // If a table with the struct name exists, update the table, otherwise create a new one.
        if (a_toml.contains(_StructName)) {
            auto& existing_table = a_toml.as_table()[_StructName].as_table();
            for (const auto& [key, value] : table.as_table()) {
                existing_table[key] = value;
            }
        } 
        else {
            a_toml.as_table()[_StructName] = table;
            //logger::info("Struct {} does not exist in the toml, created a new table for it",_StructName);
        }
        return true;
    }
    catch(toml::exception e){
        //logger::error("Could not parse the toml table into a struct: {}",e.what());
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
        // Write the updated data to a file
        CheckFile(a_file);

        //Create a output file stream and enable exceptions for it.
        std::ofstream file(a_file);
        file.exceptions(std::ofstream::failbit);

        if (file.is_open()) {
            file << toml::format(a_toml);
            file.close();
            return true;
        }
       
        //logger::error("Could not open configuration file to save it. Settings not saved!");
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
}

bool Config::CheckFile(const std::filesystem::path& a_file) {
    try {
        // Check if the file exists
        if (std::filesystem::exists(a_file)) {
            return true;
        }
        else {
            // Try to create the file
            std::ofstream file(a_file);
            file.exceptions(std::ofstream::failbit);
            if (file) {
                file.close();
                //logger::warn("Configuration file did not exist but was successfully created");
                return true;
            }
        }
        return false;
        
    } catch (const std::filesystem::filesystem_error& e) {
        //logger::error("CheckFile() Filesystem error: {}", e.what());
        return false;
    } 
    catch (const std::exception& e) {
        //logger::error("CheckFile() Exception: {}", e.what());
        return false;
    }
}

/// @brief Reinit all data to defaults.
void Config::ResetToDefaults(){
    Actions = SettingsActions{};
    Advanced = SettingsAdvanced{};
    AI = SettingsAI{};
    Audio = SettingsAudio{};
    Balance = SettingsBalance{};
    Camera = SettingsCamera{};
    Gameplay = SettingsGameplay{};
    UI = SettingsUI{};
}

bool Config::LoadSettings() {
    const std::filesystem::path ConfigFile = std::filesystem::current_path() / _Subfolder / _ConfigFile;

    if (!CheckFile(ConfigFile)) {
        return false;
    }

    try {
        TomlData = toml::parse<toml::ordered_type_config>(ConfigFile.string());
        LoadStructFromTOML(TomlData, Actions);
        LoadStructFromTOML(TomlData, AI);
        LoadStructFromTOML(TomlData, Audio);
        LoadStructFromTOML(TomlData, Balance);
        LoadStructFromTOML(TomlData, Camera);
        LoadStructFromTOML(TomlData, Gameplay);
        LoadStructFromTOML(TomlData, UI);
        LoadStructFromTOML(TomlData, Hidden);

        //If Enabled Allow Loading Advanced Settings from TOML.
        if(Hidden.IKnowWhatImDoing){
            LoadStructFromTOML(TomlData, Advanced);
        }

        return true;
    } 
    catch (const toml::exception& e) {
        // logger::error("Could not parse {}: {}",_ConfigFile, e.what());
        return false;
    }
}

bool Config::SaveSettings() {
    const std::filesystem::path ConfigFile = std::filesystem::current_path() / _Subfolder / _ConfigFile;

    if (!CheckFile(ConfigFile)) {
        return false;
    }
    
    try {
        //UpdateTOMLFromStruct(TomlData, Hidden); <- does not get saved on purpose.
        UpdateTOMLFromStruct(TomlData, Actions);
        UpdateTOMLFromStruct(TomlData, AI);
        UpdateTOMLFromStruct(TomlData, Audio);
        UpdateTOMLFromStruct(TomlData, Balance);
        UpdateTOMLFromStruct(TomlData, Camera);
        UpdateTOMLFromStruct(TomlData, Gameplay);
        UpdateTOMLFromStruct(TomlData, UI);

        //If Enabled Allow Saving Advanced Settings
        if(Hidden.IKnowWhatImDoing){
            UpdateTOMLFromStruct(TomlData, Advanced);
        }
        
        SaveTOMLToFile(TomlData,ConfigFile);

        return true;
    } 
    catch (const toml::exception& e) {
        // logger::error("Could not update one ore more structs: {}",_ConfigFile, e.what());
        return false;
    }
}

int TomlTest(){
    return 0;
}
