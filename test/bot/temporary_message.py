# 使用poe-api链接AI bot
# https://github.com/ading2210/poe-api
# pip install poe-api

# poe是Quora的一款应用，以网页形式接入ChatGPT、Cluade等聊天机器人
# https://poe.com/
# poe-api是一个逆向工程，伪装请求头，用python接入poe的聊天机器人

# 使用时注意设置token和proxy

import poe
import logging
import sys

#send a message and immediately delete it

# token是用浏览器接入poe.com时获得的token
# 获取方式为：科学上网 -> https://poe.com/ -> F12打开dev tools -> 
# applications -> cookies -> https://poe.com/ -> p-b对应的value
# 隔一段时间会更新

token = "Y0nlN3ktWV03tsp5YpNaAg%3D%3D"

# 关闭log INFO
# poe.logger.setLevel(logging.INFO)

# poe需要科学上网才能访问，所以需要设置代理proxy
# 这台ubuntu18.04时虚拟机，windows上运行了clash代理工具
# 打开windows上的clash，进入general选项
# 记下Port(7890)，打开Allow LAN，关闭System Proxy
# cmd中ipconfig获取WLAN的ip (192.168.31.178)

client = poe.Client(token, proxy="http://192.168.31.178:7890")

# print(client.bot_names) # 查看可用的bots
# {'name' : 'model'}
# {'capybara': 'Sage', 'beaver': 'GPT-4', 'a2_2': 'Claude+', 'a2': 'Claude', 'chinchilla': 'ChatGPT', 'nutria': 'Dragonfly'}

message = "Who are you?"
reply = ""
for chunk in client.send_message("capybara", message, with_chat_break=True):
  print(chunk["text_new"], end="", flush=True)
  reply += chunk["text_new"]

print('\n')
print(reply)

#delete the 3 latest messages, including the chat break
client.purge_conversation("capybara", count=3)
