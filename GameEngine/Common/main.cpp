#include "../../Common/Engine.h"
#include "../../Common/Testing/MemoryTest.h"

using namespace Engine;
using namespace Engine::Memory;


int main()
{
    std::vector<string> words;
    GetWords("It's Chelseas Birthday Woo I Love Her!!!!", words);


    words.clear();

	Reflection::Runtime::Initialize();
	Reflection::Runtime::Compile(nullptr);


	//ExecuteStabilityTest();
	//ExecuteMemoryLeakTest();
	//ExecuteInvalidOperationTest();
	//ExecutePerformanceTest();

	bool screenSpaceAmbientOcclusion = true;
	bool depthOfField = true;
	bool shadowsOn = true;
	int shadowQuality = 3;
	int maxPlayers = 20;
	string defaultPlayerName = "Chelsea";
	float startingTime = 30.056f;
	float damageAmount = 2.0f;

	IniFileStream iniFile;

	iniFile.SetPath("TestFile.ini");
	//iniFile.AddSection("Graphics");
	//iniFile.BindSection("Graphics");
	//iniFile.AddBool("screenSpaceAmbientOcclusion", screenSpaceAmbientOcclusion);
	//iniFile.AddBool("depthOfField", depthOfField);
	//iniFile.AddBool("shadowsOn", shadowsOn);
	//iniFile.AddInt("shadowQuality", shadowQuality);
    //
	//iniFile.AddSection("Gameplay");
	//iniFile.BindSection("Gameplay");
	//iniFile.AddInt("maxPlayers", maxPlayers);
	//iniFile.AddString("defaultPlayerName", defaultPlayerName);
	//iniFile.AddFloat("startingTime", startingTime);
	//iniFile.AddFloat("damageAmount", damageAmount);
    //
	//iniFile.Save();

    iniFile.Read();
    iniFile.LogConsole();

    if (!iniFile.BindSection("Graphics"))
    {
        DEBUG_LOG("Missing Graphics section");
    }
    else
    {
        screenSpaceAmbientOcclusion = iniFile.GetBool("screenSpaceAmbientOcclusion").GetValue();
        depthOfField = iniFile.GetBool("depthOfField").GetValue();
        shadowsOn = iniFile.GetBool("shadowsOn").GetValue();
        shadowQuality = iniFile.GetInt("shadowQuality").GetValue();
    }

    if (!iniFile.BindSection("Gameplay"))
    {
        DEBUG_LOG("Missing Gameplay section");
    }
    else
    {
        maxPlayers = iniFile.GetInt("maxPlayers").GetValue();
        defaultPlayerName = iniFile.GetString("defaultPlayerName").GetValue();
        startingTime = iniFile.GetFloat("startingTime").GetValue();
        damageAmount = iniFile.GetFloat("damageAmount").GetValue();
    }

    if (!iniFile.BindSection("Network"))
    {
        DEBUG_LOG("Missing Network section");
    }

    


	system("pause");

    iniFile.Clear();
	Reflection::Runtime::Terminate();
    
    return 0;
}

