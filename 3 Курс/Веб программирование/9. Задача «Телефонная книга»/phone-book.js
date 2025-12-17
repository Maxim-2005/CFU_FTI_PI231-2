'use strict';

/**
 * Телефонная книга
 */
let phoneBook = new Map();

function isValidPhone(phone) {
    return typeof phone === 'string' && /^\d{10}$/.test(phone);
}

function formatPhone(phone) {
    return `+7 (${phone.slice(0, 3)}) ${phone.slice(3, 6)}-${phone.slice(6, 8)}-${phone.slice(8)}`;
}

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

exports.findAndRemove = function (query) {
    // Проверка и нормализация запроса
    if (!query || typeof query !== 'string' || query.trim() === '') {
        return 0;
    }
    
    let removedCount = 0;
    const isWildcard = query.trim() === '*';
    const normalizedQuery = query.trim();

    for (const [phone, record] of phoneBook.entries()) {
        if (isWildcard || 
            record.name.includes(normalizedQuery) || 
            phone.includes(normalizedQuery) || 
            (record.email && record.email.includes(normalizedQuery))) {
            
            if (phoneBook.delete(phone)) {
                removedCount++;
            }
        }
    }
    
    return removedCount;
};