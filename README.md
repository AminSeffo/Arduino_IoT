# Send Serial Data Using Arduino Hardware via REST API to IoT Dashboard
See these 2 videos to set up your arduino.

For more information:
https://de.mathworks.com/help/supportpkg/arduino/ref/send-and-receive-serial-data-using-arduino-hardware.html

## Thingsboard for IoT
- [ ] Firstly you have to create a demo account on [Thingsboard](http://demo.thingsboard.io/home), don't worry it is free!!
- [ ] Create a new Dashbaord and then go to _Devices>Add device>Add new device_
- [ ] Under Name add "Arduino_Iot" or your favorite one then click on "copy access token"
- [ ] Add your new device to the new created dashbaord and select **chart** to display the temperature

## Install dependencies and run the Python scrpit
Go to _src_  and edit **thingsboard.py** by replacing **ACCESS_TOKEN** with yours from thingsboard then install some packages:
```bash
pip install pyserial
pip install requests
```
finally run the script:
```bash
python thingsboard.py 
```
Go back to the Thingsboard and you will see the arduino temperature signal :)




