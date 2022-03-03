/*
  ==============================================================================

    ColourPalette.h
    Created: 23 Feb 2022 10:52:09am
    Author:  ZECHS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

enum Themes 
{
    Default,
    InkPink,
    Oil,
    Curiosities,
    LemonLime,
    Yamazaki,
    IcyWitch,
    DontForget,
    Puffball,
    Violets,
    END // FOR ITERATION ONLY
};

inline const std::map<Themes, String>& GetThemes()
{
    static std::map<Themes, String> items =
    {
        {Default, "Default"},
        {InkPink,"InkPink"},
        {Oil,"Oil"},
        {Curiosities,"Curiosities"},
        {LemonLime,"LemonLime"},
        {Yamazaki,"Yamazaki"},
        {IcyWitch,"IcyWitch"},
        {DontForget,"DontForget"},
        {Puffball ,"Puffball"},
        {Violets,"Violets"},
    };

    return items;
};

struct Theme
{
    Colour bgMain;
    Colour bgGroup;
    Colour bgComponent;

    Colour compFace;
    Colour compHighlight;

    Colour mainText;
    Colour invertedText;
    Colour altText;
    Colour titleText;

    Themes currentTheme;

    AudioProcessorValueTreeState& apvts;

    Theme(AudioProcessorValueTreeState& a) :
        apvts(a)
    {
        setTheme(Default);
    }

    Themes getTheme()
    {
        return currentTheme;
    }

    void setTheme(Themes themeName)
    {
        currentTheme = themeName;

        apvts.state.setProperty("Theme", (int)currentTheme, nullptr);

        if (themeName == InkPink)
        {
            // https://lospec.com/palette-list/inkpink
        //========================================================
            bgMain = Colour(0xff260d34);
            bgGroup = bgMain.darker();
            bgComponent = Colour(0xff452459);

            compFace = Colour(0xff87286a);
            compHighlight = Colour(0xffd03791);

            mainText = Colour(0xffffffff);
            invertedText = Colour(0xff260d34);
            altText = Colour(0xffd03791);
            titleText = Colour(0xffffffff);
        }
        else
        if (themeName == Oil)
        {
            // https://lospec.com/palette-list/oil-6
        //========================================================
            bgMain = Colour(0xff494d7e);
            bgGroup = Colour(0xff272744).darker();
            bgComponent = Colour(0xff272744);

            compFace = Colour(0xff8b6d9c);
            compHighlight = Colour(0xfff2d3ab);

            mainText = Colour(0xfffbf5ef);
            invertedText = Colour(0xff272744);
            altText = Colour(0xfff2d3ab);
            titleText = Colour(0xfffbf5ef);
        }
        else
        if (themeName == Curiosities)
        {
            // https://lospec.com/palette-list/curiosities
        //========================================================
            bgMain = Colour(0xffffeecc);
            bgGroup = Colour(0xffffb0a3);
            bgComponent = Colour(0xff15788c);

            compFace = Colour(0xff00b9be);
            compHighlight = Colour(0xffff6973);

            mainText = Colour(0xff46425e);
            invertedText = Colour(0xffffeecc);
            altText = Colour(0xffff6973);
            titleText = Colour(0xffff6973);
        }
        else
        if (themeName == LemonLime)
        {
            // https://lospec.com/palette-list/green-top-down
        //========================================================
            bgMain = Colour(0xff267049);
            bgGroup = Colour(0xff28594f);
            bgComponent = Colour(0xff72b046);

            compFace = Colour(0xff9fd943);
            compHighlight = Colour(0xfff0fa37);

            mainText = Colour(0xfff0fa37);
            invertedText = Colour(0xff28594f);
            altText = Colour(0xff9fd943);
            titleText = Colour(0xfff0fa37);
        }
        else
        if (themeName == Yamazaki)
        {
            // https://lospec.com/palette-list/yamazaki
        //========================================================
            bgMain = Colour(0xff363a54);
            bgGroup = Colour(0xff843451);
            bgComponent = Colour(0xff8c7e7d);

            compFace = Colour(0xffc74061);
            compHighlight = Colour(0xffd699a0);

            mainText = Colour(0xffd9c8be);
            invertedText = Colour(0xff363a54);
            altText = Colour(0xffc74061);
            titleText = Colour(0xffd9c8be);
        }
        else
        if (themeName == IcyWitch)
        {
            // https://lospec.com/palette-list/icywitch
        //========================================================
            bgMain = Colour(0xff32535f);
            bgGroup = Colour(0xff313638);
            bgComponent = Colour(0xff0a777a);

            compFace = Colour(0xff4aa881);
            compHighlight = Colour(0xff73efe8);

            mainText = Colour(0xffecf3b0);
            invertedText = Colour(0xff313638);
            altText = Colour(0xff4aa881);
            titleText = Colour(0xffecf3b0);
        }
        else
        if (themeName == DontForget)
        {
            // https://lospec.com/palette-list/dnot-froget
        //========================================================
            bgMain = Colour(0xff6f4367);
            bgGroup = Colour(0xff253657);
            bgComponent = Colour(0xffa69aca);

            compFace = Colour(0xfff5a1a1);
            compHighlight = Colour(0xffe76d8a);

            mainText = Colour(0xfff8e9e5);
            invertedText = Colour(0xff253657);
            altText = Colour(0xffe76d8a);
            titleText = Colour(0xfff8e9e5);
        }
        else
        if (themeName == Puffball)
        {
            // https://lospec.com/palette-list/puffball-8
        //========================================================
            bgMain = Colour(0xff548b71);
            bgGroup = Colour(0xff5a473e);
            bgComponent = Colour(0xffd58353);

            compFace = Colour(0xffe0bb68);
            compHighlight = Colour(0xff97b34e);

            mainText = Colour(0xffeedbc8);
            invertedText = Colour(0xff5a473e);
            altText = Colour(0xff97b34e);
            titleText = Colour(0xffeedbc8);
        }
        else
        if (themeName == Violets)
        {
            // https://lospec.com/palette-list/6-violets
        //========================================================
            bgMain = Colour(0xff2c2fa3);
            bgGroup = Colour(0xff2b0b76);
            bgComponent = Colour(0xff4792eb);

            compFace = Colour(0xff74d7e9);
            compHighlight = Colour(0xffb343d1);

            mainText = Colour(0xff74d7e9);
            invertedText = Colour(0xff2b0b76);
            altText = Colour(0xffb343d1);
            titleText = Colour(0xff74d7e9);
        }
        else
        {
            // Default
            //========================================================
            bgMain = Colours::black;
            bgGroup = Colours::darkgrey;
            bgComponent = Colours::grey;

            compFace = Colours::lightgrey;
            compHighlight = Colours::white;

            mainText = Colours::white;
            invertedText = Colours::black;
            altText = Colours::dimgrey;
            titleText = Colours::lightslategrey;
        }
    }
};