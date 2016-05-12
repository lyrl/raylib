/**********************************************************************************************
*
*   raylib.audio
*
*   Basic functions to manage Audio: InitAudioDevice, LoadAudioFiles, PlayAudioFiles
*
*   Uses external lib:
*       OpenAL Soft - Audio device management lib (http://kcat.strangesoft.net/openal.html)
*       stb_vorbis - Ogg audio files loading (http://www.nothings.org/stb_vorbis/)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef AUDIO_H
#define AUDIO_H

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
// NOTE: Below types are required for CAMERA_STANDALONE usage
//----------------------------------------------------------------------------------
#ifndef __cplusplus
// Boolean type
    #ifndef true
        typedef enum { false, true } bool;
    #endif
#endif

// Sound source type
typedef struct Sound {
    unsigned int source;
    unsigned int buffer;
} Sound;

// Wave type, defines audio wave data
typedef struct Wave {
    void *data;                 // Buffer data pointer
    unsigned int dataSize;      // Data size in bytes
    unsigned int sampleRate;
    short bitsPerSample;
    short channels;
} Wave;

// Audio Context, used to create custom audio streams that are not bound to a sound file. There can be
// no more than 4 concurrent audio contexts in use. This is due to each active context being tied to
// a dedicated mix channel.
typedef void* AudioContext;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void InitAudioDevice(void);                                     // Initialize audio device and context
void CloseAudioDevice(void);                                    // Close the audio device and context (and music stream)
bool IsAudioDeviceReady(void);                                  // True if call to InitAudioDevice() was successful and CloseAudioDevice() has not been called yet

// Audio contexts are for outputing custom audio waveforms, This will shut down any other sound sources currently playing
// The mixChannel is what mix channel you want to operate on, 0-3 are the ones available. Each mix channel can only be used one at a time.
// exmple usage is InitAudioContext(48000, 0, 2, true); // mixchannel 1, 48khz, stereo, floating point
AudioContext InitAudioContext(unsigned short sampleRate, unsigned char mixChannel, unsigned char channels, bool floatingPoint);
void CloseAudioContext(AudioContext ctx);                       // Frees audio context
unsigned short UpdateAudioContext(AudioContext ctx, void *data, unsigned short numberElements); // Pushes more audio data into context mix channel, if NULL is passed to data then zeros are played

Sound LoadSound(char *fileName);                                // Load sound to memory
Sound LoadSoundFromWave(Wave wave);                             // Load sound to memory from wave data
Sound LoadSoundFromRES(const char *rresName, int resId);        // Load sound to memory from rRES file (raylib Resource)
void UnloadSound(Sound sound);                                  // Unload sound
void PlaySound(Sound sound);                                    // Play a sound
void PauseSound(Sound sound);                                   // Pause a sound
void StopSound(Sound sound);                                    // Stop playing a sound
bool IsSoundPlaying(Sound sound);                               // Check if a sound is currently playing
void SetSoundVolume(Sound sound, float volume);                 // Set volume for a sound (1.0 is max level)
void SetSoundPitch(Sound sound, float pitch);                   // Set pitch for a sound (1.0 is base level)

void PlayMusicStream(char *fileName);                           // Start music playing (open stream)
void UpdateMusicStream(void);                                   // Updates buffers for music streaming
void StopMusicStream(int index);                                // Stop music playing (close stream)
void PauseMusicStream(int index);                               // Pause music playing
void ResumeMusicStream(int index);                              // Resume playing paused music
bool IsMusicPlaying(int index);                                 // Check if music is playing
void SetMusicVolume(int index, float volume);                   // Set volume for music (1.0 is max level)
float GetMusicTimeLength(void);                                 // Get music time length (in seconds)
float GetMusicTimePlayed(void);                                 // Get current music time played (in seconds)
int getMusicStreamCount(void);
void SetMusicPitch(int index, float pitch);

#ifdef __cplusplus
}
#endif

#endif // AUDIO_H