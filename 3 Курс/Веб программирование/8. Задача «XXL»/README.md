# Задача «XXL»

## Основное задание

Создадим небольшой скриптик **roman-time.js** (заготовка уже лежит). 
Внутри скрипта – функция, код которой вам и необходимо дописать:

```js
function romanTime(time) {
    // Немного авторского кода
    return time;
}
```

На вход функция принимает время в виде строки в формате «часы:минуты», например, «09:05».  
А на выходе даёт то же время, но записанное римскими числами – «IX:V»

Важно учитывать:

* Среди римских цифр (сюрприз-сюрприз) нет нуля, поэтому используйте символ `N` вместо него
* На вход может прийти любое неверное время: «03:123», «без десяти:три», даже null и undefined. В этом случае необходимо выбрасывать исключение [TypeError](https://developer.mozilla.org/ru/docs/Web/JavaScript/Reference/Global_Objects/TypeError)

В файле **index.js** вы можете найти примеры использования получившегося скриптика.

## Полезные ссылки:
- [Римские цифры](https://ru.wikipedia.org/wiki/Римские_цифры)
- [NaN для чайников](https://developer.mozilla.org/ru/docs/Web/JavaScript/Reference/Global_Objects/NaN)
- [О parseInt за 10 минут](https://developer.mozilla.org/ru/docs/Web/JavaScript/Reference/Global_Objects/parseInt)
- [isNaN: Beginners guide](https://developer.mozilla.org/ru/docs/Web/JavaScript/Reference/Global_Objects/isNaN)
- [Split, как метод для строк](https://developer.mozilla.org/ru/docs/Web/JavaScript/Reference/Global_Objects/String/split)
- [Как без стеснения бросить исключение](https://developer.mozilla.org/ru/docs/Web/JavaScript/Reference/Global_Objects/TypeError)
