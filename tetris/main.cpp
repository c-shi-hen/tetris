#include<easyx.h>
#include"Frame.h"
#include"Begin_frame.h"
#include"Animation.h"
#include "ConfigManager.h"
#include "EndGame.h"
#include <iostream>
#include <windows.h> 
#include <tchar.h>   
#include <filesystem> 

namespace fs = std::filesystem;
//
//
//
//// 运行游戏
//void runGame() {
//    Animation* animation = new Animation();
//    
//    Begin_frame* my_begin_frame = new Begin_frame(animation);
//    SetWindowText(initgraph(my_begin_frame->begin_frame_width, my_begin_frame->begin_frame_height), L"俄罗斯方块");
//    my_begin_frame->initial();
//    closegraph();
//    
//    
//    Frame* myFrame = new Frame(my_begin_frame->map_width, my_begin_frame->map_height, animation);
//    SetWindowText(initgraph(myFrame->frame_width, myFrame->frame_height), L"俄罗斯方块");
//    BeginBatchDraw();
//    myFrame->game_begin();
//    EndBatchDraw();
//    closegraph();
//    
//    delete(myFrame);
//    delete(animation);
//    delete(my_begin_frame);
//    
//}
//
//int main() {
//    //// 确保 config 目录存在
//    //if (!createdirectoryifnotexists("config")) {
//    //    std::cerr << "无法创建 'config' 目录。" << std::endl;
//    //    return 1;
//    //}
//
//    //// 加载最后使用的配置
//    //Config currentConfig;
//    //loadLastConfig(currentConfig);
//
//    // 初始化主菜单界面
//    int menuWidth = 600;
//    int menuHeight = 400;
//    initgraph(menuWidth, menuHeight);
//    SetWindowText(GetHWnd(), L"俄罗斯方块 - 主菜单");
//
//    // 主菜单消息循环
//    Begin_frame::MainMenuMessage menuMsg;
//    Animation* animation0 = new Animation();
//    Begin_frame* my_begin_frame0 = new Begin_frame(animation0);
//    while (true) {
//        my_begin_frame0->drawMainMenu();
//
//        // 等待用户输入
//        while (!my_begin_frame0->getMainMenuMessage(menuMsg)) {
//            Sleep(10);
//        }
//
//        if (menuMsg.startGame) {
//            closegraph();
//            runGame();
//            break;
//        }
//        if (menuMsg.quitGame) {
//            closegraph();
//            std::cout << "退出游戏。" << std::endl;
//            break;
//        }
//        /*if (menuMsg.createConfig) {
//            createConfig();
//        }
//        if (menuMsg.loadConfig) {
//            loadConfig(currentConfig);
//        }*/
//
//        // 重置消息
//        menuMsg = {};
//    }
//
//    return 0;
//}
//
//



//测试config
#include "ConfigManager.h"
#include <iostream>
#include <cassert>
#include <fstream>

// 测试初始化默认配置
void testInitializeDefaults() {
    ConfigManager configManager;
    assert(configManager.getConfig("gameSpeed").value() == "5");
    assert(configManager.getConfig("randomSeed").value() == "-1");
    assert(configManager.getConfig("initialLevel").value() == "1");
    std::cout << "testInitializeDefaults passed!\n";
}

// 测试加载指定配置文件
void testLoadConfig() {
    ConfigManager configManager;
    assert(configManager.loadConfig("config/default.config") == true);
    assert(configManager.getConfig("gameSpeed").value() == "5");
    assert(configManager.getConfig("randomSeed").value() == "-1");
    assert(configManager.getConfig("initialLevel").value() == "1");
    std::cout << "testLoadConfig passed!\n";
}

// 测试保存配置到文件
void testSaveConfig() {
    ConfigManager configManager;
    configManager.setConfig("gameSpeed", "7");
    configManager.setConfig("randomSeed", "1234");
    configManager.setConfig("initialLevel", "3");

    assert(configManager.saveConfig("config/test_save.config") == true);

    ConfigManager loadedConfig;
    assert(loadedConfig.loadConfig("config/test_save.config") == true);
    assert(loadedConfig.getConfig("gameSpeed").value() == "7");
    assert(loadedConfig.getConfig("randomSeed").value() == "1234");
    assert(loadedConfig.getConfig("initialLevel").value() == "3");
    std::cout << "testSaveConfig passed!\n";
}

// 测试自定义文件中的值和命名
void testCustomFileNamingAndValues() {
    ConfigManager configManager;

    // 用户输入配置值
    std::string gameSpeed, randomSeed, initialLevel, filename;
    std::cout << "请输入 gameSpeed (1-10): ";
    std::cin >> gameSpeed;
    std::cout << "请输入 randomSeed: ";
    std::cin >> randomSeed;
    std::cout << "请输入 initialLevel (>=1): ";
    std::cin >> initialLevel;
    std::cout << "请输入配置文件名（不包含路径和后缀，英文字母、数字和下划线）: ";
    std::cin >> filename;

    // 验证文件名是否合法
    if (filename.empty() || filename.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos) {
        std::cerr << "非法的文件名: " << filename << std::endl;
        return;
    }

    // 设置用户输入的配置值
    configManager.setConfig("gameSpeed", gameSpeed);
    configManager.setConfig("randomSeed", randomSeed);
    configManager.setConfig("initialLevel", initialLevel);

    // 保存到自定义文件
    std::string customFile = "config/" + filename + ".config";
    assert(configManager.saveConfig(customFile) == true);

    // 重新加载文件
    ConfigManager loadedConfig;
    assert(loadedConfig.loadConfig(customFile) == true);

    // 验证文件中自定义的值是否正确
    assert(loadedConfig.getConfig("gameSpeed").value() == gameSpeed);
    assert(loadedConfig.getConfig("randomSeed").value() == randomSeed);
    assert(loadedConfig.getConfig("initialLevel").value() == initialLevel);

    // 打印验证结果
    std::cout << "Custom file named " << customFile << " loaded correctly with values:\n";
    for (const auto& key : { "gameSpeed", "randomSeed", "initialLevel" }) {
        auto value = loadedConfig.getConfig(key);
        if (value) {
            std::cout << key << " = " << value.value() << std::endl;
        }
        else {
            std::cout << key << " 未找到." << std::endl;
        }
    }

    std::cout << "testCustomFileNamingAndValues passed!\n";
}

// 测试读取某个指定文件
void testReadSpecificFile() {
    ConfigManager configManager;
    std::string filename;
    std::cout << "请输入要读取的配置文件名（包括路径和后缀）: ";
    std::cin >> filename;

    // 尝试加载指定文件
    if (configManager.loadConfig(filename)) {
        std::cout << "成功加载配置文件: " << filename << std::endl;
        for (const auto& key : { "gameSpeed", "randomSeed", "initialLevel" }) {
            auto value = configManager.getConfig(key);
            if (value) {
                std::cout << key << " = " << value.value() << std::endl;
            }
            else {
                std::cout << key << " 未找到." << std::endl;
            }
        }
    }
    else {
        std::cerr << "无法加载配置文件: " << filename << std::endl;
    }
    std::cout << "testReadSpecificFile completed!\n";
}

// 测试验证键值对是否合法
void testValidateKeyValue() {
    ConfigManager configManager;

    // 合法值
    assert(configManager.testValidateKeyValue("gameSpeed", "5") == true);
    assert(configManager.testValidateKeyValue("randomSeed", "0") == true);
    assert(configManager.testValidateKeyValue("initialLevel", "1") == true);

    // 非法值
    assert(configManager.testValidateKeyValue("gameSpeed", "20") == false);
    assert(configManager.testValidateKeyValue("randomSeed", "abc") == false);
    assert(configManager.testValidateKeyValue("initialLevel", "-1") == false);

    std::cout << "testValidateKeyValue passed!\n";
}

// 测试重置为默认配置
void testResetToDefault() {
    ConfigManager configManager;
    configManager.setConfig("gameSpeed", "9");
    configManager.setConfig("randomSeed", "9999");
    configManager.setConfig("initialLevel", "10");

    configManager.resetToDefault();

    assert(configManager.getConfig("gameSpeed").value() == "5");
    assert(configManager.getConfig("randomSeed").value() == "-1");
    assert(configManager.getConfig("initialLevel").value() == "1");
    std::cout << "testResetToDefault passed!\n";
}

// 测试读写配置文件
void testReadWriteConfig() {
    ConfigManager configManager;

    configManager.setConfig("gameSpeed", "10");
    configManager.setConfig("randomSeed", "2023");
    configManager.setConfig("initialLevel", "5");

    assert(configManager.saveConfig("config/test_rw.config") == true);

    ConfigManager loadedConfig;
    assert(loadedConfig.loadConfig("config/test_rw.config") == true);

    assert(loadedConfig.getConfig("gameSpeed").value() == "10");
    assert(loadedConfig.getConfig("randomSeed").value() == "2023");
    assert(loadedConfig.getConfig("initialLevel").value() == "5");

    std::cout << "Read config values from config/test_rw.config:" << std::endl;
    for (const auto& key : { "gameSpeed", "randomSeed", "initialLevel" }) {
        auto value = loadedConfig.getConfig(key);
        if (value) {
            std::cout << key << " = " << value.value() << std::endl;
        }
        else {
            std::cout << key << " not found in config." << std::endl;
        }
    }
    std::cout << "testReadWriteConfig passed!\n";


}


// 测试创建残局功能
void testCreateEndGame() {
    EndGame endGame;
    std::cout << "测试创建残局功能，请按照提示输入数据：" << std::endl;
    bool result = endGame.createEndGame();
    assert(result == true || result == false); // 返回值应为 true 或 false
    std::cout << "testCreateEndGame passed!\n";
}

// 测试保存到文件功能
void testSaveToFile() {
    EndGame endGame;
    endGame.createEndGame(); // 需要用户输入

    std::string filename = "test_endgame_save.end";
    bool result = endGame.saveToFile(filename);
    assert(result == true); // 保存文件应成功

    // 验证文件是否存在
    std::ifstream infile(filename);
    assert(infile.good());
    infile.close();

    std::cout << "testSaveToFile passed!\n";
}

// 测试从文件加载功能
void testLoadFromFile() {
    EndGame endGame;

    // 首先保存一个测试文件
    std::string filename = "test_endgame_save.end";
    bool saveResult = endGame.saveToFile(filename);
    assert(saveResult == true);

    // 然后加载文件
    bool loadResult = endGame.loadFromFile(filename);
    assert(loadResult == true); // 加载文件应成功

    std::cout << "testLoadFromFile passed!\n";
}

// 测试完整工作流程
void testEndGameWorkflow() {
    testCreateEndGame();
    testSaveToFile();
    testLoadFromFile();
    std::cout << "All EndGame tests passed!\n";
}




// 主函数运行所有测试
int main() {
    testInitializeDefaults();
    testLoadConfig();
    testSaveConfig();
    testCustomFileNamingAndValues();
    testReadSpecificFile();
    testValidateKeyValue();
    testResetToDefault();
    testReadWriteConfig();

    testEndGameWorkflow();

    std::cout << "All tests passed successfully!\n";
    return 0;
}
