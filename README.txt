The Problem statement is descirbed as an animation which shows an amublance both cut off by traffic as well as blocked by
big vehicles. We also aim to decongest the tremendous amount of traffic found in metro cities.

The TrafficEmergency application is an Android project which is deployed in the emergency vehicle. This application sends a beacon
to a localhost which calculates its coordinates and checks if the vehicle is approaching the coordinates of oncoming traffic signals.

The Ambulance Detection(YOLO) is an image processing project developed in TensorFlow to recognize ambulances in an image relayed by the Pi cameras. At the time of submitting this project, we have not been able to get the level of accuracy required in recognizing images.

The Traffic Management folder contains C++ files deployed on the server which converts the beacon emitted from the Android app into an 
object file for further processing, namely, if the vehicle is in emergency, it finds the nearest traffic junctions from a database which is created by
trafficjunction.cpp

The Raspberry Pi folder contains code and a unique ID for each signal, to manipulate the traffic signal based on the information received from the server, which is picked based on its code.
