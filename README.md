#DataCommProject1
GitHub Link: https://github.com/LordMars/DataCommProject1

This code must first be compiled using the makefile. Inside of a terminal while under this codes parent directory, run make.
This will create the server and client executables.

After the applications are compiled, the server must be run first. The server is run with this command:
./server [port number]

where port number is the port you want the server to be listening on.

Client must then be run with this command:
./client  [server ip] [port number] [input file] [format] [output file]

Where input file is the file where the client sends the data to the server from and output file is the name of the file to store the output in.
Format is a number from 0 to 3 that determines how the content of the input file is translated.

When the server is run, a socket is created and the server will wait for a connection from a client application.
The client application, after connecting, will then send the server 3 seperate pieces of information.

Protocol:
The first piece of information is the name of the output file. There is no limit on the length of the file name. If this file does not alreay exist it is created. If it does exist it is overwritten.
The second piece of information is the format that the output will be printed in. This piece of data is 1 byte long and will be any number from 0 to 3. Either no translation will take place in format 0, type 1 will translate into type 0 for format 1, type 0 will translate into type 1 for format 2, or type 0 and 1 will both be translated for format 3.
The third piece of information is the content of the input file that is sent to the server. The client reads the data from the input file and uploads it to the server in as small amounts as 1 byte at a time or as large amounts as the size of the entire file.

For each piece of information the client waits until the server has finished reading the data, indicated by whether or not the pipe is empty, until it begins to send the next piece of information.


The format and the file name are stored and the contents of the file are translated depening on the provided format.
The output is both printed out onto the screen and stored in an output file of a name provided by the user.

Known problems: Though the translation is correct and is printed out on the screen correctly, when the translated information is stored in the file there are a number of null values intermixed with the data. This has to do with how I store the data before I write to the file.

Test Cases:
(For my test cases I will show the printed output.)
input:
./client 127.0.0.1 80 practice_project_test_file_1 1 first
╔002258,772 ╗ ;╔[ ╔╚╔0032330,48350,1╔0010 ╗
output:
Amount: 2
59
347
Amount: 1
644
Amount: 3
2330
48350
1
Amount: 1
0
Amount: 2
65279
0

input:
./client 127.0.0.1 80 practice_project_test_file_1 1 first
 ╗╔╗╚╝╔00259,347╔001900 ╚        ╔ ╔  ╔00265535,0

output:
Amount: 2
258
772
Amount: 2
59
347
Amount: 1
900
Amount: 3
2330
48094
1
Amount: 1
0
Amount: 2
65535
0

input:
./client 127.0.0.1 80 practice_project_test_file_1 0 first
 ╗╔╗╚╝╔00259,347╔001900 ╚        ╔ ╔  ╔00265535,0

output:
Amount: 2
╔╗
╚╝
Amount: 2
59
347
Amount: 1
900
Amount: 3


Amount: 1
Amount: 2
65535
0

input:
./client 127.0.0.1 80 practice_project_test_file_1 2 first
 ╗╔╗╚╝╔00259,347╔001900 ╚        ╔ ╔  ╔00265535,0

output:
Amount: 2
╔╗
╚╝
Amount: 2
Amount: 1
Amount: 3


Amount: 1
Amount: 2

input:
./client 127.0.0.1 80 practice_project_test_file_1 3 first
 ╗╔╗╚╝╔00259,347╔001900 ╚        ╔ ╔  ╔00265535,0

output:
Amount: 2
258
772
Amount: 2
Amount: 1
Amount: 3
2330
48094
1
Amount: 1
0
Amount: 2