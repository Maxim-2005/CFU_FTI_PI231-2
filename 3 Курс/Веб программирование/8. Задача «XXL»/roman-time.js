'use strict';

/**
 * @param {String} time – время в формате HH:MM (например, 09:05)
 * @returns {String} – время римскими цифрами (IX:V)
 */
function romanTime(time) {
    let hours = 0; 
    let minutes = 0;
    const romanNumerals = [
        { value: 50, numeral: 'L' },
        { value: 40, numeral: 'XL' },
        { value: 10, numeral: 'X' },
        { value: 9, numeral: 'IX' },
        { value: 5, numeral: 'V' },
        { value: 4, numeral: 'IV' },
        { value: 1, numeral: 'I' }
    ];
Object.keys()
    function isValidTime(timeString) {
        [hours, minutes] = timeString.split(':').map(Number);
        return hours >= 0 && hours <= 23 && 
        minutes >= 0 && minutes <= 59 &&
               timeString.length === 5;
    }

    // Проверка входных данных
    if (typeof time !== 'string' || !isValidTime(time)) {
        throw new TypeError('Неверное время');
    }


    function toRoman(num) {
        if (num === 0) {
            return 'N';
        }

        let result = '';
        let remaining = num;

        for (const { value, numeral } of romanNumerals) {
            while (remaining >= value) {
                result += numeral;
                remaining -= value;
            }
        }

        return result;
    }

    return `${toRoman(hours)}:${toRoman(minutes)}`;
}

module.exports = romanTime;