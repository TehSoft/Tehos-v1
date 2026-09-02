# 🚀 TEHOS Operating System

A **TEHOS** egy egyedi, 64-bites, saját fejlesztésű operációs rendszer, amely magában foglalja a **TehFS** fájlrendszert és a **TehLang** programozási nyelvet.

## 📁 Projekt Struktúra
* **`boot/`** - A rendszer indításáért felelős bootloader kódok.
* **`tehlibs/`** - Nyílt forráskódú alacsony szintű hardver- és lemezkezelő könyvtárak.
* **`system/`** - A rendszer magja: a kernel, a TehConsole és a TehLang interpreter.
* **`kernel.cc`** - A rendszer fő belépési pontja.

## 🛠️ Fordítás és Futtatás
A rendszer lefordításához és QEMU emulátorban való futtatásához egyszerűen futtasd a következő parancsot a terminálban:

```bash
make run
```

A fordítási szemetek takarításához:
```bash
make clean
```

## ⚖️ Licenc és Szerzői Jogok (License)
A projekt hibrid forráskódú modell alapján működik:
1. **MIT Licenc:** A `boot/`, `tehlibs/` mappák és a `kernel.cc` szabadon felhasználhatók és módosíthatók.
2. **Kötelező Értesítési Záradék:** A `system/` mappa tartalma (a **TehLang** és a **TehFS**) jogvédett. Másolásuk vagy felhasználásuk esetén **KÖTELEZŐ értesíteni a szerzőt** egy GitHub Issue megnyitásával vagy a profilomon keresztül!

*A részletes jogi feltételeket a projekt gyökerében található **LICENSE** fájl tartalmazza.*
