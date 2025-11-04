gcc -o maintest "src\main.c" "src\display.c" "graphics\graphics.c" -I"inc" -I"graphics"
maintest.exe | java -jar "drawapp.4.5\drawapp-4.5.jar"