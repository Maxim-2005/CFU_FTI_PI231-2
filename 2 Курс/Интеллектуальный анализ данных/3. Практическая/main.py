from selenium import webdriver
from bs4 import BeautifulSoup
from selenium.webdriver.firefox.options import Options
import dateparser
import locale
import csv

# Устанавливаем локализацию для корректного форматирования цен
locale.setlocale(locale.LC_ALL, 'ru_RU.UTF-8')

# Настройки selenium
options = Options()
options.add_argument("--headless")

BASE_URL = "https://www.avito.ru/"
URL = "https://www.avito.ru/simferopol/fototehnika/zerkalnye_fotoapparaty-ASgBAgICAUS~A7AX?cd=1&p="
MIN_PRICE = 5_000
MAX_PRICE = 15_000

driver = webdriver.Firefox(options=options)
page = 1 # Начальная страница

# Открываем файлы для записи в форматах Markdown и CSV
with open("parsed_data.md", 'w', encoding="utf-8", newline='') as md_file, \
     open("parsed_data.csv", 'w', encoding="utf-8", newline='') as csv_file:
    
    # Настройки для записи в CSV
    csv_writer = csv.writer(csv_file, delimiter=';')
    csv_writer.writerow(["ID", "Название", "Цена (руб)", "Дата", "Ссылка"])
    
    # Настройки для записи в Markdown
    md_file.write("| ID | Название | Цена (руб) | Дата | Ссылка |\n")
    md_file.write("|----|----------|------------|------|--------|\n")
    
    print("Файлы открыты")
    
    # Обходим все страницы
    while True:
        driver.get(URL + str(page))
        
        page_source = driver.page_source 
    
        soup = BeautifulSoup(page_source, 'html.parser') 
        items = soup.find_all('div', attrs={'data-marker': 'item'})
        
        # Стоп сигнал
        if len(items) == 0:
            print("Ура, победа!")
            break

        # Ковальский анализ (обходим элементы страницы)
        for item in items:
            id = item.get("id")  # ID
            name = item.find('h3', attrs={"itemprop": "name"}).text.strip()  # Название
            price = item.find('meta', attrs={"itemprop": "price"})["content"]  # Цена

            # Парсим дату
            raw_date = item.find('p', attrs={"data-marker": "item-date"}).text
            date = dateparser.parse(raw_date).strftime("%d-%m-%Y") if raw_date else "Не указана"

            # Форматируем цену с разделением тысяч
            formatted_price = locale.format_string("%d", int(price), grouping=True)

            # Получаем ссылку на объявление
            link = BASE_URL + item.find('a', href=True)['href']

            # Терория великого фильтра (цен)
            if MIN_PRICE <= int(price) <= MAX_PRICE:
                # Консектируем данные в CSV
                csv_writer.writerow([id, name, formatted_price, date, link])

                # Конспектируем данные в Markdown
                md_file.write(f"| {id} | {name} | {formatted_price} | {date} | [Ссылка]({link}) |\n")
        
        page += 1

driver.quit()
print("Запись завершена, проверяйте файлы")