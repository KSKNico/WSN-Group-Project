# WSN-Group-Project
This repo is contains code for a group project for the Wireless Sensor Networks (WSN) lecture of 2024 at TU Dresden.

## Description
The purpose of this project is to monitor structural health using the NRF52840 sensing platforms and the RIOT OS. Three sensor nodes will be deployed on a bridge in a linear topology. A fourth node will be deployed on the ground. This node serves as a root or a server node. The three sensor nodes regularly sample the motion of the structure using 3D accelerometers and 3D gyroscopes. Data from these sensors are transmitted to the root node at 10 packets per second rate. A higher rate is desirable if it is sustainable throughout the experiments. The receiver always measures the RSSI value of a received packet and associates it with the parameters in the payload. A single experiment lasts from 20 to 30 minutes without interruption and should produce data with the following formats: timestamp, RSSI, Ax, Ay, Az, Gx, Gy, Gz, Packet Number. The packet number is required to trace the number of lost packets between any successful transmissions. The experiments on a single civil structure (bridge) should be repeated 10 times, in order to collect appreciable statistics.

## Goal
The experiment should be carried out on two bridges. A CNN can be trained on the collected data.
Two objectives are defined:
- Estimate the change in link quality (RSSI) in terms of the changes in the 3D motion of the structure. Here the inputs to the model are Ax, Ay, Az, Gx, Gy, Gz (or features pertaining to these measurements) and the output is RSSI.
- Estimate the 3D motion of the structure from the change in the RSSI of received packets. Here the input is RSSI and the output is (1) the total acceleration: SQRT(Ax^2 + Ay^2 + Az^2) and (2) total angular velocity: SQRT(Gx^2 + Gy^2 + Gz^2)

## Requirements
- Timers: which are required to schedule packet transmission.
- SAUL: which is required to read sensor data.
- NETAPI: To transmit packets over a wireless link.
