#include"Begin_frame.h"


#define VK_G 0x47
#define VK_Q 0x51
#define VK_I 0x49
#define VK_U 0x55
#define VK_M 0x4D
#define VK_N 0x4E
namespace fs = std::filesystem;

Begin_frame::Begin_frame(Animation* animation) {

    //初始化默认参数
    default_param();

    //获取资源
    this->animation = animation;
	this->background = &animation->back_ground;

}

Begin_frame::~Begin_frame()
{
}

void Begin_frame::default_param() {

    //清除map和blockColor数组
    this->map.clear();
    this->blockColors.clear();

    this->map_height = 20;
    this->map_width = 10;
    this->randomSeed = -1;
    this->gameSpeed = 1;
    this->initialLevel = 1;

    // 默认加载 last.config
    if (!this->loadLastConfig()) {
        std::cout << "未能加载 last.config，将使用默认配置。" << std::endl;
    }
    else {
        std::cout << "成功加载 last.config。" << std::endl;
    }

    for (int i = 0; i < map_height; i++) {
        std::vector<bool> temp_map_line;
        std::vector<int> temp_color_line;
        for (int j = 0; j < map_width; j++) {
            temp_color_line.push_back(-1);
            temp_map_line.push_back(false);
        }
        this->map.push_back(temp_map_line);
        this->blockColors.push_back(temp_color_line);
    }
}

void Begin_frame::initial() {

    //初始化界面
    SetWindowText(initgraph(this->begin_frame_width, this->begin_frame_height), L"俄罗斯方块"); 

    BeginBatchDraw();

	//初始界面背景
	draw_backgroud();

    //初始化菜单
    draw_menu();

    FlushBatchDraw();

    //更新默认参数
    default_param();
}

void inline Begin_frame::draw_backgroud() {
	putimage(0, 0, background);
}

void Begin_frame::draw_menu() {

    settextstyle(60, 0, _T("Arial"));
    settextcolor(YELLOW);

    TCHAR title[] = _T("欢迎来到俄罗斯方块");
    TCHAR prompt1[] = _T("按 'G' 开始游戏");
    TCHAR prompt2[] = _T("按 'Q' 退出游戏");
    TCHAR prompt3[] = _T("按 'I' 新建配置");
    TCHAR prompt4[] = _T("按 'U' 加载配置");
    TCHAR prompt5[] = _T("按 'N' 创建残局");
    TCHAR prompt6[] = _T("按 'M' 加载残局");

    int titleWidth = textwidth(title);
    int prompt1Width = textwidth(prompt1);
    int prompt2Width = textwidth(prompt2);
    int prompt3Width = textwidth(prompt3);
    int prompt4Width = textwidth(prompt4);
    int prompt5Width = textwidth(prompt5);
    int prompt6Width = textwidth(prompt6);
    setbkmode(TRANSPARENT);

    outtextxy((getwidth() - titleWidth) / 2, getheight() / 2 - 120, title);
    settextstyle(30, 0, _T("Arial"));
    outtextxy((getwidth() - prompt1Width) / 2, getheight() / 2 - 20, prompt1);
    outtextxy((getwidth() - prompt2Width) / 2, getheight() / 2 + 20, prompt2);
    outtextxy((getwidth() - prompt3Width) / 2, getheight() / 2 + 60, prompt3);
    outtextxy((getwidth() - prompt4Width) / 2, getheight() / 2 + 100, prompt4);
    outtextxy((getwidth() - prompt5Width) / 2, getheight() / 2 + 140, prompt5);
    outtextxy((getwidth() - prompt6Width) / 2, getheight() / 2 + 180, prompt6);

}

bool Begin_frame::getMainMenuMessage(MainMenuMessage& msg) {
    ExMessage message;
    while (peekmessage(&message)) {
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

bool Begin_frame::fileExists(const std::string& filename) {
    try {
        return fs::exists(filename);
    }
    catch (fs::filesystem_error& e) {
        std::cout << "文件不存在: " << e.what() << std::endl;
        return false;
    }
}

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

void Begin_frame::initializeDefaults() {
    gameSpeed = 5;
    randomSeed = -1;
    initialLevel= 1;
}

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
                    std::cout << "配置文件中多余的行: " << line << std::endl;
                }
                count++;
            }
            catch (const std::invalid_argument&) {
                std::cout << "配置文件中存在无效值: " << line << std::endl;
                return false;
            }
        }

        infile.close();

        // 确保文件包含了所有必需的配置项
        if (count < 3) {
            std::cout << "配置文件中缺少必要的配置项。" << std::endl;
            return false;
        }

        std::cout << "加载的配置: " << std::endl;
        std::cout << "游戏速度: " << gameSpeed << std::endl;
        std::cout << "初始关卡: " << initialLevel << std::endl;
        std::cout << "随机种子: " << randomSeed << std::endl;

        return true;
    }
    catch (const std::exception& e) {
        std::cout << "加载配置失败: " << e.what() << std::endl;
        return false;
    }
}

bool Begin_frame::saveConfig(const std::string& filename) const {
    try {
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            std::cout << "无法打开文件进行写入: " << filename << std::endl;
            return false;
        }

        outfile << gameSpeed << "\n";
        outfile << initialLevel << "\n";
        outfile << randomSeed << "\n";

        outfile.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cout << "保存配置失败: " << e.what() << std::endl;
        return false;
    }
}

bool Begin_frame::createConfig(std::string &name) {

    std::regex validName("^[A-Za-z0-9_]+$");
    if (!std::regex_match(name, validName)) {
        std::cout << "无效的配置名称。\n";
        return false;
    }

    // 让用户输入三个量的值
    int gameSpeed, initialLevel;
    int randomSeed;

    /*std::cout << "请输入游戏速度 (1-10)：";
    std::cin >> gameSpeed;
    if (gameSpeed < 1 || gameSpeed > 10) {
        std::cout << "无效的游戏速度值，必须在 1-10 之间。\n";
        return false;
    }*/

    while (true) {
        std::cout << "请输入游戏速度 (1-10)：";
        std::cin >> gameSpeed;
        if (std::cin.fail() || gameSpeed < 1 || gameSpeed > 10) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "无效的游戏速度值，必须在 1-10 之间。\n";
        }
        else {
            break;
        }
       
    }

    /*std::cout << "请输入初始关卡 (>= 1)：";
    std::cin >> initialLevel;
    if (initialLevel < 1) {
        std::cout << "无效的初始关卡值，必须大于等于 1。\n";
        return false;
    }*/

    while (true) {
        std::cout << "请输入初始关卡 (>= 1)：";
        std::cin >> initialLevel;
        if (std::cin.fail() || initialLevel < 1) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "无效的初始关卡值，必须大于等于 1。\n";
        }
        else {
            break;
        }

    }

    /* td::cout << "请输入随机种子值（整数，输入 -1 表示随机）：";
    std::cin >> randomSeed;*/

    while (true) {
        std::cout << "请输入随机种子值（整数，输入 -1 表示随机）：";
        std::cin >> randomSeed;
        if (std::cin.fail() ) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "无效的随机种子值\n";
        }
        else {
            break;
        }

    }

    // 将这些值写入配置文件
    std::string filename = "config/" + name + ".config";
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cout << "无法创建配置文件。\n";
        return false;
    }

    outfile << gameSpeed << "\n";
    outfile << initialLevel << "\n";
    outfile << randomSeed << "\n";

    outfile.close();
    std::cout << "配置文件已保存为: " << filename << std::endl;

    return true;
    
}

bool Begin_frame::saveLastConfig() const {
    const std::string lastConfigPath = "config/last.config";
    return saveConfig(lastConfigPath);
}

std::optional<std::string> Begin_frame::getConfig(const std::string& key) const {
    auto it = configMap.find(key);
    if (it != configMap.end()) {
        return it->second;
    }
    return std::nullopt;
}

void Begin_frame::setConfig(const std::string& key, const std::string& value) {
    if (validateKeyValue(key, value)) {
        configMap[key] = value;
    }
    else {
        std::cout << "无效的配置值: " << key << "=" << value << std::endl;
    }
}

void Begin_frame::resetToDefault() {
    initializeDefaults();
}

bool Begin_frame::isValid() const {
    for (const auto& [key, value] : configMap) {
        if (!validateKeyValue(key, value)) {
            return false;
        }
    }
    return true;
}

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

bool Begin_frame::loadLastConfig() {
    const std::string lastConfigPath = "config/last.config";

    // 检查 last.config 文件是否存在
    if (!fileExists(lastConfigPath)) {
        std::cout << "last.config 文件不存在，将创建默认配置。" << std::endl;

        // 创建默认配置
        gameSpeed = 5;         // 默认游戏速度
        initialLevel = 1;      // 默认初始关卡
        randomSeed = -1;       // 默认随机种子
        saveConfig(lastConfigPath); // 保存默认配置到 last.config

        return true;
    }

    // 如果存在，加载配置
    std::cout << "正在加载 last.config 文件..." << std::endl;
    return loadConfig(lastConfigPath);
}