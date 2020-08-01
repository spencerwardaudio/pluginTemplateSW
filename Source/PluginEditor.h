/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PluginTemplateSwAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    PluginTemplateSwAudioProcessorEditor (PluginTemplateSwAudioProcessor&);
    ~PluginTemplateSwAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    std::unique_ptr<Slider> volumeSlider, lpfSlider;
    std::unique_ptr<Label> volumeLabel,  lpfLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> volumeAttachment, lpfAttachment;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginTemplateSwAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginTemplateSwAudioProcessorEditor)
};
