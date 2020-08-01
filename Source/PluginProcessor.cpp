/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginTemplateSwAudioProcessor::PluginTemplateSwAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    apvts.state.addListener(this);
    init();
}

PluginTemplateSwAudioProcessor::~PluginTemplateSwAudioProcessor()
{
}

//==============================================================================
const String PluginTemplateSwAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginTemplateSwAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginTemplateSwAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginTemplateSwAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginTemplateSwAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginTemplateSwAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginTemplateSwAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginTemplateSwAudioProcessor::setCurrentProgram (int index)
{
}

const String PluginTemplateSwAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginTemplateSwAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PluginTemplateSwAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    prepare(sampleRate, samplesPerBlock);
    update();
    reset();
    isActive = true;
}

void PluginTemplateSwAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginTemplateSwAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PluginTemplateSwAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (!isActive)
    {
        return;
    }
    
    if (mustUpdateProcessing)
    {
        update();
    }
    
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    auto numSamples = buffer.getNumSamples();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, numSamples);

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        iirFilter[channel].processSamples(channelData, numSamples);
        
        outputVolume[channel].applyGain(channelData, numSamples);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            //Hard clip values
            channelData[sample] = jlimit(-1.0f, 1.0f, channelData[sample]);
        }

        // ..do something to the data...
    }
}

//==============================================================================
bool PluginTemplateSwAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluginTemplateSwAudioProcessor::createEditor()
{
    return new PluginTemplateSwAudioProcessorEditor (*this);
}

//==============================================================================
void PluginTemplateSwAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ValueTree copyState = apvts.copyState();
    std::unique_ptr<XmlElement> xml = copyState.createXml();
    copyXmlToBinary(*xml.get(), destData);
}

void PluginTemplateSwAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
    ValueTree copyState = ValueTree::fromXml(*xml.get());
    apvts.replaceState(copyState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginTemplateSwAudioProcessor();
}

//==============================================================================

void PluginTemplateSwAudioProcessor::init()
{
   // called once -- give initial values to DSP
}

void PluginTemplateSwAudioProcessor::prepare(double sampleRate, int samplesPerBlock)
{
    //Pass sample rate and buffer size to DSP
}
void PluginTemplateSwAudioProcessor::update()
{
    
    //Update DSP when a user changes parameters
    mustUpdateProcessing = false;
    
    auto frequency = apvts.getRawParameterValue("LPF");
    auto volume = apvts.getRawParameterValue("VOL");
    
    
    for (int channel = 0; channel < 2; ++channel)
    {
        iirFilter[channel].setCoefficients(IIRCoefficients::makeLowPass(getSampleRate(), frequency->load()));
        outputVolume[channel].setTargetValue(Decibels::decibelsToGain(volume->load()));
    }

    
}
void PluginTemplateSwAudioProcessor::reset()
{
    for (int channel = 0; channel < 2; ++channel)
    {
        iirFilter[channel].reset();
        
        outputVolume[channel].reset(getSampleRate(), 0.050);
    }
    // Reset DSP parameters
}

AudioProcessorValueTreeState::ParameterLayout PluginTemplateSwAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;
    
    std::function<String(float, int)> valueToTextFunction = [](float x, int l) { return String(x, 4); };
    std::function<float (const String&)> textToValueFunction = [](const String& str) { return str.getFloatValue(); };
    
    //Filter
    parameters.push_back(std::make_unique<AudioParameterFloat>("LPF", "Low Pass Filter", NormalisableRange<float>(20.0f, 22000.0f, 10.0f, 0.2f), 800.0f, "Hz", AudioProcessorParameter::genericParameter, valueToTextFunction, textToValueFunction));
 
    //Volume
    parameters.push_back(std::make_unique<AudioParameterFloat>("VOL", "Volume", NormalisableRange< float > (-40.0f, 40.0f), 0.0f, "db", AudioProcessorParameter::genericParameter, valueToTextFunction, textToValueFunction));
    
    //create our parameters
    //add them to vector
    
    return { parameters.begin(), parameters.end() };
}
