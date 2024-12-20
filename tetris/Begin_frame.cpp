#include"Begin_frame.h"


#define VK_G 0x47
#define VK_Q 0x51
#define VK_I 0x49
#define VK_U 0x55
#define VK_M 0x4D
#define VK_N 0x4E
namespace fs = std::filesystem;

Begin_frame::Begin_frame(Animation* animation) {
	//默认地图宽度和高度
	this->map_height = 20;
	this->map_width = 10;
	this->background = &animation->back_ground;
}

Begin_frame::Begin_frame() {

}

Begin_frame::~Begin_frame()
{
}

/*
* @brief 获取初始化游戏界面的必要信息
*/
void Begin_frame::initial() {
	//初始界面背景
	draw_backgroud();

}

/*
* @brief 绘制地图背景
*/
void inline Begin_frame::draw_backgroud() {
	putimage(0, 0, background);
}


// 绘制主菜单界面
void Begin_frame::drawMainMenu() {
    // 清空屏幕
    cleardevice();

    // 获取屏幕宽高
    int screenWidth = 800;  // 主界面宽度（稍大）
    int screenHeight = 600; // 主界面高度（稍大）

    // 初始化窗口大小
    initgraph(screenWidth, screenHeight);
    SetWindowText(GetHWnd(), L"俄罗斯方块 - 主菜单");

    // 设置标题字体和颜色
    settextstyle(48, 0, _T("Arial"));
    settextcolor(YELLOW);

    // 标题内容
    TCHAR title[] = _T("欢迎来到俄罗斯方块");
    int titleWidth = textwidth(title);
    int titleHeight = textheight(title);

    // 居中绘制标题
    int titleX = (screenWidth - titleWidth) / 2;
    int titleY = screenHeight / 6; // 标题位置稍高，1/6 高度
    outtextxy(titleX, titleY, title);

    // 设置菜单字体
    settextstyle(24, 0, _T("Arial"));

    // 主菜单选项
    TCHAR prompt1[] = _T("按 'G' 开始游戏");
    TCHAR prompt2[] = _T("按 'Q' 退出游戏");
    TCHAR prompt3[] = _T("按 'I' 新建配置");
    TCHAR prompt4[] = _T("按 'U' 加载配置");
    TCHAR prompt5[] = _T("按 'M' 进入残局挑战");
    TCHAR prompt6[] = _T("按 'N' 创建残局");

    // 垂直居中绘制选项
    int menuStartY = titleY + titleHeight + 50; // 菜单起始位置在标题下方
    int menuSpacing = 50; // 菜单行间距

    TCHAR* menuOptions[] = { prompt1, prompt2, prompt3, prompt4, prompt5, prompt6 };
    for (int i = 0; i < 6; ++i) {
        int optionWidth = textwidth(menuOptions[i]);
        int optionX = (screenWidth - optionWidth) / 2; // 水平居中
        int optionY = menuStartY + i * menuSpacing;
        outtextxy(optionX, optionY, menuOptions[i]);
    }

    // 刷新屏幕
    FlushBatchDraw();
}





// 获取主菜单消息
bool Begin_frame::getMainMenuMessage(MainMenuMessage& msg) {
    ExMessage message;
    if (peekmessage(&message)) {
        switch (message.vkcode) {
        case VK_G:
            msg.startGame = true;
            return true;
        case VK_Q:
            msg.quitGame = true;
            return true;
        case VK_I:
            msg.createConfig = true;
            return true;
        case VK_U:
            msg.loadConfig = true;
            return true;
        case VK_M:  
            msg.challengeEndGame = true;
            return true;
        case VK_N:  
            msg.createEndGame = true;
            return true;
        default:
            break;
        }
    }
    return false;
}


//检查文件是否存在
bool Begin_frame::fileExists(const std::string& filename) {
    try {
        return fs::exists(filename);
    }
    catch (fs::filesystem_error& e) {
        std::cout << "文件不存在: " << e.what() << std::endl;
        return false;
    }
}

// 确认目录存在，如果不存在则创建
bool Begin_frame::createDirectoryIfNotExists(const std::string& path) {
    try {
        if (fs::create_directories(path)) {
            std::cout << "目录已创建: " << path << std::endl;
        }
        return true;
    }
    catch (fs::filesystem_error& e) {
        std::cout << "创建目录失败: " << e.what() << std::endl;
        return false;
    }
}


// 初始化默认配置
void Begin_frame::initializeDefaults() {
    gameSpeed = 5;
    randomSeed = -1;
    initialLevel= 1;
}

// 加载指定配置文件
bool Begin_frame::loadConfig(const std::string& filename) {
    try {
        if (!fileExists(filename)) {
            std::cout << "配置文件不存在: " << filename << std::endl;
            return false;
        }

        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cout << "无法打开配置文件: " << filename << std::endl;
            return false;
        }

        std::string line;
        int count = 0; // 用于标记当前读取的配置项次序
        while (std::getline(infile, line)) {
            try {
                int value = std::stoi(line); // 将每行内容转换为整数
                if (count == 0) {
                    gameSpeed = value; // 第一行为 gameSpeed
                }
                else if (count == 1) {
                    initialLevel = value; // 第二行为 initialLevel
                }
                else if (count == 2) {
                    randomSeed = value; // 第三行为 randomSeed
                }
                else {
                    std::cerr << "配置文件中多余的行: " << line << std::endl;
                }
                count++;
            }
            catch (const std::invalid_argument&) {
                std::cerr << "配置文件中存在无效值: " << line << std::endl;
                return false;
            }
        }

        infile.close();

        // 确保文件包含了所有必需的配置项
        if (count < 3) {
            std::cerr << "配置文件中缺少必要的配置项。" << std::endl;
            return false;
        }

        std::cout << "加载的配置: " << std::endl;
        std::cout << "游戏速度: " << gameSpeed << std::endl;
        std::cout << "初始关卡: " << initialLevel << std::endl;
        std::cout << "随机种子: " << randomSeed << std::endl;

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "加载配置失败: " << e.what() << std::endl;
        return false;
    }
}


// 保存当前配置到指定文件
bool Begin_frame::saveConfig(const std::string& filename) const {
    try {
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            std::cout << "无法打开文件进行写入: " << filename << std::endl;
            return false;
        }

        for (const auto& [key, value] : configMap) {
            outfile << key << "=" << value << "\n";
        }
        outfile.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cout << "保存配置失败: " << e.what() << std::endl;
        return false;
    }
}

// 用户交互：新建配置文件
bool Begin_frame::createConfig() {
   
    std::string name;
    std::cout << "请输入新配置文件名称（仅限字母、数字和下划线，输入 'q' 退出）：";
    std::cin >> name;

    if (name == "q") {
        std::cout << "取消新建配置。\n";
        return false;
    }

    std::regex validName("^[A-Za-z0-9_]+$");
    if (!std::regex_match(name, validName)) {
        std::cerr << "无效的配置名称。\n";
        return false;
    }

    // 让用户输入三个量的值
    int gameSpeed, initialLevel;
    int randomSeed;

    std::cout << "请输入游戏速度 (1-10)：";
    std::cin >> gameSpeed;
    if (gameSpeed < 1 || gameSpeed > 10) {
        std::cerr << "无效的游戏速度值，必须在 1-10 之间。\n";
        return false;
    }

    std::cout << "请输入初始关卡 (>= 1)：";
    std::cin >> initialLevel;
    if (initialLevel < 1) {
        std::cerr << "无效的初始关卡值，必须大于等于 1。\n";
        return false;
    }

    std::cout << "请输入随机种子值（整数，输入 -1 表示随机）：";
    std::cin >> randomSeed;

    // 将这些值写入配置文件
    std::string filename = "config/" + name + ".config";
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "无法创建配置文件。\n";
        return false;
    }

    outfile << gameSpeed << "\n";
    outfile << initialLevel << "\n";
    outfile << randomSeed << "\n";

    outfile.close();
    std::cout << "配置文件已保存为: " << filename << std::endl;

    return true;
    
}

// 加载上次使用的配置
bool Begin_frame::loadLastConfig() {
    return loadConfig("config/last.config");
}

// 保存当前配置为上次使用的配置
bool Begin_frame::saveLastConfig() const {
    return saveConfig("config/last.config");
}

// 获取某个配置项的值
std::optional<std::string> Begin_frame::getConfig(const std::string& key) const {
    auto it = configMap.find(key);
    if (it != configMap.end()) {
        return it->second;
    }
    return std::nullopt;
}

// 设置某个配置项的值
void Begin_frame::setConfig(const std::string& key, const std::string& value) {
    if (validateKeyValue(key, value)) {
        configMap[key] = value;
    }
    else {
        std::cerr << "无效的配置值: " << key << "=" << value << std::endl;
    }
}

// 重置为默认配置
void Begin_frame::resetToDefault() {
    initializeDefaults();
}

// 验证整个配置是否合法
bool Begin_frame::isValid() const {
    for (const auto& [key, value] : configMap) {
        if (!validateKeyValue(key, value)) {
            return false;
        }
    }
    return true;
}

// 验证单个键值对是否合法
bool Begin_frame::validateKeyValue(const std::string& key, const std::string& value) const {
    if (key == "gameSpeed") {
        int speed = std::stoi(value);
        return speed >= 1 && speed <= 10;
    }
    else if (key == "randomSeed") {
        return std::regex_match(value, std::regex("^-?\\d+$"));
    }
    else if (key == "initialLevel") {
        int level = std::stoi(value);
        return level >= 1;
    }
    return false;
}


bool Begin_frame::testValidateKeyValue(const std::string& key, const std::string& value) const {
    return validateKeyValue(key, value);
}