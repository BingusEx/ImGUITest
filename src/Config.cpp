#include "TOMLUtil.hpp"
#include "boost/pfr.hpp"
#include "imgui.h"

#include "Config.hpp"
#include "magic_enum/magic_enum.hpp"

#pragma warning( push )
#pragma warning( disable : 4101) //Yes, Yes MSVC. Thank you for telling me something i already know ffs.

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
/// @tparam T Given a parsed toml file and struct, tries to update the contents of the toml table/value with the data found in the stuct.
/// @param a_toml Parsed TOML File.
/// @param a_data Reference to a data only struct.
/// @return true on success, false on failure.
template<typename T>
bool Config::UpdateTOMLFromStruct(auto& a_toml, T& a_data) {
    static_assert(std::is_class_v<T>, "a_data must be a struct or class type");
    try{
        std::lock_guard<std::mutex> lock(_ReadWriteLock);
        std::string _StructName = std::string(GetStructName(a_data));

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
    catch(...){
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
    } 
    catch (const std::filesystem::filesystem_error& e) {
        //logger::error("CheckFile() Filesystem error: {}", e.what());
        return false;
    } 
    catch (const std::exception& e) {
        //logger::error("CheckFile() -> Exception: {}", e.what());
        return false;
    }
    catch(...){
        //logger::error("CheckFile() -> Unknown Exception));
        return false;
    }
}

bool Config::DeleteFile(const std::filesystem::path& a_file) {
    try {
        // Check if the file exists
        if (std::filesystem::exists(a_file)) {
            std::filesystem::remove(a_file);
            //logger::info("Configuration file was successfully deleted");
            return true;
        }
        return false;
        
    } 
    catch (const std::filesystem::filesystem_error& e) {
        //logger::error("DeleteFile() Filesystem error: {}", e.what());
        return false;
    } 
    catch (const std::exception& e) {
        //logger::error("DeleteFile() -> Exception: {}", e.what());
        return false;
    }
    catch(...){
        //logger::error("DeleteFile() -> Unknown Exception));
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
        //The way to even trigger this exception would be to modify the file incorrectly while ingame.
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

        LoadRes &= LoadStructFromTOML(TomlData, AI);
        LoadRes &= LoadStructFromTOML(TomlData, Audio);
        LoadRes &= LoadStructFromTOML(TomlData, Balance);
        LoadRes &= LoadStructFromTOML(TomlData, Camera);
        LoadRes &= LoadStructFromTOML(TomlData, Gameplay);
        LoadRes &= LoadStructFromTOML(TomlData, General);
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
        }

        UpdateRes &= UpdateTOMLFromStruct(TomlData, AI);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, Audio);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, Balance);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, Camera);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, General);
        UpdateRes &= UpdateTOMLFromStruct(TomlData, Gameplay);
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

void Test() {
    toml::ordered_value Root;

    // 1. Load existing TOML data
    try {
        Root = toml::parse("binds.toml");
    } 
    catch (const std::exception& e) {
        Root = toml::ordered_table();
    }

    // 2. Ensure root is a table
    if (!Root.is_table()) {
        Root = toml::ordered_table();
    }
    auto& rootTable = Root.as_table();

    // 3. Get or create InputEvent array
    toml::ordered_array& inputEventArray = [&]() -> auto& {
        if (rootTable.count("InputEvent") && rootTable["InputEvent"].is_array()) {
            return rootTable["InputEvent"].as_array();
        }
        rootTable["InputEvent"] = toml::ordered_array();
        return rootTable["InputEvent"].as_array();
    }();

    // 4. Define reference binds
    const std::vector<InputEvent> Binds = {
        {
            .Event = "Test",
            .Keys = {"A", "B", "C"},
            .Exclusive = true,
            .Duration = 0.0,
            .BlockInput = false,
        },
        {
            .Event = "Test2",
            .Keys = {"E", "F", "G"},
            .Exclusive = false,
            .Duration = 1.0,
            .BlockInput = true
        }
    };

    // 5. Create set of valid events for quick lookup
    std::unordered_set<std::string> validEvents;
    for (const auto& bind : Binds) {
        validEvents.insert(bind.Event);
    }

    // 6. Remove entries not in Binds (reverse iteration)
    for (std::size_t i = inputEventArray.size(); i-- > 0;) {
        const auto& entry = inputEventArray[i];
        if (!entry.is_table()) {
            inputEventArray.erase(inputEventArray.begin() + i);
            continue;
        }

        const auto& table = entry.as_table();
        const auto it = table.find("Event");
        if (it == table.end() || !it->second.is_string()) {
            inputEventArray.erase(inputEventArray.begin() + i);
            continue;
        }

        const std::string& event = it->second.as_string();
        if (!validEvents.count(event)) {
            inputEventArray.erase(inputEventArray.begin() + i);
        }
    }

    // 7. Add missing binds and update existing ones
    for (const auto& bind : Binds) {
        bool exists = false;
        
        // Check for existing entry
        for (auto& entry : inputEventArray) {
            if (!entry.is_table()) continue;
            
            auto& table = entry.as_table();
            const auto it = table.find("Event");
            
            if (it != table.end() && 
                it->second.is_string() && 
                it->second.as_string() == bind.Event) {
                exists = true;

                //TODO Check if keys are valid

                //TODO Create new binds use default as base then overlay loaded data into binds vector
                
            
                // Update existing entry with current bind data
                break;
            }
        }

        // Add new entry if missing
        if (!exists) {
            toml::ordered_table newEntry;
            newEntry["Event"] = bind.Event;
            newEntry["Keys"] = bind.Keys;
            newEntry["Exclusive"] = bind.Exclusive;
            newEntry["Duration"] = bind.Duration;
            newEntry["Trigger"] = bind.Trigger;;
            newEntry["BlockInput"] = bind.BlockInput;
            
            inputEventArray.push_back(newEntry);
        }
    }

    // 8. Write updated TOML
    std::ofstream ofs("binds.toml");
    if (ofs) {
        ofs << toml::format(Root);
    }
}

#pragma warning( pop ) 