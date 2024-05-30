
// Define data structure for sound driver
typedef struct {
    void (*init)();
    void (*play_wav)(const char* filename);
    void (*set_volume)(int volume);
    int volume;
} SoundDriver;

// Function to initialize the sound driver
void sound_init(SoundDriver* driver);

// Function to play a WAV file
void sound_play_wav(SoundDriver* driver, const char* filename);

// Function to control the volume
void sound_set_volume(SoundDriver* driver, int volume);
