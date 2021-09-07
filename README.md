# KV存储引擎
- 基于跳表实现的轻量级键值型存储引擎，使用C++实现。插入数据、删除数据、查询数据、数据展示、数据落盘、文件加载数据等
- 在随机写读情况下，该项目每秒可处理写请求数（QPS）约20w，每秒可处理读请求数（QPS）约18w
- 通过序列化将key、value进行存盘，支持大部分数据类型，同时可以用自定义的结构作为key，需要重载结构体里面的<<,<,==,!=
# 接口
- InsertNode 插入节点
- DeleteNode 删除节点
- SearchNode 查询节点
- DisplayList 数据可视化
- DumpFile    数据存盘
- LoadFile    数据加载
- Size        获取数据量
# 过程
- [picture](https://github.com/hustlyhang/SkipList/blob/master/src/skiplist.md)
# 测试
- 测试相关函数都在[test.h](https://github.com/hustlyhang/SkipList/blob/master/Test.h)里面, 可以根据实际情况调整参数测试  
  ![test](https://github.com/hustlyhang/SkipList/blob/master/src/test.png)
# TODO
- Node类中传入自己定义的比较函数，支持更多的数据类型
- 有时间准备尝试加入raft一致性协议，对外提供分布式服务
