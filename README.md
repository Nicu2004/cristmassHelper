# Christmas Helper - Lab 12

Acesta este un proiect dezvoltat pentru Laboratorul 12, menit să gestioneze listele de copii și elfi pentru spiridușii lui Moș Crăciun. Proiectul este structurat modular, folosind multiple headere pentru o lizibilitate sporită.

## 🚀 Funcționalități
* Gestionarea utilizatorilor (Elfi) folosind moștenire și polimorfism.
* Criptarea parolelor utilizând un algoritm de tip `xorCipher`.
* Încărcarea și salvarea datelor din fișiere text (`users.txt`).
* Organizarea copiilor în liste gestionate de elfi.

## 🛠️ Instalare și Configurare

Pentru a rula acest proiect pe calculatorul tău, urmează pașii de mai jos:

### 1. Clonarea repository-ului
Deschide un terminal și rulează următoarea comandă:
```bash
git clone [https://github.com/Nicu2004/cristmassHelper.git](https://github.com/Nicu2004/cristmassHelper.git)
cd cristmassHelper

2. Compilarea proiectului

Poți folosi orice compilator de C++ (precum g++). Rulează următoarea comandă în folderul rădăcină:
Bash

g++ main.cpp -o ChristmasHelper

(Notă: Asigură-te că toate fișierele .h și .cpp necesare sunt în același folder conform structurii proiectului.)
3. Rularea aplicației

După compilare, pornește programul folosind:
Bash

./ChristmasHelper

📂 Structura Fișierelor

    User.h / User.cpp - Clasa de bază pentru utilizatori.

    Elf.h - Definirea clasei Elf și a listelor de cadouri.

    Kid.h - Gestionarea entităților de tip Copil.

    xorCipher.h - Logica de criptare a parolelor.

    users.txt - Baza de date locală pentru utilizatori.

👨‍💻 Autor

Nicu2004

Sărbători frumoase tuturor!