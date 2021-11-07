#! /usr/bin/env python

#Autor: Amin Seffo
#Institute: ETI@KIT

# Importing Libraries
import serial
import json
import requests
import time

#define a varialbel to get data from the serial COM
#PLEASE CHECK YOUR COM via device mangager!!

arduino_iot = serial.Serial(port='COM8', baudrate=115200,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS,timeout=.1)

def read_value():
    '''
    encode "data" after reading to get a useable
    value without strings
    '''
    data = arduino_iot.readline()
    data=data.decode('utf-8')
    return data
    
if  __name__ == '__main__':

    while True:       
        value = read_value()
        task={"temperature": value}
        ##http://demo.thingsboard.io/
        #https://thingsboard.io/docs/reference/http-api/
        #http(s)://host:port/api/v1/$ACCESS_TOKEN/telemetry
        REST_API=requests.post("https://demo.thingsboard.io/api/v1/1VsdK2HvPYaKQBYxcJ2e/telemetry",json=task)
        #printing the value on the bash
        print(value)
        