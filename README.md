# calc_cpp

Графический калькулятор, написанный на C++ с использованием библиотеки [Raylib](https://www.raylib.com/).  
Работает под Windows. Реализован интерфейс с кнопками, поддержка операций и удобный вывод результата.

<img width="395" height="627" alt="изображение" src="https://github.com/user-attachments/assets/afcb9922-8bdc-46ce-a5ec-01a134acd19d" />


---

## Функционал

- Поддержка операций: `+`, `-`, `*`, `/`, `^2`, `√`, `!`
- Графический интерфейс
- Обработка мыши
- Простая сборка через `g++`

---

##  Как собрать и запустить

### Установка MSYS2 + Raylib

1. Установи [MSYS2](https://www.msys2.org/)
2. Открой терминал **MSYS2 MinGW 64-bit**
3. Установи компилятор и Raylib:
   ```bash
   pacman -Syu
   pacman -Su
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-raylib
