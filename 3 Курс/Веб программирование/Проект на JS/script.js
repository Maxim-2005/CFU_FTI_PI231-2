/**
 * Project Settings
 * Массив LAYERS_CONFIG теперь генерируется автоматически.
 * Поместите ваши изображения в папку 'images' с именами image_01.png, image_02.png и так далее.
 */

const TOTAL_IMAGES = 5; // Укажите здесь общее количество ваших картинок
const LAYERS_CONFIG = [];

for (let i = 1; i <= TOTAL_IMAGES; i++) {
    // Форматируем число, чтобы получить 01, 02 и т.д.
    const imageNumber = i.toString().padStart(2, '0');
    LAYERS_CONFIG.push({
        id: i,
        url: `images/image_${imageNumber}.jpg`, // Путь к вашей папке и файлу
        label: `Layer ${imageNumber}`
    });
}

const container = document.getElementById('zoom-container');
let currentProgress = 0; // Total zoom progress (от 0 до количества слоев)
const zoomIntensity = 0.002; // Wheel sensitivity

// Layers initialization
function init() {
    // Очищаем контейнер перед добавлением (на случай перезагрузки)
    container.innerHTML = '';
    
    LAYERS_CONFIG.forEach((config, index) => {
        const div = document.createElement('div');
        div.className = 'layer';
        div.id = `layer-${index}`;
        div.style.backgroundImage = `url('${config.url}')`;
        // Устанавливаем z-index, чтобы первые слои были сверху
        div.style.zIndex = LAYERS_CONFIG.length - index;
        container.appendChild(div);
    });
    
    update();
}

/**
 * Main transformation logic
 * Использует экспоненциальное масштабирование
 */
function update() {
    LAYERS_CONFIG.forEach((_, index) => {
        const layer = document.getElementById(`layer-${index}`);
        if (!layer) return;

        // Локальный прогресс для конкретного слоя
        const localProgress = currentProgress - index;
        
        // Формула масштаба: 10 в степени прогресса
        const scale = Math.pow(10, localProgress);
        
        // Управление прозрачностью (Opacity)
        let opacity = 1;
        
        if (localProgress > 0) {
            // Слой исчезает, когда мы "проходим сквозь него"
            opacity = 1 - (localProgress * 0.8); 
        }
        
        if (localProgress < -1) {
            // Слой еще слишком далеко
            opacity = 0;
        } else if (localProgress < 0) {
            // Слой появляется из глубины
            opacity = 1 + localProgress; 
        }

        layer.style.transform = `scale(${scale})`;
        layer.style.opacity = Math.max(0, Math.min(1, opacity));
        
        // Оптимизация производительности: скрываем невидимые слои
        layer.style.visibility = opacity <= 0 ? 'hidden' : 'visible';
    });
}

// Mouse Wheel event handling
window.addEventListener('wheel', (e) => {
    e.preventDefault();
    
    const delta = e.deltaY;
    currentProgress += delta * zoomIntensity;
    
    // Ограничение границ зума
    currentProgress = Math.max(0, Math.min(currentProgress, LAYERS_CONFIG.length - 0.5));
    
    requestAnimationFrame(update);
}, { passive: false });

// Touch events support для мобильных устройств
let lastTouchY = 0;
window.addEventListener('touchstart', (e) => {
    lastTouchY = e.touches[0].clientY;
});

window.addEventListener('touchmove', (e) => {
    e.preventDefault();
    const touchY = e.touches[0].clientY;
    const delta = lastTouchY - touchY;
    
    currentProgress += delta * zoomIntensity * 2;
    currentProgress = Math.max(0, Math.min(currentProgress, LAYERS_CONFIG.length - 0.5));
    
    lastTouchY = touchY;
    requestAnimationFrame(update);
}, { passive: false });

window.onload = init;