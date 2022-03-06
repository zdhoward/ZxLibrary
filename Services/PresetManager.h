/*
  ==============================================================================

    PresetManager.h
    Created: 27 Feb 2022 1:17:32pm
    Author:  ZECHS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PresetManager : ValueTree::Listener
{
public:
    static const inline File defaultDirectory
    {
        File::getSpecialLocation(File::SpecialLocationType::commonDocumentsDirectory).getChildFile(ProjectInfo::companyName).getChildFile(ProjectInfo::projectName)
    };

    static const inline String extension{ "preset" };
    static const inline String presetNameProperty{ "presetName" };

    PresetManager(AudioProcessorValueTreeState& apvts) : valueTreeState(apvts)
    {
        if (!defaultDirectory.exists())
        {
            const auto result = defaultDirectory.createDirectory();
            if (result.failed())
            {
                DBG("Could not create preset directory: " << result.getErrorMessage());
                jassertfalse;
            }
        }

        valueTreeState.state.addListener(this);
        currentPreset.referTo(valueTreeState.state.getPropertyAsValue(presetNameProperty, nullptr));
    }

    void savePreset(const String& presetName)
    {
        if (presetName.isEmpty())
            return;

        currentPreset.setValue(presetName);
        const auto xml = valueTreeState.copyState().createXml();
        const auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
        if (!xml->writeTo(presetFile))
        {
            DBG("Could not create preset file: " + presetFile.getFullPathName());
            jassertfalse;
        }
    }

    void deletePreset(const String& presetName)
    {
        if (presetName.isEmpty())
            return;

        const auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
        if (!presetFile.existsAsFile())
        {
            DBG("Preset file " + presetFile.getFullPathName() + " does not exist");
            jassertfalse;
            return;
        }
        if (!presetFile.deleteFile())
        {
            DBG("Preset file " + presetFile.getFullPathName() + " could not be deleted");
            jassertfalse;
            return;
        }
        currentPreset.setValue("");
    }

    void loadPreset(const String& presetName)
    {
        if (presetName.isEmpty())
            return;

        if (!getAllPresets().contains(presetName))
            return;

        const auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
        if (!presetFile.existsAsFile())
        {
            DBG("Preset file " + presetFile.getFullPathName() + " does not exist");
            jassertfalse;
            return;
        }

        XmlDocument xmlDocument{ presetFile };
        const auto valueTreeToLoad = ValueTree::fromXml(*xmlDocument.getDocumentElement());

        valueTreeState.replaceState(valueTreeToLoad);
        currentPreset.setValue(presetName);
    }

    int loadNextPreset()
    {
        const auto allPresets = getAllPresets();
        if (allPresets.isEmpty())
            return -1;
        const auto currentIndex = allPresets.indexOf(currentPreset.toString());
        const auto nextIndex = currentIndex + 1 > (allPresets.size() - 1) ? 0 : currentIndex + 1;
        loadPreset(allPresets.getReference(nextIndex));
        return nextIndex;
    }

    int loadPreviousPreset()
    {
        const auto allPresets = getAllPresets();
        if (allPresets.isEmpty())
            return -1;
        const auto currentIndex = allPresets.indexOf(currentPreset.toString());
        const auto previousIndex = currentIndex - 1 < 0 ? allPresets.size() - 1 : currentIndex - 1;
        loadPreset(allPresets.getReference(previousIndex));
        return previousIndex;
    }

    StringArray getAllPresets() const
    {
        StringArray presets;
        const auto fileArray = defaultDirectory.findChildFiles(File::TypesOfFileToFind::findFiles, false, "*." + extension);

        for (const auto& file : fileArray)
        {
            presets.add(file.getFileNameWithoutExtension());
        }
        return presets;
    }

    String getCurrentPreset() const
    {
        return currentPreset.toString();
    }

private:
    void valueTreeRedirected(ValueTree& treeWhichHasBeenChanged) override
    {
        currentPreset.referTo(treeWhichHasBeenChanged.getPropertyAsValue(presetNameProperty, nullptr));
    }

    AudioProcessorValueTreeState& valueTreeState;
    Value currentPreset;
};