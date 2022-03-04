/*
  ==============================================================================

    OversamplingManager.h
    Created: 4 Mar 2022 8:45:10am
    Author:  ZECHS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace dsp;

class OversamplingManager
{
public:
    OversamplingManager(int numChannels, int factor)
    {
        oversampling = new Oversampling<float>(numChannels, factor, Oversampling<float>::FilterType::filterHalfBandFIREquiripple, false);
    };
    ~OversamplingManager() { oversampling = nullptr; };

    void prepare(int blockSize)
    {
        oversampling->reset();
        oversampling->initProcessing(static_cast<size_t> (blockSize));
    }

    dsp::AudioBlock<float> upsample(ProcessContextReplacing<float> context)
    {
        dsp::AudioBlock<float> oversampledBlock = oversampling->processSamplesUp(context.getInputBlock());
        return oversampledBlock;
    }

    void downsample(ProcessContextReplacing<float> context)
    {
        oversampling->processSamplesDown(context.getOutputBlock());
    }

    int getLatencyInSamples()
    {
        return oversampling->getLatencyInSamples();
    }

private:
    ScopedPointer<Oversampling<float>> oversampling;
    int oversamplingFactor;
};