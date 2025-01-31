#include "TOMLUtil.hpp"
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

    // Define the new binds to potentially add
std::vector<InputEvent> Binds = {
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

void Test() {
    toml::ordered_value Root;

    // 1. Load existing TOML data
    try {
        //std::ifstream ifs("binds.toml");
        //if (ifs.good()) {
            Root = toml::parse("binds.toml");
        //}
    } catch (const std::exception& e) {
        std::cerr << "TOML parse error: " << e.what() << "\n";
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
    for (int i = inputEventArray.size() - 1; i >= 0; --i) {
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