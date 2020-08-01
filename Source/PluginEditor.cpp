/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginTemplateSwAudioProcessorEditor::PluginTemplateSwAudioProcessorEditor (PluginTemplateSwAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    volumeSlider = std::make_unique<Slider>(Slider::SliderStyle::RotaryVerticalDrag, Slider::TextBoxBelow);
    addAndMakeVisible(volumeSlider.get());
    
    volumeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "VOL", *volumeSlider);
    
    volumeLabel = std::make_unique<Label>("", "Volume");
    addAndMakeVisible(volumeLabel.get());
    volumeLabel->attachToComponent(volumeSlider.get(), false);
    volumeLabel->setJustificationType(Justification::centred);
    
    //LPF
    lpfSlider = std::make_unique<Slider>(Slider::SliderStyle::RotaryVerticalDrag, Slider::TextBoxBelow);
    addAndMakeVisible(lpfSlider.get());
    lpfAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "LPF", *lpfSlider);
    
    lpfLabel = std::make_unique<Label>("", "Low-Pass");
    addAndMakeVisible(lpfLabel.get());
    lpfLabel->attachToComponent(lpfSlider.get(), false);
    lpfLabel->setJustificationType(Justification::centred);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

PluginTemplateSwAudioProcessorEditor::~PluginTemplateSwAudioProcessorEditor()
{
}

//==============================================================================
void PluginTemplateSwAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void PluginTemplateSwAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
