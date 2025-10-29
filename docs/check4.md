**English:**
CS144: Introduction to Computer Networking
Checkpoint 4: measuring the real world
Due: Sunday, February 16, 11:59 p.m. (late deadline: Feb. 19, 7 p.m.)
Winter 2025

**中文:**
CS144: 计算机网络导论
检查点 4：测量真实世界
截止日期：周日，2 月 16 日，晚上 11:59（延迟截止日期：2 月 19 日，晚上 7 点）
2025 年冬季

---

### **English:** 0 Collaboration Policy
### **中文:** 0 合作政策

---

**English:**
Collaboration Policy: Same as checkpoint 0. Please fully disclose any collaborators or any gray areas in your writeup—disclosure is the best policy.

**中文:**
合作政策：与检查点 0 相同。请在你的报告中完全披露任何合作者或任何灰色地带——披露是最好的策略。

---

### **English:** 1 Overview
### **中文:** 1 概述

---

**English:**
By this point in the class, you've implemented the Transmission Control Protocol in an almost fully standards-compliant manner. TCP implementations are arguably the world's single most popular computer program, found in billions of devices. Most implementations use a different strategy from yours, but because all TCP implementations share a common language, they are all interoperable—every TCP implementation can be a peer with any other, across the whole Internet. This checkpoint won't use your TCP implementation: it's about measuring the long-term statistics of some real-world Internet paths.

**中文:**
到课程的这个阶段，你已经以一种几乎完全符合标准的方式实现了传输控制协议（Transmission Control Protocol）。TCP 的实现可以说是世界上最受欢迎的计算机程序，存在于数十亿台设备中。大多数实现使用与你不同的策略，但因为所有的 TCP 实现都共享一种通用语言，所以它们都是可互操作的——每个 TCP 实现都可以与互联网上的任何其他实现成为对等方。这个检查点不会使用你的 TCP 实现：它是关于测量一些真实世界互联网路径的长期统计数据。

---

**English:**
To complete this checkpoint, we want you to choose and characterize at least three “interesting” Internet paths. Each path will be between your computer and another host and will either go some significant distance (RTT greater than 100 ms) or will include at least one “interesting" link along the way (e.g. a Wi-Fi or tethered cellular or satellite link). Ideally your final report will include a mix—at least one long-distance “boring" path and at least one path that includes an “interesting" link.

**中文:**
为了完成这个检查点，我们希望你选择并描述至少三个“有趣”的互联网路径。每条路径都将在你的计算机和另一台主机之间，并且要么跨越相当长的距离（RTT 大于 100 毫秒），要么沿途至少包含一个“有趣”的链接（例如 Wi-Fi、蜂窝网络共享或卫星链接）。理想情况下，你的最终报告将包含一个混合组合——至少一条长距离的“无聊”路径和至少一条包含“有趣”链接的路径。

---

**English:**
For each path, please measure at least the below statistics:

**中文:**
对于每条路径，请至少测量以下统计数据：

---

### **English:** 2 Collecting data
### **中文:** 2 收集数据

---

**English:**
1. Choose a remote host on the Internet to ping (measured by ping from your computer or VM). Some possibilities of faraway paths to get there:
    * www.cs.ox.ac.uk (Oxford University CS department webserver, United Kingdom)
    * 162.105.253.58 (Computer Center of Peking University, China)
    * www.canterbury.ac.nz (University of Canterbury webserver, New Zealand)
    * 41.186.255.86 (MTN Rwanda)
    * A friend's VM on the CS144 private network
    * preferred: an original choice with an RTT of at least 100 ms from you or that requires crossing a wireless link

**中文:**
1.  在互联网上选择一个远程主机进行 ping 测试（从你的计算机或虚拟机上测量）。一些可以到达的遥远路径的可能性：
    *   www.cs.ox.ac.uk（英国牛津大学计算机系网络服务器）
    *   162.105.253.58（中国北京大学计算中心）
    *   www.canterbury.ac.nz（新西兰坎特伯雷大学网络服务器）
    *   41.186.255.86（MTN 卢旺达）
    *   CS144 私有网络上一个朋友的虚拟机
    *   **首选**：一个你自选的目标，其 RTT 距离你至少 100 毫秒，或者需要跨越无线链接

---

**English:**
2. Use the `mtr` or `traceroute` commands to trace the route between your VM and this host.
3. Run a `ping` for at least an hour to collect data on this Internet path. Use a command like `ping -D -n -i 0.2 hostname | tee data.txt` to save the data in the "data.txt" file. (The `-D` argument makes ping record the timestamp of every line, and `-i 0.2` makes it send one “echo request" ICMP message every 0.2 seconds. The `-n` argument makes it skip trying to use DNS to reverse-lookup the replying IP address to a hostname.)
4. Note: A default-sized ping every 0.2 seconds is fine, but please do not flood anybody with traffic faster than this for more than a few seconds.

**中文:**
2.  使用 `mtr` 或 `traceroute` 命令追踪你的虚拟机与该主机之间的路由。
3.  运行 `ping` 至少一小时，以收集该互联网路径上的数据。使用类似 `ping -D -n -i 0.2 hostname | tee data.txt` 的命令将数据保存在 "data.txt" 文件中。（`-D` 参数使 ping 记录每行的时间戳，`-i 0.2` 使其每 0.2 秒发送一个“回显请求”ICMP 消息。`-n` 参数使其跳过尝试使用 DNS 对回复的 IP 地址进行反向查找主机名。）
4.  注意：每 0.2 秒发送一个默认大小的 ping 是可以的，但请不要用比这更快的流量淹没任何人超过几秒钟。

---

### **English:** 3 Analyzing data
### **中文:** 3 分析数据

---

**English:**
If you sent five pings per second for an hour, you will have sent approximately 3,600 echo requests (= 5 × 3600), of which we expect the vast majority to have received a reply in the ping output. Using the programming language and graphing tools of your choice, please compute and graph at least the following information:

**中文:**
如果你以每秒五次的频率发送 ping 持续一小时，你将发送大约 3,600 个回显请求（= 5 × 3600），我们预计其中绝大多数会在 ping 的输出中收到回复。请使用你选择的编程语言和绘图工具，计算并绘制至少以下信息：

---

**English:**
1. What was the overall delivery rate over the entire interval? In other words: how many echo replies were received, divided by how many echo requests were sent? (Note: ping on GNU/Linux doesn't print any message about echo replies that are not received. You'll have to identify missing replies by looking for missing sequence numbers.)
2. What was the longest consecutive string of successful pings (all replied-to in a row)?
3. What was the longest burst of losses (all not replied-to in a row)?
4. Produce a graph showing the autocorrelation of “packet loss” over time. In other words:
    * Given that echo request #N received a reply, what is the probability that echo request #(N+k) was also successfully replied-to? In your graph, include a bar for each k between -10 and 10 (inclusive).
    * Given that echo request #N did not receive a reply, what is the probability that echo request #(N+k) was also not replied-to?
    * How do these figures (the conditional delivery rates) compare with the overall “unconditional” packet delivery rate in the first question? How independent or "bursty” were the losses?
5. What was the minimum RTT seen over the entire interval? (This is probably a reasonable approximation of the true MinRTT...)
6. What was the maximum RTT seen over the entire interval?

**中文:**
1.  整个时间间隔内的总体投递率是多少？换句话说：收到了多少回显应答，除以发送了多少回显请求？（注意：GNU/Linux 上的 ping 不会打印任何关于未收到回显应答的消息。你将需要通过查找缺失的序列号来识别丢失的回复。）
2.  最长的连续成功 ping 序列（连续全部收到回复）是多长？
3.  最长的连续丢包（连续全部未收到回复）是多长？
4.  生成一个图表，显示“丢包”随时间的自相关性。换句话说：
    *   给定回显请求 #N 收到了回复，回显请求 #(N+k) 也成功收到回复的概率是多少？在你的图表中，为 k 在 -10 到 10（含）之间的每个值包含一个条形。
    *   给定回显请求 #N **没有**收到回复，回显请求 #(N+k) 也**没有**收到回复的概率是多少？
    *   这些数据（条件投递率）与第一个问题中的总体“无条件”丢包率相比如何？丢包是独立的还是“突发性的”？
5.  在整个时间间隔内观察到的最小 RTT 是多少？（这可能是真实最小 RTT 的一个合理近似值...）
6.  在整个时间间隔内观察到的最大 RTT 是多少？

---

**English:**
7. Make a graph of the RTT as a function of time. Label the x-axis with the actual time of day (covering the hour+ period), and the y-axis should be the number of milliseconds of RTT.
8. Graph the Cumulative Distribution Function of the distribution of RTTs observed. This is a graph where the x-axis is each observed value of RTT, and the y-axis is the proportion of samples that were less than or equal to this number (so the y-axis will go from 0 to 1). What rough shape is the distribution?
9. Make a scatter plot of the correlation between “RTT of ping #N” and “RTT of ping #N+1". The x-axis should be the number of milliseconds from the first RTT, and the y-axis should be the number of milliseconds from the second RTT. How correlated is the RTT over time?
10. Do some brief (less than 10 seconds) experiments where you send a higher data rate of pings, by increasing the packet size and frequency. On Linux, you can increase the size of an echo request (and reply) with the “-s” argument (do not use values greater than 1400), and you can increase the frequency of an echo request by reducing the interval given to the “-i" argument. You can tell ping to stop after a certain number of requests with the “-c” argument. Make a graph of the overall data rate of replies (packet size × number of replies) / total duration as a function of the data rate of your echo requests. Does it level off at some value? What was the maximum throughput you were able to obtain?
11. What are your conclusions from the data? Did the network path behave the way you were expecting? What (if anything) surprised you from looking at the graphs and summary statistics?
12. What interesting comparisons can you make between this path and the other network paths you characterized?

Please submit your report as a PDF via Gradescope.

**中文:**
7.  制作一个 RTT 作为时间函数的图表。x 轴用实际的当日时间标记（覆盖一小时以上的时间段），y 轴应该是 RTT 的毫秒数。
8.  绘制观察到的 RTT 分布的累积分布函数（Cumulative Distribution Function）。这是一个图表，其中 x 轴是每个观察到的 RTT 值，y 轴是小于或等于该值的样本比例（所以 y 轴将从 0 到 1）。这个分布的大致形状是什么？
9.  制作一个“ping #N 的 RTT”与“ping #(N+1) 的 RTT”之间相关性的散点图。x 轴应该是第一个 RTT 的毫秒数，y 轴应该是第二个 RTT 的毫秒数。RTT 随时间的相关性如何？
10. 进行一些简短的（少于 10 秒）实验，通过增加包大小和频率来发送更高数据率的 ping。在 Linux 上，你可以使用“-s”参数增加回显请求（和回复）的大小（不要使用大于 1400 的值），并且可以通过减小给“-i”参数的间隔来增加回显请求的频率。你可以使用“-c”参数告诉 ping 在一定数量的请求后停止。制作一个总体回复数据率（（包大小 × 回复数） / 总时长）作为你回显请求数据率的函数的图表。它是否在某个值上趋于平稳？你能够获得的最大吞吐量是多少？
11. 你从数据中得出了什么结论？网络路径的行为是否如你所料？在查看图表和摘要统计数据时，有什么（如果有的话）让你感到惊讶？
12. 在这条路径和你描述的其他网络路径之间，你能做出哪些有趣的比较？

请通过 Gradescope 以 PDF 格式提交你的报告。