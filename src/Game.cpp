#include "Game.h"
#include "GameLogger.h"
#include "input_utils.h"
#include <ctime>

// === Game Initialization ===

Game::Game(GameWindow* gameWindow)
    : window(gameWindow), player("Hero"), world()
{
    GameLogger::setWindow(gameWindow);
}

void Game::update() {
    if (combatManager.isCombatActive()) {
        combatManager.update(player);
        if (!combatManager.isCombatActive()) {
            inCombat = false;
        }
        return;
    }

    std::string input = getLineInput(window, "Enter command: ");

    if (input == "move") {
        std::string direction = getLineInput(window, "Direction: ");
        world.movePlayer(player, direction);
        world.describeCurrentTile(player);
    } else if (input == "inventory") {
        player.showInventory();
    } else if (input == "status") {
        player.displayStats();
    } else if (input == "quit") {
        isRunning = false;
    } else {
        GameLogger::info("Unknown command.");
    }

    if (world.shouldTriggerCombat()) {
        auto enemy = std::make_shared<Enemy>(world.getRandomEnemy());
        combatManager.startCombat(player, enemy, rivalSystem);
        inCombat = true;
    }
}

bool Game::isGameOver() const {
    return !isRunning || player.isDead();
}

Player Game::initializePlayer() {
    std::string name = getLineInput(window, "Enter your character's name (or press Enter for 'Hero'): ");
    if (name.empty()) name = "Hero";
    return Player(name);
}

void Game::initializeGame() {
    char choice = getCharInput(window, "Load saved game? (y/n): ");
    if (choice == 'y' || choice == 'Y') {
        loadGame();
    } else {
        setupNewGame();
    }

    addStartingItems();
}

void Game::setupNewGame() {
    unsigned int seed;
    seed = getIntInput(window, "Enter a World seed? (0 for random): ", 0, std::numeric_limits<int>::max());
    if (seed == 0) seed = static_cast<unsigned int>(std::time(nullptr));
    worldSeed = seed;

    std::string startLoc;
    worldMap = WorldGenerator::generateMap(10, startLoc, seed);
    player.setPosition(startLoc);

    for (const auto& skill : player.getValidSkills()) {
        player.getSkills()[skill] = 0;
        player.getSkillXP()[skill] = 0;
    }
}

void Game::addStartingItems() {
    Item sword("Sword", "A sharp blade for combat", ItemType::Weapon);
    player.addItem(sword);
}

// === Main Game Loop ===

void Game::run() {
    GameState state = GameState::MainMenu;

    while (state != GameState::Exit) {
        state = updateState(state);
    }

    char choice = getCharInput(window, "Save game before exiting? (y/n): ");
    if (choice == 'y' || choice == 'Y') {
        saveGame();
    }
}

GameState Game::updateState(GameState state) {
    switch (state) {
        case GameState::MainMenu:
            displayMenu();
            return handleInput();
        case GameState::GameOver:
            GameLogger::info("Game Over! Returning to Menu...");
            return GameState::MainMenu;
        case GameState::Inventory:
            inventoryMenu();
            return GameState::MainMenu;
        case GameState::Exit:
            return GameState::Exit;
        default:
            GameLogger::info("Unhandled Game State...");
            return GameState::Exit;
    }
}

// === Menus ===

void Game::displayMenu() {
    GameLogger::info("\n=== Text RPG ===");
    GameLogger::info("1. Train a skill");
    GameLogger::info("2. View Stats");
    GameLogger::info("3. View Inventory");
    GameLogger::info("4. Save Game");
    GameLogger::info("5. Exit");
}

GameState Game::handleInput() {
    int choice = getIntInput(window, "Choose an action: ", 1, 5);

    switch (choice) {
        case 1:
            trainSkillMenu();
            return GameState::MainMenu;
        case 2:
            player.displayStats();
            return GameState::MainMenu;
        case 3:
            return GameState::Inventory;
        case 4:
            saveGame();
            return GameState::MainMenu;
        case 5:
            GameLogger::info("Exiting game...");
            return GameState::Exit;
        default:
            GameLogger::info("Invalid choice, try again.");
            return GameState::MainMenu;
    }
}

void Game::trainSkillMenu() {
    std::string skill = getLineInput(window, "Enter the skill you want to train: ");
    player.trainSkill(skill, 10); // Award 10 XP
}

void Game::inventoryMenu() {
    while (true) {
        const auto& items = player.getInventory().getItems();

        GameLogger::info("\n=== Inventory Menu ===");
        if (items.empty()) {
            GameLogger::info("Your inventory is empty...");
            break;
        }

        for (size_t i = 0; i < items.size(); ++i) {
            GameLogger::info(std::to_string(i + 1) + ". " + items[i].getName());
        }

        int choice = getIntInput(window, "0. Back\nChoose an item: ", 0, static_cast<int>(items.size()));
        if (choice == 0) break;

        handleInventoryAction(choice - 1);
    }
}

void Game::handleInventoryAction(size_t index) {
    const auto& item = player.getInventory().getItems()[index];

    while (true) {
        GameLogger::info("\nSelected: " + item.getName());
        GameLogger::info("1. Inspect");
        GameLogger::info("2. Use");
        GameLogger::info("3. Drop");
        GameLogger::info("4. Equip");
        GameLogger::info("5. Back");

        int action = getIntInput(window, "Choose an action: ", 1, 5);

        switch (action) {
            case 1:
                player.getInventory().inspectItem(index);
                break;
            case 2:
                if (player.getInventory().useItem(index, player)) return;
                break;
            case 3:
                if (player.getInventory().removeItem(index)) return;
                break;
            case 4:
                if (item.getType() == ItemType::Weapon) {
                    player.equipWeapon(item);
                } else {
                    GameLogger::info("You can't equip that.");
                }
                break;
            case 5:
                return;
        }
    }
}

// === Saving and Loading ===

void Game::saveGame() {
    std::string saveName = getLineInput(window, "Enter save name (or press Enter for default): ");
    if (saveName.empty()) saveName = "save";

    PlayerData pdata;
    pdata.name = player.getName();
    pdata.health = player.getHealth();
    pdata.position = player.getPosition();
    pdata.skills = player.getSkills();
    pdata.skillXP = player.getSkillXP();
    pdata.inventory = player.getInventoryString();

    WorldData wdata;
    wdata.location = player.getPosition();
    wdata.time = "day";
    wdata.seed = worldSeed;

    SaveManager::saveGame(pdata, wdata, saveName);
    GameLogger::info("Game saved as \"" + saveName + "\".");
}

void Game::loadGame() {
    std::string saveName = getLineInput(window, "Enter save name (or press Enter for default): ");
    if (saveName.empty()) saveName = "save";

    PlayerData pdata;
    WorldData wdata;
    SaveManager::loadGame(pdata, wdata, saveName);

    if (pdata.name.empty()) {
        GameLogger::info("No valid save data found.");
        return;
    }

    player.setName(pdata.name);
    player.setHealth(pdata.health);
    player.setPosition(pdata.position);
    player.loadInventoryFromString(pdata.inventory);
    player.getSkills() = pdata.skills;
    player.getSkillXP() = pdata.skillXP;

    worldSeed = wdata.seed;
    std::string ignoreStart;
    worldMap = WorldGenerator::generateMap(10, ignoreStart, worldSeed);
}
