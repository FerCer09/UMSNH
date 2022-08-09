# https://parzibyte.me/blog/2019/07/06/conversion-texto-voz-tts-python-gtts/
# https://pypi.org/project/SpeechRecognition/1.2.4/

# chatterbot
# pip install chatterbot_corpus


from chatterbot import ChatBot
from chatterbot.trainers import ChatterBotCorpusTrainer
from chatterbot.trainers import ListTrainer

from gtts import gTTS
from playsound import playsound
NOMBRE_ARCHIVO = "sonido_generado.mp3"


import time


chatbot = ChatBot('InitBot',storage_adapter='chatterbot.storage.SQLStorageAdapter',read_only=True,  logic_adapters=[
        'chatterbot.logic.BestMatch'])
chatbot.storage.drop()

saludos = open("saludos.txt","r").readlines()
conversar = ListTrainer(chatbot)
conversar.train(saludos)

despedida = open("despedidas.txt","r").readlines()
conversar.train(despedida)

archivo = open("conversacion#1.txt","r").readlines()
conversar.train(archivo)

archivo = open("conversacion#2.txt","r").readlines()
conversar.train(archivo)

archivo = open("conversacion#3.txt","r").readlines()
conversar.train(archivo)

import speech_recognition as sr
r = sr.Recognizer() 
with sr.Microphone() as source:
	while True:
		r.adjust_for_ambient_noise(source)
		print("Estoy escuchando...")
		solicitud = ""
		audio = r.record(source, duration = 7,offset=2)
		try:
			solicitud = r.recognize_google(audio,language="es-ES")
			respuesta = chatbot.get_response(solicitud) #obteniendo respuesta del bot
		except:
			respuesta= "Lo siento no te oí"

		print("Yo: " + solicitud)
		print("Termine de escuchar\n")
		
		tts = gTTS(str(respuesta), lang='es')	#creo una instancia gTTS
		with open(NOMBRE_ARCHIVO, "wb") as archivo:		#creo un archivo de audio
		    tts.write_to_fp(archivo)				#escribo en el archivo de audio la respuesta del bot
		playsound(NOMBRE_ARCHIVO)					#Reproduzco el audio
		
#		if(solicitud == 'salir','adios','hasta luego'):
		if(str(respuesta)+'\n' in despedida):
			break
		
		time.sleep(2)
