'use strict';

const formulas = window.formulas;

const availableListEl = document.getElementById('available-list');
const cauldronListEl = document.getElementById('cauldron-list');
const filterInput = document.getElementById('filter-input');
const clearFilterBtn = document.getElementById('clear-filter');
const resultDisplay = document.getElementById('result-display');
const themeToggleBtn = document.getElementById('theme-toggle');
const themeIcon = document.getElementById('theme-icon');

let allElements = [];
let cauldronState = [];
let filterText = '';

function init() {
    // Сбор данных из HTML
    availableListEl.querySelectorAll('li').forEach(item => {
        allElements.push({
            id: item.getAttribute('data-element'),
            name: item.textContent
        });
    });

    // Обработчики событий
    availableListEl.addEventListener('click', (e) => {
        const li = e.target.closest('li');
        if (li) addToCauldron(li.getAttribute('data-element'));
    });

    cauldronListEl.addEventListener('click', (e) => {
        const li = e.target.closest('li');
        if (li) removeFromCauldron(li.getAttribute('data-element'));
    });

    filterInput.addEventListener('input', (e) => {
        filterText = e.target.value.toLowerCase().trim();
        updateClearBtn();
        render();
    });

    clearFilterBtn.addEventListener('click', () => {
        filterText = '';
        filterInput.value = '';
        updateClearBtn();
        render();
    });

    themeToggleBtn.addEventListener('click', toggleTheme);

    initTheme();
    render();
}

function initTheme() {
    const savedTheme = localStorage.getItem('theme');
    const prefersDark = window.matchMedia('(prefers-color-scheme: dark)').matches;
    
    if (savedTheme === 'dark' || (!savedTheme && prefersDark)) {
        document.body.classList.add('dark-mode');
        themeIcon.textContent = '☀️';
    } else {
        themeIcon.textContent = '🌙';
    }
}

function toggleTheme() {
    const isDark = document.body.classList.toggle('dark-mode');
    themeIcon.textContent = isDark ? '☀️' : '🌙';
    localStorage.setItem('theme', isDark ? 'dark' : 'light');
}

function addToCauldron(id) {
    if (!cauldronState.includes(id)) {
        cauldronState.push(id);
        render();
    }
}

function removeFromCauldron(id) {
    cauldronState = cauldronState.filter(item => item !== id);
    render();
}

function updateClearBtn() {
    clearFilterBtn.style.display = filterText.length > 0 ? 'block' : 'none';
}

function checkFormulas() {
    const matches = formulas.filter(f => f.elements.every(el => cauldronState.includes(el)));
    
    if (matches.length === 0) {
        resultDisplay.textContent = cauldronState.length === 0 ? 'Результат появится здесь...' : 'Ничего не происходит...';
        resultDisplay.style.color = 'var(--text-secondary)';
        return;
    }

    matches.sort((a, b) => b.elements.length - a.elements.length);
    resultDisplay.textContent = matches[0].result + ' ✨';
    resultDisplay.style.color = 'var(--primary-color)';
}

function render() {
    availableListEl.innerHTML = '';
    cauldronListEl.innerHTML = '';

    allElements.forEach(el => {
        if (cauldronState.includes(el.id)) {
            const li = document.createElement('li');
            li.setAttribute('data-element', el.id);
            li.textContent = el.name;
            cauldronListEl.appendChild(li);
        } else if (!filterText || el.name.toLowerCase().includes(filterText)) {
            const li = document.createElement('li');
            li.setAttribute('data-element', el.id);
            li.innerHTML = filterText ? highlightMatch(el.name, filterText) : el.name;
            availableListEl.appendChild(li);
        }
    });
    checkFormulas();
}

function highlightMatch(text, filter) {
    const regex = new RegExp(`(${filter.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')})`, 'gi');
    return text.replace(regex, '<span class="highlight">$1</span>');
}

init();