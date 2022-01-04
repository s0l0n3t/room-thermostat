import socket


from playsound import playsound
from tkinter import *
from tkinter import messagebox

host = "192.168.1.101"
port = 1200

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind((host, port))
print("Socket bağlantısı sağlandı {}")

s.listen(5)
print("socket dinleniyor")

for i in range(5000):

    server, addr = s.accept()      
    print('Gelen bağlantı:', addr)
 
    listening = server.recv(1024).decode()
 
    print(type(listening))
    if (listening != "Gas"):
        if (float(listening) > 26):
            playsound('sound_alert.wav')
            messagebox.showwarning("UYARI", "     LÜTFEN SICAKLIĞI DÜŞÜRÜN    ")
        elif (float(listening) < 20):
            playsound('sound_alert.wav')
            messagebox.showwarning("UYARI", "     LÜTFEN SICAKLIĞI ARTTIRIN    ")
    
    elif (listening == "Gas"):
        playsound('sound_alert.wav')
        messagebox.showwarning("UYARI", "     GAZ KAÇAĞI VAR !    ")
    else:
        print("hatalı bilgi : {0}", listening)
   # Bağlantıyı sonlandıralım 
    server.close()
