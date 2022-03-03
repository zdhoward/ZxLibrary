/*
  ==============================================================================

    ThemeManager.h
    Created: 1 Mar 2022 6:21:25pm
    Author:  ZECHS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct Theme {
    int themeId = 0;
    String themeName = "Default";

    Colour logo;
    Colour pluginName;

    Colour mainBackground;

    Colour compFace;
    Colour compHighlight;
    Colour compBackground;

    Colour groupBackground;

    Colour textMain;
    Colour textHighlight;
    Colour textLink;

    Colour buttonText;
    Colour buttonBackground;
    Colour buttonToggledText;
    Colour buttonToggledBackground;
    Colour buttonPressed;

    Colour comboBoxActive;
    Colour comboBoxHighlighted;
};

class ThemeManager
{
public:
    ThemeManager(AudioProcessorValueTreeState& a) :
        apvts(a)
    {
        // Load theme from apvts
        int id = apvts.state.getProperty("ThemeId", 0);//, 0);
        setThemeById(id);
        DBG("ThemeManager: Constructor - " << id);

        //setThemeByName("Default");
        //setThemeByName("LemonLime");
    };

    ~ThemeManager() {};

    Theme getCurrentTheme()
    {
        return currentTheme;
    };

    int getCurrentThemeId()
    {
        return currentTheme.themeId;
    };

    String getCurrentThemeName()
    {
        return currentTheme.themeName;
    };

    StringArray getAllThemes() 
    {
        return themes;
    };

    void setThemeById(int themeId)
    {
        setTheme(themes[themeId]);
    };

    void setThemeByName(String themeName)
    {
        setTheme(themeName);
    };

private:
    AudioProcessorValueTreeState& apvts;

    Theme currentTheme;

    StringArray themes = {
        "Default",
        "InkPink",
        "Oil",
        "Curiosities",
        "LemonLime",
        "Yamazaki",
        "IcyWitch",
        "DontForget",
        "Puffball",
        "Violets",
    };

    void setTheme(String themeName)
    {
        DBG("ThemeManager: setTheme - Setting - " << themeName);

        if (themeName == "InkPink")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff);
            currentTheme.pluginName = Colour(0xff);

            currentTheme.mainBackground = Colour(0xff);

            currentTheme.compFace = Colour(0xff);
            currentTheme.compHighlight = Colour(0xff);
            currentTheme.compBackground = Colour(0xff);

            currentTheme.groupBackground = Colour(0xff);

            currentTheme.textMain = Colour(0xff);
            currentTheme.textHighlight = Colour(0xff);
            currentTheme.textLink = Colour(0xff);

            currentTheme.buttonText = Colour(0xff);
            currentTheme.buttonBackground = Colour(0xff);
            currentTheme.buttonToggledText = Colour(0xff);
            currentTheme.buttonToggledBackground = Colour(0xff);
            currentTheme.buttonPressed = Colour(0xff);

            currentTheme.comboBoxActive = Colour(0xff);
            currentTheme.comboBoxHighlighted = Colour(0xff);
        }
        else if (themeName == "Oil")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff);
            currentTheme.pluginName = Colour(0xff);

            currentTheme.mainBackground = Colour(0xff);

            currentTheme.compFace = Colour(0xff);
            currentTheme.compHighlight = Colour(0xff);
            currentTheme.compBackground = Colour(0xff);

            currentTheme.groupBackground = Colour(0xff);

            currentTheme.textMain = Colour(0xff);
            currentTheme.textHighlight = Colour(0xff);
            currentTheme.textLink = Colour(0xff);

            currentTheme.buttonText = Colour(0xff);
            currentTheme.buttonBackground = Colour(0xff);
            currentTheme.buttonToggledText = Colour(0xff);
            currentTheme.buttonToggledBackground = Colour(0xff);
            currentTheme.buttonPressed = Colour(0xff);

            currentTheme.comboBoxActive = Colour(0xff);
            currentTheme.comboBoxHighlighted = Colour(0xff);
        }
        else if(themeName == "Curiosities")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff);
            currentTheme.pluginName = Colour(0xff);

            currentTheme.mainBackground = Colour(0xff);

            currentTheme.compFace = Colour(0xff);
            currentTheme.compHighlight = Colour(0xff);
            currentTheme.compBackground = Colour(0xff);

            currentTheme.groupBackground = Colour(0xff);

            currentTheme.textMain = Colour(0xff);
            currentTheme.textHighlight = Colour(0xff);
            currentTheme.textLink = Colour(0xff);

            currentTheme.buttonText = Colour(0xff);
            currentTheme.buttonBackground = Colour(0xff);
            currentTheme.buttonToggledText = Colour(0xff);
            currentTheme.buttonToggledBackground = Colour(0xff);
            currentTheme.buttonPressed = Colour(0xff);

            currentTheme.comboBoxActive = Colour(0xff);
            currentTheme.comboBoxHighlighted = Colour(0xff);
        }
        else if(themeName == "LemonLime")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff9fd943);
            currentTheme.pluginName = Colour(0xfff0fa37);

            currentTheme.mainBackground = Colour(0xff267049);

            currentTheme.compFace = Colour(0xff9fd943);
            currentTheme.compHighlight = Colour(0xfff0fa37);
            currentTheme.compBackground = Colour(0xff72b046);

            currentTheme.groupBackground = Colour(0xff28594f);

            currentTheme.textMain = Colour(0xfff0fa37);
            currentTheme.textHighlight = Colour(0xff9fd943);
            currentTheme.textLink = Colour(0xff28594f);

            currentTheme.buttonText = currentTheme.textMain;
            currentTheme.buttonBackground = currentTheme.compBackground;
            currentTheme.buttonToggledText = currentTheme.compFace;
            currentTheme.buttonToggledBackground = currentTheme.compHighlight;
            currentTheme.buttonPressed = currentTheme.compBackground.darker();

            currentTheme.comboBoxActive = currentTheme.groupBackground.darker();
            currentTheme.comboBoxHighlighted = currentTheme.groupBackground.brighter();
        }
        else if(themeName == "Yamazaki")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff);
            currentTheme.pluginName = Colour(0xff);

            currentTheme.mainBackground = Colour(0xff);

            currentTheme.compFace = Colour(0xff);
            currentTheme.compHighlight = Colour(0xff);
            currentTheme.compBackground = Colour(0xff);

            currentTheme.groupBackground = Colour(0xff);

            currentTheme.textMain = Colour(0xff);
            currentTheme.textHighlight = Colour(0xff);
            currentTheme.textLink = Colour(0xff);

            currentTheme.buttonText = Colour(0xff);
            currentTheme.buttonBackground = Colour(0xff);
            currentTheme.buttonToggledText = Colour(0xff);
            currentTheme.buttonToggledBackground = Colour(0xff);
            currentTheme.buttonPressed = Colour(0xff);

            currentTheme.comboBoxActive = Colour(0xff);
            currentTheme.comboBoxHighlighted = Colour(0xff);
        }
        else if(themeName == "IcyWitch")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff);
            currentTheme.pluginName = Colour(0xff);

            currentTheme.mainBackground = Colour(0xff);

            currentTheme.compFace = Colour(0xff);
            currentTheme.compHighlight = Colour(0xff);
            currentTheme.compBackground = Colour(0xff);

            currentTheme.groupBackground = Colour(0xff);

            currentTheme.textMain = Colour(0xff);
            currentTheme.textHighlight = Colour(0xff);
            currentTheme.textLink = Colour(0xff);

            currentTheme.buttonText = Colour(0xff);
            currentTheme.buttonBackground = Colour(0xff);
            currentTheme.buttonToggledText = Colour(0xff);
            currentTheme.buttonToggledBackground = Colour(0xff);
            currentTheme.buttonPressed = Colour(0xff);

            currentTheme.comboBoxActive = Colour(0xff);
            currentTheme.comboBoxHighlighted = Colour(0xff);
        }
        else if(themeName == "DontForget")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff);
            currentTheme.pluginName = Colour(0xff);

            currentTheme.mainBackground = Colour(0xff);

            currentTheme.compFace = Colour(0xff);
            currentTheme.compHighlight = Colour(0xff);
            currentTheme.compBackground = Colour(0xff);

            currentTheme.groupBackground = Colour(0xff);

            currentTheme.textMain = Colour(0xff);
            currentTheme.textHighlight = Colour(0xff);
            currentTheme.textLink = Colour(0xff);

            currentTheme.buttonText = Colour(0xff);
            currentTheme.buttonBackground = Colour(0xff);
            currentTheme.buttonToggledText = Colour(0xff);
            currentTheme.buttonToggledBackground = Colour(0xff);
            currentTheme.buttonPressed = Colour(0xff);

            currentTheme.comboBoxActive = Colour(0xff);
            currentTheme.comboBoxHighlighted = Colour(0xff);
        }
        else if(themeName == "Puffball")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff);
            currentTheme.pluginName = Colour(0xff);

            currentTheme.mainBackground = Colour(0xff);

            currentTheme.compFace = Colour(0xff);
            currentTheme.compHighlight = Colour(0xff);
            currentTheme.compBackground = Colour(0xff);

            currentTheme.groupBackground = Colour(0xff);

            currentTheme.textMain = Colour(0xff);
            currentTheme.textHighlight = Colour(0xff);
            currentTheme.textLink = Colour(0xff);

            currentTheme.buttonText = Colour(0xff);
            currentTheme.buttonBackground = Colour(0xff);
            currentTheme.buttonToggledText = Colour(0xff);
            currentTheme.buttonToggledBackground = Colour(0xff);
            currentTheme.buttonPressed = Colour(0xff);

            currentTheme.comboBoxActive = Colour(0xff);
            currentTheme.comboBoxHighlighted = Colour(0xff);
        }
        else if(themeName == "Violets")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff);
            currentTheme.pluginName = Colour(0xff);

            currentTheme.mainBackground = Colour(0xff);

            currentTheme.compFace = Colour(0xff);
            currentTheme.compHighlight = Colour(0xff);
            currentTheme.compBackground = Colour(0xff);

            currentTheme.groupBackground = Colour(0xff);

            currentTheme.textMain = Colour(0xff);
            currentTheme.textHighlight = Colour(0xff);
            currentTheme.textLink = Colour(0xff);

            currentTheme.buttonText = Colour(0xff);
            currentTheme.buttonBackground = Colour(0xff);
            currentTheme.buttonToggledText = Colour(0xff);
            currentTheme.buttonToggledBackground = Colour(0xff);
            currentTheme.buttonPressed = Colour(0xff);

            currentTheme.comboBoxActive = Colour(0xff);
            currentTheme.comboBoxHighlighted = Colour(0xff);
        }
        else
        {
            // DEFAULT
            // Pollen8
            // https://lospec.com/palette-list/pollen8
            currentTheme.themeId = themes.indexOf("Default");
            currentTheme.themeName = "Default";

            currentTheme.logo = Colour(0xffffa7a5);
            currentTheme.pluginName = Colour(0xffee6a7c);

            currentTheme.mainBackground = Colour(0xff73464c);

            currentTheme.compFace = Colour(0xffffa7a5);
            currentTheme.compHighlight = Colour(0xff72dcbb);
            currentTheme.compBackground = Colour(0xffee6a7c);

            currentTheme.groupBackground = Colour(0xffab5675);

            currentTheme.textMain = Colour(0xffffe7d6);
            currentTheme.textHighlight = Colour(0xffee6a7c);
            currentTheme.textLink = Colour(0xff72dcbb);

            currentTheme.buttonText = currentTheme.textMain;
            currentTheme.buttonBackground = currentTheme.compBackground;
            currentTheme.buttonToggledText = currentTheme.compFace;
            currentTheme.buttonToggledBackground = currentTheme.compHighlight;
            currentTheme.buttonPressed = currentTheme.compBackground.darker();

            currentTheme.comboBoxActive = currentTheme.groupBackground.darker();
            currentTheme.comboBoxHighlighted = currentTheme.groupBackground.brighter();
        }

        //DBG("ThemeManager: setTheme - ID - " << currentTheme.themeId);
        apvts.state.setProperty("ThemeId", currentTheme.themeId, nullptr);
    };
};

