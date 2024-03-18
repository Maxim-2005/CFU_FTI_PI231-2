// Скрипты...
var description=document.getElementById("description");
var download=document.getElementById("download");
var about=document.getElementById("about");
var up=document.getElementById("up");
// Загрузка файла

// Плавная прокрутка
document.getElementById('scrollButton2').addEventListener('click', function() {
    var section2 = document.getElementById('section2');
    var topPos = section2.offsetTop; // Получаем верхнюю позицию раздела 2
    window.scrollTo({
    top: topPos,
    behavior: 'smooth' // Делаем прокрутку плавной
    });
});

document.getElementById('scrollButton3').addEventListener('click', function() {
    var section3 = document.getElementById('section3');
    var topPos = section3.offsetTop; // Получаем верхнюю позицию раздела 3
    window.scrollTo({
    top: topPos,
    behavior: 'smooth' // Делаем прокрутку плавной
    });
});

document.getElementById('scrollButton1').addEventListener('click', function() {
    var section1 = document.getElementById('section1');
    var topPos = section1.offsetTop; // Получаем верхнюю позицию раздела 1
    window.scrollTo({
    top: topPos,
    behavior: 'smooth' // Делаем прокрутку плавной
    });
});

// Прыжок на вверх
up.onclick=()=> {
    document.body.scrollTop=0;
    document.documentElement.scrollTop=0;
}

window.onscroll=()=> {
    if(document.body.scrollTop>512 || document.documentElement.scrollTop>512)
        up.style.display="block";
    else
        up.style.display="none";
}

// Можно добавить слайдер

// Можно добавить темную/светлую тему

