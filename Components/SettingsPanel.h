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

    TextButton resetFactoryPresetsButton;

    AudioProcessorValueTreeState& apvts;
    AudioProcessorEditor& ape;

    ZxLookAndFeel& lnf;

    GeneralSettingsComponent(ZxLookAndFeel& l, AudioProcessorEditor& p, AudioProcessorValueTreeState& a) :
        lnf(l),
        apvts(a),
        ape(p)
    { 
        setLookAndFeel(&lnf);
        addAndMakeVisible(oversamplingLabel);
        oversamplingLabel.setText("Oversampling: ", NotificationType::dontSendNotification);
        oversamplingLabel.setJustificationType(Justification::centredRight);

        addAndMakeVisible(oversamplingComboBox);
        StringArray items{
            "None",
            "2x",
            "4x",
            "8x",
            "16x"
        };
        oversamplingComboBox.addItemList(items, 1);
        oversamplingComboBox.onChange = [&] {
            apvts.state.setProperty("Oversampling", oversamplingComboBox.getSelectedId(), nullptr);
            updateFields();
        };

        addAndMakeVisible(resetFactoryPresetsButton);
        resetFactoryPresetsButton.setButtonText("Reset Factory Presets");

        addAndMakeVisible(themeLabel);
        themeLabel.setText("Theme: ", NotificationType::dontSendNotification);
        themeLabel.setJustificationType(Justification::centredRight);

        addAndMakeVisible(themeComboBox);
        themeComboBox.addItemList(lnf.themeManager->getAllThemes(), 1);
        themeComboBox.onChange = [&] {
            int valIndex = themeComboBox.getSelectedItemIndex();
            lnf.themeManager->setThemeById(valIndex);

            p.repaint();
            repaint();
            updateFields();
        };

        updateFields();
    };
    ~GeneralSettingsComponent() { };

    void paint(Graphics& g) override 
    { 
        Theme theme = lnf.themeManager->getCurrentTheme();
        g.fillAll(theme.mainBackground);
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

        bounds.removeFromTop(5);

        iBounds = bounds.removeFromTop(30);
        resetFactoryPresetsButton.setBounds(iBounds);

    };

    void updateFields()
    {
        Theme theme = lnf.themeManager->getCurrentTheme();

        int themeId = (int)apvts.state.getProperty("Theme");
        
        themeComboBox.setSelectedItemIndex(lnf.themeManager->getCurrentThemeId(), true);
        
        int oversamplingId = (int)apvts.state.getProperty("Oversampling");
        oversamplingComboBox.setSelectedId(oversamplingId);

        oversamplingLabel.setColour(oversamplingLabel.textColourId, theme.textMain);
        oversamplingComboBox.setColour(oversamplingComboBox.textColourId, theme.textMain);

        themeComboBox.setColour(themeComboBox.textColourId, theme.textMain);
        themeLabel.setColour(themeLabel.textColourId, theme.textMain);
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
        setLookAndFeel(&lnf);

        Theme theme = lnf.themeManager->getCurrentTheme();

        addAndMakeVisible(companyName);
        companyName.setText("ZxTools", NotificationType::dontSendNotification);
        companyName.setColour(companyName.textColourId, theme.textMain);

        addAndMakeVisible(companyEmail);
        companyEmail.setText("@gmail.com", NotificationType::dontSendNotification);
        companyEmail.setColour(companyEmail.textColourId, theme.textMain);

        addAndMakeVisible(companyGithub);
        companyGithub.setText("https://github.com/zdhoward", NotificationType::dontSendNotification);
        companyGithub.setColour(companyGithub.textColourId, theme.textMain);

        addAndMakeVisible(companyWebsite);
        companyWebsite.setText("https://zdhoward.github.io/ZxTools/", NotificationType::dontSendNotification);
        companyWebsite.setColour(companyWebsite.textColourId, theme.textMain);

        addAndMakeVisible(bio);
        bio.setMultiLine(true, true);
        bio.setEnabled(false);
        bio.setColour(bio.outlineColourId, Colour(0x00));
        bio.setColour(bio.backgroundColourId, theme.mainBackground);
        bio.setColour(bio.textColourId, theme.textMain);
        bio.setText("My name is Zach and I like to make VSTs", NotificationType::dontSendNotification);
    };
    ~AboutSettingsComponent() { };

    void paint(Graphics& g) override 
    { 
        Theme theme = lnf.themeManager->getCurrentTheme();
        g.fillAll(theme.mainBackground);
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

    GeneralSettingsComponent* generalComp;
    AboutSettingsComponent* aboutComp;

public:
    SettingsPanel(ZxLookAndFeel& l, AudioProcessorEditor& p, AudioProcessorValueTreeState& a) :
        lnf(l),
        ape(p),
        apvts(a)
    {
        //generalComp = new GeneralSettingsComponent(lnf, ape, apvts);
        //aboutComp = new AboutSettingsComponent(lnf, ape);

        setLookAndFeel(&lnf);
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

        addSettingsPage("General", BinaryData::settingsicon_png, BinaryData::settingsicon_pngSize);
        addSettingsPage("About", BinaryData::settingsicon_png, BinaryData::settingsicon_pngSize);

        setButtonSize(50);

        setCurrentPage("General");
    }

    ~SettingsPanel() override
    {
        //generalComp = nullptr;
        //aboutComp = nullptr;
        //delete generalComp;
        //delete aboutComp;
    }

    Component* SettingsPanel::createComponentForPage(const String& pageName) override
    {
        if (pageName == "General")
        {
            setSize(250, 165);
            generalComp = new GeneralSettingsComponent(lnf, ape, apvts);
            generalComp->updateFields();
            return generalComp;
        }
        else if (pageName == "About")
        {
            setSize(250, 200);
            aboutComp = new AboutSettingsComponent(lnf, ape);
            return aboutComp;
        }
        else {
            return new Component();
        }
    }

    void SettingsPanel::paint(Graphics& g) override
    {
        Theme theme = lnf.themeManager->getCurrentTheme();
        g.setColour(theme.groupBackground);
        g.fillAll();

        g.setColour(theme.groupBackground.brighter());
        g.fillRect(0, getButtonSize() + 4, getWidth(), 1);

        //g.setColour(Colours::black);
        //g.fillRect(0, 0, getWidth(), getHeight());
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPanel)
};