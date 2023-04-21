# see /test/bot/temporary_message.py
import socket
import time
import poe
import logging
import sys

def BotServer():
    connection, address = server.accept()
    print(connection, address)
    recv_str = connection.recv(1024)
    recv_str = recv_str.decode("ascii")
    if not recv_str:
        return
    print("receive:    {}".format(recv_str))

    client = poe.Client(token, proxy="http://192.168.31.178:7890")

    reply = ""
    for chunk in client.send_message("capybara", recv_str, with_chat_break=True):
        reply += chunk["text_new"]

    # print(reply)

    connection.send(bytes(reply, encoding="ascii"))
    print("send:   {}".format(reply))

    client.purge_conversation("capybara")
    connection.close()

if __name__ == '__main__':

    # token may be reset
    token = "Y0nlN3ktWV03tsp5YpNaAg%3D%3D"

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("localhost", 8888))
    server.listen(10)

    try:
        while True:
            BotServer()

    except KeyboardInterrupt:
        server.close()
        print("client end, exit!")
        sys.exit()
    
    
