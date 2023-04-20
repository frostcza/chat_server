# 基于muduo网络库的集群服务器项目 #

基于muduo网络库的集群服务器，可以实现跨服务器的聊天功能  

1. muduo网络库的ThreadPool Reactor  
2. mysql  
3. nginx配置tcp负载均衡
4. redis实现服务器间通信

## Enviornment ##

ubuntu 18.04

[boost 1.77.0](https://www.boost.org/) && [guide](https://blog.csdn.net/QIANGWEIYUAN/article/details/88792874) 

[muduo](https://github.com/chenshuo/muduo) && [guide](https://blog.csdn.net/QIANGWEIYUAN/article/details/89023980) 

mysql 
```bash
sudo apt install mysql-server
sudo apt-get install mysql-server
sudo apt-get install libmysqlclient-dev
```

[nginx 1.12.2](http://nginx.org/en/download.html) 
```bash
sudo apt-get install libpcre3 libpcre3-dev

./configure --with-stream
sudo make
sudo make install

sudo gedit /usr/local/nginx/conf/nginx.conf
```
add these
```text
# nginx tcp load balance config
stream {
    upstream MyServer {
        server 127.0.0.1:6000 weight=1 max_fails=3 fail_timeout=30s;
        server 127.0.0.1:6002 weight=1 max_fails=3 fail_timeout=30s;
    }
    server {
        proxy_connect_timeout 1s;
        # proxy_timeout 3s;
        listen 8000;
        proxy_pass MyServer;
        tcp_nodelay on;
    }
}
```

```bash
sudo ./nginx
```

[redis 4.0.9](https://redis.io/download/#redis-downloads) && [guide](https://blog.csdn.net/m0_61491995/article/details/125906242)
```bash
sudo apt-get install redis-server
```
[hiredis](https://github.com/redis/hiredis)
```bash
make
sudo make install
sudo ldconfig /usr/local/lib
```

## run ##
```bash
cd chat_server
mkdir build
cd build
cmake ..
make
cd ../bin
./server 127.0.0.1 6000

# new terminal
./server 127.0.0.1 6002

# new terminal
./client 127.0.0.8000
```