:: Клеточный автомат
:: Студенты:
:: - Максим Покидько
:: - Усейной Даниэль
:: - Ярослав Епишенко
:: 10 января 2024 г.
chcp 1251 >nul
color 0a
title Server
mode con cols=100 lines=25

@echo off
echo %time:~,-3%

@echo on
start http://localhost:8080/
go run BackEnd/server.go