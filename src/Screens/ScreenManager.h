#pragma once

enum class Screen
{
    MainMenu,
    OneVsAI,
    OneMatch,
    Match
};

class ScreenManager
{
public:

    ScreenManager();

    void setScreen(Screen screen);

    Screen currentScreen() const;

private:

    Screen m_currentScreen;
};