## 题目
```swift
100GB url 文件，使用 1GB 内存计算出出现次数 top100 的 url 和出现的次数。
```
## 开发需求
* PingCAP 2019校招小作业-赵易
* 开始时间：2018 年 10 月 8 日，上午 11:00
* 截止时间：2018 年 10 月 15 日，上午 11:00
* 作业要求：在 GitHub 上实现，截止时间前提交项目链接

## 提示
* 注意代码可读性，添加必要的注释
* 注意代码风格与规范，添加必要的单元测试和文档
*  注意异常处理，尝试优化性能
## 开发环境
* 语言：c++ (c++0x)
* 运行环境：linux
## 设计思路
* 总体思路：将大文件分割成小文件，以便让有限内存足以处理数据，对小文件分别处理统计后再将结果合并，取得想要的部分。即hash映射+map统计+堆排序。
* 1.将源文件中的URL哈希到子文件中，这样相同的URL一定在同一子文件中；
* 2.对每个子文件中的URL进行出现频率统计，并统计出前100个URL及其频次；
* 3.建立一个大小为100的小根堆，初始的堆节点由第一个文件的元素组成（若第一个文件不足100个元素，则从后续文件中取元素）；
* 4.将后续文件中URL的频次和小根堆的堆顶进行比较，如果大于堆顶则替换并调整堆，反之开始比较下一个文件中的记录。该步保证当前堆中保留的记录一定是当前已经比较过的文件中出现频次最多的前100个；
* 5.对最终100个元素进行排序，即得结果。
## 产生文件说明
* 步骤1（hash映射）产生文件名为：resolved_X.txt（X=0,1,2,3……表示映射文件序号）。
* 如果步骤1产生的文件仍大于file_size，将resolved_X.txt进行切分，切分出的文件名为：resolved_X_Y.txt（Y=0,1,2,3……表示切分出小文件的序号），再对其进行统计，结果名为：sorted_ resolved_X_Y.txt。
* 若步骤1产生的子文件不超过file_size，或将将上述切分出的小文件合并后，即步骤2最终的结果文件名为：soted_ resolved_X.txt。
* 结果直接打印出来，不再写到文件中。
## 参数调整
* 1.source_file_name，该参数表示源文件名。
* 2.topK，要统计出前K个出现最多的次数。
* 3.File_num，需要将源文件hash到File_num个子文件中。
* 4.File_size，每个子文件的最大大小，以便每个子文件都可以放到内存中进行处理。
* 可以根据系统调整参数3和4，已达到更好的效果。
## 项目构成
* topk.cpp中为主函数，调用了hash_file.h，handle_file.h，find_topk.h，urlelement.h。编译时需要编译* topk.cpp,hash_file.cpp,handle_file.cpp,find_topk.cpp。
* hash_file的作用是将大文件哈希到子文件中。
* handle_file的作用是将子文件进行处理，包括分割成更小的文件以及对URL的出现频率进行统计和排序。
* find_topk的作用是找到最终前100个元素的集合。
* urlelement中定义了一个结构体，用来保存URL记录和其出现频次。
## 未来的工作
* 目前只实现了一个最基础的功能，性能表现不是很好，主要有以下几个方面的问题：
* 1.将大文件hash映射到小文件中的速度很慢，可能是由于对大文件的频繁读操作，曾尝试使用mmap，但是因为要对字符逐个比较来切分url，所以导致速度更慢。后续可以尝试其他方案对文件进行读取，但是可能需要考虑如果使用指定大小切分成小文件的话，处理截断部分数据的问题。
* 2.将大文件hash映射到小文件时频繁的写盘也会导致速度变慢，后续可以考虑建立一个类似缓冲区的空间，缓冲区填充慢了再一次性写多条数据。
* 3.现在使用的hash函数（获得URL的哈希值的函数）对URL的映射效果不好，后续可以尝试使用其他hash函数对URL进行哈希。
* 4.在步骤2中对每个子文件进行排序的时候，由于是串行操作也会消耗更多的时间，后续可以考虑开多线程并行对几个子文件同时做排序工作。
* 此外，在开发过程中只做了一些简单的功能测试，所以后续还需增加更完善的测试。
