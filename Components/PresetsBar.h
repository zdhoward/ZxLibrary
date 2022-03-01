/*
  ==============================================================================

    PresetsBar.h
    Created: 27 Feb 2022 4:59:48pm
    Author:  ZECHS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SettingsPanel.h"

//==============================================================================
/*
*/
class PresetsBar  : public juce::Component
{
public:
    Theme& theme;

    TextButton savePresetButton;
    TextButton deletePresetButton;

    ArrowButton prevPresetButton;
    ComboBox presetsComboBox;
    ArrowButton nextPresetButton;

    TextButton settingsButton;

    SettingsPanel settingsPanel;

    PresetsBar(PresetManager& pm, ZxLookAndFeel& lnf, AudioProcessorEditor& p, AudioProcessorValueTreeState& apvts) :
        theme(lnf.theme),
        prevPresetButton("prevPresetButton", 0.5f, Colours::white),
        nextPresetButton("nextPresetButton", 0.f, Colours::white),
        settingsPanel(lnf, p, apvts)
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        setLookAndFeel(&lnf);

        addAndMakeVisible(savePresetButton);
        savePresetButton.setButtonText("Save");
        savePresetButton.onClick = [&] { 
            pm.savePreset(presetsComboBox.getText()); 
            presetsComboBox.clear();
            StringArray allPresets = pm.getAllPresets();
            presetsComboBox.addItemList(allPresets, 1);
        };
        presetsComboBox.setEditableText(true);


        addAndMakeVisible(deletePresetButton);
        deletePresetButton.setButtonText("Delete");
        deletePresetButton.onClick = [&] { 
            auto preset = pm.getCurrentPreset();
            pm.deletePreset(preset); 
            presetsComboBox.clear();
            StringArray allPresets = pm.getAllPresets();
            presetsComboBox.addItemList(allPresets, 1);
            presetsComboBox.setText("");
        };

        addAndMakeVisible(prevPresetButton);
        prevPresetButton.onClick = [&] {
            pm.loadNextPreset();
            presetsComboBox.setText(pm.getCurrentPreset());
        };

        addAndMakeVisible(nextPresetButton);
        nextPresetButton.onClick = [&] {
            pm.loadPreviousPreset();
            presetsComboBox.setText(pm.getCurrentPreset());
        };

        addAndMakeVisible(presetsComboBox);
        presetsComboBox.setText(pm.getCurrentPreset(), true);
        StringArray allPresets = pm.getAllPresets();
        presetsComboBox.addItemList(allPresets, 1);
        presetsComboBox.onChange = [&]() {
            pm.loadPreset(presetsComboBox.getText());
        };

        addAndMakeVisible(settingsButton);
        settingsButton.setButtonText("SETTINGS");
        settingsButton.onClick = [&] {
            String settingsTitle = "Settings";
            settingsPanel.showInDialogBox(settingsTitle, 250, 250, lnf.theme.bgGroup);// , Colours::grey);
        };
    }

    ~PresetsBar() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */
        g.setColour(theme.bgGroup);
        g.fillAll();
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        auto presetBounds = getLocalBounds();
        auto presetLeftBounds = presetBounds.removeFromLeft(presetBounds.getWidth() * 0.25);
        presetLeftBounds.removeFromTop(5);
        presetLeftBounds.removeFromBottom(5);
        settingsButton.setBounds(presetLeftBounds);

        auto presetCentreBounds = presetBounds.removeFromLeft(presetBounds.getWidth() * 0.6666);
        presetCentreBounds.removeFromTop(5);
        presetCentreBounds.removeFromBottom(5);
        prevPresetButton.setBounds(presetCentreBounds.removeFromLeft(20));
        nextPresetButton.setBounds(presetCentreBounds.removeFromRight(20));
        presetsComboBox.setBounds(presetCentreBounds);

        auto presetRightBounds = presetBounds;
        presetRightBounds.removeFromTop(5);
        presetRightBounds.removeFromBottom(5);
        deletePresetButton.setBounds(presetRightBounds.removeFromRight(presetRightBounds.getWidth()/2));
        savePresetButton.setBounds(presetRightBounds);
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetsBar)
};
