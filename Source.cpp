#include <iostream>
#include <raylib.h>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int main()
{
    const int screenW = 400;                        
    const int screenH = 600;
    InitWindow(screenW, screenH, "CALCULATOR");
    SetTargetFPS(60);

    double currentValue = 0.0;
    double previousValue = 0.0;
    char operation = '\0';
    bool hasDecimal = false;
    bool operationPressed = false;

    string znach = "0";

    const int countbut = 20;
    const char* buttons[countbut] =
    {
        "1", "2", "3", "+", "!",
        "4", "5", "6", "-", "^2",
        "7", "8", "9", "*", "root",
        "C", "0", ".", "/", "=",
    };

    const float padding = 10.0f;
    const float buttonWidth = (screenW - 2 * padding - 4 * padding) / 5;
    const float buttonHeight = 80.0f;
    Rectangle buttonRects[countbut];

    int buttonIndex = 0;
    for (int row = 0; row < 4; row++) 
    {
        for (int col = 0; col < 5; col++)
        {
            buttonRects[buttonIndex] = 
            {
                padding + col * (buttonWidth + padding),
                120 + row * (buttonHeight + padding),
                buttonWidth,
                buttonHeight
            };
            buttonIndex++;
        }
    }

    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();

        BeginDrawing();
        ClearBackground(WHITE);

        Rectangle znachpream = { 10, 10, screenW - 20, 80 };
        DrawRectangleRec(znachpream, LIGHTGRAY);
        DrawRectangleLinesEx(znachpream, 2, BLACK);

        stringstream ss;
        ss << currentValue;
        znach = ss.str();
        DrawText(znach.c_str(), znachpream.x + 30, znachpream.y + 30, 20, BLACK);

        for (int i = 0; i < countbut; i++)
        {
            bool isMouseOver = CheckCollisionPointRec(mousePos, buttonRects[i]);
            bool isPressedVisual = isMouseOver && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
            Color buttonColor = LIGHTGRAY;
            if (isPressedVisual) buttonColor = DARKGRAY;
            else if (isMouseOver) buttonColor = GRAY;

            DrawRectangleRec(buttonRects[i], buttonColor);
            DrawRectangleLinesEx(buttonRects[i], 2, BLACK);
            int textWidth = MeasureText(buttons[i], 20);
            DrawText(buttons[i],
                buttonRects[i].x + (buttonWidth - textWidth) / 2,
                buttonRects[i].y + (buttonHeight - 20) / 2,
                20, BLACK);
        }

        for (int i = 0; i < countbut; i++)
        {
            bool isMouseOver = CheckCollisionPointRec(mousePos, buttonRects[i]);
            bool isPressed = isMouseOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

            if (isPressed)
            {
                string label = buttons[i];

                if (label >= "0" && label <= "9")
                {
                    if (operationPressed)
                    {
                        currentValue = 0.0;
                        operationPressed = false;
                    }
                    currentValue = currentValue * 10 + stoi(label);
                }
                else if (label == ".") 
                {
                    if (!hasDecimal)
                    {
                        hasDecimal = true;
                        stringstream ss;
                        ss << currentValue << ".";
                        znach = ss.str();
                    }
                }
                else if (label == "C")
                {
                    currentValue = 0.0;
                    previousValue = 0.0;
                    znach = "0";
                    hasDecimal = false;
                    operation = '\0';
                }
                else if (label == "+" || label == "-" || label == "*" || label == "/") {
                    previousValue = currentValue;
                    operation = label[0];
                    operationPressed = true;
                    hasDecimal = false;
                }
                else if (label == "=")
                {
                    switch (operation)
                    {
                    case '+': currentValue = previousValue + currentValue; break;
                    case '-': currentValue = previousValue - currentValue; break;
                    case '*': currentValue = previousValue * currentValue; break;
                    case '/': currentValue = (currentValue != 0) ? previousValue / currentValue : 0; break;
                    }
                    operation = '\0';
                    hasDecimal = false;
                }
                else if (label == "^2")
                {
                    currentValue = currentValue * currentValue;
                }
                else if (label == "root") 
                {
                    if (currentValue >= 0)
                        currentValue = sqrt(currentValue);
                }
                else if (label == "!")
                {
                    double result = 1;
                    for (int j = 1; j <= (int)currentValue; j++) {
                        result *= j;
                    }
                    currentValue = result;
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
