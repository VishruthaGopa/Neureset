# Neureset Device Simulator

**Contributors:** Caitlin Wardle, Damon Gee, Vishrutha Gopa, Mion Keenan and Ada Huang

## Prerequisites
To display the waveform, our project utilizes the `QTCharts` library, which has been approved by our professor for this purpose. To install `QTCharts` on your local machine, execute the following command in the terminal:
```
sudo apt install libqt5charts5-dev
```

## Instructions
After ensuring `QTCharts` is installed, to run the Neureset program from Qt Creator, open the project by selecting the `Neureset.pro` file, then build and execute.

Alternatively, to compile Neureset directly from the command-line, enter the project directory and run
```
qmake -makefile
make
```
followed by `./Neureset` to execute.

## Troubleshooting
If building the project from Qt Creator, the compiler may throw `Error while building/deploying project Neureset (kit: Desktop) When executing step "qmake"`. If this happens, go to the "Projects" tab on the left and make sure the "Shadow build" option at the top of the build settings is **unchecked**.

Alternatively, you may also just try deleting the `Neureset.pro.user` file, clean, and attempting to build again. 

## Organization of Project Code:
- **EEGHeadset:** Controls the 21 Electrodes and handles the returns baselines of Electrodes and overall Baseline Calculation.
- **Electrode:** Controls individual treatments, waveform generation/display, baseline calculation from waveform.
- **MainWindow:** Controls integration between UI and NeuresetDevice UI. Designed per specs to allow user to interact with Neureset device.
- **NeuresetDevice:** Controls the EEGHeadset and order of/control flow of treatment process.
- **Session:** Contains vital information about each treatment including the before and after baselines from EEGHeadset.
- **SessionLog:** Contains a list of Sessions.
- **PC:** Retrieves sessions from Neureset device and saves them to database.
- **TransferWindow:** Confirmation after PC receives sessions from Neureset. It displays the sessions that are to be transferred for user confirmation.
- **DataModel:** Handles pulling data from the database and displaying it (as well as any changes).
- **DBManager:** Handles the SQL instances and connection to the database (includes helper function for data input).
- **PC Window:** Displays the session information and has a transfer data button as well as a checkbox to simulate connection between Neureset Device.

## Design Documentation:
- Use Cases
- Design Decisions
- UML Class Diagram
- State Diagrams
- Sequence Diagrams
- Traceability Matrix

## Video Demonstration:
https://youtu.be/xwzlRh9NO7U (IMPORTANT: the video uses an older version of the code and includes a bug with the timer display that has since been fixed. Due to a VM issue I was unable to dowload the newest version, but fortunately the differences were minimal and the video demonstrates the necessary functionality. -Damon)

## Contributions:
|  |                                                                                                        |
|-------------|---------------------------------------------------------------------------------------------------------------------|
| Caitlin     | - Neureset classes: `NeuresetDevice`, `EEGHeadset`, `Electrode`, `Session`, `SessionLog`. <br> - Sequence Diagrams. <br> - Use Cases. |
| Ada         | - PC classes: `DataModel`, `DBManager`, `PC Window`. <br> - Design Decisions.                            |
| Mion        | - PC classes: `PC`, `TransferWindow`. <br> - Traceability Matrix.                                                  |
| Vishrutha   | - Main UI: `MainWindow`, `UI (MainWindow.ui)`. <br> - UML Class Diagram.                                           |
| Damon       | - General Research. <br> - State Diagrams.                                                                          |
