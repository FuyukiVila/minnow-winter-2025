**English:**
CS144: Introduction to Computer Networking
Lab Checkpoint 0: networking warmup
Winter 2025

**中文:**
CS144: 计算机网络导论
实验检查点 0：网络热身
冬季 2025

---

**English:**
Due: Sunday, January 12, 11:59 p.m. (late/extension deadline: Wed. Jan. 15 @ 7 p.m.)

**中文:**
**截止日期：** 周日，1 月 12 日，晚上 11:59（延迟/延期截止日期：周三，1 月 15 日 @ 晚上 7 点）

---

**English:**
Welcome to CS144: Introduction to Computer Networking. In this warmup, you will set up an installation of GNU/Linux on your computer, learn how to perform some tasks over the Internet by hand, write a small program in C++ that fetches a Web page over the Internet, and implement (in memory) one of the key abstractions of networking: a reliable stream of bytes between a writer and a reader. We expect this warmup to take you between 2 and 6 hours to complete (future labs will take more of your time). Three quick points about the lab assignment:

**中文:**
欢迎来到 CS144：计算机网络导论。在本次热身实验中，你将在你的计算机上安装 GNU/Linux，学习如何通过手动操作在互联网上执行一些任务，用 C++ 编写一个小程序来通过互联网获取网页，并（在内存中）实现网络的一个关键抽象：在写入者和读取者之间建立一个可靠的字节流。我们预计这个热身实验将花费你 2 到 6 个小时来完成（未来的实验将需要更多时间）。关于本次实验作业，有三点简要说明：

---

**English:**
* It's a good idea to read the whole document before diving in!

**中文:**
*   在开始之前，最好先阅读整个文档！

---

**English:**
* Over the course of this 8-part lab assignment, you'll be building up your own implementation of a significant portion of the Internet—a router, a network interface, and the TCP protocol (which transforms unreliable datagrams into a reliable byte stream). Most weeks will build on work you have done previously, i.e., you are building up your own implementation gradually over the course of the quarter, and you'll continue to use your work in future weeks. This makes it hard to “skip” a checkpoint.

**中文:**
*   在这个包含 8 个部分的实验作业中，你将逐步构建你自己对互联网重要部分的实现——一个路由器、一个网络接口和 TCP 协议（它将不可靠的数据报转换为可靠的字节流）。大多数周的实验都将建立在你之前完成的工作之上，也就是说，你将在整个学期中逐步构建你自己的实现，并在未来的几周内继续使用你的工作。这使得“跳过”一个检查点变得很困难。

---

**English:**
* If you don't meet the CS144 prerequisites, please don't take this class yet—our teaching staff's resources are limited. And please use checkpoints 0 and 1 as a gauge: if you find yourself uncomfortable with the programming in the first two checkpoints, please consider taking CS144 in a later year after you've attained more comfort with this kind of programming (perhaps after taking CS 106L, embarking on a self-directed programming project, or otherwise building up your comfort and experience level).

**中文:**
*   如果你不满足 CS144 的先决条件，请暂时不要选修这门课——我们的教学人员资源有限。请将检查点 0 和 1 作为衡量标准：如果你对前两个检查点中的编程感到不适，请考虑在未来的某一年再来学习 CS144，那时你已经对这类编程更加熟悉（可能是在修完 CS 106L、进行一个自导的编程项目，或通过其他方式积累了足够的舒适度和经验水平之后）。

---

**English:**
* The lab documents aren't "specifications" —meaning they're not intended to be consumed in a one-way fashion. They're written closer to the level of detail that a software engineer will get from a boss or client. We expect that you'll benefit from attending the lab sessions and asking clarifying questions if you find something to be ambiguous and you think the answer matters. We'll update the “lab FAQ" document on the course website in response to late questions that need clarification.

**中文:**
*   实验文档并非“规格说明书”——这意味着它们不应被单向地解读。它们的编写方式更接近于软件工程师从老板或客户那里获得的细节水平。我们期望你通过参加实验课和在你认为答案重要且发现问题模糊时提出澄清问题来获益。我们将在课程网站上更新“实验 FAQ”文档，以回应需要澄清的后续问题。

---

### **English:** 0 Collaboration Policy
### **中文:** 0 合作政策

---

**English:**
The programming assignments must be your own work: You must write all the code you hand in for the programming assignments, except for the code that we give you as part of the assignment. Please do not copy-and-paste code from Stack Overflow, GitHub, or other sources. If you base your own code on examples you find on the Web or elsewhere, cite the URL in a comment in your submitted source code.

**中文:**
**编程作业必须是你自己的工作**：你必须编写所有你提交的编程作业代码，除了我们作为作业一部分提供给你的代码。请不要从 Stack Overflow、GitHub 或其他来源复制粘贴代码。如果你基于在网络或其他地方找到的示例编写自己的代码，请在你提交的源代码中的注释里注明 URL。

---

**English:**
Working with others: You may not show your code to anyone else, look at anyone else's code, or look at solutions from previous years. You may discuss the assignments with other students, but do not copy anybody's code. If you discuss an assignment with another student, please name them in a comment in your submitted source code. Please refer to the course administrative handout for more details, and ask on EdStem if anything is unclear. Services like GitHub Copilot or ChatGPT should be considered to be equivalent to “a student that took CS144 in a prior year."

**中文:**
**与他人合作**：你不能向任何人展示你的代码，不能看任何人的代码，也不能看往年的解决方案。你可以与其他学生讨论作业，但不能复制任何人的代码。如果你与另一位学生讨论了作业，请在你提交的源代码的注释中写上他们的名字。更多详情请参考课程的管理讲义，如果有任何不清楚的地方，请在 EdStem 上提问。像 GitHub Copilot 或 ChatGPT 这样的服务应被视为等同于“一个往年修过 CS144 的学生”。

---

**English:**
EdStem: Please feel free to ask questions on EdStem, but please don't post any source code.

**中文:**
**EdStem**：欢迎在 EdStem 上提问，但请不要发布任何源代码。

---

### **English:** 1 Set up GNU/Linux on your computer
### **中文:** 1 在你的计算机上安装 GNU/Linux

---

**English:**
CS144's assignments require the GNU/Linux operating system and a recent C++ compiler that supports the C++ 2023 standard. Please choose one of these three options:

**中文:**
CS144 的作业需要 GNU/Linux 操作系统和一个支持 C++ 2023 标准的近期 C++ 编译器。请选择以下三种方式之一：

---

**English:**
1. Recommended: Install the CS144 VirtualBox virtual-machine image (instructions at https://stanford.edu/class/cs144/vm_howto/vm-howto-image.html).
2. Use a Google Cloud virtual machine using our class's coupon code (instructions at https://stanford.edu/class/cs144/vm_howto).
3. Run Ubuntu version 24.04, then install the required packages:
   ```
   sudo apt update && sudo apt install git cmake gdb build-essential clang \
   clang-tidy clang-format gcc-doc pkg-config glibc-doc tcpdump tshark
   ```
4. Use another GNU/Linux distribution “at your own risk," but be aware that you may hit roadblocks along the way and will need to be comfortable debugging them. Your code will be tested on Ubuntu 24.04 LTS with g++ 13.3 and must compile and run properly under those conditions.
5. If you have a 2020-24 MacBook (with the ARM64 M-series chips), VirtualBox will not successfully run. Instead, please install the UTM virtual machine software and our ARM64 virtual machine image from https://stanford.edu/class/cs144/vm_howto/.

**中文:**
1.  **推荐**：安装 CS144 VirtualBox 虚拟机镜像（说明在 https://stanford.edu/class/cs144/vm_howto/vm-howto-image.html）。
2.  使用我们课程的优惠码来使用 Google Cloud 虚拟机（说明在 https://stanford.edu/class/cs144/vm_howto）。
3.  运行 Ubuntu 24.04 版本，然后安装所需的软件包：
    ```bash
    sudo apt update && sudo apt install git cmake gdb build-essential clang \
    clang-tidy clang-format gcc-doc pkg-config glibc-doc tcpdump tshark
    ```
4.  使用其他 GNU/Linux 发行版需“风险自负”，但请注意你可能会遇到障碍，需要自己熟练调试。你的代码将在 Ubuntu 24.04 LTS 和 g++ 13.3 环境下进行测试，并且必须在这些条件下正确编译和运行。
5.  如果你有一台 2020-24 年的 MacBook（搭载 ARM64 M 系列芯片），VirtualBox 将无法成功运行。请改为安装 UTM 虚拟机软件和我们的 ARM64 虚拟机镜像，地址在 https://stanford.edu/class/cs144/vm_howto/。

---

### **English:** 2 Networking by hand
### **中文:** 2 手动操作网络

---

**English:**
Let's get started with using the network. You are going to do two tasks by hand: retrieving a Web page (just like a Web browser) and sending an email message (like an email client). Both of these tasks rely on a networking abstraction called a reliable bidirectional byte stream: you'll type a sequence of bytes into the terminal, and the same sequence of bytes will eventually be delivered, in the same order, to a program running on another computer (a server). The server responds with its own sequence of bytes, delivered back to your terminal.

**中文:**
让我们开始使用网络。你将手动完成两项任务：获取一个网页（就像网页浏览器一样）和发送一封电子邮件（就像电子邮件客户端一样）。这两项任务都依赖于一种称为**可靠双向字节流**的网络抽象：你将在终端输入一个字节序列，同样顺序的字节序列最终将被传送到另一台计算机上运行的程序（服务器）。服务器会用它自己的字节序列进行响应，并传送回你的终端。

---

#### **English:** 2.1 Fetch a Web page
#### **中文:** 2.1 获取一个网页

---

**English:**
1. In a Web browser, visit http://cs144.keithw.org/hello and observe the result.
2. Now, you'll do the same thing the browser does, by hand.
   (a) On your VM (or on your own computer—e.g. the Terminal program on macOS), run `telnet cs144.keithw.org http`. This tells the telnet program to open a reliable byte stream between your computer and another computer (named cs144.keithw.org), and with a particular service running on that computer: the "http" service, for the Hyper-Text Transfer Protocol, used by the World Wide Web.¹
   If your computer has been set up properly and is on the Internet, you will see:
   ```
   user@computer:~$ telnet cs144.keithw.org http
   Trying 104.196.238.229...
   Connected to cs144.keithw.org.
   Escape character is '^]'.
   ```
   If you need to quit, hold down `ctrl` and press `]`, and then type `close`
   (b) Type `GET /hello HTTP/1.1`. This tells the server the path part of the URL. (The part starting with the third slash.)
   (c) Type `Host: cs144.keithw.org`. This tells the server the host part of the URL. (The part between http:// and the third slash.)
   (d) Type `Connection: close`. This tells the server that you are finished making requests, and it should close the connection as soon as it finishes replying.
   (e) Hit the Enter key one more time: . This sends an empty line and tells the server that you are done with your HTTP request.
   (f) If all went well, you will see the same response that your browser saw, preceded by HTTP headers that tell the browser how to interpret the response.
3. Assignment: Now that you know how to fetch a Web page by hand, show us you can! Use the above technique to fetch the URL http://cs144.keithw.org/lab0/sunetid, replacing sunetid with your own primary SUNet ID. You will receive a secret code in the X-Your-Code-Is: header. Save your SUNet ID and the code for inclusion in your writeup.

**中文:**
1.  在网页浏览器中，访问 http://cs144.keithw.org/hello 并观察结果。
2.  现在，你将手动完成浏览器所做的事情。
    (a) 在你的虚拟机上（或你自己的电脑上——例如 macOS 上的终端程序），运行 `telnet cs144.keithw.org http`。这会告诉 `telnet` 程序在你的计算机和另一台计算机（名为 `cs144.keithw.org`）之间打开一个可靠的字节流，并连接到那台计算机上运行的一个特定服务：即用于万维网的超文本传输协议（Hyper-Text Transfer Protocol）的 “http” 服务。¹
    如果你的计算机设置正确并且连接到了互联网，你将会看到：
    ```
    user@computer:~$ telnet cs144.keithw.org http
    Trying 104.196.238.229...
    Connected to cs144.keithw.org.
    Escape character is '^]'.
    ```
    如果需要退出，按住 `ctrl` 和 `]`，然后输入 `close`
    (b) 输入 `GET /hello HTTP/1.1`。这告诉服务器 URL 的路径部分。（从第三个斜杠开始的部分。）
    (c) 输入 `Host: cs144.keithw.org`。这告诉服务器 URL 的主机部分。（`http://` 和第三个斜杠之间的部分。）
    (d) 输入 `Connection: close`。这告诉服务器你已经完成了请求，它在回复后应立即关闭连接。
    (e) 再按一次回车键。这会发送一个空行，告诉服务器你的 HTTP 请求已经结束。
    (f) 如果一切顺利，你将看到与你的浏览器看到的相同的响应，前面会带有一些 HTTP 标头，这些标头告诉浏览器如何解释响应。
3.  **作业**：既然你知道如何手动获取网页了，那就向我们展示一下吧！使用上述技巧获取 URL http://cs144.keithw.org/lab0/sunetid，将 `sunetid` 替换为你自己的主 SUNet ID。你将在 `X-Your-Code-Is:` 标头中收到一个密码。保存你的 SUNet ID 和这个密码，以便在你的报告中使用。

---

**English:**
¹The computer's name has a numerical equivalent (104.196.238.229, an Internet Protocol v4 address), and so does the service's name (80, a TCP port number). We'll talk more about these later.
²These instructions might also work from outside Stanford's network, but we can't guarantee it.

**中文:**
¹ 计算机名有一个数字等价物（104.196.238.229，一个 IPv4 地址），服务名也是如此（80，一个 TCP 端口号）。我们稍后会详细讨论这些。
² 这些指令可能在斯坦福网络之外也能工作，但我们不能保证。

---

#### **English:** 2.2 Send yourself an email
#### **中文:** 2.2 给自己发一封邮件

---

**English:**
Now that you know how to fetch a Web page, it's time to send an email message, again using a reliable byte stream to a service running on another computer.

1. SSH to sunetid@cardinal.stanford.edu (to make sure you are on Stanford's network), then run `telnet 148.163.153.234 smtp`.² The "smtp" service refers to the Simple Mail Transfer Protocol, used to send email messages. If all goes well, you will see:
   ```
   user@computer:~$ telnet 148.163.153.234 smtp
   Trying 148.163.153.234...
   Connected to 148.163.153.234.
   Escape character is '^]'.
   220 mx0b-00000d03.pphosted.com ESMTP mfa-m0214089
   ```
2. First step: identify your computer to the email server. Type `HELO mycomputer.stanford.edu`. Wait to see something like “250 ... Hello cardinal3.stanford.edu [171.67.24.75], pleased to meet you”.
3. Next step: who is sending the email? Type `MAIL FROM: sunetid@stanford.edu`. Replace sunetid with your SUNet ID.³ If all goes well, you will see “250 2.1.0 Sender ok".
4. Next: who is the recipient? For starters, try sending an email message to yourself. Type `RCPT TO: sunetid@stanford.edu`. Replace sunetid with your own SUNet ID. If all goes well, you will see “250 2.1.5 Recipient ok.”
5. It's time to upload the email message itself. Type `DATA` to tell the server you're ready to start. If all goes well, you will see "354 End data with <CR><LF>.<CR><LF>".
6. Now you are typing an email message to yourself. First, start by typing the headers that you will see in your email client. Leave a blank line at the end of the headers.
   ```
   354 End data with <CR><LF>.<CR><LF>
   From: sunetid@stanford.edu
   To: sunetid@stanford.edu
   Subject: Hello from CS144 Lab 0!
   ```7. Type the body of the email message—anything you like. When finished, end with a dot on a line by itself: `.`. Expect to see something like: “250 2.0.0 33h24dpdsr-1 Message accepted for delivery".
8. Type `QUIT` to end the conversation with the email server. Check your inbox and spam folder to make sure you got the email.
9. Assignment: Now that you know how to send an email by hand to yourself, try sending one to a friend or lab partner and make sure they get it. Finally, show us you can send one to us. Use the above technique to send an email, from yourself, to cs144grader@gmail.com.

**中文:**
既然你知道如何获取网页，是时候发送一封电子邮件了，同样是使用可靠的字节流连接到另一台计算机上的服务。

1.  SSH 到 `sunetid@cardinal.stanford.edu`（以确保你在斯坦福的网络内），然后运行 `telnet 148.163.153.234 smtp`。² “smtp” 服务指的是简单邮件传输协议（Simple Mail Transfer Protocol），用于发送电子邮件。如果一切顺利，你将看到：
    ```
    user@computer:~$ telnet 148.163.153.234 smtp
    Trying 148.163.153.234...
    Connected to 148.163.153.234.
    Escape character is '^]'.
    220 mx0b-00000d03.pphosted.com ESMTP mfa-m0214089
    ```
2.  第一步：向邮件服务器表明你的计算机身份。输入 `HELO mycomputer.stanford.edu`。等待看到类似 “250 ... Hello cardinal3.stanford.edu [171.67.24.75], pleased to meet you” 的信息。
3.  下一步：谁在发送邮件？输入 `MAIL FROM: sunetid@stanford.edu`。将 `sunetid` 替换为你的 SUNet ID。³ 如果一切顺利，你将看到 “250 2.1.0 Sender ok”。
4.  下一步：谁是收件人？首先，尝试给自己发送一封邮件。输入 `RCPT TO: sunetid@stanford.edu`。将 `sunetid` 替换为你的 SUNet ID。如果一切顺利，你将看到 “250 2.1.5 Recipient ok.”
5.  是时候上传邮件本身了。输入 `DATA`，告诉服务器你准备好开始了。如果一切顺利，你将看到 “354 End data with <CR><LF>.<CR><LF>”。
6.  现在你正在给自己输入一封邮件。首先，输入你会在邮件客户端中看到的邮件**标头**。在标头的末尾留一个空行。
    ```
    354 End data with <CR><LF>.<CR><LF>
    From: sunetid@stanford.edu
    To: sunetid@stanford.edu
    Subject: Hello from CS144 Lab 0!
    ```
7.  输入邮件的**正文**——任何你喜欢的内容。完成后，在新的一行只输入一个点 `.`。预计会看到类似：“250 2.0.0 33h24dpdsr-1 Message accepted for delivery”。
8.  输入 `QUIT` 来结束与邮件服务器的对话。检查你的收件箱和垃圾邮件文件夹，确保你收到了邮件。
9.  **作业**：既然你知道如何手动给自己发送邮件，尝试给朋友或实验伙伴发送一封，并确保他们收到了。最后，向我们展示你也可以给我们发送一封。使用上述技巧，从你自己的邮箱，发送一封邮件到 cs144grader@gmail.com。

---

**English:**
³Yes, it's possible to give a phony "from" address. Electronic mail is a bit like real mail from the postal service, in that the accuracy of the return address is (mostly) on the honor system. You can write anything you like as the return address on a postcard, and the same is largely true of email. Please do not abuse this—seriously. With engineering knowledge comes responsibility! Sending email with a phony "from" address is commonly done by spammers and criminals so they can pretend to be somebody else. It's fun to play around with this and pretend to be santaclaus@northpole.gov, but make sure you don't deceive any recipient. And: even if the recipient is in on the joke, do not send email pretending to be any Stanford employee (otherwise you may set off the university's IT security alerts).

**中文:**
³是的，可以提供一个假的“发件人”地址。电子邮件有点像邮政服务寄送的真实邮件，返回地址的准确性（大部分）依赖于诚信系统。你可以在明信片上写任何你喜欢的返回地址，电子邮件也大体如此。请不要滥用这一点——说真的。工程知识伴随着责任！使用假的“发件人”地址发送邮件是垃圾邮件发送者和犯罪分子常用的手段，以便他们可以冒充他人。用 santaclaus@northpole.gov 这样的地址来玩玩很有趣，但请确保你**不要欺骗任何收件人**。而且：即使收件人知道这是个玩笑，**也不要发送冒充任何斯坦福员工的邮件**（否则你可能会触发大学的 IT 安全警报）。

---

#### **English:** 2.3 Listening and connecting
#### **中文:** 2.3 监听与连接

---

**English:**
You've seen what you can do with telnet: a client program that makes outgoing connections to programs running on other computers. Now it's time to experiment with being a simple server: the kind of program that waits around for clients to connect to it.

1. In one terminal window, run `netcat -v -l -p 9090` on your VM. You should see:
   ```
   user@computer:~$ netcat -v -l -p 9090
   Listening on [0.0.0.0] (family 0, port 9090)
   ```
2. Leave netcat running. In another terminal window, run `telnet localhost 9090` (also on your VM).
3. If all goes well, the netcat will have printed something like “Connection from localhost 53500 received!".
4. Now try typing in either terminal window—the netcat (server) or the telnet (client). Notice that anything you type in one window appears in the other, and vice versa. You'll have to hit for bytes to be transfered.
5. In the netcat window, quit the program by typing `ctrl-C`. Notice that the telnet program immediately quits as well.

**中文:**
你已经见识了 `telnet` 的功能：它是一个**客户端**程序，用于向其他计算机上运行的程序建立出站连接。现在是时候体验一下作为简单的**服务器**了：那种等待客户端连接的程序。

1.  在一个终端窗口中，在你的虚拟机上运行 `netcat -v -l -p 9090`。你应该会看到：
    ```
    user@computer:~$ netcat -v -l -p 9090
    Listening on [0.0.0.0] (family 0, port 9090)
    ```
2.  保持 `netcat` 运行。在另一个终端窗口中，运行 `telnet localhost 9090`（也在你的虚拟机上）。
3.  如果一切顺利，`netcat` 将会打印出类似 “Connection from localhost 53500 received!” 的信息。
4.  现在尝试在任一终端窗口中输入——无论是 `netcat`（服务器）还是 `telnet`（客户端）。注意你在一个窗口中输入的任何内容都会出现在另一个窗口中，反之亦然。你需要按回车键才能传输字节。
5.  在 `netcat` 窗口中，通过输入 `ctrl-C` 退出程序。注意 `telnet` 程序也立即退出了。

---

### **English:** 3 Writing a network program using an OS stream socket
### **中文:** 3 使用操作系统流套接字编写网络程序

---

**English:**
In the next part of this warmup lab, you will write a short program that fetches a Web page over the Internet. You will make use of a feature provided by the Linux kernel, and by most other operating systems: the ability to create a reliable bidirectional byte stream between two programs, one running on your computer, and the other on a different computer across the Internet (e.g., a Web server such as Apache or nginx, or the netcat program).

This feature is known as a stream socket. To your program and to the Web server, the socket looks like an ordinary file descriptor (similar to a file on disk, or to the stdin or stdout I/O streams). When two stream sockets are connected, any bytes written to one socket will eventually come out in the same order from the other socket on the other computer.

**中文:**
在本次热身实验的下一部分，你将编写一个简短的程序来通过互联网获取网页。你将利用 Linux 内核以及大多数其他操作系统提供的一个功能：在两个程序之间创建**可靠的双向字节流**的能力，一个在你的计算机上运行，另一个在互联网上的另一台计算机上运行（例如，像 Apache 或 nginx 这样的 Web 服务器，或 `netcat` 程序）。

这个功能被称为**流套接字**。对于你的程序和 Web 服务器来说，套接字看起来就像一个普通的文件描述符（类似于磁盘上的文件，或 `stdin` 或 `stdout` I/O 流）。当两个流套接字连接时，写入一个套接字的任何字节最终都会以相同的顺序从另一台计算机上的另一个套接字中出来。

---

**English:**
In reality, however, the Internet doesn't provide a service of reliable byte-streams. Instead, the only thing the Internet really does is to give its “best effort” to deliver short pieces of data, called Internet datagrams, to their destination. Each datagram contains some metadata (headers) that specifies things like the source and destination addresses—what computer it came from, and what computer it's headed towards—as well as some payload data (up to about 1,500 bytes) to be delivered to the destination computer.

Although the network tries to deliver every datagram, in practice datagrams can be (1) lost, (2) delivered out of order, (3) delivered with the contents altered, or even (4) duplicated and delivered more than once. It's normally the job of the operating systems on either end of the connection to turn "best-effort datagrams" (the abstraction the Internet provides) into "reliable byte streams" (the abstraction that applications usually want).

The two computers have to cooperate to make sure that each byte in the stream eventually gets delivered, in its proper place in line, to the stream socket on the other side. They also have to tell each other how much data they are prepared to accept from the other computer, and make sure not to send more than the other side is willing to accept. All this is done using an agreed-upon scheme that was set down in 1981, called the Transmission Control Protocol, or TCP.

In this lab, you will simply use the operating system's pre-existing support for the Transmission Control Protocol. You'll write a program called “webget” that creates a TCP stream socket, connects to a Web server, and fetches a page—much as you did earlier in this lab. In future labs, you'll implement the other side of this abstraction, by implementing the Transmission Control Protocol yourself to create a reliable byte-stream out of not-so-reliable datagrams.

**中文:**
然而，实际上，互联网并不提供可靠的字节流服务。互联网真正做的唯一事情是“尽力而为”地将称为**互联网数据报**的短数据块传送到它们的目的地。每个数据报都包含一些元数据（**标头**），用于指定源地址和目标地址等信息——它来自哪台计算机，以及它要去的计算机——以及一些要传送的**有效载荷**数据（最多约 1,500 字节）。

尽管网络试图传递每个数据报，但在实践中，数据报可能会 (1) 丢失，(2) 乱序到达，(3) 内容被篡改，甚至 (4) 重复并多次到达。通常，连接两端的操作系统负责将“尽力而为的数据报”（互联网提供的抽象）转换为“可靠的字节流”（应用程序通常想要的抽象）。

两台计算机必须合作，确保流中的每个字节最终都能按正确顺序传送到另一端的流套接字。它们还必须相互告知准备接受多少数据，并确保发送的数据不会超过对方愿意接受的数量。所有这些都是通过一个于 1981 年制定的、被称为**传输控制协议 (Transmission Control Protocol)** 或 **TCP** 的商定方案来完成的。

在本实验中，你将简单地使用操作系统预先存在的对传输控制协议的支持。你将编写一个名为 “webget” 的程序，它创建一个 TCP 流套接字，连接到一个 Web 服务器，并获取一个页面——就像你之前在本实验中所做的那样。在未来的实验中，你将实现这个抽象的另一面，通过自己实现传输控制协议，从不可靠的数据报中创建可靠的字节流。

---

#### **English:** 3.1 Let's get started—setting up the repository on your VM and on GitHub
#### **中文:** 3.1 开始——在你的虚拟机和 GitHub 上设置仓库

---

**English:**
1. The lab assignments will use a starter codebase called “Minnow.” On your VM, run `git clone https://github.com/cs144/minnow` to fetch the source code for the lab.
2. Enter the minnow directory by typing: `cd minnow`
3. In a Web browser, you'll make a repository within your own GitHub account to hold your solutions to the lab assignment.
   (a) If you don't already have a GitHub account, please make one at https://github.com.
   (b) Navigate to https://github.com/new to create a new repository.
   (c) Name the repository "minnow" within your GitHub account.
   (d) Make sure to set the repository to “Private” so your solutions are not public.
   (e) Click "Create Repository".
   (f) On the next screen, click “Invite collaborators”, then “Add people".
   (g) Add “cs144-grader” as a collaborator (this will let us see and grade your code, while keeping it private).
4. Back on your VM, register the GitHub repository as a target by running the command: `git remote add github https://github.com/username/minnow` (replacing “username" with your actual GitHub username). This creates an association between your local copy of the lab assignment (on your VM) and your copy on GitHub (which you'll use to back up your local copy and be graded).
5. Run `git push github` to send the starter code to your GitHub repository. If all goes well, you will see a few lines of text printed, ending in: `* [new branch] main -> main`. If you see an error message, double-check that you have executed the above steps correctly. This command uploads your code to your private copy of the repository on GitHub and lets us grade your submissions.

**中文:**
1.  实验作业将使用一个名为 “Minnow” 的入门代码库。在你的虚拟机上，运行 `git clone https://github.com/cs144/minnow` 来获取实验的源代码。
2.  输入 `cd minnow` 进入 `minnow` 目录。
3.  在网页浏览器中，你将在自己的 GitHub 帐户内创建一个仓库来存放你的实验解决方案。
    (a) 如果你还没有 GitHub 帐户，请在 https://github.com 创建一个。
    (b) 导航到 https://github.com/new 创建一个新仓库。
    (c) 在你的 GitHub 帐户中将仓库命名为 “minnow”。
    (d) **确保将仓库设置为“私有 (Private)”**，这样你的解决方案就不会公开。
    (e) 点击 “Create Repository”。
    (f) 在下一个屏幕上，点击 “Invite collaborators”，然后点击 “Add people”。
    (g) 添加 “cs144-grader” 作为协作者（这将让我们能够看到并评分你的代码，同时保持其私有性）。
4.  回到你的虚拟机上，通过运行以下命令将 GitHub 仓库注册为目标：`git remote add github https://github.com/username/minnow`（将 “username” 替换为你的实际 GitHub 用户名）。这会在你的本地实验副本（在你的虚拟机上）和你的 GitHub 副本之间建立关联（你将用它来备份你的本地副本并进行评分）。
5.  运行 `git push github` 将入门代码发送到你的 GitHub 仓库。如果一切顺利，你将看到几行文本打印出来，最后是：`* [new branch] main -> main`。如果你看到错误消息，请仔细检查你是否正确执行了上述步骤。这个命令会将**你的**代码上传到你在 GitHub 上的私有仓库副本，并让我们能够对你的提交进行评分。

---

#### **English:** 3.2 Compiling the starter code
#### **中文:** 3.2 编译入门代码

---

**English:**
1. Still in the “minnow” directory, create a directory to compile the lab software: `cmake -S . -B build`
2. Compile the source code: `cmake --build build`
3. Using your favorite text editor (many students prefer VS Code editing files over SSH, but you can use whatever you want): open and start editing the `writeups/check0.md` file. This is the template for your lab checkpoint writeup and will be included in your submission.

**中文:**
1.  仍在 “minnow” 目录中，创建一个目录来编译实验软件：`cmake -S . -B build`
2.  编译源代码：`cmake --build build`
3.  使用你喜欢的文本编辑器（许多学生喜欢通过 SSH 使用 VS Code 编辑文件，但你可以使用任何你想要的工具）：打开并开始编辑 `writeups/check0.md` 文件。这是你的实验检查点报告模板，并将包含在你的提交中。

---

#### **English:** 3.3 Modern C++: mostly safe but still fast and low-level
#### **中文:** 3.3 现代 C++：基本安全但仍然快速和低级

---

**English:**
CS144 is a programming-heavy class. The lab assignment is done in a contemporary C++ style that uses recent (2011 and later) features to program as safely as possible. This might be different from how you have been asked to write C++ in the past. For references to this style, please see the C++ Core Guidelines (http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

The basic idea is to make sure that every object is designed to have the smallest possible public interface, has a lot of internal safety checks and is hard to use improperly, and knows how to clean up after itself. We want to avoid “paired” operations (e.g. malloc/free, or new/delete), where it might be possible for the second half of the pair not to happen (e.g., if a function returns early or throws an exception). Instead, operations happen in the constructor to an object, and the opposite operation happens in the destructor. This style is called “Resource acquisition is initialization,” or RAII.

In particular, we would like you to:
* Use the language documentation at https://en.cppreference.com as a resource. (We'd recommend you avoid cplusplus.com which is more likely to be out-of-date.)
* Never use `malloc()` or `free()`.
* Never use `new` or `delete`.
* Essentially never use raw pointers (*), and use "smart" pointers (unique_ptr or shared_ptr) only when necessary. (You will not need to use these in CS144.)
* Avoid templates, threads, locks, and virtual functions. (You will not need to use these in CS144.)
* Avoid C-style strings (char *str) or string functions (strlen(), strcpy()). These are pretty error-prone. Use a std::string instead.
* Never use C-style casts (e.g., (FILE *)x). Use a C++ static_cast if you have to (you generally will not need this in CS144).
* Prefer passing function arguments by const reference (e.g.: const Address & address).
* Make every variable const unless it needs to be mutated.
* Make every method const unless it needs to mutate the object.
* Avoid global variables, and give every variable the smallest scope possible.
* Before handing in an assignment, run `cmake --build build --target tidy` for suggestions on how to improve the code related to C++ programming practices, and `cmake --build build --target format` to format the code consistently.

On using Git: The labs are distributed as Git (version control) repositories—a way of documenting changes, checkpointing versions to help with debugging, and tracking the provenance of source code. Please make frequent small commits as you work, and use commit messages that identify what changed and why. The Platonic ideal is that each commit should compile and should move steadily towards more and more tests passing. Making small “semantic” commits helps with debugging (it's much easier to debug if each commit compiles and the message describes one clear thing that the commit does) and protects you against claims of cheating by documenting your steady progress over time—and it's a useful skill that will help in any career that includes software development. The graders will be reading your commit messages to understand how you developed your solutions to the labs. If you haven't learned how to use Git, please do ask for help at the CS144 office hours or consult a tutorial (e.g., https://guides.github.com/introduction/git-handbook). Finally, while we ask you to back your code up and submit your code to us by using a private repository on GitHub, please make sure your code is not publicly accessible.

To repeat (because we have taught this class before): make frequent small commits as you work, and use commit messages that identify what changed and why.

**中文:**
CS144 是一门编程密集型课程。实验作业采用当代 C++ 风格，使用最近（2011 年及以后）的特性，以尽可能安全的方式编程。这可能与你过去被要求编写 C++ 的方式有所不同。有关这种风格的参考，请参阅 C++ 核心准则 (http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)。

基本思想是确保每个对象都设计有尽可能小的公共接口，有大量的内部安全检查，难以被不当使用，并且知道如何自我清理。我们希望避免“成对”操作（例如 `malloc`/`free` 或 `new`/`delete`），因为其中一对的后半部分可能不会发生（例如，如果函数提前返回或抛出异常）。相反，操作在对象的构造函数中发生，而相反的操作在析构函数中发生。这种风格被称为“资源获取即初始化 (Resource acquisition is initialization)”或 RAII。

具体来说，我们希望你：
*   使用 https://en.cppreference.com 上的语言文档作为资源。（我们建议你避免使用 cplusplus.com，因为它很可能已经过时。）
*   **永远不要**使用 `malloc()` 或 `free()`。
*   **永远不要**使用 `new` 或 `delete`。
*   基本上**永远不要**使用原始指针（`*`），仅在必要时使用“智能”指针（`unique_ptr` 或 `shared_ptr`）。（在 CS144 中你将不需要使用这些。）
*   避免使用模板、线程、锁和虚函数。（在 CS144 中你将不需要使用这些。）
*   避免使用 C 风格字符串（`char *str`）或字符串函数（`strlen()`、`strcpy()`）。这些非常容易出错。请使用 `std::string` 代替。
*   **永远不要**使用 C 风格的类型转换（例如 `(FILE *)x`）。如果必须转换，请使用 C++ 的 `static_cast`（通常在 CS144 中你不需要这样做）。
*   优先通过 `const` 引用传递函数参数（例如：`const Address & address`）。
*   除非需要修改，否则将每个变量声明为 `const`。
*   除非需要修改对象，否则将每个方法声明为 `const`。
*   避免使用全局变量，并为每个变量赋予尽可能小的作用域。
*   在提交作业之前，运行 `cmake --build build --target tidy` 以获取有关如何改进代码以符合 C++ 编程实践的建议，并运行 `cmake --build build --target format` 来统一代码格式。

**关于使用 Git**：实验以 Git（版本控制）仓库的形式分发——这是一种记录变更、为调试创建检查点以及跟踪源代码来源的方式。**请在你工作时进行频繁的小提交，并使用能够说明更改内容和原因的提交信息**。理想的情况是，每次提交都应该能够编译，并且稳步地通过越来越多的测试。进行小的“语义化”提交有助于调试（如果每次提交都能编译并且消息描述了该次提交所做的一件清晰的事情，那么调试会容易得多），并通过记录你稳定的进展来保护你免受作弊指控——这是一项有用的技能，将在任何包含软件开发的职业生涯中帮助你。评分人员将阅读你的提交信息，以了解你是如何开发解决方案的。如果你还没有学会如何使用 Git，请在 CS144 的办公时间寻求帮助，或查阅教程（例如 https://guides.github.com/introduction/git-handbook）。最后，虽然我们要求你通过使用 GitHub 上的**私有**仓库来备份和提交你的代码，但**请确保你的代码不被公开访问**。

**再次强调（因为我们以前教过这门课）：在你工作时进行频繁的小提交，并使用能够说明更改内容和原因的提交信息。**

---

#### **English:** 3.4 Reading the Minnow support code
#### **中文:** 3.4 阅读 Minnow 支持代码

---

**English:**
To support this style of programming, Minnow's classes wrap operating-system functions (which can be called from C) in "modern" C++. We have provided you with C++ wrappers for concepts we hope you're broadly familiar with from CS 111, especially sockets and file descriptors.

Please read over the public interfaces (the part that comes after “public:") in the files `util/socket.hh` and `util/file_descriptor.hh`. (Please note that a `Socket` is a type of `FileDescriptor`, and a `TCPSocket` is a type of `Socket`.)

**中文:**
为了支持这种编程风格，Minnow 的类将操作系统函数（可以从 C 调用）封装在“现代”C++ 中。我们为你提供了 C++ 封装器，用于封装我们希望你从 CS 111 中大致熟悉的概念，特别是套接字和文件描述符。

**请阅读 `util/socket.hh` 和 `util/file_descriptor.hh` 文件中的公共接口（`public:`之后的部分）。（请注意，`Socket` 是 `FileDescriptor` 的一种类型，而 `TCPSocket` 是 `Socket` 的一种类型。）**

---

#### **English:** 3.5 Writing webget
#### **中文:** 3.5 编写 webget

---

**English:**
It's time to implement `webget`, a program to fetch Web pages over the Internet using the operating system's TCP support and stream-socket abstraction—just like you did by hand earlier in this lab.

1. From the `build` directory, open the file `../apps/webget.cc` in a text editor or IDE.
2. In the `get_URL` function, implement the simple Web client as described in this file, using the format of an HTTP (Web) request that you used earlier. Use the `TCPSocket` and `Address` classes.
3. Hints:
   * Please note that in HTTP, each line must be ended with “\r\n” (it's not sufficient to use just "\n" or endl).
   * Don't forget to include the “Connection: close" line in your client's request. This tells the server that it shouldn't wait around for your client to send any more requests after this one. Instead, the server will send one reply and then will immediately end its outgoing bytestream (the one from the server's socket to your socket). You'll discover that your incoming byte stream has ended because your socket will reach “EOF” (end of file) when you have read the entire byte stream coming from the server. That's how your client will know that the server has finished its reply.
   * Make sure to read and print all the output from the server until the socket reaches “EOF” (end of file)—a single call to read is not enough.
   * We expect you'll need to write about ten lines of code.
4. Compile your program by running `cmake --build build`. If you see an error message, you will need to fix it before continuing.
5. Test your program by running `./apps/webget cs144.keithw.org /hello`. How does this compare to what you see when visiting http://cs144.keithw.org/hello in a Web browser? How does it compare to the results from Section 2.1? Feel free to experiment—test it with any http URL you like!
6. When it seems to be working properly, run `cmake --build build --target check_webget` to run the automated test. Before implementing the `get_URL` function, you should expect to see the following:
   ```
   $ cmake --build build --target check_webget
   Test project /home/cs144/minnow/build
   Start 1: compile with bug-checkers
   1/2 Test #1: compile with bug-checkers ......   Passed    1.02 sec
   Start 2: t_webget
   2/2 Test #2: t_webget .....................***Failed    0.01 sec
   Function called: get_URL(cs144.keithw.org, /nph-hasher/xyzzy)
   Warning: get_URL() has not been implemented yet.
   ERROR: webget returned output that did not match the test's expectations
   ```
   After completing the assignment, you will see:
   ```
   $ cmake --build build --target check_webget
   Test project /home/cs144/minnow/build
   Start 1: compile with bug-checkers
   1/2 Test #1: compile with bug-checkers ......   Passed    1.09 sec
   Start 2: t_webget
   2/2 Test #2: t_webget .....................   Passed    0.72 sec
   
   100% tests passed, 0 tests failed out of 2
   ```
7. The graders will run your `webget` program with a different hostname and path than `make check_webget` runs—so make sure it doesn't only work with the hostname and path used by the unit tests.

**中文:**
是时候实现 `webget` 了，一个使用操作系统的 TCP 支持和流套接字抽象来从互联网获取网页的程序——就像你之前在本实验中手动操作的那样。

1.  从 `build` 目录，在文本编辑器或 IDE 中打开文件 `../apps/webget.cc`。
2.  在 `get_URL` 函数中，实现本文件中描述的简单 Web 客户端，使用你之前用过的 HTTP (Web) 请求格式。使用 `TCPSocket` 和 `Address` 类。
3.  提示：
    *   请注意，在 HTTP 中，每行必须以 “`\r\n`” 结尾（仅使用 “`\n`” 或 `endl` 是不够的）。
    *   不要忘记在你的客户端请求中包含 “`Connection: close`” 这一行。这告诉服务器，在这次请求之后，它不应该等待你的客户端发送任何更多的请求。相反，服务器将发送一个回复，然后立即结束其出站字节流（从服务器的套接字到你的套接字的那个）。你会发现，当你的套接字读到来自服务器的整个字节流并达到 “EOF”（文件结束）时，你的入站字节流就结束了。这就是你的客户端知道服务器已完成回复的方式。
    *   确保读取并打印出来自服务器的**所有**输出，直到套接字达到 “EOF”（文件结束）——**单次调用 `read` 是不够的**。
    *   我们预计你大约需要写十行代码。
4.  通过运行 `cmake --build build` 来编译你的程序。如果你看到错误消息，你需要先修复它才能继续。
5.  通过运行 `./apps/webget cs144.keithw.org /hello` 来测试你的程序。它与你在浏览器中访问 http://cs144.keithw.org/hello 时看到的内容相比如何？它与你在第 2.1 节中的结果相比如何？随时进行实验——用你喜欢的任何 http URL 来测试它！
6.  当它看起来工作正常时，运行 `cmake --build build --target check_webget` 来运行自动化测试。在实现 `get_URL` 函数之前，你应该会看到以下内容：
    ```
    $ cmake --build build --target check_webget
    Test project /home/cs144/minnow/build
    Start 1: compile with bug-checkers
    1/2 Test #1: compile with bug-checkers ......   Passed    1.02 sec
    Start 2: t_webget
    2/2 Test #2: t_webget .....................***Failed    0.01 sec
    Function called: get_URL(cs144.keithw.org, /nph-hasher/xyzzy)
    Warning: get_URL() has not been implemented yet.
    ERROR: webget returned output that did not match the test's expectations
    ```
    完成作业后，你将看到：
    ```
    $ cmake --build build --target check_webget
    Test project /home/cs144/minnow/build
    Start 1: compile with bug-checkers
    1/2 Test #1: compile with bug-checkers ......   Passed    1.09 sec
    Start 2: t_webget
    2/2 Test #2: t_webget .....................   Passed    0.72 sec
    
    100% tests passed, 0 tests failed out of 2
    ```
7.  评分程序将使用与 `make check_webget` 运行的主机名和路径不同的主机名和路径来运行你的 `webget` 程序——所以请确保它**不仅仅**对单元测试中使用的主机名和路径有效。

---

### **English:** 4 An in-memory reliable byte stream
### **中文:** 4 内存中的可靠字节流

---

**English:**
By now, you've seen how the abstraction of a reliable byte stream can be useful in communicating across the Internet, even though the Internet itself only provides the service of "best-effort” (unreliable) datagrams.

To finish off this week's lab, you will implement, in memory on a single computer, an object that provides this abstraction. (You may have done something similar in CS 110/111.) Bytes are written on the "input" side and can be read, in the same sequence, from the "output" side. The byte stream is finite: the writer can end the input, and then no more bytes can be written. When the reader has read to the end of the stream, it will reach “EOF" (end of file) and no more bytes can be read.

Your byte stream will also be flow-controlled to limit its memory consumption at any given time. The object is initialized with a particular “capacity": the maximum number of bytes it's willing to store in its own memory at any given point. The byte stream will limit the writer in how much it can write at any given moment, to make sure that the stream doesn't exceed its storage capacity. As the reader reads bytes and drains them from the stream, the writer is allowed to write more. Your byte stream is for use in a single thread—you don't have to worry about concurrent writers/readers, locking, or race conditions.

To be clear: the byte stream is finite, but it can be almost arbitrarily long⁴ before the writer ends the input and finishes the stream. Your implementation must be able to handle streams that are much longer than the capacity. The capacity limits the number of bytes that are held in memory (written but not yet read) at a given point, but does not limit the length of the stream. An object with a capacity of only one byte could still carry a stream that is terabytes and terabytes long, as long as the writer keeps writing one byte at a time and the reader reads each byte before the writer is allowed to write the next byte.

Here's what the interface looks like for the writer:
```cpp
void push(std::string data); // Push data to stream, but only as much as available capacity allows.
void close();                // Signal that the stream has reached its ending. Nothing more will be written.

bool is_closed() const;      // Has the stream been closed?

uint64_t available_capacity() const; // How many bytes can be pushed to the stream right now?
uint64_t bytes_pushed() const;       // Total number of bytes cumulatively pushed to the stream
```

And here is the interface for the reader:
```cpp
std::string_view peek() const; // Peek at the next bytes in the buffer
void pop(uint64_t len);        // Remove `len` bytes from the buffer

bool is_finished() const;      // Is the stream finished (closed and fully popped)?
bool has_error() const;        // Has the stream had an error?

uint64_t bytes_buffered() const; // Number of bytes currently buffered (pushed and not popped)
uint64_t bytes_popped() const;   // Total number of bytes cumulatively popped from stream
```

Please open the `src/byte_stream.hh` and `src/byte_stream.cc` files, and implement an object that provides this interface. As you develop your byte stream implementation, you can run the automated tests with `cmake --build build --target check0`.

If all tests pass, the `check0` test will then run a speed benchmark of your implementation. Anything faster than 0.1 Gbit/s (in other words, 100 million bits per second) is acceptable for purposes of this class, for the three pop lengths tested. (It is possible for an implementation to perform faster than 10 Gbit/s, but this depends on the speed of your computer and is not required.)

For any late-breaking questions, please check out the lab FAQ on the course website or ask your classmates or the teaching staff in the lab session (or on EdStem).

**中文:**
到现在为止，你已经看到了**可靠字节流**的抽象在跨互联网通信中是多么有用，尽管互联网本身只提供“尽力而为”的（不可靠）数据报服务。

为了完成本周的实验，你将在内存中、在单台计算机上实现一个提供这种抽象的对象。（你可能在 CS 110/111 中做过类似的事情。）字节在“输入”端被写入，并可以以相同的顺序从“输出”端被读取。字节流是有限的：写入者可以结束输入，之后就不能再写入更多字节了。当读取者读到流的末尾时，它将达到“EOF”（文件结束），之后就不能再读取更多字节了。

你的字节流还将具有**流控制**功能，以限制其在任何给定时间的内存消耗。该对象用一个特定的“容量”进行初始化：它愿意在任何给定时间点在其内存中存储的最大字节数。字节流将限制写入者在任何时刻可以写入的数量，以确保流不会超过其存储容量。随着读取者读取字节并从流中消耗它们，写入者被允许写入更多。你的字节流用于**单线程**环境——你不必担心并发的写入者/读取者、锁定或竞争条件。

需要明确的是：字节流是有限的，但它在写入者结束输入并完成流之前，可以是**几乎任意长的**⁴。你的实现必须能够处理比容量长得多的流。容量限制的是在任何给定时间点内存中持有的字节数（已写入但尚未读取），但并不限制流的长度。一个容量只有一个字节的对象仍然可以承载一个长达数 TB 的流，只要写入者每次只写一个字节，并且在写入下一个字节之前，读取者已经读取了前一个字节。

这是写入者的接口：
```cpp
void push(std::string data); // 将数据推入流中，但最多只推入可用容量允许的数量。
void close();                // 发出流已结束的信号。之后将无法再写入任何内容。

bool is_closed() const;      // 流是否已关闭？

uint64_t available_capacity() const; // 现在可以向流中推入多少字节？
uint64_t bytes_pushed() const;       // 累计推入流中的总字节数
```

这是读取者的接口：
```cpp
std::string_view peek() const; // 查看缓冲区中的下一个字节
void pop(uint64_t len);        // 从缓冲区中移除 `len` 个字节

bool is_finished() const;      // 流是否已完成（已关闭且已完全弹出）？
bool has_error() const;        // 流是否出现错误？

uint64_t bytes_buffered() const; // 当前缓冲的字节数（已推入但未弹出）
uint64_t bytes_popped() const;   // 从流中累计弹出的总字节数
```

请打开 `src/byte_stream.hh` 和 `src/byte_stream.cc` 文件，并实现一个提供此接口的对象。在你开发字节流实现的过程中，你可以使用 `cmake --build build --target check0` 运行自动化测试。

如果所有测试都通过，`check0` 测试将接着对你的实现进行速度基准测试。对于本课程的目的，任何快于 **0.1 Gbit/s**（换句话说，每秒 1 亿比特）的速度，在三种 pop 长度的测试中都是可以接受的。（一个实现有可能达到超过 10 Gbit/s 的性能，但这取决于你计算机的速度，不是必需的。）

如有任何突发问题，请查看课程网站上的实验 FAQ，或在实验课上询问你的同学或教学人员（或在 EdStem 上提问）。

---

**English:**
⁴At least up to 2⁶⁴ bytes, which in this class we will regard as essentially arbitrarily long

**中文:**
⁴ 至少高达 2⁶⁴ 字节，在本课程中我们将其视为基本上是任意长的。

---

**English:**
What's next? Over the next four weeks, you'll implement a system to provide the same interface, no longer in memory, but instead over an unreliable network. This is the Transmission Control Protocol—and its implementations are arguably the most prevalent computer program in the world.

**中文:**
接下来是什么？在接下来的四周里，你将实现一个系统来提供相同的接口，不再是在内存中，而是在一个不可靠的网络上。这就是传输控制协议（Transmission Control Protocol）——它的实现可以说是世界上最流行的计算机程序。

---

### **English:** 5 Submit
### **中文:** 5 提交

---

**English:**
1. In your submission, please only make changes to `webget.cc` and the source code in the top level of `src` (`byte_stream.hh` and `byte_stream.cc`). Please don't modify any of the tests or the helpers in `util`.
2. Remember to make small commits as you code, with good commit messages. After making a commit, back up your VM's repository to your private GitHub repository often by running `git push github`. Your code needs to be committed and pushed to GitHub for it to be gradable.
3. Before handing in any assignment, please run these in order:
   (a) Make sure you have committed all of your changes to the Git repository. You can run `git status` to make sure there are no outstanding changes. Remember: make small commits as you code.
   (b) `cmake --build build --target format` (to normalize the coding style)
   (c) `cmake --build build --target check0` (to make sure the automated tests pass)
   (d) Optional: `cmake --build build --target tidy` (suggests improvements to follow good C++ programming practices)
4. Finish editing `writeups/check0.md`, filling in the number of hours this assignment took you and any other comments.
5. Make sure your code is committed and pushed to your private GitHub repository (`git push github`).
6. There will be a Gradescope assignment due Sunday 11:59 p.m. for you to submit the commit ID of your submission.
7. Please let the course staff know ASAP of any problems at the Wednesday lab session, or by posting a question on EdStem. Good luck and welcome to CS144!

**中文:**
1.  在你的提交中，请**只**对 `webget.cc` 以及 `src` 顶级目录中的源代码（`byte_stream.hh` 和 `byte_stream.cc`）进行更改。请不要修改 `util` 中的任何测试或辅助文件。
2.  记住在你编码时进行小的提交，并附上好的提交信息。在进行一次提交后，经常通过运行 `git push github` 将你的虚拟机的仓库备份到你的私有 GitHub 仓库。你的代码需要被提交并推送到 GitHub 才能被评分。
3.  在提交任何作业之前，请按以下顺序运行这些命令：
    (a) 确保你已经将所有更改提交到 Git 仓库。你可以运行 `git status` 来确保没有未提交的更改。记住：在你编码时进行小的提交。
    (b) `cmake --build build --target format` （以规范化编码风格）
    (c) `cmake --build build --target check0` （以确保自动化测试通过）
    (d) 可选：`cmake --build build --target tidy` （建议改进以遵循良好的 C++ 编程实践）
4.  完成编辑 `writeups/check0.md`，填写你完成此作业所花费的小时数以及任何其他评论。
5.  确保你的代码已提交并推送到你的私有 GitHub 仓库（`git push github`）。
6.  将会有一个截止于周日晚上 11:59 的 Gradescope 作业，供你提交你提交的 commit ID。
7.  如果在周三的实验课上遇到任何问题，请尽快告知课程工作人员，或在 EdStem 上发帖提问。祝你好运，欢迎来到 CS144！