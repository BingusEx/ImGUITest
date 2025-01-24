#include <iostream>
#include <fstream>
#include <reflect>
#include "Config.hpp"
#include "boost/pfr.hpp"
#include <stdio.h>
#include "imgui.h"

#include "imgui.h"

//Due to a lack of propper reflection in c++...
//Serializing Structs to Toml tables and vise-versa has some limitations.
//Only basic data type support. ie Float bool std::string.... etc...
//"Arrays" are supported in the form of vectors of a basic type.
//Nested structs are supported as long as the child struct also has been processed by the reflect macro.
//Nested structs will be serialized as a dot table.
//structs can only contain a maxium of 64 values. This is due to the reflect library only implementing 64 visit macros

struct TestStruct2 {
    std::string nameofthisvar1 = "TestStruct2dddwad";
    int interger1 = 222;
    int interger12 = 111;
    int interger13 = 222222;
    int interger14 = 333;
    int interger15 = 444;
    std::vector<int> dddd = {1,2,3,4,5,6};
};
TOML11_REFLECT(TestStruct2)

struct TestStruct {
    std::string nameofthisvar3 = "DefaultDataOfTestStruct";
    int interger1 = 222;
    float float1 = 111.0;
    float float2;
    double aaath;
    uint8_t smol;
    uint64_t beeg;
    TestStruct2 Aeugh;
};
TOML11_REFLECT(TestStruct)



struct TestStruct3 {
    std::string nameofthisvar2 = "TestStruct3";
    int interger1 = 222;
    float float1 = 111.0;
    float float2 = 1.0;
};
TOML11_REFLECT(TestStruct3)

struct TestStruct4 {
    std::string nameofthisvar4 = "ddwwa";
    int interger1 = 222;
    float float1 = 111.0;
    float float2 = 1.0;
};
TOML11_REFLECT(TestStruct4)


template<typename T>
void TomlReadStruct(const auto& a_toml, T& a_data) {
    static_assert(std::is_class_v<T>, "a_data must be a struct or class type");

    // Reflect: name of struct
    auto x = reflect::type_name<T&>(a_data);

    // // Check if the table with the struct name exists in the toml
    // if (!a_toml.contains(std::string(x))) {
    //     std::cerr << "Table with name " << x << " does not exist in the toml file." << std::endl;
    //     return a_data;
    // }

    // // Ensure the data type is actually a table
    // const auto& table = a_toml.at(std::string(x));
    // if (!table.is_table()) {
    //     std::cerr << "The entry with name " << x << " is not a table in the toml file." << std::endl;
    //     return a_data;
    // }

    // //Return a struct of type t, if every struct field is found within the table return the filled struct.
    // //else return a new struct.
    // //Note the order of the contents does not matter. Only that they're all present.

    a_data = toml::find_or<T>(a_toml, x, T{});

    // reflect::for_each([a_data](auto I) {

        
    //return st;
    // });

}
#include <filesystem>

template<typename T>
void TomlUpdate(auto& a_toml, T& a_data) {
    static_assert(std::is_class_v<T>, "a_data must be a struct or class type");
    auto x = reflect::type_name<T&>(a_data);

    // Convert the struct to a toml::value
    toml::value table = a_data;

    // Merge the new data with the existing data while preserving comments
    if (a_toml.contains(std::string(x))) {
        auto& existing_table = a_toml.as_table()[std::string(x)].as_table();
        for (const auto& [key, value] : table.as_table()) {
            existing_table[key] = value;
        }
    } else {
        a_toml.as_table()[std::string(x)] = table;
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

    
    auto x = toml::parse("data.toml");
    


    TestStruct a = {};
    //TestStruct2 b = {};
    TestStruct3 c = {};
    TestStruct4 d = {};

    TomlReadStruct(x,a);
    //TomlReadStruct(x,b);
    TomlReadStruct(x,c);
    TomlReadStruct(x,d);

    d.nameofthisvar4 = "d22";
    a.Aeugh.nameofthisvar1 = "All of this just works.";

    TomlUpdate(x,a);
    //TomlUpdate(x,b);
    TomlUpdate(x,c);
    TomlUpdate(x,d);

    TomlSave(x);

}
int dawd()
{
   

    TomlRead();

    return 0;
}

