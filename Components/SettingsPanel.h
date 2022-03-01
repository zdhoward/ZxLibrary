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
        

        addAndMakeVisible(themeLabel);
        themeLabel.setText("Theme: ", NotificationType::dontSendNotification);
        themeLabel.setJustificationType(Justification::centredRight);

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
            Themes theme = (Themes)valIndex;

            lnf.setTheme(theme);
            p.repaint();
            repaint();
            updateFields();
        };
        //int themeId = (int)apvts.state.getProperty("Theme");
        //themeComboBox.setText(GetThemes().at((Themes)themeId), true);

        //themeComboBox.setText(GetThemes().at(lnf.theme.getTheme()), true);

        //auto th = lnf.theme.getTheme();
        //int thProp = apvts.state.getProperty("Theme");
        //auto thName = GetThemes().at((Themes)thProp);
        //DBG("Theme Name: " << thName);
        
         
        //
        //themeComboBox.setColour(themeComboBox.backgroundColourId, lnf.theme.bgGroup);
        //themeComboBox.setColour(themeComboBox.outlineColourId, Colour(0x00));

        updateFields();
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

    void updateFields()
    {
        int themeId = (int)apvts.state.getProperty("Theme");
        themeComboBox.setText(GetThemes().at((Themes)themeId), true);
        
        int oversamplingId = (int)apvts.state.getProperty("Oversampling");
        oversamplingComboBox.setSelectedId(oversamplingId);

        oversamplingLabel.setColour(oversamplingLabel.textColourId, lnf.theme.mainText);
        themeLabel.setColour(themeLabel.textColourId, lnf.theme.mainText);

        oversamplingComboBox.setColour(themeComboBox.textColourId, lnf.theme.mainText);
        themeComboBox.setColour(themeComboBox.textColourId, lnf.theme.mainText);
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

        addAndMakeVisible(companyName);
        companyName.setText("ZxTools", NotificationType::dontSendNotification);
        companyName.setColour(companyName.textColourId, lnf.theme.mainText);

        addAndMakeVisible(companyEmail);
        companyEmail.setText("@gmail.com", NotificationType::dontSendNotification);
        companyEmail.setColour(companyEmail.textColourId, lnf.theme.mainText);

        addAndMakeVisible(companyGithub);
        companyGithub.setText("https://github.com/zdhoward", NotificationType::dontSendNotification);
        companyGithub.setColour(companyGithub.textColourId, lnf.theme.mainText);

        addAndMakeVisible(companyWebsite);
        companyWebsite.setText("https://zdhoward.github.io/ZxTools/", NotificationType::dontSendNotification);
        companyWebsite.setColour(companyWebsite.textColourId, lnf.theme.mainText);

        addAndMakeVisible(bio);
        bio.setMultiLine(true, true);
        bio.setEnabled(false);
        bio.setColour(bio.outlineColourId, Colour(0x00));
        bio.setColour(bio.backgroundColourId, lnf.theme.bgMain);
        bio.setColour(bio.textColourId, lnf.theme.mainText);
        bio.setText("My name is Zach and I like to make VSTs", NotificationType::dontSendNotification);
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

//struct SplashSettingsComponent : public Component
//{
//    ZxLookAndFeel& lnf;
//
//    SplashSettingsComponent(ZxLookAndFeel& l, AudioProcessorEditor& p) :
//        lnf(l)
//    {
//        setLookAndFeel(&lnf);
//    };
//    ~SplashSettingsComponent() {};
//
//    void paint(Graphics& g) override
//    {
//        g.fillAll(Colours::black);//lnf.theme.bgMain);
//    };
//
//    void resized() override
//    {
//
//    }
//};


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
        setLookAndFeel(&lnf);
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

        addSettingsPage("General", BinaryData::settingsicon_png, BinaryData::settingsicon_pngSize);
        addSettingsPage("About", BinaryData::settingsicon_png, BinaryData::settingsicon_pngSize);

        setButtonSize(50);

        setCurrentPage("General");
        //setCurrentPage("Splash");

        //setSize(250, 250);
    }

    ~SettingsPanel() override
    {
    }

    Component* SettingsPanel::createComponentForPage(const String& pageName) override
    {
        if (pageName == "General")
        {
            //setSize(250, 250);
            generalComp = new GeneralSettingsComponent(lnf, ape, apvts);
            generalComp->updateFields();
            return generalComp;
            //return &general;
        }
        else if (pageName == "About")
        {
            //setSize(250, 300);
            aboutComp = new AboutSettingsComponent(lnf, ape);
            return aboutComp;
        }
        //else if (pageName == "Splash")
        //{
        //    return new SplashSettingsComponent(lnf, ape);
        //}
        else {
            return new Component();
        }
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPanel)
};