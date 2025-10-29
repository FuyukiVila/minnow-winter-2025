**English:**
CS144: Introduction to Computer Networking
Winter 2025
Lab Checkpoint 2: the TCP receiver

**中文:**
CS144: 计算机网络导论
冬季 2025
实验检查点 2：TCP 接收器

---

**English:**
Due: Sunday, January 26, 11:59 p.m. (late/extension deadline: Wed. Jan. 29 @ 7 p.m.)
Collaboration Policy: Same as checkpoint 0. Please do not look at other students' code or solutions to past versions of these assignments. Please fully disclose any collaborators or any gray areas in your writeup—disclosure is the best policy.

**中文:**
截止日期：周日，1 月 26 日，晚上 11:59（延迟/延期截止日期：周三，1 月 29 日 @ 晚上 7 点）
合作政策：与检查点 0 相同。请不要查看其他学生的代码或这些作业过去版本的解决方案。请在你的报告中完全披露任何合作者或任何灰色地带——披露是最好的策略。

---

### **English:** 0 Overview
### **中文:** 0 概述

---

**English:**
Suggestion: read the whole lab document before implementing.
In Checkpoint 0, you implemented the abstraction of a flow-controlled byte stream (ByteStream). And in Checkpoint 1, you created a Reassembler that accepts a sequence of substrings, all excerpted from the same byte stream, and reassembles them back into the original stream.

**中文:**
建议：在实现之前阅读整个实验文档。
在检查点 0 中，你实现了一个流量控制字节流（`ByteStream`）的抽象。在检查点 1 中，你创建了一个 `Reassembler`，它接受一系列从同一字节流中摘录的子字符串，并将它们重新组装回原始流中。

---

**English:**
These modules will prove useful in your TCP implementation, but nothing in them was specific to the details of the Transmission Control Protocol. That changes now. In Checkpoint 2, you will implement the TCPReceiver, the part of a TCP implementation that handles the incoming byte stream.

**中文:**
这些模块将在你的 TCP 实现中证明是有用的，但它们本身并没有特定于传输控制协议（TCP）的细节。现在情况变了。在检查点 2 中，你将实现 `TCPReceiver`，这是 TCP 实现中处理传入字节流的部分。

---

**English:**
The TCPReceiver receives messages from the peer's sender (via the `receive()` method) and turns them into calls to a Reassembler, which eventually writes to the incoming ByteStream. Applications read from this ByteStream, just as you did in Lab 0 by reading from the TCPSocket.

**中文:**
`TCPReceiver` 从对端的发送方接收消息（通过 `receive()` 方法），并将它们转换为对 `Reassembler` 的调用，`Reassembler` 最终会写入到传入的 `ByteStream` 中。应用程序从这个 `ByteStream` 中读取数据，就像你在实验 0 中通过从 `TCPSocket` 读取数据一样。

---

**English:**
Meanwhile, the TCPReceiver also generates messages that go back to the peer's sender, via the `send()` method. These “receiver messages” are responsible for telling the sender:
1. the index of the “first unassembled” byte, which is called the “acknowledgment number" or “ackno.” This is the first byte that the receiver needs from the sender.
2. the available capacity in the output ByteStream. This is called the “window size”.

**中文:**
同时，`TCPReceiver` 也通过 `send()` 方法生成返回给对端发送方的消息。这些“接收器消息”负责告诉发送方：
1.  “第一个未组装”字节的索引，这被称为“确认号”（acknowledgment number）或“ackno”。这是接收器需要从发送方获取的第一个字节。
2.  输出 `ByteStream` 中的可用容量。这被称为“窗口大小”（window size）。

---

**English:**
Together, the ackno and window size describe the receiver's window: a range of indexes that the TCP sender is allowed to send. Using the window, the receiver can control the flow of incoming data, making the sender limit how much it sends until the receiver is ready for more. We sometimes refer to the ackno as the “left edge” of the window (smallest index the TCPReceiver is interested in), and the ackno + window size as the "right edge" (just beyond the largest index the TCPReceiver is interested in).

**中文:**
ackno 和窗口大小共同描述了接收器的窗口：一个 TCP 发送方被允许发送的索引范围。通过使用这个窗口，接收器可以控制传入数据的流量，让发送方在接收器准备好接收更多数据之前限制其发送量。我们有时将 ackno 称为窗口的“左边缘”（`TCPReceiver` 感兴趣的最小索引），将 ackno + 窗口大小称为“右边缘”（刚好超过 `TCPReceiver` 感兴趣的最大索引）。

---

**English:**
You've already done most of the algorithmic work involved in implementing the TCPReceiver when you wrote the Reassembler and ByteStream; this lab is about wiring those general classes up to the details of TCP. The hardest part will involve thinking about how TCP will represent each byte's place in the stream—known as a "sequence number.”

**中文:**
在编写 `Reassembler` 和 `ByteStream` 时，你已经完成了实现 `TCPReceiver` 所涉及的大部分算法工作；这个实验是关于将这些通用类与 TCP 的细节连接起来。最难的部分将是思考 TCP 如何表示流中每个字节的位置——这被称为“序列号”（sequence number）。

---

### **English:** 1 Getting started
### **中文:** 1 开始

---

**English:**
Your implementation of a TCPReceiver will use the same Minnow library that you used in Checkpoints 0 and 1, with additional classes and tests. To get started:
1. Make sure you have committed all your solutions to Checkpoint 1. Please don't modify any files outside the top level of the `src` directory, or `webget.cc`. You may have trouble merging the Checkpoint 1 starter code otherwise.
2. While inside the repository for the lab assignments, run `git fetch --all` to retrieve the most recent version of the lab assignment.
3. Download the starter code for Checkpoint 2 by running `git merge origin/check2-startercode` (If you have renamed the “origin” remote to be something else, you might need to use a different name here, e.g. `git merge upstream/check2-startercode`.)
4. Make sure your build system is properly set up: `cmake -S . -B build`
   * Note for arm64 (UTM) Mac users: The g++ 13 “sanitizers” (bug checkers) seem to run very slow on arm64. Minnow uses these to run the tests. If you are on an arm64 Mac, please configure `cmake` to use a different compiler:
     `cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++`
5. Compile the source code: `cmake --build build`
6. Open and start editing the `writeups/check2.md` file. This is the template for your lab writeup and will be included in your submission.

**中文:**
你的 `TCPReceiver` 实现将使用与检查点 0 和 1 中相同的 Minnow 库，但会增加一些额外的类和测试。开始步骤如下：
1.  确保你已经提交了检查点 1 的所有解决方案。请不要修改 `src` 顶级目录之外的任何文件，或 `webget.cc`。否则，在合并检查点 1 的起始代码时可能会遇到麻烦。
2.  在实验作业的仓库内，运行 `git fetch --all` 来获取实验作业的最新版本。
3.  通过运行 `git merge origin/check2-startercode` 来下载检查点 2 的起始代码。（如果你已将“origin”远程重命名为其他名称，你可能需要在此处使用不同的名称，例如 `git merge upstream/check2-startercode`。）
4.  确保你的构建系统已正确设置：`cmake -S . -B build`
    *   **arm64 (UTM) Mac 用户请注意**：g++ 13 的“sanitizers”（错误检查器）在 arm64 上似乎运行得非常慢。Minnow 使用这些来运行测试。如果你使用的是 arm64 Mac，请配置 `cmake` 使用不同的编译器：
        `cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++`
5.  编译源代码：`cmake --build build`
6.  打开并开始编辑 `writeups/check2.md` 文件。这是你实验报告的模板，并将包含在你的提交中。

---

### **English:** 2 Checkpoint 2: The TCP Receiver
### **中文:** 2 检查点 2：TCP 接收器

---

**English:**
TCP is a protocol that reliably conveys a pair of flow-controlled byte streams (one in each direction) over unreliable datagrams. Two parties, or “peers,” participate in the TCP connection, and each peer acts as both “sender” (of its own outgoing byte stream) and "receiver” (of an incoming byte stream) at the same time.
This week, you'll implement the “receiver" part of TCP, responsible for receiving messages from the sender, reassembling the byte stream (including its ending, when that occurs), and determining that messages that should be sent back to the sender for acknowledgment and flow control.

**中文:**
TCP 是一个通过不可靠的数据报可靠地传输一对流量控制字节流（每个方向一个）的协议。两个参与方，或称“对等方”（peers），参与 TCP 连接，每个对等方同时扮演“发送方”（发送自己的出站字节流）和“接收方”（接收一个入站字节流）的角色。
本周，你将实现 TCP 的“接收方”部分，负责从发送方接收消息，重组字节流（包括其结束标志，如果出现的话），并确定应发送回发送方的用于确认和流量控制的消息。

---

**English:**
*Why am I doing this? These signals are crucial to TCP's ability to provide the service of a flow-controlled, reliable byte stream over an unreliable datagram network. In TCP, acknowledgment means, “What's the index of the next byte that the receiver needs so it can reassemble more of the ByteStream?” This tells the sender what bytes it needs to send or resend. Flow control means, “What range of indices is the receiver interested and willing to receive?" (a function of its available capacity). This tells the sender how much it's allowed to send.

**中文:**
*我为什么要做这个？ 这些信号对于 TCP 在不可靠的数据报网络上提供流量控制、可靠字节流服务的能力至关重要。在 TCP 中，**确认（acknowledgment）**意味着：“接收方需要下一个字节的索引是什么，以便它可以重组更多的 `ByteStream`？”这告诉发送方它需要发送或重传哪些字节。**流量控制（Flow control）**意味着：“接收方感兴趣并愿意接收的索引范围是什么？”（这是其可用容量的函数）。这告诉发送方它被允许发送多少数据。

---

#### **English:** 2.1 Translating between 64-bit indexes and 32-bit seqnos
#### **中文:** 2.1 在 64 位索引和 32 位序列号之间转换

---

**English:**
As a warmup, we'll need to implement TCP's way of representing indexes. Last week you created a Reassembler that reassembles substrings where each individual byte has a 64-bit stream index, with the first byte in the stream always having index zero. A 64-bit index is big enough that we can treat it as never overflowing.¹ In the TCP headers, however, space is precious, and each byte's index in the stream is represented not with a 64-bit index but with a 32-bit “sequence number,” or “seqno." This adds three complexities:

**中文:**
作为热身，我们需要实现 TCP 表示索引的方式。上周你创建了一个 `Reassembler`，它重组子字符串，其中每个字节都有一个 64 位的流索引（stream index），流中的第一个字节的索引总是零。一个 64 位的索引足够大，我们可以认为它**永远不会溢出**。¹然而，在 TCP 头部中，空间是宝贵的，流中每个字节的索引不是用 64 位索引表示，而是用 32 位的“序列号”（sequence number）或“seqno”表示。这带来了三个复杂性：

---

**English:**
1. Your implementation needs to plan for 32-bit integers to wrap around. Streams in TCP can be arbitrarily long—there's no limit to the length of a ByteStream that can be sent over TCP. But 2³² bytes is only 4 GiB, which is not so big. Once a 32-bit sequence number counts up to 2³² – 1, the next byte in the stream will have the sequence number zero.
2. TCP sequence numbers start at a random value: To improve robustness and avoid getting confused by old segments belonging to earlier connections between the same endpoints, TCP tries to make sure sequence numbers can't be guessed and are unlikely to repeat. So the sequence numbers for a stream don't start at zero. The first sequence number in the stream is a random 32-bit number called the Initial Sequence Number (ISN). This is the sequence number that represents the “zero point" or the SYN (beginning of stream). The rest of the sequence numbers behave normally after that: the first byte of data will have the sequence number of the ISN+1 (mod 2³²), the second byte will have the ISN+2 (mod 2³²), etc.
3. The logical beginning and ending each occupy one sequence number: In addition to ensuring the receipt of all bytes of data, TCP makes sure that the beginning and ending of the stream are received reliably. Thus, in TCP the SYN (beginning-of-stream) and FIN (end-of-stream) control flags are assigned sequence numbers. Each of these occupies one sequence number. (The sequence number occupied by the SYN flag is the ISN.) Each byte of data in the stream also occupies one sequence number. Keep in mind that SYN and FIN aren't part of the stream itself and aren't "bytes” —they represent the beginning and ending of the byte stream itself.

**中文:**
1.  **你的实现需要为 32 位整数的回绕（wrap around）做好计划**。TCP 中的流可以是任意长的——通过 TCP 发送的 `ByteStream` 的长度没有限制。但是 2³² 字节只有 4 GiB，这并不算大。一旦一个 32 位的序列号计数到 2³² – 1，流中的下一个字节的序列号将是零。
2.  **TCP 序列号从一个随机值开始**：为了提高鲁棒性并避免被属于同一端点之间早期连接的旧段所混淆，TCP 试图确保序列号不能被猜测并且不太可能重复。所以流的序列号不从零开始。流中的第一个序列号是一个称为初始序列号（Initial Sequence Number, ISN）的随机 32 位数字。这个序列号代表了“零点”或 SYN（流的开始）。此后的其余序列号行为正常：第一个数据字节的序列号将是 ISN+1 (mod 2³²)，第二个字节将是 ISN+2 (mod 2³²)，依此类推。
3.  **逻辑上的开始和结束各自占用一个序列号**：除了确保接收所有数据字节外，TCP 还确保流的开始和结束被可靠地接收。因此，在 TCP 中，SYN（流开始）和 FIN（流结束）控制标志被分配了序列号。它们每个都**占用一个序列号**。（SYN 标志占用的序列号是 ISN。）流中的每个数据字节也占用一个序列号。请记住，SYN 和 FIN 本身不是流的一部分，也不是“字节”——它们代表字节流本身的开始和结束。

---

**English:**
These sequence numbers (seqnos) are transmitted in the header of each TCP segment. (And, again, there are two streams—one in each direction. Each stream has separate sequence numbers and a different random ISN.) It's also sometimes helpful to talk about the concept of an "absolute sequence number” (which always starts at zero and doesn't wrap), and about a "stream index" (what you've already been using with your Reassembler: an index for each byte in the stream, starting at zero).
To make these distinctions concrete, consider the byte stream containing just the three-letter string 'cat'. If the SYN happened to have seqno 2³² – 2, then the seqnos, absolute seqnos, and stream indices of each byte are:

**中文:**
这些序列号（seqnos）在每个 TCP 段的头部中传输。（再次强调，有两个流——每个方向一个。每个流都有独立的序列号和不同的随机 ISN。）有时，讨论“绝对序列号”（absolute sequence number，它总是从零开始并且不会回绕）和“流索引”（stream index，你已经在你的 `Reassembler` 中使用过的：流中每个字节的索引，从零开始）的概念也很有帮助。
为了使这些区别具体化，考虑一个只包含三个字母字符串 'cat' 的字节流。如果 SYN 恰好有序列号 2³² – 2，那么每个字节的序列号、绝对序列号和流索引是：

---

**(Table)**
| element        | SYN   | c     | a    | t    | FIN  |
| -------------- | ----- | ----- | ---- | ---- | ---- |
| seqno          | 2³²-2 | 2³²-1 | 0    | 1    | 2    |
| absolute seqno | 0     | 1     | 2    | 3    | 4    |
| stream index   |       | 0     | 1    | 2    |      |

---

**English:**
¹Transmitting at 100 gigabits/sec, it would take almost 50 years to reach 2⁶⁴ bytes. By contrast, it takes only a third of a second to reach 2³² bytes.

**中文:**
¹以 100 吉比特/秒的速度传输，达到 2⁶⁴ 字节需要将近 50 年。相比之下，达到 2³² 字节只需要三分之一秒。

---

![image-20250913184557150](./assets/image-20250913184557150.png)

**中文:**
该图显示了 TCP 中涉及的三种不同类型的索引：
**序列号 (Sequence Numbers)**

*   从 ISN 开始
*   包括 SYN/FIN
*   32 位，会回绕
*   "seqno"
**绝对序列号 (Absolute Sequence Numbers)**
*   从 0 开始
*   包括 SYN/FIN
*   64 位，不回绕
*   "absolute seqno"
**流索引 (Stream Indices)**
*   从 0 开始
*   不包括 SYN/FIN
*   64 位，不回绕
*   "stream index"

---

**English:**
Converting between absolute sequence numbers and stream indices is easy enough—just add or subtract one. Unfortunately, converting between sequence numbers and absolute sequence numbers is a bit harder, and confusing the two can produce tricky bugs. To prevent these bugs systematically, we'll represent sequence numbers with a custom type: `Wrap32`, and write the conversions between it and absolute sequence numbers (represented with `uint64_t`). `Wrap32` is an example of a wrapper type: a type that contains an inner type (in this case `uint32_t`) but provides a different set of functions/operators.
We've defined the type for you and provided some helper functions, but you'll implement the conversions in `wrapping_integers.cc`:
1. `static Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )`
   Convert absolute seqno → seqno. Given an absolute sequence number (n) and an Initial Sequence Number (zero_point), produce the (relative) sequence number for n.
2. `uint64_t unwrap( Wrap32 zero_point, uint64_t checkpoint ) const`
   Convert seqno → absolute seqno. Given a sequence number (the `Wrap32`), the Initial Sequence Number (zero_point), and an absolute `checkpoint` sequence number, find the corresponding absolute sequence number that is **closest to** the `checkpoint`.
   Note: A `checkpoint` is required because any given seqno corresponds to many absolute seqnos. E.g. with an ISN of zero, the seqno “17” corresponds to the absolute seqno of 17, but also 2³² + 17, or 2³³ + 17, or 2³³ + 2³² + 17, or 2³⁴ + 17, or 2³⁴ + 2³² + 17, etc. The checkpoint helps resolve the ambiguity: it's an absolute seqno that the user of this class knows is “in the ballpark" of the correct answer. In your TCP implementation, you'll use the first unassembled index as the checkpoint.
   Hint: The cleanest/easiest implementation will use the helper functions provided in `wrapping_integers.hh`. The wrap/unwrap operations should preserve offsets—two seqnos that differ by 17 will correspond to two absolute seqnos that also differ by 17.
   Hint #2: We're expecting one line of code for `wrap`, and less than 10 lines of code for `unwrap`. If you find yourself implementing a lot more than this, it might be wise to step back and try to think of a different strategy.

**中文:**
在绝对序列号和流索引之间转换相当容易——只需加一或减一。不幸的是，在序列号和绝对序列号之间转换要困难一些，并且混淆两者会产生棘手的错误。为了系统地防止这些错误，我们将用一个自定义类型来表示序列号：`Wrap32`，并编写它与绝对序列号（用 `uint64_t` 表示）之间的转换。`Wrap32` 是一个包装器类型（wrapper type）的例子：一个包含内部类型（在这种情况下是 `uint32_t`）但提供一组不同函数/运算符的类型。
我们已经为你定义了该类型并提供了一些辅助函数，但你需要在 `wrapping_integers.cc` 中实现转换：

1.  `static Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )`
    将**绝对序列号 → 序列号**。给定一个绝对序列号 (n) 和一个初始序列号 (zero\_point)，生成 n 的（相对）序列号。
2.  `uint64_t unwrap( Wrap32 zero_point, uint64_t checkpoint ) const`
    将**序列号 → 绝对序列号**。给定一个序列号 (即 `Wrap32` 对象)、一个初始序列号 (zero\_point) 和一个绝对的 `checkpoint` 序列号，找出与该 `checkpoint` **最接近**的相应绝对序列号。
    注意：需要一个 `checkpoint` 是因为任何给定的序列号都对应于许多绝对序列号。例如，当 ISN 为零时，序列号“17”对应于绝对序列号 17，但也对应 2³² + 17、2³³ + 17 等等。`checkpoint` 有助于解决这种歧义：它是一个该类的用户知道与正确答案“在同一范围内”的绝对序列号。在你的 TCP 实现中，你将使用第一个未组装的索引作为 `checkpoint`。
    **提示**：最简洁/最简单的实现将使用 `wrapping_integers.hh` 中提供的辅助函数。wrap/unwrap 操作应保留偏移量——相差 17 的两个序列号将对应于也相差 17 的两个绝对序列号。
    **提示 #2**：我们期望 `wrap` 的代码为一行，`unwrap` 的代码少于 10 行。如果你发现自己实现的远不止这些，那么退一步思考一种不同的策略可能是明智的。

---

**English:**
You can test your implementation by running the tests: `cmake --build build --target check2`
(Reminder: Mac arm64 users should have configured to use the “clang++" compiler—see above.)

**中文:**
你可以通过运行测试来检验你的实现：`cmake --build build --target check2`
（提醒：Mac arm64 用户应该已经配置使用“clang++”编译器——见上文。）

---

#### **English:** 2.2 Implementing the TCP receiver
#### **中文:** 2.2 实现 TCP 接收器

---

**English:**
Congratulations on getting the wrapping and unwrapping logic right! We'll shake your hand (or, post-COVID, elbow-bump) if this victory happens at the lab session. In the rest of this lab, you'll be implementing the TCPReceiver. It will (1) receive messages from its peer's sender and reassemble the ByteStream using a Reassembler, and (2) send messages back to the peer's sender that contain the acknowledgment number (ackno) and window size. We're expecting this to take about 15 lines of code in total.
First, let's review the format of a TCP “sender message," which contains the information about the ByteStream. These messages are sent from a TCPSender to its peer's TCPReceiver:

**中文:**
恭喜你正确实现了包装和解包逻辑！如果这个胜利发生在实验课上，我们会和你握手（或者，在后疫情时代，碰碰手肘）。在本实验的其余部分，你将实现 `TCPReceiver`。它将 (1) 从其对等方的发送方接收消息并使用 `Reassembler` 重组 `ByteStream`，以及 (2) 将包含确认号 (ackno) 和窗口大小的消息发送回对等方的发送方。我们预计这总共需要大约 15 行代码。
首先，让我们回顾一下 TCP“发送方消息”的格式，其中包含有关 `ByteStream` 的信息。这些消息从一个 `TCPSender` 发送给其对等方的 `TCPReceiver`：

---

**中文:**
```cpp
/*
 * The TCPSenderMessage structure contains five fields (minnow/util/tcp_sender_message.hh):
 *
 * 1) The sequence number (seqno) of the beginning of the segment. If the SYN flag is set,
 *    this is the sequence number of the SYN flag. Otherwise, it's the sequence number of
 *    the beginning of the payload.
 *
 * 2) The SYN flag. If set, this segment is the beginning of the byte stream, and the seqno field
 *    contains the Initial Sequence Number (ISN) -- the zero point.
 *
 * 3) The payload: a substring (possibly empty) of the byte stream.
 *
 * 4) The FIN flag. If set, the payload represents the ending of the byte stream.
 *
 * 5) The RST (reset) flag. If set, the stream has suffered an error and the connection
 *    should be aborted.
 */
/*
 * TCPSenderMessage 结构体包含五个字段 (minnow/util/tcp_sender_message.hh):
 *
 * 1) 段起始位置的序列号 (seqno)。如果设置了 SYN 标志，
 *    这是 SYN 标志的序列号。否则，它是
 *    载荷（payload）起始位置的序列号。
 *
 * 2) SYN 标志。如果设置，此段是字节流的开始，并且 seqno 字段
 *    包含初始序列号 (ISN) -- 即零点。
 *
 * 3) 载荷：字节流的一个子字符串（可能为空）。
 *
 * 4) FIN 标志。如果设置，此载荷代表字节流的结束。
 *
 * 5) RST (重置) 标志。如果设置，表示流发生了错误，连接
 *    应被中止。
 */
struct TCPSenderMessage
{
    Wrap32 seqno { 0 };

    bool SYN {};
    std::string payload {};
    bool FIN {};

    bool RST {};

    // 这个段使用了多少个序列号？
    size_t sequence_length() const { return SYN + payload.size() + FIN; }
};
```

---

**English:**
The TCPReceiver generates its own messages back to the peer's TCPSender:

**中文:**
`TCPReceiver` 生成自己的消息返回给对等方的 `TCPSender`：

```cpp
/*
 * The TCPReceiverMessage structure contains three fields (minnow/util/tcp_receiver_message.hh):
 *
 * 1) The acknowledgment number (ackno): the *next* sequence number needed by the TCP Receiver.
 *    This is an optional field that is empty if the TCPReceiver hasn't yet received the
 *    Initial Sequence Number.
 *
 * 2) The window size. This is the number of sequence numbers that the TCP receiver is interested
 *    to receive, starting from the ackno if present. The maximum value is 65,535 (UINT16_MAX from
 *    the <cstdint> header).
 *
 * 3) The RST (reset) flag. If set, the stream has suffered an error and the connection
 *    should be aborted.
 */

/*
 * TCPReceiverMessage 结构体包含三个字段 (minnow/util/tcp_receiver_message.hh):
 *
 * 1) 确认号 (ackno): TCP 接收器需要的 *下一个* 序列号。
 *    这是一个可选字段，如果 TCPReceiver 尚未收到
 *    初始序列号，则为空。
 *
 * 2) 窗口大小。这是 TCP 接收器有兴趣接收的序列号数量，
 *    如果 ackno 存在，则从 ackno 开始计算。最大值为 65,535 (来自
 *    <cstdint> 头文件的 UINT16_MAX)。
 *
 * 3) RST (重置) 标志。如果设置，表示流发生了错误，连接
 *    应被中止。
 */
struct TCPReceiverMessage
{
    std::optional<Wrap32> ackno {};
    uint16_t window_size {};
    bool RST {};
};
```

---

**English:**
Your TCPReceiver's job is to receive one of these kinds of messages and send the other:
```cpp
class TCPReceiver
{
public:
    // Construct with given Reassembler
    explicit TCPReceiver( Reassembler&& reassembler ) : reassembler_( std::move( reassembler ) ) {}

    // The TCPReceiver receives TCPSenderMessages from the peer's TCPSender.
    void receive( TCPSenderMessage message );

    // The TCPReceiver sends TCPReceiverMessages to the peer's TCPSender.
    TCPReceiverMessage send() const;

    // Access the output (only Reader is accessible non-const)
    const Reassembler& reassembler() const { return reassembler_; }
    Reader& reader() { return reassembler_.reader(); }
    const Reader& reader() const { return reassembler_.reader(); }
    const Writer& writer() const { return reassembler_.writer(); }
private:
    Reassembler reassembler_;
};
```

**中文:**
你的 `TCPReceiver` 的工作是接收其中一种消息并发送另一种：
```cpp
class TCPReceiver
{
public:
    // 使用给定的 Reassembler 进行构造
    explicit TCPReceiver( Reassembler&& reassembler ) : reassembler_( std::move( reassembler ) ) {}

    // TCPReceiver 从对等方的 TCPSender 接收 TCPSenderMessages。
    void receive( TCPSenderMessage message );

    // TCPReceiver 向对等方的 TCPSender 发送 TCPReceiverMessages。
    TCPReceiverMessage send() const;

    // 访问输出（只有 Reader 是非 const 可访问的）
    const Reassembler& reassembler() const { return reassembler_; }
    Reader& reader() { return reassembler_.reader(); }
    const Reader& reader() const { return reassembler_.reader(); }
    const Writer& writer() const { return reassembler_.writer(); }
private:
    Reassembler reassembler_;
};
```

---

#### **English:** 2.2.1 `receive()`
#### **中文:** 2.2.1 `receive()`

---

**English:**
This is method will be called each time a new segment is received from the peer's sender. This method needs to:
* Set the Initial Sequence Number if necessary. The sequence number of the first-arriving segment that has the SYN flag set is the initial sequence number. You'll want to keep track of that in order to keep converting between 32-bit wrapped seqnos/acknos and their absolute equivalents. (Note that the SYN flag is just one flag in the header. The same message could also carry data or have the FIN flag set.)
* Push any data to the Reassembler. If the FIN flag is set in a TCPSegment's header, that means that the last byte of the payload is the last byte of the entire stream. Remember that the `Reassembler` expects stream indexes starting at zero; you will have to unwrap the seqnos to produce these.

**中文:**
每次从对等方的发送方接收到一个新的段时，都会调用此方法。该方法需要：

*   **如有必要，设置初始序列号**。第一个到达的、设置了 SYN 标志的段的序列号就是初始序列号。你需要跟踪这个值，以便在 32 位回绕的 seqnos/acknos 与其绝对等价物之间进行转换。（请注意，SYN 标志只是头部中的一个标志。同一个消息也可能携带数据或设置了 FIN 标志。）
*   **将任何数据推送到 Reassembler**。如果 TCP 段的头部设置了 FIN 标志，这意味着载荷的最后一个字节是整个流的最后一个字节。请记住，`Reassembler` 期望的流索引从零开始；你将需要解开（unwrap）序列号以生成这些索引。

---

### **English:** 3 Development and debugging advice
### **中文:** 3 开发和调试建议

---

**English:**
1. Implement the TCPReceiver's public interface (and any private methods or functions you'd like) in the file `tcp_receiver.cc`. You may add any private members you like to the `TCPReceiver` class in `tcp_receiver.hh`.
2. You can test your code with `cmake --build build --target check2`
3. Please re-read the section on “using Git" in the Lab 0 document, and remember to keep the code in the Git repository it was distributed in on the `main` branch. Make small commits, using good commit messages that identify what changed and why.
4. Please work to make your code readable to the CA who will be grading it for style. Use reasonable and clear naming conventions for variables. Use comments to explain complex or subtle pieces of code. Use “defensive programming”—explicitly check preconditions of functions or invariants, and throw an exception if anything is ever wrong. Use modularity in your design—identify common abstractions and behaviors and factor them out when possible. Blocks of repeated code and enormous functions will make your code harder to follow.
5. Please also keep to the “Modern C++” style described in the Checkpoint 0 document. The cppreference website (https://en.cppreference.com) is a great resource, although you won't need any sophisticated features of C++ to do these labs.

**中文:**
1.  在 `tcp_receiver.cc` 文件中实现 `TCPReceiver` 的公共接口（以及你喜欢的任何私有方法或函数）。你可以在 `tcp_receiver.hh` 中的 `TCPReceiver` 类中添加任何你喜欢的私有成员。
2.  你可以用 `cmake --build build --target check2` 来测试你的代码。
3.  请重读实验 0 文档中关于“使用 Git”的部分，并记住将代码保存在其分发时所在的 `main` 分支的 Git 仓库中。进行小的提交，并使用能够说明更改内容和原因的良好提交信息。
4.  请努力使你的代码对于将要对其进行风格评分的助教（CA）来说是可读的。为变量使用合理且清晰的命名约定。使用注释来解释复杂或微妙的代码片段。使用“防御性编程”——明确检查函数或不变量的前提条件，如果出现任何错误就抛出异常。在你的设计中使用模块化——识别共同的抽象和行为，并在可能时将它们提取出来。重复的代码块和庞大的函数将使你的代码难以理解。
5.  也请遵守检查点 0 文档中描述的“现代 C++”风格。cppreference 网站（https://en.cppreference.com）是一个很好的资源，尽管你不需要使用 C++ 的任何复杂特性来完成这些实验。

---

### **English:** 4 Submit
### **中文:** 4 提交

---

**English:**
1. In your submission, please only make changes to the `.hh` and `.cc` files in the `src` directory. Within these files, please feel free to add private members as necessary, but please don't change the `public` interface of any of the classes.
2. Before handing in any assignment, please run these in order:
   (a) Make sure you have committed all of your changes to the Git repository. You can run `git status` to make sure there are no outstanding changes. Remember: make small commits as you code.
   (b) `cmake --build build --target format` (to normalize the coding style)
   (c) `cmake --build build --target check2` (to make sure the automated tests pass)
   (d) Optional: `cmake --build build --target tidy` (suggests improvements to follow good C++ programming practices)
3. Write a report in `writeups/check2.md`. This file should be a roughly 20-to-50-line document with no more than 80 characters per line to make it easier to read. The report should contain the following sections:
   (a) Program Structure and Design. Describe the high-level structure and design choices embodied in your code. You do not need to discuss in detail what you inherited from the starter code. Use this as an opportunity to highlight important design aspects and provide greater detail on those areas for your grading TA to understand. You are strongly encouraged to make this writeup as readable as possible by using subheadings and outlines. Please do not simply translate your program into an paragraph of English.
   (b) Alternative design choices that you considered or ideally evaluated in terms of their performance, difficulty to write (e.g., hours required to produce a bug-free implementation), difficulty to read (e.g., lines of code and their degree of subtlety or nonobvious correctness), and any other dimensions you think are interesting for the reader (or for your own past self before you did this assignment). Include any measurements if applicable.
   (c) Implementation Challenges. Describe the parts of code that you found most troublesome and explain why. Reflect on how you overcame those challenges and what helped you finally understand the concept that was giving you trouble. How did you attempt to ensure that your code maintained your assumptions, invariants, and preconditions, and in what ways did you find this easy or difficult? How did you debug and test your code?
   (d) Remaining Bugs. Point out and explain as best you can any bugs (or unhandled edge cases) that remain in the code.
4. In your writeup, please also fill in the number of hours the assignment took you and any other comments.
5. Please let the course staff know ASAP of any problems at the lab session, or by posting a question on Ed. Good luck!

**中文:**
1.  在你的提交中，请仅对 `src` 目录中的 `.hh` 和 `.cc` 文件进行更改。在这些文件中，你可以根据需要随意添加私有成员，但请不要更改任何类的 `public` 接口。
2.  在提交任何作业之前，请按以下顺序运行这些命令：
    (a) 确保你已经将所有更改提交到 Git 仓库。你可以运行 `git status` 来确保没有未完成的更改。记住：在你编码时进行小的提交。
    (b) `cmake --build build --target format` （以规范化编码风格）
    (c) `cmake --build build --target check2` （以确保自动化测试通过）
    (d) 可选：`cmake --build build --target tidy` （建议改进以遵循良好的 C++ 编程实践）
3.  在 `writeups/check2.md` 中撰写一份报告。这个文件应该是一个大约 20 到 50 行的文档，每行不超过 80 个字符，以便于阅读。报告应包含以下部分：
    (a) **程序结构与设计**。描述你代码中体现的高层结构和设计选择。你不需要详细讨论你从起始代码继承了什么。以此为契机，突出重要的设计方面，并为你的评分助教提供更详细的信息以理解这些领域。强烈建议你通过使用副标题和提纲来使这份报告尽可能可读。请不要简单地将你的程序翻译成一段英文。
    (b) **备选设计选择**。描述你曾考虑过或理想情况下评估过的其他设计选择，从它们的性能、编写难度（例如，产生一个无 bug 实现所需的小时数）、阅读难度（例如，代码行数及其精妙或不明显的正确性程度），以及你认为对读者（或对完成此作业前的你自己）有趣的其他任何维度进行评估。如果适用，请包括任何测量数据。
    (c) **实现挑战**。描述你觉得最棘手的代码部分并解释原因。反思你是如何克服这些挑战的，以及是什么帮助你最终理解了那个让你困扰的概念。你是如何尝试确保你的代码维持你的假设、不变量和前提条件的，以及在哪些方面你觉得这很容易或困难？你是如何调试和测试你的代码的？
    (d) **剩余的 Bug**。尽你所能指出并解释代码中仍然存在的任何 bug（或未处理的边缘情况）。
4.  在你的报告中，也请填写完成此作业所花费的小时数以及任何其他评论。
5.  如果在实验课上遇到任何问题，请尽快告知课程工作人员，或在 Ed 上发帖提问。祝你好运！

---

### **English:** 5 Extra Credit
### **中文:** 5 额外加分

---

**English:**
Extra credit will be rewarded for improvements to the test suite. Add a test case to one of the files in the `tests` directory (e.g. `minnow/tests/recv_connect.cc`) that catches a real bug that somebody might reasonably make that isn't already caught by the existing test suite. Please submit your test as a Pull Request (it's okay to make this public) so we can take a look and decide whether to add it to the overall testsuite. (This opportunity will remain open—e.g. if you find a good additional test for the Reassembler in week 7, that's great too.)

**中文:**
对测试套件的改进将获得额外加分。在 `tests` 目录中的一个文件（例如 `minnow/tests/recv_connect.cc`）中添加一个测试用例，该用例能捕获一个别人很可能会犯的、且现有测试套件尚未能捕获的**真实**错误。请将你的测试作为 Pull Request 提交（可以公开），以便我们查看并决定是否将其添加到整体测试套件中。（这个机会将一直开放——例如，如果你在第 7 周为 `Reassembler` 找到了一个很好的附加测试，那也很棒。）