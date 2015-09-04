# Local Dns Server

Local DNS Server to bring more control over the OS

# Description

This program allow the user to redirect the requests through this software to :
* Monitor the DNS requests (spot spywares, weird domains, etc)
* Filter the DNS requests

Indeed, if a software can't obtain the IP of it's server, so it will not be able to send any request. But most of viruses use direct IP, no DNS requests, so this software will not protect from most of viruses but it will bring a better control over not trusted softwares like Google Chrome which can send private information to a server (this way you can spot this activity and block it).

While the program is running, it will use the "filters.txt" file to know which domain to filter and which one to allow. It shows too (in diagnosis mode [default mode]) the domains requested by your computer, allowing you to see clearly the domains reached.

# Compatibilities


<table>
  <tbody>
    <tr>
      <td><img src="http://wctechblog.com/wp-content/uploads/2015/06/8461c40e-b054-491a-ba53-d0cd72cda3a3_7.png" width="50"></td>
      <td>Windows 10</td>
      <td></td>
      <td><img src="http://www.7tutorials.com/files/img/win8_icons/w8li1.png" width="50"></td>
      <td>Windows 8.1</td>
      <td></td>
      <td><img src="http://img02.deviantart.net/c862/i/2009/141/e/e/vista_orb_by_fediafedia.png" width="50"></td>
      <td>Windows 7</td>
    </tr>
    <tr>
      <td><img src="http://www.photoshop101.com/content_images/1/vista_orb/Greenorb.png" width="50"></td>
      <td>Windows Vista</td>
      <td></td>
      <td><img src="http://www.ezref.com/wp-content/uploads/Windows-XP-icon.png" width="50"></td>
      <td>Windows XP</td>
      <td></td>
      <td><img src="http://icons.iconarchive.com/icons/martz90/circle/48/ubuntu-icon.png" width="50"></td>
      <td>Ubuntu</td>
    </tr>
  </tbody>
</table>


# Run

#### Windows
```
$ localdnsserver.exe [arguments]
```
#### Linux
```
$ ./localdnsserver.exe [arguments]
```

#### Arguments
<table>
  <thead>
    <tr>
      <th>Command(s)</th>
      <th>Parameter(s)</th>
      <th>Description</th>
      <th>Compatibility</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>-h, -help, --help</td>
      <td></td>
      <td>Display the help about the arguments</td>
      <td></td>
    </tr>
    <tr>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>-p, -port</td>
      <td>[PORT]</td>
      <td>Define the port</td>
      <td></td>
    </tr>
    <tr>
      <td>-rip, -remoteip</td>
      <td>[IP]</td>
      <td>Define the IP of the remote DNS Server</td>
      <td></td>
    </tr>
    <tr>
      <td>-rp, -remoteport</td>
      <td>[PORT]</td>
      <td>Define the port of the remote DNS Server</td>
      <td></td>
    </tr>
    <tr>
      <td>-dns</td>
      <td>[FILE_PATH]</td>
      <td>Define the file containing the filters</td>
      <td></td>
    </tr>
    <tr>
      <td>-o, -output</td>
      <td>[FILE_PATH]</td>
      <td>Define the output file</td>
      <td></td>
    </tr>
    <tr>
      <td>-hide</td>
      <td></td>
      <td>Hide the window</td>
      <td>Windows only</td>
    </tr>
  </tbody>
</table>


# Installation

### Windows

On Windows, there is no DNS Server already installed and running, making the
installation something easy.
The DNS cache is managed by the operating system (made by "dnsmasq" in some distributions of Linux).

The installation consists to change the DNS server which will be used by your operating system to send DNS requests.
This software is a DNS server hosted in local ; so you will have to change the IP of the DNS server to use into "127.0.0.1".

To do so, in Windows, you can follow this tutorial : http://mintywhite.com/windows-7/change-dns-server-windows-7/ .
In the "Use the following DNS server addresses" at step 5, your will put on the first line : "127.0.0.1" and on the second line nothing or an IP that you may be using if you encounter a problem with the software (in France I use "212.27.40.241").

#### Get the software

...

#### Autorun

Open the folder "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\StartUp" and create a new CMD file (for example : "startlocaldnsserver.cmd").
Put in the file the following code (with [SOFT_PATH] the path of the folder containing the software and [ARGS] the list of arguments you want to use) :
```cmd
@echo off

:: Clear the DNS Cache
ipconfig /flushdns

:: Go where the software is
cd [SOFT_PATH]

:: Start the software
start /b localdnsserver.exe [ARGS]

cls
```

##### Note no.1
If [SOFT_PATH] is not on the same drive of your operating system, you will have to specify it in the CMD file.
For example, if the software path is : "D:\Projects\cpp\LocalDnsServer\dist\Debug\MinGW-Windows" and my operating system is on the drive "C:", i will have to do so :
```cmd
@echo off

:: Clear the DNS Cache
ipconfig /flushdns

:: Go where the software is
D:
cd D:\Projects\cpp\LocalDnsServer\dist\Debug\MinGW-Windows

:: Start the software
start /b localdnsserver.exe [ARGS]

cls
```

##### Note no.2
Don't forget that if you want to start it without window (hidden), you will have to add the argument "-hide" in [ARGS].

### Linux

<table>
  <tr>
    <td><img src="https://cdn0.iconfinder.com/data/icons/super-mono-basic/blue/information_basic_blue.png"></td>
    <td>Tested with <i>Ubuntu</i></td>
  </tr>
</table>

When you will try to bind a socket to the port 53 (DNS Server port), you will have an error. It is explained by the presence of the software <b>dnsmasq</b> running in background and allowing the computer to have a DNS cache. Indeed, this software is binding a socket on the port 53. That's why we will have to stop <b>dnsmasq</b> and restart it but on another port. Then we will chain it to our software.


#### Get the software

Here you have two choices :
 * Compile the software for your machine
 * Use an already compiled version

##### Compilation
If you don't have git installed on your computer, you need to [download and install](http://git-scm.com/download/linux) it.

First of all, you have to [download the Repository](https://git-scm.com/book/en/v2/Git-Basics-Getting-a-Git-Repository) :

```
$ git clone https://github.com/OpenMarshal/LocalDnsServerCpp.git
```
Now, you have to compile the code for your processor, using your own compiler.

##### Download already compiled

...

#### Installation

```
$ sudo pkill dns
```


http://linux.die.net/man/8/dnsmasq
```
$ sudo dnsmasq -p [PORT]
```
```
$ sudo dnsmasq -p 35353
```


```
$ sudo nano /etc/resolv.conf
```

add
```
nameserver 127.0.0.1
```
put in comment others :
```
# nameserver 212.27.40.240
```

Result :

```bash
# Dynamic resolv.conf(5) file for glibc resolver(3) generated by resolvconf(8)
#     DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

# nameserver 212.27.40.240
# nameserver 212.27.40.241

nameserver 127.0.0.1
```

```
sudo pkill dnsmasq
```


Get the list of process using the port 53 :
```
sudo netstat -lanp | grep ":53 "
```

Run it after compilation :
```
sudo ./localdnsservercpp
```


Restart the cache "dnsmasq" after having stopped localdnsservercpp :
```
sudo dnsmasq
```


