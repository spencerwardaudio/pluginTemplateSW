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
class PluginTemplateSwAudioProcessorEditor  : public AudioProcessorEditor, public Button::Listener
{
public:
    PluginTemplateSwAudioProcessorEditor (PluginTemplateSwAudioProcessor&);
    ~PluginTemplateSwAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked (Button* button) override;

private:
    
    std::unique_ptr<Slider> volumeSlider, lpfSlider;
    std::unique_ptr<Label> volumeLabel,  lpfLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> volumeAttachment, lpfAttachment;
    std::unique_ptr<TextButton> lookAndFeelButton;
    
    LookAndFeel_V4 theLFDark, theLFMid, theLFGrey, theLFLight;
    LookAndFeel_V3 theLFV3;
    LookAndFeel_V1 theLFV2;
    int currentLF = 1;

    PluginTemplateSwAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginTemplateSwAudioProcessorEditor)
};
