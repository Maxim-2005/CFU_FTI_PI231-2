'use strict';

/**
 * Телефонная книга
 */
let phoneBook = new Map();

/**
 * Проверка формата телефона
 * @param {String} phone
 * @returns {Boolean}
 */
function isValidPhone(phone) {
    return typeof phone === 'string' && /^\d{10}$/.test(phone);
}

/**
 * Форматирование телефона
 * @param {String} phone
 * @returns {String}
 */
function formatPhone(phone) {
    return `+7 (${phone.slice(0, 3)}) ${phone.slice(3, 6)}-${phone.slice(6, 8)}-${phone.slice(8)}`;
}

/**
 * Добавление записи в телефонную книгу
 * @param {String} phone
 * @param {String} name
 * @param {String} email
 * @returns {Boolean}
 */
exports.add = function (phone, name, email) {
    // Проверка обязательных параметров
    if (!isValidPhone(phone) || !name || typeof name !== 'string' || name.trim() === '') {
        return false;
    }
    
    // Проверка существующей записи
    if (phoneBook.has(phone)) {
        return false;
    }
    
    // Добавление записи
    phoneBook.set(phone, {
        name: name.trim(),
        email: email && typeof email === 'string' ? email.trim() : ''
    });
    
    return true;
};

/**
 * Обновление записи в телефонной книге
 * @param {String} phone
 * @param {String} name
 * @param {String} email
 * @returns {Boolean}
 */
exports.update = function (phone, name, email) {
    // Проверка обязательных параметров
    if (!isValidPhone(phone) || !name || typeof name !== 'string' || name.trim() === '') {
        return false;
    }
    
    // Проверка существующей записи
    if (!phoneBook.has(phone)) {
        return false;
    }
    
    // Обновление записи
    const record = phoneBook.get(phone);
    record.name = name.trim();
    record.email = email !== undefined && typeof email === 'string' ? email.trim() : '';
    
    return true;
};

/**
 * Поиск записей по запросу в телефонной книге
 * @param {String} query
 * @returns {Array}
 */
exports.find = function (query) {
    // Обработка пустого запроса
    if (!query || typeof query !== 'string' || query.trim() === '') {
        return [];
    }
    
    const results = [];
    
    // Поиск по всем записям
    for (const [phone, record] of phoneBook.entries()) {
        let match = false;
        
        // Поиск по всем полям
        if (query === '*' || 
            record.name.includes(query) || 
            phone.includes(query) || 
            (record.email && record.email.includes(query))) {
            match = true;
        }
        
        if (match) {
            const formattedPhone = formatPhone(phone);
            const entry = record.email ? 
                `${record.name}, ${formattedPhone}, ${record.email}` :
                `${record.name}, ${formattedPhone}`;
            results.push(entry);
        }
    }
    
    // Сортировка по имени
    return results.sort((a, b) => {
        const nameA = a.split(',')[0].toLowerCase();
        const nameB = b.split(',')[0].toLowerCase();
        return nameA.localeCompare(nameB);
    });
};

/**
 * Удаление записей по запросу из телефонной книги
 * @param {String} query
 * @returns {Number}
 */
exports.findAndRemove = function (query) {
    if (!query || typeof query !== 'string' || query.trim() === '') {
        return 0;
    }
    
    const phonesToRemove = [];
    
    // Поиск записей для удаления
    for (const [phone, record] of phoneBook.entries()) {
        if (query === '*' || 
            record.name.includes(query) || 
            phone.includes(query) || 
            (record.email && record.email.includes(query))) {
            phonesToRemove.push(phone);
        }
    }
    
    // Удаление найденных записей
    let removedCount = 0;
    for (const phone of phonesToRemove) {
        if (phoneBook.delete(phone)) {
            removedCount++;
        }
    }
    
    return removedCount;
};