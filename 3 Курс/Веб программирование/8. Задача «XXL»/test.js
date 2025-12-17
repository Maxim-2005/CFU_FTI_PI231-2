'use strict';

var romanTime = require('./roman-time');

// Тестируем правильные случаи
console.log('09:10 ->', romanTime('09:10'));
console.log('00:00 ->', romanTime('00:00'));
console.log('23:59 ->', romanTime('23:59'));
console.log('06:30 ->', romanTime('06:30'));
console.log('14:45 ->', romanTime('14:45'));

// Тестируем ошибочные случаи
try {
    romanTime('24:00');
} catch (e) {
    console.log('24:00 ->', e.message);
}

try {
    romanTime('12:60');
} catch (e) {
    console.log('12:60 ->', e.message);
}

try {
    romanTime('abc');
} catch (e) {
    console.log('abc ->', e.message);
}

try {
    romanTime(null);
} catch (e) {
    console.log('null ->', e.message);
}