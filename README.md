# StringSplitTest

本次在i5-8600K, Ubuntu 18.04系统上的一个308万行、一亿字符的文件测试了C++的各种split方法，源代码参考了[C++ Split方法](http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html). 

| FLAG                | Stringstream | Find_first_of | Boost split | Boost Tokenizer | Regex | C NonCopy | Python 3.7 |
| ------------------- | ------------ | ------------- | ----------- | --------------- | ----- | --------- | ---------- |
| -                   | **2.25s**    | 2.33s(0.84s)  | 10.26s      | 6.07s           | 80.7s | 0.43s     |            |
| -O2                 | **1.26s**    | 1.53s         | 1.75s       | 1.83s           | 6.74s | 0.25s     |            |
| -O3                 | **1.24s**    | 1.41s(0.65s)  | 1.53s       | 1.80s           | 6.68s | 0.24s     | 0.96s      |
| configure delimeter | char         | string        | is_any_of   | -               | regex | -         |            |

Find_first_of一栏中的括号表示不将split的子串装入容器的测试结果，C NonCopy表示用纯C语言实现，同时只存储子串在原始字符串中的index, 而不拷贝构造子串的结果。

考虑到split任务中的delimeter常常包含多种字符，如`\n`和`\t`，**Boost split**在灵活性和性能上的平衡最优。

Python在字符串处理的接口规整性和性能相比C++都有相当大的优势，可见在C++标准库中字符串的拷贝构造带来了显著的性能开销。



