// #include "qtexample.h"
// #include <QApplication>
#include "Config.h"
#include <iostream>
#include "Process.hpp"
#include "PlayerData.hpp"

std::string ProjectName()
{
    std::string Res = PROJECT_NAME;
    Res += " (";
    Res += std::to_string(PROJECT_VERSION_MAJOR);
    Res += ".";
    Res += std::to_string(PROJECT_VERSION_MINOR);
    Res += ".";
    Res += std::to_string(PROJECT_VERSION_PATCH);
    Res += ")";
    return Res;
}


int main(int argc, char *argv[])
{
    // QApplication app(argc, argv);
    // MHWMkArmor w;
    // w.show();

    // return app.exec();

    std::cout << ProjectName() << std::endl;

    Process MHW("MonsterHunterWorld.exe");

    if (!MHW.isOpen())
    {
        std::cout << "Process Not Found" << std::endl;
        return -1;
    }

    std::cout << "MonsterHunterWorld Process Found!!" << std::endl;

    int steamID;

    for (auto Mod : MHW.getModuleList())
        if (Mod.getName() ==  "steam_api64.dll")
        {
            steamID = MHW.ReadMemoryInt(Mod.getBaseAddress() + 237592);
            if (!steamID)
                std::cout<< "Failed to retrieve steam data."<<std::endl;
            else
                std::cout << "Steam UserData ID: " << steamID <<std::endl;
        }
    std::cout<< "Please wait while we retrieve your data..."<<std::endl;
    DWORD ptr = FindDataAddress(MHW);
    if (ptr == 0)
    {
        std::cout << "Failed to Find Data Adress" << std::endl;
        return -1;
    }
    std::cout << "Data Adress Found Sucessful!!" << std::endl;
    ptr -= 29;

    auto Data = GetCharData(MHW,ptr,1);

    if (Data.isEmpty())
    {
        std::cout << "Error Opening Game Data" << std::endl;
        return -1;
    }

    std::cout << Data.getBody() << std::endl;

    return 0;
}