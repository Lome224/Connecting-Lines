# Connecting Lines

Connecting Lines brings together capacitive touch input, TouchDesigner visuals, and Max audio patches.

## Project files

| Path | Contents |
| --- | --- |
| `Arduino_capacitance_input/sketch_sep25a/sketch_sep25a.ino` | Circuit Playground capacitive sensing sketch. |
| `TD/ConnectLines for NYC/NewProject.toe` | TouchDesigner project, with an existing numbered copy alongside it. |
| `TD/elements/` | Video and point-cloud assets for the visual project. |
| `MAX/ambidronepulse.maxpat` | Audio patch with sample playback, synthesis, and a UDP/OSC receiver. |
| `MAX/crossfade.maxpat` | Supporting patch used by `ambidronepulse.maxpat`. |
| `MAX/OSCsender_test.maxpat` | UDP/OSC test patch. |
| `MAX/*.wav` | Audio samples referenced by the Max patches. |

## Requirements

- A compatible Adafruit Circuit Playground board, Arduino IDE, and the `Adafruit_CircuitPlayground` library.
- TouchDesigner to open the `.toe` project. The required version has not been confirmed.
- Cycling '74 Max. The saved patches identify Max 8.6.0 and 8.6.5; the main audio patch also references Vizzie components.

## Arduino input

1. Open `Arduino_capacitance_input/sketch_sep25a/sketch_sep25a.ino` in Arduino IDE.
2. Install the Adafruit Circuit Playground library and select the board and serial port that match your hardware.
3. Upload the sketch.
4. Open the serial monitor at **9600 baud** to check the sensor readings.

The sketch reads four capacitive inputs in this order:

| Output column | Pin |
| --- | --- |
| 1 | 9 |
| 2 | 2 |
| 3 | 12 |
| 4 | 0 |

It prints comma-separated readings, with a 100 ms delay between iterations. It also prints a startup message and a timer message every 60 seconds. A downstream serial parser must handle those nonnumeric lines. The timer currently prints a message; it does not reset the board or sensors.

## Visuals and sound

1. Open `TD/ConnectLines for NYC/NewProject.toe` in TouchDesigner.
2. Check its media paths, serial input settings, and OSC output settings on the computer running the project. Media assets are included under `TD/elements/`.
3. Open `MAX/ambidronepulse.maxpat` in Max. Keep `crossfade.maxpat` and the WAV files in the same directory so the patch can resolve them.
4. Check the audio output device before enabling audio.

The main Max patch contains `udpreceive 8000` and routes `/chan1`, `/chan2`, and `/chan3`. Confirm that the sender uses matching settings. The Arduino sketch outputs four sensor values, while this OSC router names three channels; the mapping needs to be checked in TouchDesigner.

The separate `OSCsender_test.maxpat` also listens on port 8000 and contains a sender saved as `udpsend 127.0.0 1 8000`. Check that sender's host and port before using it. Run the receiving patches separately unless you have configured their ports to avoid conflicts.

## Import notes

This repository was initialized from the existing Connecting Lines project folder. The folder structure and media files were preserved, and macOS metadata files were omitted. A missing closing brace at the end of the Arduino sketch was restored in this copy.

The Max patches were checked as JSON, and the copied assets were checked against their originals. Hardware behavior, audio playback, and the TouchDesigner project have not been tested as part of the repository setup.
