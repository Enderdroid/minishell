# minishell
### By [tkleiner](https://github.com/Enderdroid) & [ttamesha](https://github.com/chaotic-binary)
![alt text](https://github.com/Enderdroid/minishell/blob/main/Intro.jpg)

## Кратко
Мы написали свой мини-баш, способный получать команды изкомандной строки, запускать исполняемые файлы, имитировать некоторые встроенные функции и обрабатывать сигналы.

## Сборка
Сборка осуществвляется командой `make`
Запуск исполняемого файла можно осуществить введя `./minishell`

## Встроенные функции:
* [`echo`](https://www.opennet.ru/man.shtml?topic=echo&category=1&russian=0)
* [`pwd`](https://www.opennet.ru/man.shtml?topic=pwd&category=1&russian=0)
* [`cd`](https://www.opennet.ru/man.shtml?topic=cd&russian=5&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man)
* [`env`](https://www.opennet.ru/man.shtml?topic=env&category=1&russian=0)
* [`export`](https://www.opennet.ru/man.shtml?topic=export&category=1&russian=5)
* [`unset`](https://www.opennet.ru/man.shtml?topic=unset&russian=5&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man)
* [`exit`](https://www.opennet.ru/man.shtml?topic=exit&category=2&russian=0)

## Сигналы
* `Ctrl-C` - Прерывает исполнение запущенной в шеле программы.
* `Ctrl-\` - Аналогичен команде exit.
* `Ctrl-D` - Посылает EOF.

## Другое
* `;` - Для исполнения нескольких команд в одной строке.
* `'`, `"` - Экранирование символов / переменных окружения и т.д.
* `<`, `>>`, `>` - Редеректы для перенаправления стандартного ввода - вывода.
* `|` - пайп - позволяте запустить несколько исполняемых файлов одновременно, перенаправляя вывод предыдущей программы на ввод следующей.
* [Переменные окружения](https://en.wikipedia.org/wiki/Environment_variable)
* Обработка и вывод кодов ошибок - при успешном/неудачном завершении операции вы всегда можете посмотреть код завершения использовав `$?`

## Заключение
![alt text](https://github.com/Enderdroid/minishell/blob/main/inception.gif)
