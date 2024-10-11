""" Notenrechner V2.0
Berechnung von zwei Schulaufgaben (SA1, SA2) und einer Kurzarbeit (KA)"""
#_______________________________________________________________________
#Eingabe FACH & SCHULNOTEN:
#_______________________________________________________________________

Schulfach = [ "IT","ET","EL-A","EL-D","MT","M1","D","E","PuG","CW"]
for i in range(10):
    print            ("eingabe für das Fach :",Schulfach[i])
    SA1       = input("Gebe deine 1. SA-Note im Fach ein: ")
    print            ("Feedback SA1:" + SA1 + "!")
    SA2       = input("Gebe deine 2. SA-Note im Fach ein: ")     
    print            ("Feedback SA2:" + SA2 + "!")
    KA        = input("Gebe deine 1. KA-Note im Fach ein: ")     
    print            ("Feedback KA1:" + KA + "!")
#_______________________________________________________________________

# Programm/Logik:

# SpeicherZuweisung:
    SA1 = int(SA1)
    SA2 = int(SA2)
    KA  = int (KA)
    GesamtAnzahl_SA = "GesamtAnzahl_SA"
    GesamtAnzahl_KA = "GesamtAnzahl_KA"
    Gesamtnote      = "Gesamtnote"
    Zeugnisnote     = "Zeugnisnote"
    SA1_RAM         = 0
    SA2_RAM         = 0
    KA_RAM          = 0

#Berechnung der GesamtAnzahl_SA:
    if  SA1>0: 
        SA1_RAM=1

    if  SA2>0:
        SA2_RAM=1

    if  KA >0:
        KA_RAM =1

    GesamtAnzahl_SA = SA1_RAM + SA2_RAM
    GesamtAnzahl_KA = KA_RAM

# Berechnung der Gesamtnote im jeweiligen Fach:
    Gesamtnote = ((SA1+SA2)*2+KA)/(GesamtAnzahl_SA*2+GesamtAnzahl_KA)

# Berechnung der Zeugnisnote im jeweiligen Fach:
    Zeugnisnote = f"Zeugnisnote {round(Gesamtnote)}"

# Ausgabe der Berechnung:
    print(f"Schulfach:",Schulfach [i])
    print(f"--------------------------------------------")
    print(f"SA:",SA1,",",SA2,"| KA:",KA)
    print(f"Gesamtnote" ,Gesamtnote ,Zeugnisnote)
 

