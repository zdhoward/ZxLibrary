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

    Colour xyPadBackground;
};

class ThemeManager
{
public:
    ThemeManager(AudioProcessorValueTreeState& a) :
        apvts(a)
    {
        // Load theme from apvts
        int id = apvts.state.getProperty("ThemeId", 0);
        setThemeById(id);

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
        if (themeName == "InkPink")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xffffffff);
            currentTheme.pluginName = Colour(0xff87286a);

            currentTheme.mainBackground = Colour(0xff260d34);

            currentTheme.compFace = Colour(0xff87286a);
            currentTheme.compHighlight = Colour(0xffd03791);
            currentTheme.compBackground = Colour(0xff452459);

            currentTheme.groupBackground = currentTheme.mainBackground.darker();

            currentTheme.textMain = Colour(0xffffffff);
            currentTheme.textHighlight = Colour(0xffd03791);
            currentTheme.textLink = Colour(0xff260d34);

            currentTheme.buttonText = currentTheme.textMain;
            currentTheme.buttonBackground = currentTheme.compBackground;
            currentTheme.buttonToggledText = currentTheme.compFace;
            currentTheme.buttonToggledBackground = currentTheme.compHighlight;
            currentTheme.buttonPressed = currentTheme.compBackground.darker();

            currentTheme.comboBoxActive = currentTheme.groupBackground.darker();
            currentTheme.comboBoxHighlighted = currentTheme.groupBackground.brighter();

            currentTheme.xyPadBackground = currentTheme.compBackground;
        }
        else if (themeName == "Oil")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xfffbf5ef);
            currentTheme.pluginName = Colour(0xff8b6d9c);

            currentTheme.mainBackground = Colour(0xff494d7e);

            currentTheme.compFace = Colour(0xff8b6d9c);
            currentTheme.compHighlight = Colour(0xfff2d3ab);
            currentTheme.compBackground = Colour(0xff272744);

            currentTheme.groupBackground = currentTheme.compBackground.darker();

            currentTheme.textMain = Colour(0xfffbf5ef);
            currentTheme.textHighlight = Colour(0xfff2d3ab);
            currentTheme.textLink = Colour(0xff272744);

            currentTheme.buttonText = currentTheme.textMain;
            currentTheme.buttonBackground = currentTheme.compBackground;
            currentTheme.buttonToggledText = currentTheme.compFace;
            currentTheme.buttonToggledBackground = currentTheme.compHighlight;
            currentTheme.buttonPressed = currentTheme.compBackground.darker();

            currentTheme.comboBoxActive = currentTheme.groupBackground.darker();
            currentTheme.comboBoxHighlighted = currentTheme.groupBackground.brighter();

            currentTheme.xyPadBackground = currentTheme.compBackground;
        }
        else if(themeName == "Curiosities")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff00b9be);
            currentTheme.pluginName = Colour(0xffff6973);

            currentTheme.mainBackground = Colour(0xffffeecc);

            currentTheme.compFace = Colour(0xff00b9be);
            currentTheme.compHighlight = Colour(0xffff6973);
            currentTheme.compBackground = Colour(0xff15788c);

            currentTheme.groupBackground = Colour(0xffffb0a3);

            currentTheme.textMain = Colour(0xff46425e);
            currentTheme.textHighlight = Colour(0xffff6973);
            currentTheme.textLink = Colour(0xffffeecc);

            currentTheme.buttonText = currentTheme.mainBackground;
            currentTheme.buttonBackground = currentTheme.compHighlight;
            currentTheme.buttonToggledText = currentTheme.compFace;
            currentTheme.buttonToggledBackground = currentTheme.compHighlight;
            currentTheme.buttonPressed = currentTheme.compHighlight.darker();

            currentTheme.comboBoxActive = currentTheme.groupBackground.darker();
            currentTheme.comboBoxHighlighted = currentTheme.groupBackground.brighter();

            currentTheme.xyPadBackground = currentTheme.compBackground;
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

            currentTheme.xyPadBackground = currentTheme.compBackground;
        }
        else if(themeName == "Yamazaki")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xffd9c8be);
            currentTheme.pluginName = Colour(0xffc74061);

            currentTheme.mainBackground = Colour(0xff363a54);

            currentTheme.compFace = Colour(0xffc74061);
            currentTheme.compHighlight = Colour(0xffd699a0);
            currentTheme.compBackground = Colour(0xff8c7e7d);

            currentTheme.groupBackground = Colour(0xff843451);

            currentTheme.textMain = Colour(0xffd9c8be);
            currentTheme.textHighlight = Colour(0xff363a54);
            currentTheme.textLink = Colour(0xffc74061);

            currentTheme.buttonText = currentTheme.textMain;
            currentTheme.buttonBackground = currentTheme.compFace;
            currentTheme.buttonToggledText = currentTheme.compFace;
            currentTheme.buttonToggledBackground = currentTheme.compHighlight;
            currentTheme.buttonPressed = currentTheme.compFace.darker();

            currentTheme.comboBoxActive = currentTheme.groupBackground.darker();
            currentTheme.comboBoxHighlighted = currentTheme.groupBackground.brighter();

            currentTheme.xyPadBackground = currentTheme.compBackground;
        }
        else if(themeName == "IcyWitch")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xffecf3b0);
            currentTheme.pluginName = Colour(0xff4aa881);

            currentTheme.mainBackground = Colour(0xff32535f);

            currentTheme.compFace = Colour(0xff4aa881);
            currentTheme.compHighlight = Colour(0xff73efe8);
            currentTheme.compBackground = Colour(0xff0a777a);

            currentTheme.groupBackground = Colour(0xff313638);

            currentTheme.textMain = Colour(0xffecf3b0);
            currentTheme.textHighlight = Colour(0xff4aa881);
            currentTheme.textLink = Colour(0xff313638);

            currentTheme.buttonText = currentTheme.textMain;
            currentTheme.buttonBackground = currentTheme.compBackground;
            currentTheme.buttonToggledText = currentTheme.compFace;
            currentTheme.buttonToggledBackground = currentTheme.compHighlight;
            currentTheme.buttonPressed = currentTheme.compBackground.darker();

            currentTheme.comboBoxActive = currentTheme.groupBackground.darker();
            currentTheme.comboBoxHighlighted = currentTheme.groupBackground.brighter();

            currentTheme.xyPadBackground = currentTheme.compBackground;
        }
        else if(themeName == "DontForget")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xfff8e9e5);
            currentTheme.pluginName = Colour(0xfff5a1a1);

            currentTheme.mainBackground = Colour(0xff6f4367);

            currentTheme.compFace = Colour(0xfff5a1a1);
            currentTheme.compHighlight = Colour(0xffe76d8a);
            currentTheme.compBackground = Colour(0xffa69aca);

            currentTheme.groupBackground = Colour(0xff253657);

            currentTheme.textMain = Colour(0xfff8e9e5);
            currentTheme.textHighlight = Colour(0xffe76d8a);
            currentTheme.textLink = Colour(0xff253657);

            currentTheme.buttonText = currentTheme.textMain;
            currentTheme.buttonBackground = currentTheme.compBackground;
            currentTheme.buttonToggledText = currentTheme.compFace;
            currentTheme.buttonToggledBackground = currentTheme.compHighlight;
            currentTheme.buttonPressed = currentTheme.compBackground.darker();

            currentTheme.comboBoxActive = currentTheme.groupBackground.darker();
            currentTheme.comboBoxHighlighted = currentTheme.groupBackground.brighter();

            currentTheme.xyPadBackground = currentTheme.compBackground;
        }
        else if(themeName == "Puffball")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xffeedbc8);
            currentTheme.pluginName = Colour(0xffe0bb68);

            currentTheme.mainBackground = Colour(0xff548b71);

            currentTheme.compFace = Colour(0xffe0bb68);
            currentTheme.compHighlight = Colour(0xff97b34e);
            currentTheme.compBackground = Colour(0xffd58353);

            currentTheme.groupBackground = Colour(0xff5a473e);

            currentTheme.textMain = Colour(0xffeedbc8);
            currentTheme.textHighlight = Colour(0xff97b34e);
            currentTheme.textLink = Colour(0xff5a473e);

            currentTheme.buttonText = currentTheme.textMain;
            currentTheme.buttonBackground = currentTheme.compBackground;
            currentTheme.buttonToggledText = currentTheme.compFace;
            currentTheme.buttonToggledBackground = currentTheme.compHighlight;
            currentTheme.buttonPressed = currentTheme.compBackground.darker();

            currentTheme.comboBoxActive = currentTheme.groupBackground.darker();
            currentTheme.comboBoxHighlighted = currentTheme.groupBackground.brighter();

            currentTheme.xyPadBackground = currentTheme.compBackground;
        }
        else if(themeName == "Violets")
        {
            currentTheme.themeId = themes.indexOf(themeName);
            currentTheme.themeName = themeName;

            currentTheme.logo = Colour(0xff74d7e9);
            currentTheme.pluginName = Colour(0xff74d7e9);

            currentTheme.mainBackground = Colour(0xff2c2fa3);

            currentTheme.compFace = Colour(0xff74d7e9);
            currentTheme.compHighlight = Colour(0xffb343d1);
            currentTheme.compBackground = Colour(0xff4792eb);

            currentTheme.groupBackground = Colour(0xff2b0b76);

            currentTheme.textMain = Colour(0xff74d7e9);
            currentTheme.textHighlight = Colour(0xffb343d1);
            currentTheme.textLink = Colour(0xff2b0b76);

            currentTheme.buttonText = currentTheme.textMain;
            currentTheme.buttonBackground = currentTheme.compBackground;
            currentTheme.buttonToggledText = currentTheme.compFace;
            currentTheme.buttonToggledBackground = currentTheme.compHighlight;
            currentTheme.buttonPressed = currentTheme.compBackground.darker();

            currentTheme.comboBoxActive = currentTheme.groupBackground.darker();
            currentTheme.comboBoxHighlighted = currentTheme.groupBackground.brighter();

            currentTheme.xyPadBackground = currentTheme.compBackground;
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

            currentTheme.xyPadBackground = currentTheme.compBackground;
        }

        apvts.state.setProperty("ThemeId", currentTheme.themeId, nullptr);
    };
};

