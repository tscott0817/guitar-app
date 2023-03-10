#include "menu.h"


// Create constructor for menu
Menu::Menu(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    active = 0;
    editMode = false;
    blackBackground = {0, 0, 0, 150};
    canDraw = true;

    // Only change the position and size of neckContainer (Make this the params the user can change, drop down menu)
    // container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height
    container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height
    containerCenter = {container.width / 2, container.height / 2};
    containerTexture = LoadTexture("../images/plaid.png");

    // Use the container position +/- some integer to move child objects
    // Use the size of the container * some float to resize child object
    //buttonOneRec = {container.x, container.y, container.width, container.height}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonOneRec = {container.x, container.y, container.width * .1f, container.height * .9f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonOneCenter = {static_cast<float>(buttonOneRec.width / 2), static_cast<float>(buttonOneRec.height / 2)};

    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);  // Default text size
}

void Menu::setBackground(int screenWidth, int screenHeight) {
        GuiGrid((Rectangle){0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight)}, "Guitar Grid", 40.0f, 4); // Draw a fancy grid
}

void Menu::drawTopMenu(int width, int height) {
    /** Container **/
//    DrawTexturePro(containerTexture,
//                   container,
//                   (Rectangle) {container.x, container.y, container.width, container.height},  /** Params = (x-pos, y-pos, height, width) **/
//                   containerCenter, 0, WHITE);

    // Draw a rectangle that is the size of the container
    DrawRectangle(container.x, container.y, container.width, container.height, blackBackground);

    //----------------------------------------------------------------------------------
    // Check all possible events that require GuiLock
    if (editMode) GuiLock();
    // NOTE: GuiDropdownBox must draw after any other control that can be covered on unfolding
    GuiUnlock();
    GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    if (GuiDropdownBox((Rectangle){ buttonOneRec.x, buttonOneRec.y + (container.height * .06f), buttonOneRec.width, buttonOneRec.height }, "Guitar;Piano;THREE", &active, editMode)) editMode = !editMode;
    // Check which button is active and print the results
//    if (active == 0) {
//        std::cout << "Guitar is active" << std::endl;
//    }
//    else if (active == 1) {
//        std::cout << "Piano is active" << std::endl;
//    }
//    else if (active == 2) {
//        std::cout << "Button 3 is active" << std::endl;
//    }
//    else {
//        std::cout << "You somehow selected a button that doesn't exist!" << std::endl;
//    }

}

bool Menu::isHovering(Vector2 mousePos) {
        if (mousePos.x > container.x && mousePos.x < container.x + (container.width) &&
            mousePos.y > container.y && mousePos.y < container.y + (container.height)) {
            std::cout << "Top Menu -> Currently Hovering at Coordinates:" << std::endl;
            std::cout << container.x << ", " << container.y << std::endl;
            return true;
        }
        else{
            return false;
        }
}

// Setters
void Menu::setActiveButton(int activeButton){
    this->active = activeButton;
}

// Getters
int Menu::getActiveButton(){
    return this->active;
}
