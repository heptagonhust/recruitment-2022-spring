# HUST Heptagon Recruitment - Spring 2022

[TOC]

https://github.com/heptagonhust/recruitment-2022-spring

本次招新题目Task 1 & 2源于Stanford CS149 Assignment-1，题目部分原文可参考https://github.com/stanford-cs149/asst1

为了在做题过程中有流畅的体验，应当预先了解以下知识：

1. [C/C++语言](https://learnxinyminutes.com/docs/c++/) 
2. [make和Makefile](https://seisman.github.io/how-to-write-makefile/index.html#) 
3. 多线程编程

## Task 1 multi-thread

分形通常被定义为“一个粗糙或零碎的几何形状，可以分成数个部分，且每一部分都（至少近似地）是整体缩小后的形状”，即具有自相似的性质。Mandelbrot 集是一个复数集，它是一种在复平面上组成分形的点的集合。你可以在 Wikipedia 获得[更多关于 Mandelbrot 集的信息](http://en.wikipedia.org/wiki/Mandelbrot_set)。

在本任务中，我们希望你使用 [std::thread](https://en.cppreference.com/w/cpp/thread/thread)，利用多线程来优化一个生成分形图的程序。

构建并运行 `prog1_mandelbrot_threads/` 文件夹下的代码（使用 `make` 构建，`./mandelbrot` 运行），这个程序将会生成一个图像文件 `mandelbrot-serial.ppm` ，它是 Mandelbrot 集的可视化，可以使用 `display` 命令显示生成的图片。

![img](https://camo.githubusercontent.com/4417cbd19f53e7ac9532d3d0d257780082f784cb39767be9142afb474ab62223/687474703a2f2f67726170686963732e7374616e666f72642e6564752f636f75727365732f6373333438762d31382d77696e7465722f617373745f696d616765732f61737374312f6d616e64656c62726f745f76697a2e6a7067)

如上图所示，生成的图像是分形图。图像中的每一个像素对应了复平面中的一个值，每个像素的亮度与确定该值是否被包含在 Mandelbrot 集中所需的计算成本成正比。 可以通过 `./mandelbrot --view 2`选项得到图像 2 。

`mandelbrotThread.cpp` 中的 `mandelbrotThread()` 函数提供了创建新线程的启动代码。在这个函数中，主线程使用构造函数 `std::thread(function, args...)` 创建了新的线程，它通过调用线程对象的 `join` 方法来等待线程完成。现在被启动的线程不会进行任何的计算，会立刻返回。你需要在 `workerThreadStart()` 函数中添加代码来完成图像的计算。在这个任务中，你不需要调用其他的 std::thread 的 API。

**你的任务：**

使用 8 个线程来优化分形图的生成，相应地，你需要分配图像的生成工作（即给每个线程分配应该计算的图像的块），从而得到至少 6x 的加速比。

通过在 `workerThreadStart()` 函数的开头与结尾插入计时代码的方式来测量每个线程完成它的工作所需要的时间可能会对你有所帮助。

**测试：**

使用 `make` 构建你的代码后，分别运行 `./mandelbrot --view 1` 和 `./mandelbrot --view 2`。

如果你的优化使得程序的结果出错，程序会提示 `Error : Output from threads does not match serial output`，否则程序会输出你的加速比。

## Task 2 SIMD

SIMD(Single Instruction Multiple Data)是CPU提供的指令集，通过使用向量寄存器，一条SIMD指令直接对一组向量进行运算，可以在相同的执行周期内完成更多的数据处理。

此任务中，你将尝试使用SIMD指令修改程序使之向量化。

注意，使用真正的向量化指令需要一定的技巧，而为了简化，你将使用“伪SIMD指令”。这些“伪SIMD指令”是一些已提供的函数，虽然其实现依然是SISD，但是在这里可以忽略其具体实现，将其当做SIMD黑盒，你可以假设它们都只是单条指令。而你的工作就是使用这些函数，将代码“向量化”。你可能需要浏览一遍 `CS149intrin.h` 以找到你所需要的函数。

**你的任务：**

1. 在 `clampedExpVector` 中实现一个向量化版本的 `clampedExpSerial` 函数。你的实现需要在任何的输入数组大小 `N` 和向量宽度 `VECTOR_WIDTH` 下都能工作。
2. 在 `arraySumVector` 中实现一个向量化版本的 `arraySumSerial` 函数。你的实现可以假设 `VECTOR_WIDTH` 是输入数组大小 `N` 的一个因子。你可能会发现 `hadd` 和 `interleave` 操作很有用。

**测试：**

使用 `make` 构建你的程序，运行 `./myexp` 可以测试你的程序，`-l` 选项可以打印 log，具体可参照 `logger.h`。 

如果你的函数通过了相应的测试，该部分将会提示你 `Passed!!!` ，否则将会提示你 `Failed!!!`，并输出你的函数的输出和正确的输出。

你的程序应当通过以下几组数据的测试：

| N      | VECTOR_WIDTH |
| ------ | ------------ |
| 32     | 4            |
| 65     | 8            |
| 512    | 16           |
| 1024   | 17           |
| 114514 | 1919         |

你可以通过 `./myexp -s N` 指定你的函数需要处理的输入数组的大小 N（默认为 50），而向量宽度 VECTOR_WIDTH 是定义在 `CS149intrin.h` 中的一个常量，需要你手动修改。

## Task 3 GEMM

前两个task介绍了一些HPC相关技巧，你应该已经明白了同一份代码在不修改算法的情况下是如何进行优化的。接下来，你需要学习并运用更多技巧来做一次简单的优化。

若你已经完成task 1 2并打算继续完成task 3，可以在招新群里私戳管理员 ，我们将为你提供一台高性能的机器的访问权限，你可以在该机器上完成task 3.

**题目**

矩阵乘法是线性代数中的基本算子，并在人工智能、图形学和科学计算中得到广泛应用。由于复杂度高且计算密集度大，矩阵乘法是一个非常合适的优化对象。

很多计算加速库都有矩阵乘法的优化实现，比如MKL，BLAS等，它们都能做到上百倍的加速比。虽然这些库的代码都非常复杂以至于难以阅读甚至难以使用，但实现一个功能单一的快速矩阵乘法却并不需要很大工作量。

在此任务中，你需要学习、理解访存相关知识，并采用各种方法，使得一次矩阵乘法运算尽可能快。

代码仓库在https://github.com/heptagonhust/recruitment-2022-spring/tree/main/task3-gemm

可以参考的优化方法：

1. [Cache BLocking](https://www.intel.com/content/www/us/en/developer/articles/technical/cache-blocking-techniques.html) 
2. [SIMD](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#) 
3. [OPENMP]( https://www.openmp.org/resources/refguides/)

**测试**

为了方便，测试集矩阵均为N*N整形矩阵，元素范围`(-1000, 1000)`，其中N分别为`256, 512, 1024, 2048`

**baseline代码已提供，包含数据输入输出、结果校验与性能测试，你只需专注于优化。**

在开始优化之前，你应当执行`./fetch_data.sh`来获取数据`data/`，然后测量并记录baseline的时间。

可以使用`make`进行编译，`make run`运行程序。注意，**Makefile中的编译优化等级不可修改**。

data目录如下

```Assembly%20language
data 
├── 1024 
│   ├── a 
│   ├── b 
│   └── result 
├── 2048 
│   ├── a 
│   ├── b 
│   └── result 
├── 256 
│   ├── a 
│   ├── b 
│   └── result 
├── 512 
│   ├── a 
│   ├── b 
│   └── result 
└── makedata.cpp
```

其中，子目录名为数据测试集的矩阵规模，a,b为输入矩阵，result为结果矩阵。**请不要破坏目录结构**。

## 提交说明

你应当fork此repo，并在招新截止日期(2022.5.12 23:59)前将自己的repo link以issue的方式发表在本repo下。

你需要提交代码和文档，文档中应该包含

1. 你的设备的信息，如 CPU 型号和核数，内存容量和频率等等。
2. 每个task的思路和效果（举例：使用了xxx优化，相对于原代码，速度提升了114.514倍）
3. 你在解题过程中所参考的资料
4. 在解题过程中，遇到的有意思的事情，或者是让你印象深刻的bug

对题目和提交方式有任何疑问，可在招新群里提问。

## 怎么入手

1. RTFM，包含此文档和链接给出的题目原文，想明白需要做什么
2. RTFSC，在开始写代码之前，应当清楚每一份文件中的代码的作用，包括Makefile
3. STFW，使用英文查询没有想明白的问题
4. 如果打算系统性地了解和学习HPC，可参考[七边形学习路线]( https://heptagonhust.github.io/HPC-roadmap/)
