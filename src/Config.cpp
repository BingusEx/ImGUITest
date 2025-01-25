#include <iostream>
#include <fstream>
#include <reflect>
#include "TOMLUtil.hpp"
#include "boost/pfr.hpp"
#include <stdio.h>
#include "imgui.h"
#include <filesystem>
#include "imgui.h"

#include "Config.hpp"

//Due to a lack of propper reflection in c++...
//Serializing Structs to Toml tables and vise-versa has some limitations.
//Only basic data type support. ie Float bool std::string.... etc...
//"Arrays" are supported in the form of vectors of a basic type.
//Nested structs are supported as long as the child struct also has been processed by the reflect macro.
//Nested structs will be serialized as a dot table.
//structs can only contain a maxium of 64 values. This is due to the reflect library only implementing 64 visit macros


/// @brief Given a parsed toml file and struct, tries to update the structs contents from the loaded toml table. If one or more elements can't be loaded. The
/// @tparam T Type of struct
/// @param a_toml Parsed TOML File.
/// @param a_data Reference to a data only struct.
template<typename T>
static void LoadStruct(const auto& a_toml, T& a_data) {
    static_assert(std::is_class_v<T>, "a_data must be a struct or class type");
    a_data = toml::find_or<T>(a_toml, reflect::type_name<T&>(a_data), T{});
}


template<typename T>
void UpdateTOMLFromStruct(auto& a_toml, T& a_data) {
    static_assert(std::is_class_v<T>, "a_data must be a struct or class type");
    auto _StructName = reflect::type_name<T&>(a_data);

    // Convert the struct to a toml::value
    toml::value table = a_data;

    // Merge the new data with the existing data while preserving comments
    if (a_toml.contains(std::string(_StructName))) {
        auto& existing_table = a_toml.as_table()[std::string(_StructName)].as_table();
        for (const auto& [key, value] : table.as_table()) {
            existing_table[key] = value;
        }
    } else {
        a_toml.as_table()[std::string(_StructName)] = table;
    }
}

void TomlSave(auto& a_toml){
    // Write the updated data to a temporary file
    std::string tempFileName = "data.toml";
    std::ofstream outFile(tempFileName);
    if (outFile.is_open()) {
        outFile << toml::format(a_toml);
        outFile.close();
        // // Atomically replace the original file with the temporary file
        // std::filesystem::write(tempFileName, "data.toml");
    } else {
        std::cerr << "Unable to open temporary file for writing" << std::endl;
    }
}

void TomlRead(){

    auto& Config = Config::GetSingleton(); 

    auto x = toml::parse("data.toml");
    
    LoadStruct(x,Config.Actions);
    LoadStruct(x,Config.Advanced);
    LoadStruct(x,Config.AI);
    LoadStruct(x,Config.Audio);
    LoadStruct(x,Config.Balance);
    LoadStruct(x,Config.Camera);
    LoadStruct(x,Config.Gameplay);
    LoadStruct(x,Config.UI);


    UpdateTOMLFromStruct(x,Config.Actions);
    UpdateTOMLFromStruct(x,Config.Advanced);
    UpdateTOMLFromStruct(x,Config.AI);
    UpdateTOMLFromStruct(x,Config.Audio);
    UpdateTOMLFromStruct(x,Config.Balance);
    UpdateTOMLFromStruct(x,Config.Camera);
    UpdateTOMLFromStruct(x,Config.Gameplay);
    UpdateTOMLFromStruct(x,Config.UI);

    TomlSave(x);



    // d.nameofthisvar4 = "d22";
    // a.Aeugh.nameofthisvar1 = "All of this just works.";

    // TomlUpdate(x,a);
    // //TomlUpdate(x,b);
    // TomlUpdate(x,c);
    // TomlUpdate(x,d);

    // TomlSave(x);

}
int TomlTest(){
   

    TomlRead();

    return 0;
}

