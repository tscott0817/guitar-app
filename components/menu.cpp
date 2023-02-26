#include "menu.h"

Menu::Menu(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {
    containerImage = LoadImage("../plaid.png");
    containerTexture = LoadTextureFromImage(containerImage);
    UnloadImage(containerImage);
    container = {posX, posY,
                 static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};
    containerCenter = {container.width / 2, container.height / 2};


//    chartImage = LoadImage("../pink.png");
//    chartTexture = LoadTextureFromImage(containerImage);
    // UnloadImage(chartImage);
    menuRectangle = {container.x, container.y, container.width * .49f, container.height * .15f};
    menuCenter = {static_cast<float>(menuRectangle.width / 2), static_cast<float>(menuRectangle.height / 2)};

    menuLocAdded = false;

    // TODO: Just filling to 100 for room, but don't want to hardcode this 100
    for (int i = 0; i < 100; i++) {
        std::vector<Vector2> tempLoc;
        std::vector<Color> tempColor;
        for (int j = 0; j < 100; j++) {
            tempLoc.push_back({0, 0});
            tempColor.push_back(BLUE);
        }
        menuLocations.push_back(tempLoc);
        menuColorVec.push_back(tempColor);
    }

}

void Menu::initMenu() {

}
int Menu::drawMenu(float windowScale) {
    /** Container **/
    DrawTexturePro(containerTexture,
                   container,
                   (Rectangle) {container.x, container.y, container.width, container.height},
                   containerCenter, 0, WHITE);

    /** Chart **/
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
//            DrawTexturePro(chartTexture,
//                           chartRectangle,
//                           (Rectangle) {container.x * i, container.y * j, chartRectangle.width, chartRectangle.height},
//                           chartCenter, 0, WHITE);

            DrawRectangle(static_cast<float>((container.x) + ((container.width * .5f) * i) - (container.width * .4925f)),
                          static_cast<float>((container.y) - ((container.height * .16f) * j) + (container.height * .325f)),
                          menuRectangle.width, menuRectangle.height, menuColorVec[i][j]);

            // Store the container coordinates (since iterated here in loop)
            if (!menuLocAdded) {
                menuLocations[i][j] = {static_cast<float>((container.x) + ((container.width * .5f) * i) - (container.width * .4925f)),
                                        static_cast<float>((container.y) - ((container.height * .16f) * j) + (container.height * .325f))};
            }
        }
    }

    menuLocAdded = true;

    return 0;  // TODO: Probably no reason to return int, make void

}
void Menu::hover(Vector2 mousePos) {
    for (int i = 0; i < menuLocations.size(); i++) {
        for (int j = 0; j < menuLocations[i].size(); j++) {
            if (mousePos.x > menuLocations[i][j].x && mousePos.x < menuLocations[i][j].x + (menuRectangle.width) &&
                mousePos.y > menuLocations[i][j].y && mousePos.y < menuLocations[i][j].y + (menuRectangle.height)) {
                std::cout << "Chord Chart -> Currently Hovering at Coordinates:" << std::endl;
                std::cout << menuLocations[i][j].x << ", " << menuLocations[i][j].y << std::endl;
                //*noteColor = MAROON;
                //noteColorVec->at(i) = MAROON;
                menuColorVec[i][j] = MAROON;
            } else {
                //*noteColor = BLUE;
                //noteColorVec->at(i) = BLUE;
                menuColorVec[i][j] = BLUE;
            }

        }
    }
}
void Menu::destroy() {
    UnloadTexture(containerTexture);
    UnloadTexture(menuTexture);
}