# CS4310-FreeNOS-Project

## Project members:
Tyler Nijmeh

Uziel Gaeta

Michael Truong

## Features 
The features include modifying the "ps" application to display the priority level of processes, priority-based scheduling to FreeNOS, and implementing a "renice" command that allows changing the priority of a process.

## Contents of branches
main branch -> FreeNOS without any changes
wait branch -> FreeNOS with wait command
priority branch -> FreeNOS with priority based scheduling

## Comments
In this project, priority-based scheduling was implemented in FreeNOS by adding priority support to the PCB class. The scheduler uses a simple linear Ready Queue to prioritize processes with a PriorityLevel ranging from 1 to 5, with 1 being the lowest priority and 5 being the highest. Additionally, the "renice" command was added to allow changing the priority of a process.

## Link to youtube video demo
<video link>
