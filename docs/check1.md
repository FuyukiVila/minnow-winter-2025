**English:**
CS144: Introduction to Computer Networking
Winter 2025
Lab Checkpoint 1: stitching substrings into a byte stream

**中文:**
CS144: 计算机网络导论
冬季 2025
实验检查点 1：将子字符串拼接成字节流

---

**English:**
Due: Sunday, January 19, 11:59 p.m. (late/extension deadline: Wed. Jan. 22 @ 7 p.m.)
Collaboration Policy: Same as checkpoint 0.

**中文:**
截止日期：周日，1 月 19 日，晚上 11:59（延迟/延期截止日期：周三，1 月 22 日 @ 晚上 7 点）
合作政策：与检查点 0 相同。

---

### **English:** 0 Overview
### **中文:** 0 概述

---

**English:**
For Checkpoint 0, you used an Internet stream socket to fetch information from a website and send an email message, using Linux's built-in implementation of the Transmission Control Protocol (TCP). This TCP implementation managed to produce a pair of reliable in-order byte streams (one from you to the server, and one in the opposite direction), even though the underlying network only delivers “best-effort” datagrams. By this we mean: short packets of data that can be lost, reordered, altered, or duplicated. You also implemented the byte-stream abstraction yourself, in memory within one computer. Over the coming weeks, you'll implement TCP yourself, to provide the byte-stream abstraction between a pair of computers separated by an unreliable datagram network.

**中文:**
在检查点 0 中，你使用了一个互联网流套接字（Internet stream socket）来从网站获取信息并发送电子邮件，这利用了 Linux 内置的传输控制协议（TCP）实现。尽管底层网络只提供“尽力而为”的数据报（datagrams），但这个 TCP 实现成功地生成了一对可靠且有序的字节流（一个从你到服务器，另一个方向相反）。我们所说的“尽力而为”是指：数据可能会以短数据包的形式丢失、重排、篡改或重复。你还在一台计算机的内存中自己实现了字节流抽象。在接下来的几周里，你将亲自实现 TCP，以便在被不可靠数据报网络分隔的两台计算机之间提供字节流抽象。

---

**English:**
*Why am I doing this? Providing a service or an abstraction on top of a different less-reliable service accounts for many of the interesting problems in networking. Over the last 40 years, researchers and practitioners have figured out how to convey all kinds of things—messaging and e-mail, hyperlinked documents, search engines, sound and video, virtual worlds, collaborative file sharing, digital currencies—over the Internet. TCP's own role, providing a pair of reliable byte streams using unreliable datagrams, is one of the classic examples of this. A reasonable view has it that TCP implementations count as the most widely used nontrivial computer programs on the planet.

**中文:**
*我为什么要做这个？ 在一个不太可靠的服务之上提供一个服务或抽象，是网络领域中许多有趣问题的根源。在过去的 40 年里，研究人员和实践者已经想出了如何通过互联网传输各种各样的事物——消息和电子邮件、超链接文档、搜索引擎、音频和视频、虚拟世界、协作文件共享、数字货币等等。TCP 自身的角色，即利用不可靠的数据报提供一对可靠的字节流，是这方面的经典范例之一。一个合理的观点认为，TCP 的实现是地球上使用最广泛的非凡计算机程序。

---

**English:**
The lab assignments will ask you to build up a TCP implementation in a modular way. Remember the `ByteStream` you just implemented in Checkpoint 0? In the coming labs, you'll end up convey two of them across the network: an “outbound" `ByteStream`, for data that a local application writes to a socket and that your TCP will send to the peer, and an “inbound" `ByteStream` for data coming from the peer that will be read by a local application.

**中文:**
实验作业将要求你以模块化的方式构建一个 TCP 实现。还记得你在检查点 0 中实现的 `ByteStream` 吗？在接下来的实验中，你最终将通过网络传输其中的两个：一个“出站”的 `ByteStream`，用于本地应用程序写入套接字的数据，你的 TCP 将其发送给对端；以及一个“入站”的 `ByteStream`，用于从对端传来的数据，由本地应用程序读取。

---

**English:**
This checkpoint contains a “hands-on” component and an implementation component. You might prefer to start the implementation component before the lab session, and do the hands-on component at the lab session. If you are a CGOE student, please use EdStem to coordinate a time with another student to do the hands-on component.

**中文:**
本检查点包含一个“动手实践”部分和一个实现部分。你可能更愿意在实验课之前开始实现部分，而在实验课上进行动手实践部分。如果你是 CGOE 学生，请使用 EdStem 与另一名学生协调时间来完成动手实践部分。

---

**English:**
The hands-on component is new this year and involves multiple moving parts—so there might be some glitches. Please bear with us at the lab session and we'll do our best to get it working for everybody. If you see an error message from the https://cs144.net website, please report it in a public post on EdStem and we'll take a look.

**中文:**
动手实践部分是今年新增的，涉及多个活动部件——所以可能会出现一些小问题。请在实验课上对我们多加包涵，我们会尽力让每个人的程序都能正常工作。如果你从 https://cs144.net 网站看到错误消息，请在 EdStem 上公开发帖报告，我们会进行检查。

---

### **English:** 1 Getting started
### **中文:** 1 开始

---

**English:**
Your implementation of TCP will use the same Minnow library that you used in Checkpoint 0, with additional classes and tests. To get started:

**中文:**
你的 TCP 实现将使用与检查点 0 中相同的 Minnow 库，但会增加一些额外的类和测试。开始步骤如下：

---

**English:**
1. Make sure you have committed all your solutions to Checkpoint 0. Please don't modify any files outside of the `src` directory, or `webget.cc`. You may have trouble merging the Checkpoint 1 starter code otherwise.
2. While inside the repository for the lab assignments, run `git fetch` to retrieve the most recent version of the lab assignments.
3. Download the starter code for Checkpoint 1 by running `git merge origin/check1-startercode`
4. Make sure your build system is properly set up: `cmake -S . -B build`
5. Compile the source code: `cmake --build build`
6. Open and start editing the `writeups/check1.md` file. This is the template for your lab writeup and will be included in your submission.

**中文:**
1.  确保你已经提交了检查点 0 的所有解决方案。请不要修改 `src` 目录或 `webget.cc` 之外的任何文件。否则，在合并检查点 1 的起始代码时可能会遇到麻烦。
2.  在实验作业的仓库内，运行 `git fetch` 来获取实验作业的最新版本。
3.  通过运行 `git merge origin/check1-startercode` 来下载检查点 1 的起始代码。
4.  确保你的构建系统已正确设置：`cmake -S . -B build`
5.  编译源代码：`cmake --build build`
6.  打开并开始编辑 `writeups/check1.md` 文件。这是你实验报告的模板，并将包含在你的提交中。

---

### **English:** 2 Hands-on component: a private network for the class
### **中文:** 2 动手实践部分：为本课程创建一个私有网络

---

**English:**
We have created a private network for the CS144 class. This will allow your VM to send datagrams directly to and from the VMs of other students in the class. To make your VM join this network:

**中文:**
我们为 CS144 课程创建了一个私有网络。这将允许你的虚拟机直接与班上其他同学的虚拟机互相发送数据报。要让你的虚拟机加入这个网络：

---

**English:**
1. On your VM, install the “wireguard” package by running `sudo apt install wireguard`
2. Visit https://cs144.net/wg and follow the instructions to join the CS144 private network.
3. Once you have joined the network, verify that you can connect by following the “ping” instructions on that page (the instructions appear after you have joined the network).
4. Every time you reboot your VM, you'll have to rejoin the network (if you want to be able to send datagrams to and from other students in this class). You don't have to register a new public key each time, but you do have to rerun the commands on that webpage. The commands will be the same each time.

**中文:**
1.  在你的虚拟机上，通过运行 `sudo apt install wireguard` 来安装 “wireguard” 软件包。
2.  访问 https://cs144.net/wg 并按照说明加入 CS144 私有网络。
3.  加入网络后，按照该页面上的 “ping” 指令来验证你是否可以连接（这些指令在你加入网络后出现）。
4.  每次重启虚拟机时，你都必须重新加入网络（如果你想能够与班上其他同学收发数据报的话）。你不需要每次都注册新的公钥，但确实需要重新运行该网页上的命令。每次的命令都是相同的。

---

#### **English:** 2.1 Ping a friend and look at the datagrams
#### **中文:** 2.1 Ping 一个朋友并查看数据报

---

**English:**
1. On your own computer (e.g. your Mac or Windows machine—not your VM), install the "wireshark" program by following the instructions at https://www.wireshark.org/. (If you are using Debian or Ubuntu GNU/Linux, the command is `sudo apt install wireshark`)

**中文:**
1.  在你自己的计算机上（例如你的 Mac 或 Windows 机器——而不是你的虚拟机），按照 https://www.wireshark.org/ 上的说明安装 "wireshark" 程序。（如果你使用的是 Debian 或 Ubuntu GNU/Linux，命令是 `sudo apt install wireshark`）

---

**English:**
2. Ask a groupmate for their IP address (the one shown on the https://cs144.net/wg webpage for them). Using the `ping` command, send some “echo request" datagrams to your friend, and make sure that you get some "echo reply" datagrams back.
3. Tips:
    * You can end the “ping” program by typing `ctrl-C`
    * You can make the "ping" command go faster by including the argument `-i 0.2`. This will make it send an “echo request” every 0.2 seconds (5 times per second).
    * You can make the “ping” command print out a summary of the statistics so far (without ending it) by running this command in another terminal: `killall -QUIT ping`
4. Begin a report in your writeup, including the following information:
   (a) What is the average round-trip delay between when your VM sends an “echo request" and when it receives an “echo reply" from your groupmate's VM?
   (b) What was the delivery rate (what percentage of “echo requests” received a corresponding "echo reply")? What was the loss rate (this is 100% minus the delivery rate)? Send at least 1,000 pings to get a reliable estimate. (This will take about three minutes if using `ping -i 0.2`.)
   (c) Did you see any duplicated datagrams (ping will print “DUP”)?
   (d) While the ping is running, you and your groupmate can capture some of the raw Internet datagrams by running `sudo rm /tmp/capture.raw; sudo tcpdump -n -w /tmp/capture.raw -i wg0 --print --packet-buffered`. This command will capture the datagrams on the "wg0" interface (the private class network) to a file ("/tmp/capture.raw"), while also printing them out to the screen. Make sure you see some “echo request” and “echo reply" lines printed—that indicates your groupmate is receiving your datagrams and replying to you.
   (e) Use the `wireshark` program to inspect the `/tmp/capture.raw` file on each of your VMs. You probably want to `scp` the `capture.raw` file to your own computer (e.g. a Mac or Windows machine) and then use wireshark to open this file, so you can use its graphical interface. Can you find the fields of the Internet datagram that were discussed in the Jan. 10 (and match the diagram at https://www.rfc-editor.org/rfc/rfc791.html#page-11)?
   (f) Are there any differences between the same datagrams when they were captured on your VM compared with when they were captured on your friend's VM? What?

**中文:**
2.  向一位组员询问他们的 IP 地址（即 https://cs144.net/wg 网页上为他们显示的地址）。使用 `ping` 命令，向你的朋友发送一些“回显请求”（echo request）数据报，并确保你收到了一些“回显应答”（echo reply）数据报。
3.  提示：
    *   你可以通过输入 `ctrl-C` 来结束 “ping” 程序。
    *   你可以通过添加参数 `-i 0.2` 使 “ping” 命令运行得更快。这将使其每 0.2 秒发送一个“回显请求”（每秒 5 次）。
    *   你可以在另一个终端中运行 `killall -QUIT ping` 命令，让 “ping” 命令打印出到目前为止的统计摘要（而无需终止它）。
4.  在你的报告中开始记录，包括以下信息：
    (a) 从你的虚拟机发送“回显请求”到从你组员的虚拟机收到“回显应答”之间的平均往返延迟是多少？
    (b) 投递率是多少（即收到相应“回显应答”的“回显请求”的百分比）？丢包率是多少（即 100% 减去投递率）？发送至少 1,000 次 ping 以获得可靠的估计。（如果使用 `ping -i 0.2`，这大约需要三分钟。）
    (c) 你是否看到了任何重复的数据报（ping 会打印 “DUP”）？
    (d) 在 ping 运行时，你和你的组员可以通过运行 `sudo rm /tmp/capture.raw; sudo tcpdump -n -w /tmp/capture.raw -i wg0 --print --packet-buffered` 来捕获一些原始的互联网数据报。这个命令将在 “wg0” 接口（班级私有网络）上捕获数据报到一个文件（"/tmp/capture.raw"），同时也会将它们打印到屏幕上。确保你看到一些“回显请求”和“回显应答”行被打印出来——这表明你的组员正在接收你的数据报并回复你。
    (e) 使用 `wireshark` 程序检查你们各自虚拟机上的 `/tmp/capture.raw` 文件。你可能需要使用 `scp` 将 `capture.raw` 文件复制到你自己的计算机（例如 Mac 或 Windows 机器），然后用 wireshark 打开这个文件，以便使用其图形界面。你能找到 1 月 10 日讲座中讨论的互联网数据报的字段吗（并与 https://www.rfc-editor.org/rfc/rfc791.html#page-11 的图表匹配）？
    (f) 在你的虚拟机上捕获的相同数据报与在你朋友的虚拟机上捕获的相比，是否存在任何差异？是什么差异？

---

#### **English:** 2.2 Send an Internet datagram by hand
#### **中文:** 2.2 手动发送一个互联网数据报

---

**English:**
In the `apps/ip_raw.cc` file, write a program that sends an Internet datagram to your friend by using a raw socket, using the same method as the January 10 lecture. It's okay to adapt code from this lecture.

**中文:**
在 `apps/ip_raw.cc` 文件中，编写一个程序，使用原始套接字（raw socket）向你的朋友发送一个互联网数据报，采用与 1 月 10 日讲座相同的方法。可以改编该讲座中的代码。

---

**English:**
1. Send your groupmate an Internet datagram with IP protocol “5” (you'll have to use "sudo” to run the "./build/apps/ip_raw" program), and have your friend use `tcpdump` to make sure they receive the datagram. They can run `sudo tcpdump -n -i wg0 'proto 5'` to print out only datagrams matching protocol “5”. Make sure they get it!
2. Send your groupmate a user datagram (with IP protocol "17"), using the “user datagram” header format in https://www.rfc-editor.org/rfc/rfc768. Have your groupmate receive this datagram without using “sudo”. They can use the “nc -u” program as was done in lecture, or a C++ program using the `UDPSocket` class—whatever they prefer!
3. Include the code for your “ip_raw.cc" in your submission to this checkpoint.
4. Do the same in reverse and receive a datagram from your groupmate.

**中文:**
1.  向你的组员发送一个 IP 协议为 “5” 的互联网数据报（你需要使用 “sudo” 来运行 “./build/apps/ip_raw” 程序），并让你的朋友使用 `tcpdump` 确保他们收到了该数据报。他们可以运行 `sudo tcpdump -n -i wg0 'proto 5'` 来只打印出协议为 “5” 的数据报。确保他们收到了！
2.  使用 https://www.rfc-editor.org/rfc/rfc768 中的“用户数据报”头部格式，向你的组员发送一个用户数据报（IP 协议为 “17”）。让你的组员在**不使用 “sudo”** 的情况下接收这个数据报。他们可以使用讲座中用过的 “nc -u” 程序，或者使用 `UDPSocket` 类的 C++ 程序——随他们喜欢！
3.  在本次检查点的提交中包含你的 “ip_raw.cc” 代码。
4.  反向执行同样的操作，从你的组员那里接收一个数据报。

---

### **English:** 3 Implementation: putting substrings in sequence
### **中文:** 3 实现：将子字符串按序排列

---

**English:**
As part of the lab assignment, you are implementing a TCP receiver: the module that receives datagrams and turns them into a reliable byte stream to be read from the socket by the application—just as your `webget` program read the byte stream from the webserver in Checkpoint 0.

The TCP sender is dividing its byte stream up into short segments (substrings no more than about 1,460 bytes apiece) so that they each fit inside a datagram. But the network might reorder these datagrams, or drop them, or deliver them more than once. The receiver must reassemble the segments into the contiguous stream of bytes that they started out as.

In this lab you'll write the data structure that will be responsible for this reassembly: a Reassembler. It will receive substrings, consisting of a string of bytes, and the index of the first byte of that string within the larger stream. Each byte of the stream has its own unique index, starting from zero and counting upwards. As soon as the Reassembler knows the next byte of the stream, it will write it to the Writer side of a ByteStream—the same ByteStream you implemented in checkpoint 0. The Reassembler's “customer” can read from the Reader side of the same ByteStream.

Here's what the interface looks like:
```cpp
// Insert a new substring to be reassembled into a ByteStream.
void insert( uint64_t first_index, std::string data, bool is_last_substring );

// How many bytes are stored in the Reassembler itself?
// This function is for testing only; don't add extra state to support it.
uint64_t count_bytes_pending() const;

// Access output stream reader
Reader& reader();
```

**中文:**
作为实验作业的一部分，你正在实现一个 TCP 接收器：这个模块接收数据报，并将它们转换成一个可靠的字节流，供应用程序从套接字读取——就像你在检查点 0 中的 `webget` 程序从网络服务器读取字节流一样。

TCP 发送方将其字节流分割成短的段（每个子字符串不超过约 1,460 字节），以便每个段都能装入一个数据报。但是网络可能会重排、丢弃或多次传递这些数据报。接收器必须将这些段重新组装成它们最初的连续字节流。

在本实验中，你将编写负责此重组的数据结构：一个 `Reassembler`。它将接收子字符串（由一串字节组成），以及该字符串在整个流中第一个字节的索引。流中的每个字节都有其唯一的索引，从零开始向上计数。一旦 `Reassembler` 知道了流的下一个字节，它就会将其写入 `ByteStream` 的写入端（Writer side）——这与你在检查点 0 中实现的 `ByteStream` 是同一个。`Reassembler` 的“客户”可以从同一个 `ByteStream` 的读取端（Reader side）进行读取。

接口如下所示：
```cpp
// 插入一个新的子字符串以重组成 ByteStream。
void insert( uint64_t first_index, std::string data, bool is_last_substring );

// Reassembler 自身存储了多少字节？
// 此函数仅用于测试；不要为了支持它而添加额外的状态。
uint64_t count_bytes_pending() const;

// 访问输出流的读取器
Reader& reader();
```

---

**English:**
*Why am I doing this? TCP robustness against reordering and duplication comes from its ability to stitch arbitrary excerpts of the byte stream back into the original stream. Implementing this in a discrete testable module will make handling incoming segments easier.

**中文:**
*我为什么要做这个？ TCP 对重排和重复的鲁棒性来自于它能够将字节流的任意片段拼接回原始流的能力。在一个独立的、可测试的模块中实现此功能，将使处理传入的段变得更加容易。

---

**English:**
The full (public) interface of the reassembler is described by the `Reassembler` class in the `reassembler.hh` header. Your task is to implement this class. You may add any private members and member functions you desire to the `Reassembler` class, but you cannot change its public interface.

**中文:**
重组器（reassembler）的完整（公共）接口由 `reassembler.hh` 头文件中的 `Reassembler` 类描述。你的任务是实现这个类。你可以根据需要向 `Reassembler` 类添加任何私有成员和成员函数，但不能更改其公共接口。

---

#### **English:** 3.1 What should the Reassembler store internally?
#### **中文:** 3.1 Reassembler 内部应该存储什么？

---

**English:**
The `insert` method informs the `Reassembler` about a new excerpt of the ByteStream, and where it fits in the overall stream (the index of the beginning of the substring).

In principle, then, the `Reassembler` will have to handle three categories of knowledge:
1. Bytes that are the next bytes in the stream. The Reassembler should push these to the stream (`output_.writer()`) as soon as they are known.
2. Bytes that fit within the stream's available capacity but can't yet be written, because earlier bytes remain unknown. These should be stored internally in the `Reassembler`.
3. Bytes that lie beyond the stream's available capacity. These should be discarded. The `Reassembler`'s will not store any bytes that can't be pushed to the `ByteStream` either immediately, or as soon as earlier bytes become known.

The goal of this behavior is to limit the amount of memory used by the `Reassembler` and `ByteStream`, no matter how the incoming substrings arrive. We've illustrated this in the picture below. The “capacity” is an upper bound on *both*:
1. The number of bytes buffered in the reassembled `ByteStream` (shown in green), and
2. The number of bytes that can be used by "unassembled" substrings (shown in red)

**中文:**
`insert` 方法通知 `Reassembler` 关于 `ByteStream` 的一个新片段，以及它在整个流中的位置（子字符串起始位置的索引）。

因此，原则上，`Reassembler` 必须处理三类信息：
1.  流中的**下一个**字节。一旦知道这些字节，`Reassembler` 应立即将它们推送到流中（`output_.writer()`）。
2.  适合流的可用容量但尚不能写入的字节，因为更早的字节仍然未知。这些应在 `Reassembler` 内部存储。
3.  超出流可用容量的字节。这些应被丢弃。`Reassembler` **不会**存储任何不能立即或在更早字节变为已知后立即推送到 `ByteStream` 的字节。

这种行为的目标是限制 `Reassembler` 和 `ByteStream` 使用的内存量，无论传入的子字符串如何到达。我们在下图中对此进行了说明。“容量”是以下**两者**的上限：
1.  已重组的 `ByteStream` 中缓冲的字节数（绿色显示），以及
2.  可被“未组装”子字符串使用的字节数（红色显示）

---

![image-20250912211045057](./assets/image-20250912211024196.png)

---

**English:**
You may find this picture useful as you implement the Reassembler and work through the tests—it's not always natural what the “right” behavior is.

**中文:**
在实现 `Reassembler` 并完成测试时，你可能会发现这张图很有用——因为“正确”的行为方式并不总是那么直观。

---

#### **English:** 3.2 FAQs
#### **中文:** 3.2 常见问题解答

---

**English:**
*   What is the index of the first byte in the whole stream? Zero.
*   How efficient should my implementation be? The choice of data structure is again important here. Please don't take this as a challenge to build a grossly space- or time-inefficient data structure—the Reassembler will be the foundation of your TCP implementation. You have a lot of options to choose from. We have provided you with a benchmark; anything greater than 0.1 Gbit/s (100 megabits per second) is acceptable. A top-of-the-line Reassembler will achieve 10 Gbit/s.
*   How should inconsistent substrings be handled? You may assume that they don't exist. That is, you can assume that there is a unique underlying byte-stream, and all substrings are (accurate) slices of it.
*   What may I use? You may use any part of the standard library you find helpful. In particular, we expect you to use at least one data structure.
*   When should bytes be written to the stream? As soon as possible. The only situation in which a byte should not be in the stream is that when there is a byte before it that has not been "pushed" yet.
*   May substrings provided to the `insert()` function overlap? Yes.
*   Will I need to add private members to the Reassembler? Yes. Substrings may arrive in any order, so your data structure will have to “remember” substrings until they're ready to be put into the stream—that is, until all indices before them have been written.
*   Is it okay for our re-assembly data structure to store overlapping substrings? No. It is possible to implement an “interface-correct” reassembler that stores overlapping substrings. But allowing the re-assembler to do this undermines the notion of “capacity” as a memory limit. If the caller provides redundant knowledge about the same index, the Reassembler should only store one copy of this information.
*   Will the Reassembler ever use the Reader side of the ByteStream? No—that's for the external customer. The Reassembler uses the Writer side only.
*   How many lines of code are you expecting? When we run `./scripts/lines-of-code` on the starter code, it prints:
    ```
    ByteStream:  82 lines of code
    Reassembler: 26 lines of code
    ```
    and when we run it on our solutions, it prints:
    ```
    ByteStream: 111 lines of code
    Reassembler: 85 lines of code
    ```
    So a reasonable implementation of the `Reassembler` might be about 50-60 lines of code for the `Reassembler` (on top of the starter code).
*   More FAQs: For more, please see https://cs144.github.io/lab_faq.html.

**中文:**
*   整个流中第一个字节的索引是什么？零。
*   我的实现应该有多高效？数据结构的选择在这里再次变得重要。请不要将这视为一个构建一个极其浪费空间或时间的挑战——`Reassembler` 将是你 TCP 实现的基础。你有很多选择。我们为你提供了一个基准测试；任何高于 0.1 Gbit/s（每秒 100 兆比特）的性能都是可以接受的。顶级的 `Reassembler` 将达到 10 Gbit/s。
*   应如何处理不一致的子字符串？你可以假设它们不存在。也就是说，你可以假设存在一个唯一的底层字节流，并且所有的子字符串都是它的（准确的）切片。
*   我可以使用什么？你可以使用你认为有用的标准库的任何部分。特别地，我们希望你至少使用一种数据结构。
*   字节应该何时写入流中？尽快。一个字节不应在流中的唯一情况是，当它之前还有一个字节尚未被“推送”时。
*   提供给 `insert()` 函数的子字符串可以重叠吗？可以。
*   我需要向 `Reassembler` 添加私有成员吗？是的。子字符串可能以任何顺序到达，所以你的数据结构必须“记住”这些子字符串，直到它们准备好被放入流中——也就是，直到它们之前的所有索引都已被写入。
*   我们的重组数据结构存储重叠的子字符串可以吗？不可以。实现一个存储重叠子字符串的“接口正确”的重组器是可能的。但是允许重组器这样做会破坏“容量”作为内存限制的概念。如果调用者提供了关于同一索引的冗余信息，`Reassembler` 只应存储该信息的一份副本。
*   `Reassembler` 会使用 `ByteStream` 的读取端（Reader side）吗？不会——那是给外部客户用的。`Reassembler` 只使用写入端（Writer side）。
*   你期望的代码行数是多少？当我们在起始代码上运行 `./scripts/lines-of-code` 时，它打印出：
    ```
    ByteStream:  82 行代码
    Reassembler: 26 行代码
    ```
    而当我们在我们的解决方案上运行时，它打印出：
    ```
    ByteStream: 111 行代码
    Reassembler: 85 行代码
    ```
    所以一个合理的 `Reassembler` 实现可能大约需要 50-60 行代码（在起始代码的基础上）。
*   更多常见问题解答：更多信息，请参阅 https://cs144.github.io/lab_faq.html。

---

### **English:** 4 Development and debugging advice
### **中文:** 4 开发和调试建议

---

**English:**
1. You can test your code (after compiling it) with `cmake --build build --target check1`
2. Please re-read the section on “using Git" in the Lab 0 document, and remember to keep the code in the Git repository it was distributed in on the main branch. Make small commits, using good commit messages that identify what changed and why.
3. Please work to make your code readable to the CA who will be grading it for style and soundness. Use reasonable and clear naming conventions for variables. Use comments to explain complex or subtle pieces of code. Use “defensive programming” —explicitly check preconditions of functions or invariants, and throw an exception if anything is ever wrong. Use modularity in your design—identify common abstractions and behaviors and factor them out when possible. Blocks of repeated code and enormous functions will make it hard to follow your code.
4. Please also keep to the “Modern C++” style described in the Checkpoint 0 document. The cppreference website (https://en.cppreference.com) is a great resource, although you won't need any sophisticated features of C++ to do these labs. (You may sometimes need to use the `move()` function to pass an object that can't be copied.)
5. If you get your builds stuck and aren't sure how to fix them, you can erase your build directory (`rm -rf build`—please be careful not to make a typo as this will erase whatever you tell it), and then run `cmake -S . -B build` again.

**中文:**
1.  你可以用 `cmake --build build --target check1` 来测试你的代码（在编译后）。
2.  请重读实验 0 文档中关于“使用 Git”的部分，并记住将代码保存在其分发时所在的主分支的 Git 仓库中。进行小的提交，并使用能够说明更改内容和原因的良好提交信息。
3.  请努力使你的代码对于将要对其进行风格和健壮性评分的助教（CA）来说是可读的。为变量使用合理且清晰的命名约定。使用注释来解释复杂或微妙的代码片段。使用“防御性编程”——明确检查函数或不变量的前提条件，如果出现任何错误就抛出异常。在你的设计中使用模块化——识别共同的抽象和行为，并在可能时将它们提取出来。重复的代码块和庞大的函数将使你的代码难以理解。
4.  也请遵守检查点 0 文档中描述的“现代 C++”风格。cppreference 网站（https://en.cppreference.com）是一个很好的资源，尽管你不需要使用 C++ 的任何复杂特性来完成这些实验。（有时你可能需要使用 `move()` 函数来传递一个不能被复制的对象。）
5.  如果你的构建卡住了，并且不确定如何修复，你可以删除你的构建目录（`rm -rf build`——请小心不要打错字，因为这会删除你指定的任何东西），然后再次运行 `cmake -S . -B build`。

---

### **English:** 5 Submit
### **中文:** 5 提交

---

**English:**
1. In your submission, please only make changes to the `.hh` and `.cc` files in the `src` directory. Within these files, please feel free to add private members as necessary, but please don't change the public interface of any of the classes.
2. Before handing in any assignment, please run these in order:
   (a) Make sure you have committed all of your changes to the Git repository. You can run `git status` to make sure there are no outstanding changes. Remember: make small commits as you code.
   (b) `cmake --build build --target format` (to normalize the coding style)
   (c) `cmake --build build --target check1` (to make sure the automated tests pass)
   (d) Optional: `cmake --build build --target tidy` (suggests improvements to follow good C++ programming practices)
3. Write a report in `writeups/check1.md`. This file should be a roughly 20-to-50-line document with no more than 80 characters per line to make it easier to read. The report should contain the following sections:
   (a) Structure and Design. Describe the high-level structure and design choices embodied in your code. You don't need to discuss in detail what you inherited from the starter code. Use this as an opportunity to highlight important design aspects and provide greater detail on those areas for your grading TA to understand. What data structures did you choose in your header file? Are any of them not strictly necessary? We'd like you to avoid redundant state if at all possible, unless you think and can justify that there's a serious performance penalty from doing so. You are strongly encouraged to make this writeup as readable as possible by using subheadings and outlines. Please do not simply translate your program into an paragraph of English.
   (b) Alternative design choices that you considered or ideally evaluated in terms of their performance, difficulty to write (e.g., hours required to produce a bug-free implementation), difficulty to read (e.g., lines of code and their degree of subtlety or nonobvious correctness), and any other dimensions you think are interesting for the reader (or for your own past self before you did this assignment). Include any measurements if applicable.
   (c) Implementation Challenges. Describe the parts of code that you found most troublesome and explain why. Reflect on how you overcame those challenges and what helped you finally understand the concept that was giving you trouble. How did you attempt to ensure that your code maintained your assumptions, invariants, and preconditions, and in what ways did you find this easy or difficult? How did you debug and test your code?
   (d) Remaining Bugs. Point out and explain as best you can any bugs (or unhandled edge cases) that remain in the code.
4. In your writeup, please also fill in the number of hours the assignment took you and any other comments.
5. The mechanics of "how to turn it in" will be announced before the deadline.
6. Please let the course staff know ASAP of any problems at the lab session, or by posting a question on Ed. Good luck!

**中文:**
1.  在你的提交中，请仅对 `src` 目录中的 `.hh` 和 `.cc` 文件进行更改。在这些文件中，你可以根据需要随意添加私有成员，但请不要更改任何类的公共接口。
2.  在提交任何作业之前，请按以下顺序运行这些命令：
    (a) 确保你已经将所有更改提交到 Git 仓库。你可以运行 `git status` 来确保没有未完成的更改。记住：在你编码时进行小的提交。
    (b) `cmake --build build --target format` （以规范化编码风格）
    (c) `cmake --build build --target check1` （以确保自动化测试通过）
    (d) 可选：`cmake --build build --target tidy` （建议改进以遵循良好的 C++ 编程实践）
3.  在 `writeups/check1.md` 中撰写一份报告。这个文件应该是一个大约 20 到 50 行的文档，每行不超过 80 个字符，以便于阅读。报告应包含以下部分：
    (a) **结构与设计**。描述你代码中体现的高层结构和设计选择。你不需要详细讨论你从起始代码继承了什么。以此为契机，突出重要的设计方面，并为你的评分助教提供更详细的信息以理解这些领域。你在头文件中选择了哪些数据结构？其中是否有任何不是绝对必要的？我们希望你尽可能避免冗余状态，除非你认为并且能够证明这样做会带来严重的性能损失。强烈建议你通过使用副标题和提纲来使这份报告尽可能可读。请不要简单地将你的程序翻译成一段英文。
    (b) **备选设计选择**。描述你曾考虑过或理想情况下评估过的其他设计选择，从它们的性能、编写难度（例如，产生一个无 bug 实现所需的小时数）、阅读难度（例如，代码行数及其精妙或不明显的正确性程度），以及你认为对读者（或对完成此作业前的你自己）有趣的其他任何维度进行评估。如果适用，请包括任何测量数据。
    (c) **实现挑战**。描述你觉得最棘手的代码部分并解释原因。反思你是如何克服这些挑战的，以及是什么帮助你最终理解了那个让你困扰的概念。你是如何尝试确保你的代码维持你的假设、不变量和前提条件的，以及在哪些方面你觉得这很容易或困难？你是如何调试和测试你的代码的？
    (d) **剩余的 Bug**。尽你所能指出并解释代码中仍然存在的任何 bug（或未处理的边缘情况）。
4.  在你的报告中，也请填写完成此作业所花费的小时数以及任何其他评论。
5.  “如何提交”的具体方法将在截止日期前公布。
6.  如果在实验课上遇到任何问题，请尽快告知课程工作人员，或在 Ed 上发帖提问。祝你好运！