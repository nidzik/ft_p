# FTP
UNIX implementation of the ftp command

## Server 
./serveur <port>
  
## Client
./client <hostname> <port> 
  
## Usage 
command in-app : 
```
ls
    List the current directory.
pwd
    Print the current path on the server.
get
    Download a file from the server.
put
    Upload a file to the server.
quit
    Exit the client.
```
### Note
The first entry will always be the username in order to create/access the directory of the user.
Thoses directories will be create where the server was executed.
The 2nd entry will be the password either to set for the first time or to connect
The password will be save in the directory of the user with the name `.pass`

### Exemple
```
$  ./serveur 4242 &
[1] 666
$ mkdir dir_client 
$ cd dir_client
$ touch myfile

$ ../client localhost 4242 
Welcome
USER:

ftp> user22
Username set. Need password.
SUCCESS
PASSWORD:

ftp> user223
Password created.
SUCCESS

ftp> ls
total 8
drwx------  3 nico  wheel   96 Jun  5 00:32 .
drwxr-xr-x  4 nico  wheel  128 Jun  5 00:31 ..
-rw-------  1 nico  wheel   13 Jun  5 00:32 .pass
SUCCESS
ftp> ^C

$ touch ../user22/file_serv
../client localhost 4242
Welcome
USER:

ftp> user22
Username set. Need password.
SUCCESS
PASSWORD:
ftp> user22
Wrong password
ERROR
PASSWORD:
ftp> user223
Connected
SUCCESS

ftp> ls
total 8
drwx------   4 nico  wheel  128 Jun  5 00:35 .
drwxr-xr-x  19 nico  wheel  608 Jun  5 00:35 ..
-rw-------   1 nico  wheel   13 Jun  5 00:35 .pass
-rw-r--r--   1 nico  wheel    0 Jun  5 00:35 file_serv
SUCCESS

ftp> pwd
/private/tmp/ft_p/user22
SUCCESS

ftp> get file_serv
File written.
SUCCESS

ftp> put myfile
Upload completed.
SUCCESS

ftp> ls
total 8
drwx------   5 nico  wheel  160 Jun  5 00:40 .
drwxr-xr-x  19 nico  wheel  608 Jun  5 00:35 ..
-rw-------   1 nico  wheel   13 Jun  5 00:35 .pass
-rw-r--r--   1 nico  wheel    0 Jun  5 00:35 file_serv
-rw-------   1 nico  wheel    0 Jun  5 00:40 myfile
SUCCESS
ftp> ftp> Bye...

$ ls
file_serv myfile
```
