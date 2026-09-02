# 🚀 TEHOS Operating System

A **TEHOS** egy egyedi, 64-bites, saját fejlesztésű operációs rendszer, amely magában foglalja a **TehFS** fájlrendszert és a **TehLang** programozási nyelvet.

## 📁 Projekt Struktúra
* **`boot/`** - A rendszer indításáért felelős bootloader kódok.
* **`tehlibs/`** - Nyílt forráskódú alacsony szintű hardver- és lemezkezelő könyvtárak.
* **`system/`** - A rendszer magja: a kernel, a TehConsole és a TehLang interpreter.

## 🛠️ Fordítás és Futtatás
A rendszer lefordításához és QEMU emulátorban való futtatásához egyszerűen futtasd a következő parancsot a terminálban:

```bash
make run
```

A fordítási szemetek takarításához:
```bash
make clean
```

*A részletes jogi feltételeket a projekt gyökerében található **LICENSE** fájl tartalmazza.*
