# CSC718
///-----------------------------------------------------------------
///   Name:		Jason Bisnette
///   Class:		CSC 718
///   Professor:	Dr. Yong Wang
///   Assignment:	#1
///   Due Date:	30 September 2021 
///   File Name: 	README.txt
///   Description:	Instructions for files
///   Notes:		<Notes>
///-----------------------------------------------------------------

# Nine (9) files included:
	1 - Makefile
	2 - myhttpd1.cpp
	3 - myhttpd1
	4 - myhttpd2.cpp
	5 - myhttpd2
	6 - myhttpd3.cpp
	7 - myhttpd3
	8 - manyclients.sh
	9 - README.txt
	
# How to compile:
	- For myhttpd2-3, you can either just type "make", or individually "gcc -pthread -g -Wall myhttpd#.cpp -o myhttpd#".
	- For myhttpd1, "gcc -g -Wall myhttpd1.cpp -o myhttpd1"



# How to run myhttpd1 (non threaded):
	- ./myhttpd1 -p 8080
	- You can do any of the following
		- open a browser and navigate to http://localhost:8080
		- use curl: curl localhost:8080
		- run my connections script: ./manyclients.sh
	- I included this file because I added a sleep() in the httpHandler() function to better show the speed improvement of threading.

# Average run time of myhttpd1:
	- I ran my manyclients.sh from the command line with the linux time command:
		time ./manyclients
	- Average time: 	
		real	1m4.609s
		user	0m0.093s
		sys	0m0.159s
	- It took a long time because of the sleep(1); I included in the httpHandler() function. Threading is much faster.


	
# How to run myhttpd2 (threaded):
	- ./myhttp2 -p 8080
	- You can do any of the following
		- open a browser and navigate to http://localhost:8080
		- use curl: curl localhost:8080
		- run my connections script: ./manyclients.sh

# Average run time of myhttpd2:
	- I ran my manyclients.sh from the command line with the linux time command:
		time ./manyclients
	- Average Time:
		real	0m0.123s
		user	0m0.128s
		sys	0m0.086s
	- As you can see the threaded program runs much faster from the client side


# Expected output of myhttpd2:
	- After running the program the following will be displayed in the terminal of the server:
	
		myhttpd server listening on port 8080
		waiting for a connection
	- Upon connecting with curl the following will be displaed in the terminal of the server:
		Received connection from 127.0.0.1
		waiting for a connection
		Received bytes 78
		Received string "GET / HTTP/1.1
		Host: localhost:8080
		User-Agent: curl/7.68.0
		Accept: */*
		
		"
		Sent bytes 137

	- Upon connecting with a browser the following will be displaed in the terminal of the server:
		Received connection from 127.0.0.1
		waiting for a connection <----- ***This happens here because the thread spins off and the while loop continues immediately***
		Received bytes 427
		Received string "GET / HTTP/1.1
		Host: localhost:8080
		User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:92.0) Gecko/20100101 Firefox/92.0
		Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
		Accept-Language: en-US,en;q=0.5
		Accept-Encoding: gzip, deflate
		Connection: keep-alive
		Upgrade-Insecure-Requests: 1
		Sec-Fetch-Dest: document
		Sec-Fetch-Mode: navigate
		Sec-Fetch-Site: none
		Sec-Fetch-User: ?1
		
		"
		Sent bytes 137
	
	- With curl, in the terminal of the client you will see the following text displayed:
		<html><body>Welcome to my first page!
		
	- In the browser window you will see the text "Welcome to my first page!" displayed.
	
	
	
# How to run myhttpd3:
	./myhttpd3 -p 8080
	
# Average run time of myhttp3:
	- I ran my manyclients.sh from the command line with the linux time command:
		time ./manyclients
	- Average Time:
		real	0m0.132s
		user	0m0.148s
		sys	0m0.071s

	- The results are about the same as myhttpd2.
	
# Expected output of myhttpd3:
	After running the program it will display the PID of the daemon. Everything else that myhttp2 displays to screen will be in /var/log/syslog.
	You can run tail -f /var/log/syslog, run this program, and connect with the client to see logged output.
	
	
	
# Other Information
	- I added a call to sleep, "sleep(1);" in the httpHandler() function to myhttpd1, myhttpd2 and myhttpd3. I did this because you can really see the time difference 		when running single thread and multi-threaded.
	
