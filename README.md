# Basic-EVE-Demo
A quick and easy sanity check to ensure that your EVE Display hardware works properly. An EVE-USB2SPI Bridge will be required, 
along with the proper interface cables to connect your EVE display to your PC and run the executables

You can download the .exe generated for your specific EVE variant to test both the TFT and touch functionality of your display. 

General guidelines for determining which .exe to use:

EVE3 - Uses BT815/BT816 Graphics controller
EVE2 - Uses FT812/FT813 Graphics Controller

29 - 2.9" 320 x 102 TFT
35 - 3.5" 320 x 240 TFT
38 - 3.8" 480 x 116 TFT
39 - 3.9" 480 x 128 TFT
43 - 4.3" 480 x 272 TFT
50 - 5.0" 800 x 480 TFT
70 - 7.0" 800 x 480 TFT

TPN - No touch panel
TPR - Resistive touch panel. Uses FT812/BT816 Graphics controller
TPC - Capacitive touch panel. Uses FT813/BT815 Graphics controller

The source code will be configured to work with a EVE2-43A-TPN display by default. Users can configure the code for their specific display 
variant by opening the MatrixEve2Conf.h file, and modifying the listed definitions appropriately.
