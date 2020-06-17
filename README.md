# Environment-Aware-Irrigation-System
In this project we developed a concurrent, multi-controller product with closed- loop machine control involving a Remote Node (Tiva C-Series) and a Control Node (Beaglebone Green). The remote node consists of three sensors: the temperature sensor, luminosity sensor and the moisture sensor. The Remote Node periodically measures sensor data and detects appropriate events. The actuators include motor and buzzer that are operated based on the control messages from the Control Node. The Control Node provides a closed-loop control logic for the Remote Node. Using data and events from the Remote Node, the application code in the Control Node provides real-time decisions and provide feedback by sending control signals to the Remote Node. The Control Node has an alerting mechanism to indicate three levels of application operation – normal operation, degraded, failed/out-of-service.  The application provides a full-duplex cross operating system communication using UART enabling exchange of sensor data and control data. The application runs a Power-on Self-Test to examine the status of the system and then decide the operational mode. To support performance and failure analysis the system provides logging and log management functions to record and retrieve data and events. The entire application is implemented in form of hierarchical code with focus on modularity and reusability.
