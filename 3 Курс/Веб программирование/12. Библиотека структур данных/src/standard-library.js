'use strict';

/**
 * Коллекция (Collection)
 */
var Collection = function () {
    this._items = [];
};

Object.defineProperties(Collection.prototype, {
    first: {
        get: function () {
            return this._items[0];
        }
    },
    last: {
        get: function () {
            return this._items[this._items.length - 1];
        }
    },
    length: {
        get: function () {
            return this._items.length;
        }
    },
    isEmpty: {
        get: function () {
            return this._items.length === 0;
        }
    }
});

Collection.prototype.pickFirst = function () {
    return this._items.shift();
};

Collection.prototype.pickLast = function () {
    return this._items.pop();
};

Collection.prototype.insertFirst = function (item) {
    this._items.unshift(item);
};

Collection.prototype.insertLast = function (item) {
    this._items.push(item);
};

Collection.prototype.empty = function () {
    this._items = [];
};

/**
 * Очередь (Queue)
 */
var Queue = function () {
    this._items = [];
};

// Можно реализовать через композицию или наследование от Collection
Queue.prototype.enqueue = function (item) {
    this._items.push(item);
};

Queue.prototype.dequeue = function () {
    return this._items.shift();
};

Queue.prototype.empty = function () {
    this._items = [];
};

Object.defineProperty(Queue.prototype, 'length', {
    get: function () {
        return this._items.length;
    }
});

/**
 * Массив фиксированной длины (FixedArray)
 */
var FixedArray = function (size) {
    this.length = size;
    this._items = new Array(size);
};

FixedArray.prototype.insertAt = function (index, item) {
    if (index < 0 || index >= this.length) {
        throw new RangeError('Index out of bounds');
    }
    this._items[index] = item;
};

FixedArray.prototype.getAt = function (index) {
    if (index < 0 || index >= this.length) {
        throw new RangeError('Index out of bounds');
    }
    return this._items[index];
};

/**
 * Множество (Set)
 */
var Set = function () {
    this._items = [];
};

Object.defineProperty(Set.prototype, 'length', {
    get: function () {
        return this._items.length;
    }
});

Set.prototype.insert = function (item) {
    if (!this.has(item)) {
        this._items.push(item);
    }
};

Set.prototype.remove = function (item) {
    var index = this._items.indexOf(item);
    if (index !== -1) {
        this._items.splice(index, 1);
    }
};

Set.prototype.has = function (item) {
    return this._items.indexOf(item) !== -1;
};

Set.prototype.intersect = function (set) {
    var result = new Set();
    this._items.forEach(function (item) {
        if (set.has(item)) {
            result.insert(item);
        }
    });
    return result;
};

Set.prototype.union = function (set) {
    var result = new Set();
    this._items.forEach(function (item) {
        result.insert(item);
    });
    // Предполагается, что у переданного set есть доступ к элементам или метод has
    // В тестах public.js set2 также является экземпляром Set
    set._items.forEach(function (item) {
        result.insert(item);
    });
    return result;
};

Set.prototype.empty = function () {
    this._items = [];
};

exports.Collection = Collection;
exports.Queue = Queue;
exports.FixedArray = FixedArray;
exports.Set = Set;