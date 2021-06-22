import pyautogui
import time
from datetime import datetime
from tkinter import *
import schedule

root = Tk()

def abrir_aula():
    
    with open("link.txt",'r') as file:
        link = file.read()
    
    pyautogui.PAUSE = 0.5

    pyautogui.press('winleft')

    pyautogui.write('Google Chrome')
    pyautogui.press('enter')

    time.sleep(1)

    pyautogui.hotkey('ctrl','t')

    pyautogui.write(f'{link}')
    pyautogui.press('enter')

    time.sleep(10)

    pyautogui.hotkey('ctrl','d')

    pyautogui.moveTo(1254,601)
    pyautogui.mouseDown()
    pyautogui.mouseUp()

    time.sleep(1)

    pyautogui.alert('Aula iniciada com sucesso!')


def salvar_aula():
    with open("link.txt",'w') as file:
        file.write(Link_aula.get())

    hora_aula = StringVar()
    hora_aula.set(horario_aula.get())
    hora_aula_str = str(horario_aula.get())

    print(hora_aula_str)

    schedule.every().day.at(hora_aula_str).do(abrir_aula)

root.title('AFK')
root.iconbitmap('Imagem/Icone.ico')
root.geometry('350x300')

img = PhotoImage(file="Imagem/logo1.png")

Escrita_Link_aula = Label(root,
text='Digite o link da aula')

Escrita_horario_aula = Label(root,text='Digite o horario da aula')

Link_aula = Entry(root,width=35)
horario_aula = Entry(root)

espaco_branco1 = Label()
espaco_branco2 = Label()

Botao = Button(root,
text='Entrar na aula',
command = salvar_aula)

espaco_branco1.grid(row=0)
espaco_branco2.grid(row=1)
imagem_logo = Label(root,image= img).grid(columnspan=2)
Escrita_Link_aula.grid(row=5,column=0,sticky=W)
Link_aula.grid(row=5,column=1,sticky=W)
Escrita_horario_aula.grid(row=6,column=0,sticky=W)
horario_aula.grid(row=6,column=1,sticky=W)
Botao.grid(row=7,column=1,sticky= E)

root.mainloop()

while True:
    schedule.run_pending()
    time.sleep(1)




