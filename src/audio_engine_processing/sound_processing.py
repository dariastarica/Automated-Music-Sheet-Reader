import contextlib
import math

import numpy as np
import pyaudio
import wave


# asio4all -> research
# input from mic

def get_input_from_mic():
    CHUNK = 1024
    FORMAT = pyaudio.paInt16
    CHANNELS = 2
    RATE = 44100
    RECORD_SECONDS = 5
    WAVE_OUTPUT_FILENAME = "output.wav"

    p = pyaudio.PyAudio()

    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK)

    print("* recording")

    frames = []

    for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
        frames.append(data)

    print("* done recording")

    stream.stop_stream()
    stream.close()
    p.terminate()

    wf = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
    wf.setnchannels(CHANNELS)
    wf.setsampwidth(p.get_sample_size(FORMAT))
    wf.setframerate(RATE)
    wf.writeframes(b''.join(frames))
    wf.close()

    # filtering
    # would want to use band-pass filter


def filter_input():
    print("* start filtering")
    fname = 'output.wav'
    outname = 'filtered.wav'

    cutOffFrequency = 400.0

    # from http://stackoverflow.com/questions/13728392/moving-average-or-running-mean
    def running_mean(x, windowSize):
        cumsum = np.cumsum(np.insert(x, 0, 0))
        return (cumsum[windowSize:] - cumsum[:-windowSize]) / windowSize

    # from http://stackoverflow.com/questions/2226853/interpreting-wav-data/2227174#2227174
    def interpret_wav(raw_bytes, n_frames, n_channels, sample_width, interleaved=True):

        if sample_width == 1:
            dtype = np.uint8  # unsigned char
        elif sample_width == 2:
            dtype = np.int16  # signed 2-byte short
        else:
            raise ValueError("Only supports 8 and 16 bit audio formats.")

        channels = np.fromstring(raw_bytes, dtype=dtype)

        if interleaved:
            # channels are interleaved, i.e. sample N of channel M follows sample N of channel M-1 in raw data
            channels.shape = (n_frames, n_channels)
            channels = channels.T
        else:
            # channels are not interleaved. All samples from channel M occur before all samples from channel M-1
            channels.shape = (n_channels, n_frames)

        return channels

    with contextlib.closing(wave.open(fname, 'rb')) as spf:
        sampleRate = spf.getframerate()
        ampWidth = spf.getsampwidth()
        nChannels = spf.getnchannels()
        nFrames = spf.getnframes()

        # Extract Raw Audio from multi-channel Wav File
        signal = spf.readframes(nFrames * nChannels)
        spf.close()
        channels = interpret_wav(signal, nFrames, nChannels, ampWidth, True)

        # get window size
        # from http://dsp.stackexchange.com/questions/9966/what-is-the-cut-off-frequency-of-a-moving-average-filter
        freqRatio = (cutOffFrequency / sampleRate)
        N = int(math.sqrt(0.196196 + freqRatio ** 2) / freqRatio)

        # Use moving average (only on first channel)        filtered = running_mean(channels[0], N).astype(channels.dtype)

        wav_file = wave.open(outname, "w")
        wav_file.setparams((1, ampWidth, sampleRate, nFrames, spf.getcomptype(), spf.getcompname()))
        wav_file.writeframes(filtered.tobytes('C'))
        wav_file.close()

    print("* stop filtering")

# note approximation
