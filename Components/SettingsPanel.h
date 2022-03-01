/*
  ==============================================================================

    SettingsPanel.h
    Created: 28 Feb 2022 8:54:51am
    Author:  ZECHS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SettingsPanel;

struct GeneralSettingsComponent : public Component
{
    Label oversamplingLabel;
    ComboBox oversamplingComboBox;

    Label themeLabel;
    ComboBox themeComboBox;

    ZxLookAndFeel& lnf;

    GeneralSettingsComponent(ZxLookAndFeel &l, AudioProcessorEditor& p, AudioProcessorValueTreeState& apvts) :
        lnf(l)
    { 
        addAndMakeVisible(oversamplingLabel);
        oversamplingLabel.setText("Oversampling: ", NotificationType::dontSendNotification);
        //oversamplingLabel.setColour(oversamplingLabel.textColourId, lnf.theme.mainText);


        //oversamplingComboBox.setColour(oversamplingComboBox.textColourId, lnf.theme.mainText);
        //oversamplingComboBox.setColour(oversamplingComboBox.backgroundColourId, lnf.theme.bgGroup);
        //oversamplingComboBox.setColour(oversamplingComboBox.outlineColourId, Colour(0x00));

        addAndMakeVisible(oversamplingComboBox);
        StringArray items{
            "None",
            "2x",
            "4x",
            "8x",
            "16x"
        };
        oversamplingComboBox.addItemList(items, 1);
        int oversamplingId = (int)apvts.state.getProperty("Oversampling");
        oversamplingComboBox.setSelectedId(oversamplingId);
        oversamplingComboBox.onChange = [&] {
            apvts.state.setProperty("Oversampling", oversamplingComboBox.getSelectedId(), nullptr);
        };
        

        addAndMakeVisible(themeLabel);
        themeLabel.setText("Theme: ", NotificationType::dontSendNotification);
        //themeLabel.setColour(themeLabel.textColourId, lnf.theme.mainText);

        addAndMakeVisible(themeComboBox);
        items = {};
        for (int i = static_cast<Themes>(0); i != Themes::END; i++)
        {
            auto item = static_cast<Themes>(i);
            if (item != END)
                items.add(GetThemes().at(item));
        }
        themeComboBox.addItemList(items, 1);
        themeComboBox.onChange = [&] {
            int valIndex = themeComboBox.getSelectedId() - 1;
            Themes theme = static_cast<Themes>(valIndex);

            lnf.setTheme(theme);
            p.repaint();
            repaint();
        };
        themeComboBox.setText(GetThemes().at(lnf.theme.getTheme()), true);
        //themeComboBox.setColour(themeComboBox.textColourId, lnf.theme.mainText);
        //themeComboBox.setColour(themeComboBox.backgroundColourId, lnf.theme.bgGroup);
        //themeComboBox.setColour(themeComboBox.outlineColourId, Colour(0x00));
    };
    ~GeneralSettingsComponent() { };

    void paint(Graphics& g) override 
    { 
        g.fillAll(lnf.theme.bgMain); 
    };

    void resized() override 
    {
        auto bounds = getLocalBounds();
        bounds.removeFromTop(5);
        bounds.removeFromRight(5);
        bounds.removeFromBottom(5);
        bounds.removeFromLeft(5);

        auto iBounds = bounds.removeFromTop(30);
        oversamplingLabel.setBounds(iBounds.removeFromLeft(iBounds.getWidth() / 2));
        oversamplingComboBox.setBounds(iBounds);

        bounds.removeFromTop(5);

        iBounds = bounds.removeFromTop(30);
        themeLabel .setBounds(iBounds.removeFromLeft(iBounds.getWidth() / 2));
        themeComboBox.setBounds(iBounds);
    };
};

struct AboutSettingsComponent : public Component
{
    Label companyName, companyEmail, companyGithub, companyWebsite;
    TextEditor bio;

    ZxLookAndFeel& lnf;

    AboutSettingsComponent(ZxLookAndFeel& l, AudioProcessorEditor& p) :
        lnf(l)
    { 
        addAndMakeVisible(companyName);
        companyName.setText("ZxTools", NotificationType::dontSendNotification);

        addAndMakeVisible(companyEmail);
        companyEmail.setText("ZxTools@gmail.com", NotificationType::dontSendNotification);

        addAndMakeVisible(companyGithub);
        companyGithub.setText("http://github.com/zdhoward", NotificationType::dontSendNotification);

        addAndMakeVisible(companyWebsite);
        companyWebsite.setText("http://github.com/zdhoward", NotificationType::dontSendNotification);

        addAndMakeVisible(bio);
        bio.setText("My name is Zach and I like to make VSTs", NotificationType::dontSendNotification);
        bio.setMultiLine(true, true);
        bio.setEnabled(false);
        bio.setColour(bio.outlineColourId, Colour(0x00));
        bio.setColour(bio.backgroundColourId, lnf.theme.bgMain);
        bio.setColour(bio.textColourId, lnf.theme.mainText);
    };
    ~AboutSettingsComponent() { };

    void paint(Graphics& g) override 
    { 
        g.fillAll(lnf.theme.bgMain);
    };

    void resized() override 
    {
        auto bounds = getLocalBounds();
        bounds.removeFromTop(5);
        bounds.removeFromRight(5);
        bounds.removeFromBottom(5);
        bounds.removeFromLeft(5);

        companyName.setBounds(bounds.removeFromTop(20));
        bounds.removeFromTop(5);

        companyEmail.setBounds(bounds.removeFromTop(20));
        bounds.removeFromTop(5);

        companyGithub.setBounds(bounds.removeFromTop(20));
        bounds.removeFromTop(5);

        companyWebsite.setBounds(bounds.removeFromTop(20));
        bounds.removeFromTop(5);

        bio.setBounds(bounds);
    };
};


//==============================================================================
/*
*/
class SettingsPanel  : public PreferencesPanel
{
    Label pageTitle;

    ZxLookAndFeel& lnf;
    AudioProcessorEditor& ape;
    AudioProcessorValueTreeState& apvts;

public:
    SettingsPanel(ZxLookAndFeel& l, AudioProcessorEditor& p, AudioProcessorValueTreeState& a) :
        lnf(l),
        ape(p),
        apvts(a)
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

        addSettingsPage("General", BinaryData::settingsicon_png, BinaryData::settingsicon_pngSize);
        addSettingsPage("About", BinaryData::settingsicon_png, BinaryData::settingsicon_pngSize);

        setButtonSize(50);

        setCurrentPage("General");
    }

    ~SettingsPanel() override
    {
    }

    Component* createComponentForPage(const String& pageName) override
    {
        if (pageName == "General")
        {
            setSize(200, 200);
            return new GeneralSettingsComponent(lnf, ape, apvts);
            //return &general;
        }
        else if (pageName == "About")
        {
            setSize(200, 400);
            return new AboutSettingsComponent(lnf, ape);
        }
        else {
            return new Component();
        }
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPanel)
};