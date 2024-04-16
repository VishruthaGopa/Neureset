# Neureset Device Simulator

### Contributors: Caitlin Wardle, Daemon Gee, Vishrutha Gopa, Mion Keenan and Ada Huang

## Prerequisites
To display the waveform, our project utilizes the `QTCharts` library, which has been approved by our professor for this purpose. To install `QTCharts` on your local machine, execute the following command in the terminal:
```
sudo apt install libqt5charts5-dev
```

## Division of Labor:

### Caitlin:
  - Neureset classes: `NeuresetDevice`, `EEGHeadset`, `Electrode`, `Session`, `SessionLog`.
  - Sequence Diagrams.
  - Use Cases.

### Ada:  
  - PC Database classes: `DataModel`, `DBManager`, `PC Window`.
  - Design Decisions.

### Mion:
  - PC Classes: `PC`, `TransferWindow`.
  - Traceability Matrix.

### Vishrutha:
  - Main UI: `MainWindow`, `UI (MainWindow.ui)`.
  - UML Class Diagram.

### Damon:
  - General Research.
  - State Diagrams.

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

**Video Link:**
