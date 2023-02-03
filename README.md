# Projet-M-t-o-2022-2023-Audrey-Matthias
Projet Meteo is a program capable of sorting a given file containing weather data in 6 different ways (temperature & pressure, with 3 modes each, wind, altitude, moisture) in 3 different sorting methods and displaying corresponding graphs.

## Installation
Create an empty folder and use the command "git init" inside.

Then use "git clone https://github.com/Lastbaguette/Projet-M-t-o-2022-2023-Audrey-Matthias.git".

## Configuration

When all files have been downloaded, type "cd meteo" and then "make".

Then "cd .." and you can use the program.

Needed libraries :

-Gnuplot         If not present use "sudo apt-get install gnuplot".

-bc          If not present use "sudo apt-get install bc".

Note : Make sure you have the file "meteo_filtered_data_v1.csv".

## Usage
./test [OPTION]... [FILE]       
Use "./test --help" to see all available options.

To see some example files, please check the "Last_files" folder.

After use, to delete the created files please use "cd meteo" and then "make clean".

## FAQ and Troubleshooting
Please check the joined PDF document for more details on this program.

If more help is needed please contact : "matthiasgalisson@gmail.com".
