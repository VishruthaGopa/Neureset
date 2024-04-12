3004Neureset Device Simulator
Team Members: Caitlin Wardle, Daemon Gee, Vishrutha Gupa, Mion Keenan and Ada Huang
NOTE: To display the waveform we have chosen to use QTCharts, which the professor comfirmed was allowed. This particular library often needs to be installed
on ones local machine, using the terminal command: sudo apt install libqt5charts5-dev

Division of Labour: Caitlin: Neureset classes including: NeuresetDevice, EEGHeadset, Electrode, Session, SessionLog. Sequence Diagrams, Use Cases

Ada: PC Database classes including: DataModel, Database Manager (DBManager), PC Window.
Design Documentation
Mion: Work within the PC Class: PC,TranseferWindow. Tracability Matrix

Visrutha: Main UI: MainWindow,UI (MainWindow.ui). ULM Class Diagram

Damon: General Research. State Diagrams

Orginization of Project Code: 
      EEGHeadset - Controls the 21 Electrodes and handles the returns baselines of Electrodes and overall Baseline Calculation 
      Electrode - Controls individual treatments, waveform generation/display, baseline calculation from waveform 
      MainWindow - Controls integration between UI and NeuresetDevice UI - Designed per specs to allow user to interact with Neureset device 
      NeuresetDevice - Controls the EEGHeadset and order of/ control flow of treatment process 
      Session - Contains vital imformation about each treatement including the before and after baselines from EEGHeadset 
      SessionLog - Contains a list of Sessions 
      PC - Retrieves sessions from Neureset device and saves them to database 
      TransferWindow - Confirmation after PC recieves sessions from Neureset it displays the sessions that are to be transeferd for user confimation 
      DataModel - Handles pulling data from the database and displaying it (as well as any changes) 
      Database Manager (DBManager)- Handles the SQL instances and connection to the database (includes helper funciton for data input) 
      PC Window - Displays the session information and has a transefer data button as well as a checkbox to simulate connection between Neureset Device

Diagrams:
      Use Cases
      Design Documentation
      UML Diagram
      State Diagrams
      Sequence Diagrams
      Traceability Matrix
