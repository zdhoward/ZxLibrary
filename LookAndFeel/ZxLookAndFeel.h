/*
  ==============================================================================

    ZxLookAndFeel.h
    Created: 23 Feb 2022 10:54:01am
    Author:  ZECHS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Services/ThemeManager.h"

class ZxLookAndFeel : public LookAndFeel_V4
{
public:
    ZxLookAndFeel(AudioProcessorValueTreeState& apvts);
    ~ZxLookAndFeel() { themeManager = nullptr; };

    ScopedPointer<ThemeManager> themeManager;

    static Colour getBGColour();
    static Colour getPluginNameColour();
    static Colour getTitleColour();

    Font getTitleFont();

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height, 
        float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider&) override;

    void drawGroupComponentOutline(Graphics& g, int w, int h, const String& text, const Justification&, GroupComponent&) override;

    void drawToggleButton(Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    void drawButtonBackground(Graphics& g, Button& button, const Colour &backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    void drawButtonText(Graphics& g, TextButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override {};

    void drawComboBox(Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& comboBox) override;

    void drawPopupMenuItem(Graphics& g, const Rectangle< int >& area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String& text, const String& shortcutKeyText, const Drawable* icon, const Colour* textColour) override;

    void getIdealPopupMenuItemSize(const String& text, bool isSeparator, int standardMenuItemHeight, int& idealWidth, int& idealHeight) override;

    void drawPopupMenuBackground(Graphics& g, int width, int height) override;

    void drawDrawableButton(Graphics& g, DrawableButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    Typeface::Ptr fontBlackgrounds;
    Typeface::Ptr fontUbuntuRegular;
    Typeface::Ptr fontUbuntuBold;
    Typeface::Ptr fontUbuntuItalic;

    Font fontRegular;
    Font fontBold;
    Font fontItalic;
    Font fontTitle;

    String getDisplayValue(double val, String suffix = "", int precision = 2)
    {
        String valStr = "";
        bool addk = false;
        
        if (val > 999.f)
        {
            addk = true;
            val /= 1000.f;
        }

        double precisionMult = std::pow(10.0, precision);
        double vdouble = val * precisionMult;
        int vint = vdouble;
        vdouble = vint / precisionMult;

        valStr << String(vdouble);
        if (suffix != "" && suffix != "%")
            valStr << " ";

        if (addk)
            valStr << "k";

        valStr << suffix;

        return valStr;
    }
};