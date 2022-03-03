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

    Label theme2Label;
    ComboBox theme2ComboBox;

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

        addAndMakeVisible(theme2Label);
        theme2Label.setText("Theme2: ", NotificationType::dontSendNotification);
        theme2Label.setJustificationType(Justification::centredRight);

        addAndMakeVisible(theme2ComboBox);
        theme2ComboBox.addItemList(lnf.themeManager->getAllThemes(), 1);
        theme2ComboBox.onChange = [&] {
            int valIndex = theme2ComboBox.getSelectedItemIndex();
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
        Theme2 theme2 = lnf.themeManager->getCurrentTheme();
        g.fillAll(theme2.mainBackground);
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
        theme2Label .setBounds(iBounds.removeFromLeft(iBounds.getWidth() / 2));
        theme2ComboBox.setBounds(iBounds);

        bounds.removeFromTop(5);

        iBounds = bounds.removeFromTop(30);
        resetFactoryPresetsButton.setBounds(iBounds);

    };

    void updateFields()
    {
        Theme2 theme2 = lnf.themeManager->getCurrentTheme();

        int themeId = (int)apvts.state.getProperty("Theme");
        
        theme2ComboBox.setSelectedItemIndex(lnf.themeManager->getCurrentThemeId(), true);
        
        int oversamplingId = (int)apvts.state.getProperty("Oversampling");
        oversamplingComboBox.setSelectedId(oversamplingId);

        oversamplingLabel.setColour(oversamplingLabel.textColourId, theme2.textMain);
        oversamplingComboBox.setColour(oversamplingComboBox.textColourId, theme2.textMain);

        theme2ComboBox.setColour(theme2ComboBox.textColourId, theme2.textMain);
        theme2Label.setColour(theme2Label.textColourId, theme2.textMain);
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

        Theme2 theme2 = lnf.themeManager->getCurrentTheme();

        addAndMakeVisible(companyName);
        companyName.setText("ZxTools", NotificationType::dontSendNotification);
        companyName.setColour(companyName.textColourId, theme2.textMain);

        addAndMakeVisible(companyEmail);
        companyEmail.setText("@gmail.com", NotificationType::dontSendNotification);
        companyEmail.setColour(companyEmail.textColourId, theme2.textMain);

        addAndMakeVisible(companyGithub);
        companyGithub.setText("https://github.com/zdhoward", NotificationType::dontSendNotification);
        companyGithub.setColour(companyGithub.textColourId, theme2.textMain);

        addAndMakeVisible(companyWebsite);
        companyWebsite.setText("https://zdhoward.github.io/ZxTools/", NotificationType::dontSendNotification);
        companyWebsite.setColour(companyWebsite.textColourId, theme2.textMain);

        addAndMakeVisible(bio);
        bio.setMultiLine(true, true);
        bio.setEnabled(false);
        bio.setColour(bio.outlineColourId, Colour(0x00));
        bio.setColour(bio.backgroundColourId, theme2.mainBackground);
        bio.setColour(bio.textColourId, theme2.textMain);
        bio.setText("My name is Zach and I like to make VSTs", NotificationType::dontSendNotification);
    };
    ~AboutSettingsComponent() { };

    void paint(Graphics& g) override 
    { 
        Theme2 theme2 = lnf.themeManager->getCurrentTheme();
        g.fillAll(theme2.mainBackground);
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
        Theme2 theme2 = lnf.themeManager->getCurrentTheme();
        g.setColour(theme2.groupBackground);
        g.fillAll();

        g.setColour(theme2.groupBackground.brighter());
        g.fillRect(0, getButtonSize() + 4, getWidth(), 1);

        //g.setColour(Colours::black);
        //g.fillRect(0, 0, getWidth(), getHeight());
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPanel)
};