# pipex_21school

Перенаправление потоков ввода/вывода с использованием pipe() и выполнение процессов параллельно в разных потоках с помощью fork(). 

Работа программы эквивалентна запуску команды shell ```< file1 cmd1 | cmd2 > file2```

## Описание и сборка

```make``` - компиляция библиотеки libft и сборка программы

```make clean``` - удаление объектных файлов

```make fclean``` - удаление всех скомпелированных файлов

Программа запускается следующим образом: ```./pipex file1 cmd1 cmd2 file2```

На вход подается ровно 4 аргумента