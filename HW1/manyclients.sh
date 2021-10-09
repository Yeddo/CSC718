#!/bin/bash

#//-----------------------------------------------------------------
#//   Name:		Jason Bisnette
#//   Class:		CSC 718
#//   Professor:	Dr. Yong Wang
#//   Assignment:	#1
#//   Due Date:	30 September 2021 
#//   File Name: 	manyclients.sh
#//   Description:	Creates 50 connections to server for testing
#//   Notes:		<Notes>
#//-----------------------------------------------------------------

for N in {1..50}
do
    curl localhost:8080 &
done
wait
