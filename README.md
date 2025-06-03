# Simulation-of-railway-crossing-operation

The task is to create a signaling control system at railroad crossings using smart sensors and design patterns to improve safety on railways.
The stages of solving the task include:
1) Analysis of railway safety needs and requirements, as well as analysis of existing signaling systems at railroad crossings.
2) Designing the system, namely developing the system architecture, including classes of smart sensors, their interconnections, and interaction with other system components.
3) Developing sensor classes, namely creating software code to implement sensor classes that will collect data on the status of the crossing, sensors, and the environment.
4)Implementation of design patterns to improve the efficiency and flexibility of the system.
5) Conducting tests required for traffic safety, namely checking the performance and reliability of the developed system.
6)Improvement of the system based on the test results, as well as ensuring further support and updating of the system if necessary.

# Description of instructions for users

User instructions for using the program for modeling a railroad crossing control system: Start the program by executing the source code file or by compiling the program and running the executable file; Select the parameters of the motion sensors, the detection distance of the train and the car. If you need other data, you can change it in trainPositions and carPositions, i.e. enter your data into these parameters. For example, setting the sensor range (MotionSensor train_s(10.0, 0.0); MotionSensor car_s(5.0, 0.0)) and setting the position data (trainPositions = { 15.0, 10.0, 15.0 ,1. 0, 9.0, 15.0 }; carPositions = { 6.0, 8.0, 8.0, 4.0, 8.0, 7.0 }); Testing the system, starting with detecting the location of a car or train. Based on the results of the analysis, it is determined whether they are within the range of the sensors. Based on the information obtained, the operating status of the crossing is selected; The system starts its operation, evaluates the specified parameters of the motion sensors, and switches between the operating states of the signaling control at the railroad crossing depending on the evaluation of the motion sensor parameters; Monitoring the program's operation. Displaying information about its status and actions performed, which simulate the operation of the crossing alarm, in the console interface; Stopping the program and evaluating the results it showed during its operation; Editing the code, if necessary, if there is a need to change the program logic. For example, adding a class for additional warning of workers who work on railroad tracks and carry out repair and other work for the safety of train traffic. In such a situation, a message about the approach of a train to the work site comes from the nearest crossing in order to ensure occupational safety and the retreat of workers to a safe distance for their safety.

# Diagrams for project

Diagram Use case Railway Control Systems 
![image](https://github.com/user-attachments/assets/5682e5c4-c840-4c91-87b0-00e3979cf4eb)

Class diagram Railway Control Systems 
![image](https://github.com/user-attachments/assets/3a18780a-d0cd-4d5b-85f1-9d15d3e3588d)

