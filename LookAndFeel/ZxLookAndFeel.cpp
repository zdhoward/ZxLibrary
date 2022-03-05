/*
  ==============================================================================

    ZxLookAndFeel.cpp
    Created: 23 Feb 2022 10:53:39am
    Author:  ZECHS

  ==============================================================================
*/

#include "ZxLookAndFeel.h"

//==============================================================================
// THEME CONFIG
//==============================================================================
//const float fontSize = 15.f;

ZxLookAndFeel::ZxLookAndFeel(AudioProcessorValueTreeState& apvts)
{
    themeManager = new ThemeManager(apvts);

    setColour(Slider::textBoxOutlineColourId, Colour(0x00));

    fontBlackgrounds = Typeface::createSystemTypefaceFor(BinaryData::BlackgroundsRegular_ttf, BinaryData::BlackgroundsRegular_ttfSize);

    fontUbuntuRegular = Typeface::createSystemTypefaceFor(BinaryData::UbuntuRegular_ttf, BinaryData::UbuntuRegular_ttfSize);
    fontUbuntuBold = Typeface::createSystemTypefaceFor(BinaryData::UbuntuBold_ttf, BinaryData::UbuntuBold_ttfSize);
    fontUbuntuItalic = Typeface::createSystemTypefaceFor(BinaryData::UbuntuItalic_ttf, BinaryData::UbuntuItalic_ttfSize);

    fontRegular = Font(fontUbuntuRegular);
    fontBold = Font(fontUbuntuBold);
    fontItalic = Font(fontUbuntuItalic);
    fontTitle = Font(fontBlackgrounds);

    //setDefaultSansSerifTypefaceName("Blackgrounds-Regular");
    //setDefaultSansSerifTypefaceName("Ubuntu Italic");
    //setDefaultSansSerifTypefaceName("Ubuntu Bold");
    setDefaultSansSerifTypefaceName("Ubuntu");
}

Font ZxLookAndFeel::getTitleFont()
{
    return fontTitle;
}

//================================================================================================
void ZxLookAndFeel::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    height -= fontSize * 4;
    const float radius = jmin(width / 2, height / 2) * 0.85f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f + fontSize * 2;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    float fwidth = (float)width;
    float fheight = (float)height;
    const float angle = rotaryStartAngle
        + sliderPos
        * (rotaryEndAngle - rotaryStartAngle);

    Theme theme = themeManager->getCurrentTheme();

    // Draw Title
    String title = slider.getName();
    g.setColour(theme.textMain);
    g.setFont(fontBold);
    g.drawFittedText(title, 0, 0, width, fontSize*2, Justification::centredBottom, 1, 1.f);

    // Draw BG Path
    g.setColour(theme.compBackground);
    Path filledArc;
    filledArc.addPieSegment(rx, ry, rw + 1, rw + 1, rotaryStartAngle, rotaryEndAngle, 0.6);
    g.fillPath(filledArc);

    // Draw Active Path
    g.setColour(theme.compFace);
    Path filledArc1;
    filledArc1.addPieSegment(rx, ry, rw + 1, rw + 1, rotaryStartAngle, angle, 0.6);
    g.fillPath(filledArc1);

    // Draw Thumb
    Path p;
    const float pointerLength = radius * 0.63f;
    const float pointerThickness = radius * 0.2f;
    p.addRectangle(-pointerThickness * 0.5f, -radius - 1, pointerThickness, pointerLength);
    p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
    g.setColour(theme.compHighlight);
    g.fillPath(p);

    // Draw Value
    auto textBounds = slider.getLocalBounds().removeFromBottom(fontSize * 2);
    g.setColour(theme.textMain);
    g.setFont(fontRegular);
    auto val = slider.getValue();
    if (slider.getTextValueSuffix() == "%")
        val = sliderPos * 100;
    String valStr = getDisplayValue(val, slider.getTextValueSuffix());
    slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 60, 20);
    if (!slider.isTextBoxEditable())
        g.drawFittedText(valStr, textBounds, Justification::centredTop, 1, 1.f);
}

//================================================================================================
void ZxLookAndFeel::drawGroupComponentOutline(Graphics& g, int w, int h, const String& text, const Justification& justification, GroupComponent& group)
{
    Theme theme = themeManager->getCurrentTheme();

    auto margins = 5.f;

    // Draw BG
    g.setColour(theme.groupBackground);
    g.setGradientFill(ColourGradient(theme.groupBackground, 0, 0, theme.groupBackground.darker(), 0, group.getHeight(), false));
    g.fillRoundedRectangle(0 + margins, 0 + margins, w - margins * 2, h - margins * 2, 10.f);

    g.setGradientFill(ColourGradient(theme.groupBackground, 0, group.getHeight(), theme.groupBackground.darker(), 0, 0, false));
    g.drawRoundedRectangle(0 + margins, 0 + margins, w - margins * 2, h - margins * 2, 10.f, 1.f);

    // Draw Text
    g.setColour(theme.textMain);
    g.setFont(fontBold);
    g.drawFittedText(group.getName(), 0 + margins , 0 + margins * 2, w - margins * 2, h - margins * 2, Justification::centredTop, 1, 1.f);
}

//================================================================================================
void ZxLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
    Theme theme = themeManager->getCurrentTheme();
    const float barWidth = 20.f;

    const float fwidth = width;
    const float fheight = slider.getLocalBounds().getHeight() - 10.f;

    const float centreX = width / 2.f - barWidth/2.f;
    const float centreY = y;

    const float botDisplacement = 20.f;
    const float topDisplacement = fontSize * 2 + 5.f;

    // Draw Title
    String title = slider.getName();
    g.setColour(theme.textMain);
    g.setFont(fontBold);
    g.drawFittedText(title, 0, 0, width, fontSize * 2, Justification::centredBottom, 1, 1.f);

    // Draw BG Path
    g.setColour(theme.compBackground);
    g.fillRect(centreX, topDisplacement, barWidth, fheight - botDisplacement - topDisplacement);

    // Draw Active Path
    g.setColour(theme.compFace);
    Path p;
    const float pointerLength = fheight - botDisplacement/2 - topDisplacement - ((fheight - botDisplacement/2 - topDisplacement) * (sliderPos / maxSliderPos));
    const float pointerThickness = barWidth;
    p.addRectangle(centreX, fheight - botDisplacement, pointerThickness, -pointerLength);
    g.fillPath(p);

    // Draw Thumb
    g.setColour(theme.compHighlight);
    g.fillRect(centreX-1.f, fheight - pointerLength - botDisplacement - 2.f, pointerThickness+2.f, 4.f);

    // Draw Value
    g.setColour(theme.textMain);
    g.setFont(fontRegular);
    auto val = slider.getValue();
    if (slider.getTextValueSuffix() == "%")
        val = sliderPos * 100;
    String valStr = getDisplayValue(slider.getValue(), slider.getTextValueSuffix());
    slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 60, 20);
    if (!slider.isTextBoxEditable())
        g.drawFittedText(valStr, 0, height, width,height - fontSize * 2, Justification::centredTop, 1, 1.f);
}

//================================================================================================
void ZxLookAndFeel::drawToggleButton(Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    Theme theme = themeManager->getCurrentTheme();

    const float margins = 5.f;

    const float height = fontSize * 2;
    const float width = button.getWidth() - margins * 2;

    const float x = 0.f + margins;
    const float y = button.getHeight() / 2 - height / 2;

    bool state = button.getToggleState();
    auto toggledOnBGColour = theme.compFace;
    auto toggledOffBGColour = theme.compHighlight;

    auto toggledOnTextColour = theme.compHighlight;
    auto toggledOffTextColour = theme.compFace;

    g.setColour(shouldDrawButtonAsDown ? theme.buttonPressed : state ? theme.buttonToggledBackground : theme.buttonBackground);
    g.fillRoundedRectangle(x, y, width, height, height / 2.f);

    g.setColour(state ? theme.buttonToggledText : theme.buttonText);
    g.setFont(fontBold);
    g.drawFittedText(button.getButtonText(), x, y, width, height, Justification::centred, 1);
}

void ZxLookAndFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    Theme theme = themeManager->getCurrentTheme();

    const float margins = 5.f;

    const float width = button.getWidth() - margins * 2;
    const float height = fontSize * 2;

    const float x = 0.f + margins;
    const float y = button.getHeight()/2 - height/2;

    g.setColour(shouldDrawButtonAsDown? theme.buttonPressed : theme.buttonBackground);
    g.fillRoundedRectangle(x, y, width, height, height / 2.f);

    g.setColour(theme.buttonText);
    g.setFont(fontBold);
    g.drawFittedText(button.getButtonText(), x, y, width, height, Justification::centred, 1);
}

//================================================================================================
void ZxLookAndFeel::drawComboBox(Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& comboBox)
{
    Theme theme = themeManager->getCurrentTheme();

    const float fwidth = width;
    const float fheight = height;

    const float margins = 0.f;

    g.setColour(theme.groupBackground);
    Rectangle<int> r = Rectangle<int>(0.f + margins, fheight / 2 - fontSize, fwidth - margins * 2, fontSize * 2.f);
    g.fillRect(r);

    g.setColour(theme.compFace);
    Rectangle<int> arrowBounds = r.removeFromRight(r.getHeight());
    arrowBounds.removeFromTop(10);
    arrowBounds.removeFromRight(10);
    arrowBounds.removeFromBottom(10);
    arrowBounds.removeFromLeft(10);
    Path tri;
    tri.addTriangle(arrowBounds.getX(), arrowBounds.getY(), arrowBounds.getX() + 10.f, arrowBounds.getY(), arrowBounds.getX() + 5.f, arrowBounds.getY() + 10.f);
    g.fillPath(tri);


    comboBox.setTextWhenNothingSelected(comboBox.getName());
}

void ZxLookAndFeel::drawPopupMenuItem(Graphics& g, const Rectangle< int >& area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, 
    const String& text, const String& shortcutKeyText, const Drawable* icon, const Colour* textColour)
{
    Theme theme = themeManager->getCurrentTheme();

    const float margins = 5.f;
    auto newArea = Rectangle<int>(area.getPosition().getX() + margins, area.getPosition().getY(), area.getWidth() - margins * 2, area.getHeight());

    g.setColour(theme.comboBoxActive);
    if (isTicked)
        g.fillRect(area);

    g.setColour(theme.comboBoxHighlighted);
    if (isHighlighted)
        g.fillRect(area);

    g.setColour(theme.textMain);
    g.drawFittedText(text, newArea, Justification::centredLeft, 1);
}

void ZxLookAndFeel::getIdealPopupMenuItemSize(const String& text, bool isSeparator, int standardMenuItemHeight, int& idealWidth, int& idealHeight)
{
    idealHeight = fontSize * 2;
}

void ZxLookAndFeel::drawPopupMenuBackground(Graphics& g, int width, int height)
{
    Theme theme = themeManager->getCurrentTheme();

    g.setColour(theme.groupBackground);
    g.fillAll();
}

void ZxLookAndFeel::drawDrawableButton(Graphics& g, DrawableButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    Theme theme = themeManager->getCurrentTheme();

    g.setColour(theme.groupBackground);

    if (shouldDrawButtonAsHighlighted)
        g.setColour(theme.groupBackground.brighter());

    if (shouldDrawButtonAsDown)
        g.setColour(theme.groupBackground.darker());

    g.fillAll();

    g.setColour(theme.groupBackground.darker());
    g.fillRect(button.getWidth() - 1, 0, 1, button.getHeight());

    g.setColour(theme.textMain);
    g.drawFittedText(button.getButtonText(), 0, 0, button.getWidth(), button.getHeight(), Justification::centredBottom, 1);
}